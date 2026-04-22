#include <iostream>
#include <fstream>
#include <thread>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>


using namespace std;

// udp broadcaster
void run_udp_broadcaster() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    int broadcast_enable = 1;
    setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &broadcast_enable, sizeof(broadcast_enable));
    
    struct sockaddr_in broadcast_addr;
    broadcast_addr.sin_family = AF_INET;
    broadcast_addr.sin_port = htons(8888);
    broadcast_addr.sin_addr.s_addr = inet_addr("239.255.255.250");

    string message = "Sumit_Laptop:192.168.1.5 Alive";

    while(true) {
        sendto(sock, message.c_str(), message.length(), 0, (struct sockaddr*)&broadcast_addr, sizeof(broadcast_addr));
        sleep(2); 
    }
    close(sock);
}

// udp listener
void run_udp_listener() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    int reuse = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    
    struct sockaddr_in listen_addr;
    listen_addr.sin_family = AF_INET;
    listen_addr.sin_port = htons(8888);
    listen_addr.sin_addr.s_addr = INADDR_ANY; 
    
    bind(sock, (struct sockaddr*)&listen_addr, sizeof(listen_addr));
    
    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr = inet_addr("239.255.255.250");
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));
    
    char buffer[1024];
    while(true) {
        memset(buffer, 0, sizeof(buffer)); 
        recvfrom(sock, buffer, sizeof(buffer), 0, nullptr, nullptr);
        std::cout << "Founded Peer: " << buffer << "\n";
    }
    close(sock);
}

// file receiver
void run_tcp_server() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    int reuse = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);
    
    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 3);
    
    int addrlen = sizeof(address);
    char buffer[1024];

    while(true) {
        int new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        cout << "Incoming file transfer started...\n";
        
        ofstream outfile("lighthouse_received_file.txt", ios::binary);
        int bytes_received;
        
        while ((bytes_received = recv(new_socket, buffer, sizeof(buffer), 0)) > 0) {
            outfile.write(buffer, bytes_received);
        }
        
        cout << "File received successfully!\n";
        outfile.close();
        close(new_socket);
    }
    close(server_fd);
}

// main

int main() {
    
    cout << "LIGHTHOUSE CORE ENGINE STARTED\n";
    

    thread mouth(run_udp_broadcaster);
    thread ear(run_udp_listener);
    thread hands(run_tcp_server);

    mouth.join();
    ear.join();
    hands.join();

    return 0;
}