#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <netdb.h>
#include <thread>
#include <vector>

class Client
{
    int socketFileDesc;
    std::mutex threadLock;
    std::vector<int> clientSockets;

    public:
        ~Client();
        void closeSockets(int sig);
        void socketCreation();
        void socketBindListen();
        void send();
        void recv();
        void init();

};

#endif
