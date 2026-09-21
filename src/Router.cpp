#include "Router.hpp"

void Router::get(const std::string& path, Handler hndl)
{
     routes["GET:" + path] = hndl;
}

void Router::post(const std::string& path, Handler hndl)
{
     routes["POST:" + path] = hndl;
}

Response Router::handle_request(const Request& req)
{
     auto it = routes.find(req.get_method() + ":" + req.get_path());
     if (it != routes.end())
     {
          return it->second(req);
     }
     else
     {
          Response not_found(404, "404 Not Found\n");
          not_found.set_header("Content-Type", "text/plain");
          return not_found;
     }
}