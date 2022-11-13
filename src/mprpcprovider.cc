#include <iostream>

#include "mprpcheader.pb.h"
#include "mprpcprovider.h"
#include "mprpcapplication.h"
#include "mprpclogger.h"
#include "zookeeperutil.h"

/*
service_name =>  service描述
                        => service* 记录服务对象
                        method_name  =>  method方法对象
json   protobuf
*/
// 这里是框架提供给外部使用的，可以发布rpc方法的函数接口
void RpcProvider::NotifyService(google::protobuf::Service *service)
{
    ServiceInfo service_info;
    // 获取了服务对象的描述信息  因为返回类型是指针。获取服务对象的描述信息。存储名字之类的。
    const google::protobuf::ServiceDescriptor *pserviceDesc = service->GetDescriptor();

    // 获取服务的名字
    std::string service_name = pserviceDesc->name();
    // 获取服务对象service的方法的数量
    int methodCnt = pserviceDesc->method_count();

    // std::cout << "service_name: " << service_name << " methodCnt: " << methodCnt << std::endl;
    LOG_INFO("service_name: ", service_name.c_str());

    for (int i = 0; i < methodCnt; ++i)
    {
        // 获取了服务对象指定下标的服务方法的描述（抽象的描述） UserService  Login
        const google::protobuf::MethodDescriptor *pmethodDesc = pserviceDesc->method(i);
        std::string method_name = pmethodDesc->name();
        service_info.methodMap_[method_name] = pmethodDesc;

        // std::cout << "method_name: " << method_name << " pmethodDesc: " << pmethodDesc << std::endl;
        LOG_INFO("method_name: %s", method_name.c_str());
    }

    service_info.service_ = service;          // 记录服务对象
    serviceMap_[service_name] = service_info; // 存储一下服务及其具体的描述
}

// 启动rpc服务节点，开始提供rpc远程网络调用服务
void RpcProvider::Run()
{
    // 读取配置文件rpcserver的信息
    std::string ip = MprpcApplication::GetInstance().GetConfig().Load("rpcserverip");                // ip
    uint16_t port = atoi(MprpcApplication::GetInstance().GetConfig().Load("rpcserverport").c_str()); // port
    InetAddress address(port, ip);

    // 创建TcpServer对象
    TcpServer server(&eventLoop_, address, "RpcProvider");

    // 绑定连接回调和消息读写回调方法 ，muduo库的好处是：分离了网络代码和业务代码
    server.setConnectionCallback(std::bind(&RpcProvider::OnConnection, this, std::placeholders::_1));
    server.setMessageCallback(std::bind(&RpcProvider::OnMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

    // 设置muduo库的线程数量
    server.setThreadNum(4);

    // 把当前rpc节点上要发布的服务全部注册到zk上面，让rpc client可以从zk上发现服务
    // session timeout   30s  zkclient 网络I/O线程  1/3 * timeout 时间发送ping消息
    ZkClient zkClient;
    zkClient.Start(); // 连接zkserver

    // service_name为永久性节点   method_name为临时性节点
    for (auto &sp : serviceMap_)
    {
        // /service_name   /UserServiceRpc
        std::string service_path = "/" + sp.first;
        zkClient.Create(service_path.c_str(), nullptr, 0);
        for (auto &mp : sp.second.methodMap_)
        {
            // /service_name/method_name   /UserServiceRpc/Login 存储当前这个rpc服务节点主机的ip和port
            std::string method_path = service_path + "/" + mp.first;
            char method_path_data[128] = {0};
            ::sprintf(method_path_data, "%s:%d", ip.c_str(), port);

            // ZOO_EPHEMERAL表示znode是一个临时性节点，和zkserver断了，就是表示不提供这个RPC服务了，所以ZK自动删掉就好啦。
            zkClient.Create(method_path.c_str(), method_path_data, strlen(method_path_data), ZOO_EPHEMERAL);

            // 临时性节点：rpc节点超时未发送心跳消息，zk会自动删除临时性节点。
            // 永久性节点：rpc节点超时未发送心跳消息，zk不会删除这个节点。
        }
    }

    // rpc服务端准备启动，打印信息
    std::cout << "RpcProvider start service at ip:" << ip << " port:" << port << std::endl;
    std::cout << std::endl;

    // 启动网络服务
    server.start();
    eventLoop_.loop(); // 相当于启动了epoll_wait，阻塞，等待远程连接
}

// 新的socket连接回调, rpc的请求是短连接的，请求一次完了，服务端返回rpc的方法的响应，就主动关闭连接了。
void RpcProvider::OnConnection(const TcpConnectionPtr &conn)
{
    if (!conn->connected())
    {
        conn->shutdown(); // 和rpc client的连接断开了
    }
}

/*
在框架内部，RpcProvider和RpcConsumer协商好之间通信用的protobuf数据类型

包含：service_name  method_name   args
对应：16UserServiceLoginzhang san123456

我们在框架中定义proto的message类型，进行数据头的序列化和反序列化
service_name method_name args_size(防止粘包的问题)

怎么去区分哪个是service_name, method_name, args

我们把消息头表示出来
header_size(4个字节) + header_str + args_str
前面几个字节是服务名和方法名。

为了防止粘包，我们还要记录参数的字符串的长度

我们统一：一开始读4个字节，数据头的长度，也就是除了方法参数之外的所有数据的长度：服务名字和方法名字

10 "10"
10000 "1000000"
std::string   insert和copy方法

把header_size按照内存的方式二进制的形式直接存4个字节。
所以，我们从字符流解析是按：数据头(4字节大小，表示service_name method_name args_size的长度）+service_name method_name args_size(防止粘包的问题)+args(参数）
*/
// 已建立连接用户的读写事件回调
void RpcProvider::OnMessage(const TcpConnectionPtr &conn, Buffer *buffer, Timestamp time)
{
    // 网络上接收的远程rpc调用请求的字符流    Login args
    std::string recv_buf = buffer->retrieveAllAsString();

    // 从字符流中读取前4个字节的内容
    uint32_t header_size = 0;
    recv_buf.copy((char *)&header_size, 4, 0); // 从0号位置读取4个字节的数据

    // 根据header_size读取数据头的原始字符流，反序列化数据，得到rpc请求的详细信息
    // 4字节大小，表示service_name method_name args_size的长度
    std::string rpc_header_str = recv_buf.substr(4, header_size);
    mprpc::RpcHeader rpcHeader;
    std::string service_name;
    std::string method_name;
    uint32_t args_size;
    if (rpcHeader.ParseFromString(rpc_header_str))
    {
        // 数据头反序列化成功
        service_name = rpcHeader.service_name();
        method_name = rpcHeader.method_name();
        args_size = rpcHeader.args_size();
    }
    else
    {
        // 数据头反序列化失败
        std::cout << "rpc_header_str: " << rpc_header_str << " parse error!" << std::endl;
        return;
    }

    // 获取rpc方法参数的字符流数据
    std::string args_str = recv_buf.substr(4 + header_size, args_size);

    // 打印调试信息
    std::cout << "============================================" << std::endl;
    std::cout << "header_size: " << header_size << std::endl;
    std::cout << "rpc_header_str: " << rpc_header_str << std::endl;
    std::cout << "service_name: " << service_name << std::endl;
    std::cout << "method_name: " << method_name << std::endl;
    std::cout << "args_str: " << args_str << std::endl;
    std::cout << "============================================" << std::endl;
    std::cout << std::endl;

    // 获取service对象和method对象
    auto it = serviceMap_.find(service_name);
    if (it == serviceMap_.end())
    {
        std::cout << service_name << " is not exist!" << std::endl;
        return;
    }

    auto mit = it->second.methodMap_.find(method_name);
    if (mit == it->second.methodMap_.end())
    {
        std::cout << service_name << ": " << method_name << " is not exist!" << std::endl;
        return;
    }

    // 获取service对象  new UserService
    google::protobuf::Service *service = it->second.service_;
    // 获取method对象  Login
    const google::protobuf::MethodDescriptor *method = mit->second;

    // 生成rpc方法调用的请求request和响应response参数
    google::protobuf::Message *request = service->GetRequestPrototype(method).New();
    if (!request->ParseFromString(args_str))
    {
        std::cout << "request parse error, content: " << args_str << std::endl;
        return;
    }
    google::protobuf::Message *response = service->GetResponsePrototype(method).New();

    // 给下面的method方法的调用，绑定一个Closure的回调函数
    google::protobuf::Closure *done = google::protobuf::NewCallback<RpcProvider,
                                                                    const TcpConnectionPtr &,
                                                                    google::protobuf::Message *>(this, &RpcProvider::SendRpcResponse, conn, response);
    // 在框架上根据远端rpc请求，调用当前rpc节点上发布的方法
    // 相当于 new UserService().Login(controller, request, response, done)
    service->CallMethod(method, nullptr, request, response, done);
}

// Closure的回调操作，用于序列化rpc的响应和网络发送
void RpcProvider::SendRpcResponse(const TcpConnectionPtr &conn, google::protobuf::Message *response)
{
    std::string response_str;
    if (response->SerializeToString(&response_str)) // response进行序列化
    {
        // 序列化成功后，通过网络把rpc方法执行的结果发送会rpc的调用方
        conn->send(response_str);
    }
    else
    {
        std::cout << "serialize response_str error!" << std::endl;
    }
    conn->shutdown(); // 模拟http的短链接服务，由rpcprovider主动断开连接
}