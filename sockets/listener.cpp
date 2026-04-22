#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

int main()
{
    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    int reuse = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    struct sockaddr_in listen_addr;
    listen_addr.sin_family = AF_INET;
    listen_addr.sin_port = htons(8888);
    listen_addr.sin_addr.s_addr = INADDR_ANY;

    bind(sock, (struct sockaddr *)&listen_addr, sizeof(listen_addr));

    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr = inet_addr("239.255.255.250");
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));

    std::cout << "Listening for Lighthouse peers on the network...\n";

    char buffer[1024];
    while (true)
    {
        memset(buffer, 0, sizeof(buffer)); // Clear buffer
        recvfrom(sock, buffer, sizeof(buffer), 0, nullptr, nullptr);
        std::cout << "Discovered new peer -> " << buffer << "\n";
    }

    close(sock);
    return 0;
}