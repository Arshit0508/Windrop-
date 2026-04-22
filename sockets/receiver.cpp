#include <iostream>
#include <fstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>


using namespace std;

int main()
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    cout << "Receiver is waiting for a file on port 8080...\n";

    int addrlen = sizeof(address);
    int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);

    ofstream outfile("received_file.txt", ios::binary);

    char buffer[1024];
    int bytes_received;

    while ((bytes_received = recv(new_socket, buffer, sizeof(buffer), 0)) > 0)
    {
        outfile.write(buffer, bytes_received);
    }

    cout << "File received and saved as 'received_file.txt'.\n";

    outfile.close();
    close(new_socket);
    close(server_fd);
    return 0;
}