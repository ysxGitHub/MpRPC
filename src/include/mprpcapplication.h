#pragma once

#include "mprpcconfig.h"
#include "mprpcchannel.h"
#include "mprpccontroller.h"

// mprpc框架的基础类，负责框架的一些初始化操作
class MprpcApplication
{
public:
    static void Init(int argc, char *argv[]); // 初始化
    static MprpcApplication &GetInstance();   // 单例模式
    static MprpcConfig &GetConfig();

private:
    MprpcApplication()
    {
    }
    MprpcApplication(const MprpcApplication &) = delete; // 删除拷贝相关的
    MprpcApplication &operator=(const MprpcApplication &) = delete;

private:
    static MprpcConfig config_;
};
