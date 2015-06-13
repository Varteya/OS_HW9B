#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main()
{
    int sock;
    struct sockaddr_in addr;

    printf("Write IP: ");
    char adr[16];
    scanf("%s", adr);

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }

    printf("Please, write your string: ");
    char message[256];
    scanf("%s", message);
    char realmsg[strlen(message) + 1];
    for(int i = 0; i < strlen(message); ++i){
        realmsg[i] = message[i];
    }
    realmsg[strlen(message)] = '\n';

    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425);
    addr.sin_addr.s_addr = inet_addr(adr);
    sendto(sock, realmsg, sizeof(realmsg), 0,
           (struct sockaddr *)&addr, sizeof(addr));


    int ssock;
    struct sockaddr_in saddr;
    char buf[1024];

    ssock = socket(AF_INET, SOCK_DGRAM, 0);
    if(ssock < 0)
    {
        perror("socket");
        exit(1);
    }

    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(3426);
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(ssock, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
    {
        perror("bind");
        exit(2);
    }

    recvfrom(ssock, buf, 1024, 0, NULL, NULL);

    printf("Your result: ");
    printf(buf);
    close(sock);
    close(ssock);

    return 0;
}