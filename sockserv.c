#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

const int portnum=9642;
const int bufsize=128;

int main()
{
    int result; /* various uses */

    int sock=socket(AF_INET,SOCK_STREAM|SOCK_NONBLOCK,0);
    /* int sock=socket(AF_INET,SOCK_STREAM,0); */
    if (sock<0) {
        perror("socket");
        exit(1);
    }
    // bind
    struct sockaddr_in servstr;
    bzero(&servstr,sizeof(servstr));
    servstr.sin_family =AF_INET;
    servstr.sin_port=htons(portnum);
    servstr.sin_addr.s_addr=INADDR_ANY;

    result=bind(sock,(const struct sockaddr*)&servstr,sizeof(servstr));
    if (result!=0) {
        perror("bind");
        exit(1);
    }
    // listen
    result=listen(sock,SOMAXCONN);
    if (result!=0) {
        perror("listen");
        exit(1);
    }
    // accept
    struct sockaddr_in clientstr;
    socklen_t clientlen=sizeof(clientstr);
    while (1) {
        bzero(&clientstr,clientlen);
        int client=accept(sock,(struct sockaddr*)&clientstr,&clientlen);
        if (client<0) {
            if ((errno==EAGAIN)||(errno=EWOULDBLOCK)) continue;
            fprintf(stderr,"error: %d\n",client);
            perror("accept");
            exit(1);
        }
        unsigned int addr=ntohl(clientstr.sin_addr.s_addr);
        int port=ntohs(clientstr.sin_port);
        printf("==== %3d: %d.%d.%d.%d : %d\n",client,
                (addr>>24),
                (addr>>16)&0xff,
                (addr>>8)&0xff,
                (addr&0xff),
                port);
        do {
            char buffer[bufsize+1];
            result=read(client,buffer,bufsize);
            if (result>0) {
                buffer[result]=0;
                printf("Rcvd: %d bytes\n",result);
            }
        } while (result>0);
        printf("Closed %d\n",client);
        close(client);
    }

    close(sock);

    return 0;
}
/* accept bind connect fcntl getpeername getsockname getsockopt ioctl listen read recv select
 * send shutdown socketpair write getprotoent
 */

