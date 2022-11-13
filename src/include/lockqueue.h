#pragma once

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

// 异步写日志的日志队列
// 队列如果是空，写日志的线程就一直等待，队列不空的时候，写日志的线程才有必要去抢锁，把日志信息写到日志文件。
template <typename T>
class LockQueue
{
public:
    // 多个worker线程都会写日志queue
    void Push(const T &data)
    {
        std::lock_guard<std::mutex> locker(mutex_);
        queue_.push(data);
        cond_.notify_one(); // 通知写日志的线程
    }

    // 一个线程读日志queue，写日志文件
    T Pop()
    {
        std::unique_lock<std::mutex> locker(mutex_);
        while (queue_.empty())
        {
            // 日志队列为空，线程进入wait状态
            cond_.wait(locker);
        }
        T data = queue_.front();
        queue_.pop();
        return data;
    }

private:
    std::queue<T> queue_;
    std::mutex mutex_;
    std::condition_variable cond_;
};
