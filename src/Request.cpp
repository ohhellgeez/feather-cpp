#include "Request.hpp"
#include <sstream>
#include <iostream>

Request::Request(const std::string& raw_request)
{
     parse(raw_request);
}

std::string Request::get_header(const std::string& key) const
{
     auto it = headers.find(key);
     if (it != headers.end())
     {
          return it->second;
     }
     return "";
}

void Request::parse(const std::string& raw_request)
{
     std::istringstream stream(raw_request);
     std::string line;

     if (std::getline(stream, line))
     {
          if (!line.empty() && line.back() == '\r') line.pop_back();
          std::istringstream line_stream(line);
          line_stream >> method >> path >> version;
     }

     while (std::getline(stream, line))
     {
          if (!line.empty() && line.back() == '\r') line.pop_back();
          if (line.empty()) break;

          size_t colon_pos = line.find(':');
          if (colon_pos != std::string::npos)
          {
               std::string key = line.substr(0, colon_pos);
               std::string value = line.substr(colon_pos + 1);
                
               size_t first_non_space = value.find_first_not_of(' ');
               if (first_non_space != std::string::npos)
               {
                    value = value.substr(first_non_space);
               }
               headers[key] = value;
          }
     }
     std::ostringstream body_stream;
     body_stream << stream.rdbuf();
     body = body_stream.str();
}

const std::string& Request::get_method() const { return method; }

const std::string& Request::get_path() const { return path; }

const std::string& Request::get_body() const { return body; }