#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char** argv)
{
    int sd;
    int port;
    int start;
    int end;
    int rval;
    char responce[1024];
    struct hostent *hostaddr;
    struct sockaddr_in servaddr;

    start = atoi(argv[2]);
    end = atoi(argv[3]);
    
    for (port=start; port<=end; port++)
    {
        sd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        
        if (sd == -1)
        {
            printf("socket() error\n");
            return (errno);
        }   

        memset( &servaddr, 0, sizeof(servaddr));

        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(port);

        hostaddr = gethostbyname( argv[1] );

        memcpy(&servaddr.sin_addr, hostaddr->h_addr, hostaddr->h_length);

        rval = connect(sd, (struct sockaddr *) &servaddr, sizeof(servaddr));
        if (rval != -1)
        {
            printf("Port %d is open\n",port);
        }
        
        close(sd);
    }
}
