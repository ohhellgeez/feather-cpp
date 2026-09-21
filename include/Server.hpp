#pragma once
#include <cstdint>
#include "Router.hpp"

class Server
{
public:
     Server(Router& router_, uint16_t port_);
     void run();
private:
     Router& router;
     int server_fd;
     uint16_t port;
     void handle_client(int client_fd);
};