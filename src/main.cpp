#include "crow.h"
// #include "crow_all.h"

int main()
{
  // define crow app
  crow::SimpleApp app;

  // define endpoint
  CROW_ROUTE(app, "/")
  ([]()
   { return "Hello, world!"; });

  // set port and run app
  app.loglevel(crow::LogLevel::Debug)
      .port(18080)
      .server_name("Indonesia'a COVID 19 API")
      .multithreaded()
      .run();
}
