#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

const int portnum=80;
const char* hostaddr="router.lornix.com";
const unsigned int hostip=0xc0a80d01;
const int bufsize=128;

const char* username="count_chocula";
const char* password="booberry";
const char* authbase64="ABCDEFGHIJKLMNOPQRS=";

const char* request="GET /start.htm HTTP/1.1\r\n" \
                    "HOST: router.lornix.com\r\n" \
                    "Authorization: Basic ABCDEFGHIJKLMNOPQRS=\r\n" \
                    "\r\n";

int main()
{
    int result; /* various uses */

    setvbuf(stdout,NULL,_IONBF,0);

    int sock=socket(AF_INET,SOCK_STREAM,0);
    if (sock<0) {
        perror("socket");
        exit(1);
    }
    // connect
    struct sockaddr_in clientstr;
    bzero(&clientstr,sizeof(clientstr));
    clientstr.sin_family =AF_INET;
    clientstr.sin_port=htons(portnum);
    clientstr.sin_addr.s_addr=htonl(hostip);

    result=connect(sock,(const struct sockaddr*)&clientstr,sizeof(clientstr));
    if (result!=0) {
        perror("connect");
        exit(1);
    }
    result=write(sock,request,strlen(request));
    printf("%s",request);
    do {
        char buffer[bufsize+1];
        result=read(sock,buffer,bufsize);
        if (result>0) {
            buffer[result]=0;
            printf("%s",buffer);
        }
    } while (result>0);

    close(sock);

    return 0;
}
