#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string>
#include <iostream>
#include <memory>

using namespace std;

class udp_server
    {
    private:

    public:
        int sock;
        void handle();
        char buffer[512] = {0};

        udp_server(int port)
        : sock(-1)
        {
            if (port)
            {
                open(port);
                std::cout << "port opened" << std::endl;
            }
            
        }
        //~udp_server();

        bool open(int port) {
            sock = socket(AF_INET, SOCK_DGRAM, 0);
            if (sock == -1)
            {
                perror("Failed. Socket is not create.");
                exit(EXIT_FAILURE);
            }

            struct sockaddr_in servaddr;

            servaddr.sin_family = AF_INET;
            servaddr.sin_port = htons(9095);
            servaddr.sin_addr.s_addr = INADDR_ANY;

            int rc = bind(sock, (const struct sockaddr *)&servaddr, sizeof(servaddr));

            if (rc == -1)
            {
                perror("failed to bind");
                close(sock);
                exit(EXIT_FAILURE);
            }
            // handle();
            return true;
        }       
    };

void udp_server::handle() {
    while (true)
    {
        socklen_t len = 0;
        int n = recvfrom(sock, (char *)buffer, 50, MSG_WAITALL, 0, &len);
        buffer[n] = '\n';
        printf("%s", buffer);
    }
    
}

static std::unique_ptr<udp_server> udp_ptrs;

void check(int port) 
{
    try
    {
        if (!udp_ptrs)
        {
            udp_ptrs.reset(new udp_server(port));
            cout << "port" << port << endl;
        }
        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

// void udp_server::handle()
// {
//     while (true)
//     {
//         int accept;
//         sockaddr_in addr_c;
//         int addrlen = sizeof(addr_c);
//         if ((accept = acpt(sock, (struct sockaddr*)&addr_c, &addrlen)) != 0)
//         {
//             /* code */
//         }
        

//     }
    
// }

int main(int argc, char const *argv[])
{
    while (1)
    {
        check(9095);
    }

    // char buffer[512] = {0};
    
    // int port = atoi(argv[1]);
    // struct sockaddr_in servaddr = {0};

    // int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    // if (sockfd == -1)
    // {
    //     perror("failed create socket");
    //     exit(EXIT_FAILURE);
    // }

    // servaddr.sin_family = AF_INET;
    // servaddr.sin_port = htons(port);
    // servaddr.sin_addr.s_addr = INADDR_ANY;

    // int check_bind = bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));

    // if (check_bind == -1)
    // {
    //     perror("failed to bind");
    //     close(sockfd);
    //     exit(EXIT_FAILURE);
    // }
    // while (1)
    // {
    //     socklen_t len = 0;
    //     int n = recvfrom(sockfd, (char *)buffer, 50, MSG_WAITALL, 0, &len);
    //     buffer[n] = '\n';
    //     printf("%s", buffer);
    // }

    // close(sockfd);
    // return 0;
}
