#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>


#define PORT 12345


int main() {
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if (connect(sock, reinterpret_cast<sockaddr *>(&serverAddr), sizeof(serverAddr)) < 0):
        std::cerr << "Connection failed!"
    std::cout << "Socket connected! ";

    return 0;
}