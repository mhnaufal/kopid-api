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
crow::json::wvalue get_all_cases_service();
crow::json::wvalue get_cases_by_date(std::string year, std::string month, std::string date);
crow::json::wvalue get_cases_by_month(std::string year, std::string month);
crow::json::wvalue get_cases_by_year(std::string year);

#endif