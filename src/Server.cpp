#include "Server.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>

Server::Server(Router& router_, uint16_t port_) : router(router_), port(port_), server_fd(-1)
{
     server_fd = socket(AF_INET, SOCK_STREAM, 0);
     if (server_fd == -1)
     {
          std::cerr << "Cannot create socket\n";
          exit(EXIT_FAILURE);
     }

     int opt = 1;
     if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
     {
          std::cerr << "Failed to set SO_REUSEADDR!\n";
          exit(EXIT_FAILURE);
     }

     sockaddr_in address{};
     address.sin_family = AF_INET;
     address.sin_addr.s_addr = INADDR_ANY;
     address.sin_port = htons(port);

     if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0)
     {
          std::cerr << "Error binding. Maybe port is already in use\n";
          exit(EXIT_FAILURE);
     }

     if (listen(server_fd, SOMAXCONN) < 0)
     {
          std::cerr << "Failed to listen on socket!\n";
          exit(EXIT_FAILURE);
     }
}

void Server::run()
{
     std::cout << "Server is running on port " << port << "...\n";
    
     while (true)
     {
          sockaddr_in client_address{};
          socklen_t client_len = sizeof(client_address);
          int client_fd = accept(server_fd, (struct sockaddr*)&client_address, &client_len);
          if (client_fd < 0)
          {
               std::cerr << "Failed to accept client connection!\n";
               continue;
          }
          handle_client(client_fd);
     }
}

void Server::handle_client(int client_fd)
{
     char buffer[4096] = {0}; 
     ssize_t bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);
     if (bytes_read > 0)
     {
          std::string raw_request(buffer, bytes_read);
          Request req(raw_request);
          Response res = router.handle_request(req);
          std::string raw_response = res.get_response();
          write(client_fd, raw_response.c_str(), raw_response.length());
     }
     close(client_fd);
}