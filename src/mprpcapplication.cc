#include <iostream>
#include <string>
#include <unistd.h>

#include "mprpcapplication.h"

MprpcConfig MprpcApplication::config_;

MprpcApplication &MprpcApplication::GetInstance()
{
    static MprpcApplication app;
    return app;
}

MprpcConfig &MprpcApplication::GetConfig()
{
    return config_;
}

void ShowArgsHelp()
{
    std::cout << "format: command -i <configfile>" << std::endl;
}

void MprpcApplication::Init(int argc, char *argv[])
{
    if (argc < 2)
    {
        ShowArgsHelp();
        ::exit(EXIT_FAILURE); // 非正常执行导致退出程序
    }

    int c = 0;
    std::string config_file;

    /**
     * #include <unistd.h>
     * getopt()用来分析命令行参数。参数argc和argv分别代表参数个数和内容，跟main（）函数的命令行参数是一样的。
     * 参数说明
     *     argc：就是main函数的形参argc，表示参数的数量
     *     argv：就是main函数的形参argv，表示参数的字符串变量数组
     *     optstring：选项字符串，一个字母表示不带值的参数，如果字母后带有一个:，表示必须带值的参数。如果带有两个:，表示是可选的参数。
     */
    while ((c = ::getopt(argc, argv, "i:")) != -1)
    {
        switch (c)
        {
        case 'i':                 // 有正确的配置文件
            config_file = optarg; // 用于获取传入的参数的值
            break;
        case '?': // 出现了不希望出现的参数，我们指定必须出现i
            ShowArgsHelp();
            ::exit(EXIT_FAILURE);
            break;
        case ':': // 出现了-i,但是没有参数
            ShowArgsHelp();
            ::exit(EXIT_FAILURE);
            break;
        default:
            break;
        }
    }

    // 开始加载配置文件了 rpcserver_ip=  rpcserver_port=   zookeeper_ip=  zookeeper_port=
    config_.LoadonfigFile(config_file.c_str());

    // 调试信息
    std::cout << "====================================================" << std::endl;
    std::cout << "rpcserverip: " << config_.Load("rpcserverip") << std::endl;
    std::cout << "rpcserverport: " << config_.Load("rpcserverport") << std::endl;
    std::cout << "zookeeperip: " << config_.Load("zookeeperip") << std::endl;
    std::cout << "zookeeperport: " << config_.Load("zookeeperport") << std::endl;
    std::cout << "====================================================" << std::endl;
    std::cout << std::endl;

}
