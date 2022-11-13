#include "zookeeperutil.h"
#include "mprpcapplication.h"

// 全局的watcher观察器   zkserver给zkclient的通知
void global_watcher(zhandle_t *zh, int type, int state, const char *path, void *watcherCtx)
{
    if (type == ZOO_SESSION_EVENT) // 回调的消息类型是和会话相关的消息类型
    {
        if (state == ZOO_CONNECTED_STATE) // zkclient和zkserver连接成功
        {
            sem_t *sem = (sem_t *)zoo_get_context(zh); // 指定的句柄获取信号量
            ::sem_post(sem);                           // 给信号量的值加上一个“1”
        }
    }
}

ZkClient::ZkClient() : zhandle_(nullptr)
{
}
ZkClient::~ZkClient()
{
    if (zhandle_ != nullptr)
    {
        zookeeper_close(zhandle_); // 关闭句柄，释放资源
    }
}

// zkclient启动连接zkserver
void ZkClient::Start()
{
    std::string host = MprpcApplication::GetInstance().GetConfig().Load("zookeeperip");
    std::string port = MprpcApplication::GetInstance().GetConfig().Load("zookeeperport");
    std::string connstr = host + ":" + port;

    /*
    zookeeper_mt：多线程版本
    zookeeper的API客户端程序提供了三个线程：
    1. API调用线程 也就是当前线程 也就是调用的线程 zookeeper_init
    2. 网络I/O线程  zookeeper_init调用了pthread_create  poll专门连接网络
    3. watcher回调线程 当客户端接收到zkserver的响应，再次调用pthread_create，产生watcher回调线程
    */

    // global_watcher回调函数
    // 返回的就是句柄，会话的创建是异步的，并不是返回成功了就是表示连接成功的，等回调函数真正接收到zkserver响应进行回调
    zhandle_ = zookeeper_init(connstr.c_str(), global_watcher, 30000, nullptr, nullptr, 0);

    if (nullptr == zhandle_)
    {
        std::cout << "zookeeper_init error!" << std::endl;
        ::exit(EXIT_FAILURE);
    }

    sem_t sem;
    ::sem_init(&sem, 0, 0);
    zoo_set_context(zhandle_, &sem); // 创建句柄资源成功后，向句柄资源上设置上下文，添加额外的信息

    ::sem_wait(&sem); //等待，因为初始的信号量是0，阻塞着，等着zkserver响应（回调）。等加1。成功了才向下走

    std::cout << "zookeeper_init success!" << std::endl; // global_watcher执行成功，连接成功了
}
// 在zkserver上根据指定的path创建znode节点
void ZkClient::Create(const char *path, const char *data, int datalen, int state)
{
    char path_buffer[128];
    int bufferlen = sizeof(path_buffer);
    int flag;

    // 先判断path表示的znode节点是否存在，如果存在，就不再重复创建了
    flag = zoo_exists(zhandle_, path, 0, nullptr);
    if (ZNONODE == flag) // 表示path的znode节点不存在
    {
        // 创建指定path的znode节点了
        flag = zoo_create(zhandle_, path, data, datalen, &ZOO_OPEN_ACL_UNSAFE, state, path_buffer, bufferlen);
        if (flag == ZOK)
        {
            std::cout << "znode create success... path: " << path << std::endl;
        }
        else //创建失败
        {
            std::cout << "flag:" << flag << std::endl;
            std::cout << "znode create error... path: " << path << std::endl;
            ::exit(EXIT_FAILURE);
        }
    }
}
// 根据参数指定的znode节点路径，或者znode节点的值
std::string ZkClient::GetData(const char *path)
{
    char buffer[64];
    int bufferlen = sizeof(buffer);
    int flag = zoo_get(zhandle_, path, 0, buffer, &bufferlen, nullptr);
    if (flag != ZOK)
    {
        std::cout << "get znode error... path:" << path << std::endl;
        return std::string();
    }
    else
    {
        return buffer;
    }
}