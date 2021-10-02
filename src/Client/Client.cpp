#include "Client.hpp"
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <iostream>
#include <string.h>
#include <unistd.h>


const std::string DEFAULT_ADDRESS = "192.168.254.142";
const int PORT = 54000;

Client::~Client()
{
    fd_set readfds;

    FD_ZERO(&readfds);
    FD_SET(socketFileDesc, &readfds);
    int status = fcntl(socketFileDesc, F_SETFL, fcntl(socketFileDesc, F_GETFL, 0) | O_NONBLOCK);
    if (status)
        std::cerr << "NON_BLOCKING state unavailable" << std::endl;
}

void Client::closeSockets(int sig)
{
    printf("Closing Sockets\n");
    close(socketFileDesc);
}

void Client::socketCreation()
{
    int opt = 1;

    socketFileDesc = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFileDesc == -1)
    {
        std::cerr << "Can't create socket" << std::endl;
        return;
    }

    if (setsockopt(socketFileDesc, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1 )
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
}

void Client::socketBindListen()
{
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(PORT);
    inet_pton(AF_INET, DEFAULT_ADDRESS.c_str(), &hint.sin_addr);

    int connection = connect(socketFileDesc, (sockaddr*)&hint, sizeof(hint));

    if (connection == -1)
    {
        std::cerr << "Could not connect to the host" << std::endl;
        return;
    }

}

void Client::send()
{
    /*
    fd_set readfds;

    FD_ZERO(&readfds);
    FD_SET(socketFileDesc, &readfds);
    int status = fcntl(socketFileDesc, F_SETFL, fcntl(socketFileDesc, F_GETFL, 0) | O_NONBLOCK);
    if (status)
        std::cerr << "NON_BLOCKING state unavailable" << std::endl;
    int flag = fcntl(socketFileDesc, F_GETFL, 0);
        printf("send : %d\n", flag);
    */
    std::string userInput;
    while (true)
    {
        std::getline(std::cin, userInput);
        int result = ::send(socketFileDesc, userInput.c_str(), userInput.size() + 1, 0);
        if (result == -1)
        {
            printf("Error\n");
            break;
        }
    }
}

void Client::recv()
{
    char buff[1024];
    while (true)
    {
        memset(buff, 0, 1024);
        int bytesReceived = ::recv(socketFileDesc, buff, 1024, 0);
        if (bytesReceived > 0)
            printf("> %s\n", buff);
    }
}

void Client::init()
{
    //std::ios_base::sync_with_stdio(false);

    socketCreation();
    socketBindListen();
    std::thread th1 (&Client::recv, this);
    std::thread th2 (&Client::send, this);
    th2.join();
}
