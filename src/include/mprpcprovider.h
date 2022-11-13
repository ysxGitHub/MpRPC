#pragma once
#include <string>
#include <functional>

#include "google/protobuf/service.h"
#include "google/protobuf/descriptor.h"
#include "InetAddress.h"
#include "EventLoop.h"
#include "TcpServer.h"
#include "TcpConnection.h"

// 框架提供的专门发布rpc服务的网络对象类
class RpcProvider
{
public:
    // 这里是框架提供给外部使用的，可以发布rpc方法的函数接口
    void NotifyService(google::protobuf::Service *service);

    // 框架是可以接收各种RPC服务的，不能依赖具体的某一个业务。
    // 基类指针指向子对象

    // 启动rpc服务节点，开始提供rpc远程网络调用服务
    void Run();

private:
    // 组合EventLoop
    EventLoop eventLoop_;

    // service服务类型信息
    struct ServiceInfo
    {
        google::protobuf::Service *service_; // 保存服务对象
        std::unordered_map<std::string, const google::protobuf::MethodDescriptor *> methodMap_; // 保存服务方法
    };

    // 存储注册成功的服务对象和其服务方法的所有信息
    std::unordered_map<std::string, struct ServiceInfo> serviceMap_;

    // 新的socket连接回调
    void OnConnection(const TcpConnectionPtr &);
    // 已建立连接用户的读写事件回调
    void OnMessage(const TcpConnectionPtr &, Buffer *, Timestamp);
    // Closure的回调操作，用于序列化rpc的响应和网络发送
    void SendRpcResponse(const TcpConnectionPtr &, google::protobuf::Message *);
};
