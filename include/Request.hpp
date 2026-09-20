#pragma once
#include <string>
#include <unordered_map>

class Request
{
public:
     explicit Request(const std::string& raw_request);
     
     std::string get_header(const std::string& key) const;
     
     const std::string& get_method() const;
     const std::string& get_path() const;
     const std::string& get_body() const;

private:
     std::string method;
     std::string path;
     std::string version;
     std::unordered_map<std::string, std::string> headers;
     std::string body;
     
     void parse(const std::string& raw_request);
};