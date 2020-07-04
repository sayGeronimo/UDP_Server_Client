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
    char buffer[512] = {0};
    struct sockaddr_in servaddr = {0};

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1)
    {
        perror("failed create socket");
        exit(EXIT_FAILURE);
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(9095);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    int check_bind = bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));

    if (check_bind == -1)
    {
        perror("failed to bind");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    while (1)
    {
        socklen_t len = 0;
        int n = recvfrom(sockfd, (char *)buffer, 50, MSG_WAITALL, 0, &len);
        buffer[n] = '\n';
        printf("%s", buffer);
    }

    close(sockfd);
    return 0;
}
