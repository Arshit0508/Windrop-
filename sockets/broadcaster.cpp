#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

using namespace std;

int main() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0); 
    
    // Allow the socket to send messages
    int broadcast_enable = 1;
    setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &broadcast_enable, sizeof(broadcast_enable));
    
    struct sockaddr_in broadcast_addr;
    broadcast_addr.sin_family = AF_INET;
    broadcast_addr.sin_port = htons(8888); // Discovery port
    broadcast_addr.sin_addr.s_addr = inet_addr("239.255.255.250");

    string message = "Sumit_Laptop:192.168.1.5 Alive";

    cout <<" Starting Discovery Broadcaster\n";
    
    while(true) {
        sendto(sock, message.c_str(), message.length(), 0, 
              (struct sockaddr*)&broadcast_addr, sizeof(broadcast_addr));
        cout << "Shouted: "  << message << endl;
        sleep(2); // Shout every 2 seconds
    }
    
    close(sock);
    return 0;
}
