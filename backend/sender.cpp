#include <iostream>
#include <fstream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cerr << "Usage: ./sender <target_ip> <file_path>" << endl;
        return 1;
    }

    string target_ip = argv[1];
    string file_path = argv[2];

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        cerr << "Socket creation error" << endl;
        return 1;
    }

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    if (inet_pton(AF_INET, target_ip.c_str(), &serv_addr.sin_addr) <= 0)
    {
        cerr << "Invalid address/ Address not supported" << endl;
        return 1;
    }

    cout << "🔄 Attempting connection to " << target_ip << "..." << endl;
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        cerr << "connection Failed. Is the other C++ engine running?" << endl;
        return 1;
    }

    string filename = file_path.substr(file_path.find_last_of("/\\") + 1);
    string header = filename + "\n";
    send(sock, header.c_str(), header.length(), 0);

    ifstream infile(file_path, ios::binary);
    if (!infile.is_open())
    {
        cerr << "Could not open file: " << file_path << endl;
        return 1;
    }

    char buffer[4096]; 
    while (infile.read(buffer, sizeof(buffer)) || infile.gcount() > 0)
    {
        send(sock, buffer, infile.gcount(), 0);
    }

    cout << "SUCCESS: " << filename << " sent!" << endl;
    infile.close();
    close(sock);
    return 0;
}