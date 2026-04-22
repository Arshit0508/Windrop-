#include <iostream>
#include <fstream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>


using namespace std;

int main()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    ifstream infile("my_file.txt", ios::binary);
    if (!infile)
    {
        cerr << "Error opening file!\n";
        return 1;
    }

    char buffer[1024];
    while (infile.read(buffer, sizeof(buffer)) || infile.gcount() > 0)
    {
        int bytes_to_send = infile.gcount();
        send(sock, buffer, bytes_to_send, 0);
    }

    cout << "File sent successfully.\n";

    infile.close();
    close(sock);
    return 0;
}