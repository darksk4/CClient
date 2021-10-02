#include <iostream>
#include <Client.hpp>
#include <signal.h>

std::function<void(int)> callback_wrapper;

void callback_function(int value)
{
    callback_wrapper(value);
    exit(0);
}

int main()
{
    Client* server = new Client();

    callback_wrapper = std::bind(&Client::closeSockets, server, std::placeholders::_1);

    struct sigaction sigIntHandler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_handler = callback_function;
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);


    server->init();

    return 0;
}
