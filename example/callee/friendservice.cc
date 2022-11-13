#include <iostream>
#include <string>
#include <vector>

#include "friends.pb.h"
#include "mprpcapplication.h"
#include "mprpcprovider.h"
#include "mprpclogger.h"

class FriendService : public friends::FriendServiceRpc
{
public:
    std::vector<std::string> GetFriendsList(uint32_t userid) //返回好友的列表，本地方法
    {
        std::cout << "do GetFriendList service! userid: " << userid << std::endl;
        std::vector<std::string> vec;
        vec.push_back("张三");
        vec.push_back("李四");
        vec.push_back("王五");
        vec.push_back("赵六");
        return vec;
    }
    // 重写基类方法,框架帮我们调用的
    void GetFriendsList(::google::protobuf::RpcController *controller,
                        const ::friends::GetFriendsListRequest *request,
                        ::friends::GetFriendsListResponse *response,
                        ::google::protobuf::Closure *done) override
    {
        uint32_t userid = request->userid();                           // 获取用户的id号
        std::vector<std::string> friendsList = GetFriendsList(userid); // 调用本地方法
        response->mutable_result()->set_errcode(0);                    // 执行成功
        response->mutable_result()->set_errmsg("");
        for (auto &name : friendsList)
        {
            std::string *p = response->add_friends(); //添加
            *p = name;
        }
        done->Run();
    }
};

int main(int argc, char *argv[])
{

    LOG_ERROR("test LOG_ERR");
    LOG_INFO("friendservice start");

    //调用框架的初始化操作
    MprpcApplication::Init(argc, argv);

    // provider是一个rpc网络服务对象。把UserService对象发布到rpc节点上
    RpcProvider provider;
    provider.NotifyService(new FriendService());

    //启动一个rpc服务发布节点 Run以后，进程进入阻塞状态，等待远程的rpc调用请求
    provider.Run();
    return 0;
}
