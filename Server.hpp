#pragma once
#include <string>
#include <unordered_map>
#include <sstream>
#include <iostream>

class Request
{
public:
     std::string method;
     std::string path;
     std::string version;
     std::unordered_map<std::string,std::string> headers;
     std::string body;

     explicit Request(const std::string& raw_request);

     std::string get_header(const std::string& key) const;

private:
     void parse(const std::string& raw_request);
};