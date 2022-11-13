#pragma once
#include <functional>

#include "noncopyable.h"
#include "Socket.h"
#include "Channel.h"

class EventLoop;
class InetAddress;

class Acceptor : noncopyable
{
public:
    using NewConnectionCallback = std::function<void(int sockfd, const InetAddress &)>;

    Acceptor(EventLoop *loop, const InetAddress &listenAddr, bool reusePort);
    ~Acceptor();

    void setNewConnectionCallback(const NewConnectionCallback &cb)
    {
        newConnectionCallback_ = cb;
    }

    bool listenning() const { return listenning_; }

    void listen();

private:
    void handleRead();

private:
    NewConnectionCallback newConnectionCallback_;

    EventLoop *loop_; // Acceptor用的就是用户定义的那个baseLoop，也称作mainLoop
    Socket acceptSocket_;
    Channel acceptChannel_;

    bool listenning_;

    int idleFd_;
};
