#include <iostream>
#include "Server.hpp"
#include "Router.hpp"
#include "Request.hpp"
#include "Response.hpp"

int main() 
{
     Router router;
     router.get("/", [](const Request&)
     {    
          Response res(200, "Hello, World from feather-cpp!");
          res.set_header("Content-Type", "text/plain");
        
          return res;
     });
     Server app(router, 8080);
     app.run();
     return 0;
}