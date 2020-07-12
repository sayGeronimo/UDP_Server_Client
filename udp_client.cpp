#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char const *argv[])
{
    char *helloworldtext = "class test.";
    int port = atoi(argv[1]);
    struct sockaddr_in ServerAddr = {0};

    int sock_obj = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_obj == -1)
    {
        perror("Failed. Socket is not create.");
        exit(EXIT_FAILURE);
    }

    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port = htons(port);
    ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int size = sendto(sock_obj, (const char *)helloworldtext, strlen(helloworldtext), 0, (const struct sockaddr *)&ServerAddr, sizeof(ServerAddr));
    if (size == -1)
    {
        perror("Failed. sendto not work.");
    }
    close(sock_obj);   
    return 0;
}
