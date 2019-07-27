#pragma once



namespace wd{
class SocketIO
{
public:
   explicit
   SocketIO(int fd);

   int readn(char * buff,int len);
   int writen(const void* buff,int len);
   int readline(char * buff,int maxlen);
private:
   int recvPeek(char *buff,int len);
private:
    int  _fd;
};


}
