#pragma once
#include <unordered_map>
#include <string>

class Response
{
public:
     explicit Response(int stat = 200, std::string bd = "")
          : status(stat), headers(), body(bd) {}
     
     void set_status(int stat);
     void set_body(const std::string& bd);
     void set_header(const std::string& key, const std::string& value);
     
     std::string get_response() const; 
     
     int get_status() const;
     std::string get_header(const std::string& key) const;
     const std::string& get_body() const;

private:
     int status;
     std::unordered_map<std::string, std::string> headers;
     std::string body;
     bool is_valid_status(int stat);
     std::string get_status_text(int stat) const;
};