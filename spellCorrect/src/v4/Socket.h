#pragma once


class Socket
{
public:
    Socket();
    Socket(int );
    void shutdown();
    int fd();
    ~Socket() ;
private:
    int _fd;
};

