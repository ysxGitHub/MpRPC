#include "test.pb.h"

#include <iostream>
#include <string>

int main(void)
{
    fixbug::LoginRequest req;
    req.set_name("li si");
    req.set_pwd("123456");

    // 对象数据序列化
    std::string send_str;
    if (req.SerializeToString(&send_str))
    {
        std::cout << send_str.c_str() << std::endl;
    }

    // 从send_str里反序列化一个login对象
    fixbug::LoginRequest req2;
    if (req2.ParseFromString(send_str))
    {
        std::cout << req2.name() << std::endl;
        std::cout << req2.pwd() << std::endl;
    }

    /**
     * @brief 使用经验
     * 一般而言，在protobuf的配置文件里会把字符串类型设置为bytes类型
     * 在编写过程中如果有重复代码，可以把重复的拿出来写成一个message。
     * 在上面的示例中，所编写的是普通的数据类型，protobuf除了数据对象，还有列表和映射表。
     */

    fixbug::GetUserListResponse rsp;

    // 如果一个数据对象的某个成员还是对象的话，需要用指针接收一个mutable的地址
    fixbug::LoginRequest *req1 = rsp.mutable_request();
    req1->set_name("root");
    req1->set_pwd("123456");

    // 列表字段
    fixbug::User *user1 = rsp.add_user_list();
    user1->set_name("zhang san");
    user1->set_age(18);
    user1->set_sex(fixbug::User::MAN);

    fixbug::User *user2 = rsp.add_user_list();
    user2->set_name("li si");
    user2->set_age(20);
    user2->set_sex(fixbug::User::MAN);

    std::cout << rsp.user_list_size() << std::endl;

    if (rsp.SerializeToString(&send_str))
    {
        std::cout << "[test]: " << send_str.c_str() << " :[end]" << std::endl;
    }

    fixbug::User user11 = rsp.user_list(0);
    fixbug::User user21 = rsp.user_list(1);

    std::cout << user11.name() << "   "
              << user11.age() << "   "
              << user11.sex() << std::endl;

    std::cout << user21.name() << "   "
              << user21.age() << "   "
              << user21.sex() << std::endl;

    return 0;
}

// sudo g++ main.cc test.pb.cc -o app -lprotobuf -std=c++11 -pthread

