#include "Response.hpp"
#include <iostream>
#include <sstream>

std::string Response::get_status_text(int stat) const
{
     switch (stat) {
          case 200: return "OK";
          case 201: return "Created";
          case 204: return "No Content";
          case 400: return "Bad Request";
          case 401: return "Unauthorized";
          case 403: return "Forbidden";
          case 404: return "Not Found";
          case 405: return "Method Not Allowed";
          case 500: return "Internal Server Error";
          default:  return "Unknown Status"; 
     }
}

bool Response::is_valid_status(int stat)
{
     return stat >= 100 && stat <= 599;
}

void Response::set_status(int stat)
{
     if (is_valid_status(stat))
     {
          status = stat;
     }
     else
     {
          std::cerr << "In Response::set_status(): status is invalid. Denied!\n";
          return;
     }
}

void Response::set_body(const std::string& bd)
{
     body = bd;
}

void Response::set_header(const std::string& key, const std::string& value)
{
     headers[key] = value;
}

int Response::get_status() const
{
     return status;
}

std::string Response::get_header(const std::string& key) const
{
     auto it = headers.find(key);
     
     if (it == headers.end())
     {
          return "";
     }
     else
     {
          return it->second;
     }
}

const std::string& Response::get_body() const
{
     return body;
}

std::string Response::get_response() const
{
     std::ostringstream response;
     response << "HTTP/1.1 " << status << " " << get_status_text(status) << "\r\n";
     for (const auto& [key, value] : headers)
     {
          response << key << ": " << value << "\r\n";
     }
     response << "Content-Length: " << body.length() << "\r\n";
     response << "\r\n";
     response << body;
     return response.str();
}