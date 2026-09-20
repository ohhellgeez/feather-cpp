#include <iostream>
#include <string>
#include <sys/socket.h> // Для socket(), bind(), listen(), accept()
#include <netinet/in.h> // Для структуры sockaddr_in
#include <unistd.h>     // Для read(), write(), close()

int main()
{
     int server_fd = socket(AF_INET, SOCK_STREAM, 0);
     if (server_fd == -1)
     {
          std::cerr << "Cannot create socket\n";
          return 1;
     } 

     sockaddr_in address;
     address.sin_family = AF_INET;
     address.sin_addr.s_addr = INADDR_ANY;
     address.sin_port = htons(8080);

     if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0)
     {
          std::cerr << "Error binding. Maybe port os already in use\n";
          return 1;
     }

     listen(server_fd, 3);

     std::cout << "Server run at http://localhost:8080\n";

     while (true)
     {
          sockaddr_in client_addr;
          socklen_t client_len = sizeof(client_addr);

          int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
          if (client_fd < 0) continue;

          char buffer[1024] = {0};

          read(client_fd, buffer, 1024);

          std::cout << "\n--- Accepted request ---\n" << buffer << "---------------------------\n";

          std::string http_response = 
               "HTTP/1.1 200 OK\r\n"
               "Content-Type: text/plain\r\n"
               "Content-Length: 12\r\n"
               "\r\n"
               "Hello World!";
          
          write(client_fd, http_response.c_str(), http_response.length());
          close(client_fd);
     }
     
     close(server_fd);
     return 0;
}