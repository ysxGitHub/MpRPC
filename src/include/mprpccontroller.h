#pragma once

#include <string>

#include "google/protobuf/service.h"

// RpcController 它可以存储一些控制信息，让我们清楚地知道当前RPC调用的状态。
class MprpcController : public google::protobuf::RpcController
{
public:
    MprpcController();
    void Reset() override;
    bool Failed() const override;
    std::string ErrorText() const override;
    void SetFailed(const std::string &reason) override;

    // 目前未实现具体的功能
    void StartCancel() override;
    bool IsCanceled() const override;
    void NotifyOnCancel(google::protobuf::Closure *callback) override;

private:
    bool failed_;         // RPC方法执行过程中的状态
    std::string errText_; // RPC方法执行过程中的错误信息
};