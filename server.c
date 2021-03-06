#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int sock;
    struct sockaddr_in addr;
    char buf[1024];
    int bytes_read;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(2);
    }

    int ssock;
    struct sockaddr_in saddr;

    ssock = socket(AF_INET, SOCK_DGRAM, 0);
    if(ssock < 0)
    {
        perror("socket");
        exit(1);
    }


    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(3426);
    saddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    while(1)
    {
        bytes_read = recvfrom(sock, buf, 1024, 0, NULL, NULL);
        buf[bytes_read] = '\0';
        for (int i = 0; i < bytes_read - 1; ++i){
            buf[i] += 1;
        }

        sendto(ssock, buf, sizeof(buf), 0,
               (struct sockaddr *)&saddr, sizeof(saddr));
    }

    close(sock);
    close(ssock);

    return 0;
}