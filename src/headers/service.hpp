#ifndef SERVICE_H
#define SERVICE_H

#include "crow.h"
#include <string>
#include <cpr/cpr.h>
#include "../../include/json.hpp"

#define MAIN_URL "https://data.covid19.go.id/public/api/update.json"

using json = nlohmann::json;

/** METHODS */
void error_service(crow::response &res);
crow::json::wvalue get_all_cases_services();

#endif