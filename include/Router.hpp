#pragma once
#include <unordered_map>
#include <string>
#include <functional>
#include "Request.hpp"
#include "Response.hpp"

class Router
{
public:
     using Handler = std::function<Response(const Request&)>;
     void get(const std::string& path, Handler hndl);
     void post(const std::string& path, Handler hndl);
     Response handle_request(const Request& req);
private:
     std::unordered_map<std::string, Handler> routes;
};