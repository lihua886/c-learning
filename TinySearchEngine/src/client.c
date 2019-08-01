#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

int readn(int _fd,char * buff,int len){
    int left=len;
    char *p=buff;
    while(left>0){
        int ret=read(_fd,p,left);
        if(ret==-1&&errno==EINTR){
            continue;            
        }else if(ret==-1){
            perror("read");
            return len-left;
        }else if(ret==0){
            return len-left;
        }else{
            left-=ret;
            p+=ret;
        }
    }
    return len-left;
}

int recvPeek(int _fd,char * buff,int len){
     int ret;
     do{
         ret=recv(_fd,buff,len,MSG_PEEK);
     }while(ret==-1&&errno==EINTR);
     return ret;
}
int readline(int fd,char * buff,int maxlen){
     int left=maxlen-1; 
     char *p=buff;
     int total=0;
     while(left>0){
         int ret=recvPeek(fd,p,left);
         for(int i=0;i<ret;++i){
             if(p[i]=='\n'){
                 int sz=i+1;
                 readn(fd,p,sz);
                 total +=sz;
                 p+=(sz-1);
                 *p='\0';
                 return total;
             }
         }
         readn(fd,p,ret);
         total +=ret;
         p+=ret;
         left -=ret;
     }
     *p='\0';
     return total;
}
void do_service(int sockfd);





int main(int argc, const char *argv[])
{
    int peerfd = socket(PF_INET, SOCK_STREAM, 0);
    if(peerfd == -1)
        ERR_EXIT("socket");

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof addr);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("192.168.4.174"); //localhost
    //addr.sin_addr.s_addr = INADDR_ANY; //localhost
    addr.sin_port = htons(6666);
    socklen_t len = sizeof addr;
    if(connect(peerfd, (struct sockaddr*)&addr, len) == -1)
        ERR_EXIT("Connect");

//	char buf[1024];
//	memset(buf, 0, sizeof(buf));
//	read(peerfd, buf, sizeof(buf));
//	printf("%s\n", buf);

    do_service(peerfd);
    return 0;
}

void do_service(int sockfd)
{
    char recvbuf[1024 * 1024 * 1] = {0};
    char sendbuf[1024] = {0};
    while(1)
    {
        fgets(sendbuf, sizeof sendbuf, stdin);
        write(sockfd, sendbuf, strlen(sendbuf));

        //read
		char length[100] = {0};
        int nread = readline(sockfd, length, sizeof(length));
		printf("nread = %d\n", nread);
        if(nread == -1)
        {
            if(errno == EINTR)
                continue;
            ERR_EXIT("read");
        }
        else if(nread == 0)
        {
            printf("server close!\n");
            close(sockfd);
            exit(EXIT_SUCCESS);
        }
        printf("receive msg length: %s\n", length);
		//获取数据
        nread = recv(sockfd, recvbuf, atoi(length),MSG_WAITALL);
        printf("recvbuf,size= %ld,receive msg : %s\n",strlen(recvbuf), recvbuf);

        memset(recvbuf, 0, sizeof recvbuf);
        memset(sendbuf, 0, sizeof sendbuf);
    }
}




