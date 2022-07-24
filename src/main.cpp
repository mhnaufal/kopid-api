#include <iostream>
#include <string>
#include <cpr/cpr.h>
#include "crow.h"
#include "../include/json.hpp"
#include "headers/service.hpp"

#define PORT 18080
#define SERVER_NAME "Kopit 19 API"
#define SET_LOG_LEVEL Debug

int main(int argc, char **argv)
{
    // define crow app
    crow::SimpleApp app;

    // GET "/"
    CROW_ROUTE(app, "/")
    ([]()
    {
        return get_all_cases_service();
    });

    // GET "/daily/<int:year>/<int:month>/<int:date>"
    CROW_ROUTE(app, "/daily/<string>/<string>/<string>")
    ([](std::string year, std::string month, std::string date)
    {
        return get_cases_by_date(year, month, date);
    });

    // GET ERROR
    CROW_CATCHALL_ROUTE(app)
    ([](crow::response &res)
    {
        error_service(res);
    });

    // set log level
    crow::logger::setLogLevel(crow::LogLevel::SET_LOG_LEVEL);    

    // set port and run app
    app.port(PORT)
        .server_name(SERVER_NAME)
        .multithreaded()
        .run();
}
