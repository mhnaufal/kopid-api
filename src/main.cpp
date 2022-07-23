#include <iostream>
#include <string>
#include <cpr/cpr.h>
#include "crow.h"
#include "json.hpp"

#define PORT 18080
#define SERVER_NAME "Kopit 19 API"
#define SET_LOG_LEVEL Debug

using json = nlohmann::json;

std::string MAIN_URL = "https://data.covid19.go.id/public/api/update.json";

int main(int argc, char **argv)
{
    // define crow app
    crow::SimpleApp app;

    // GET "/"
    CROW_ROUTE(app, "/")
    ([]()
    {
        cpr::Response covid_data_raw = cpr::Get(cpr::Url{MAIN_URL});
        json covid_data_json = json::parse(covid_data_raw.text); // change string to JSON
        json covid_data_array = json::array({covid_data_json}); // change JSON to array

        crow::json::wvalue result({
            {"oke", true},
            {"message", "[SUCCESS] Berhasil mendapatkan semua data COVID"},
            {"data", {
                {"total_positive", covid_data_json["update"]["total"]["jumlah_positif"].get<int>()},
                {"total_recovered", covid_data_json["update"]["total"]["jumlah_sembuh"].get<int>()},
                {"total_deaths", covid_data_json["update"]["total"]["jumlah_meninggal"].get<int>()},
                {"total_active", covid_data_json["update"]["total"]["jumlah_dirawat"].get<int>()},
                {"new_positive", covid_data_json["update"]["penambahan"]["jumlah_positif"].get<int>()},
                {"new_recovered", covid_data_json["update"]["penambahan"]["jumlah_sembuh"].get<int>()},
                {"new_deaths", covid_data_json["update"]["penambahan"]["jumlah_meninggal"].get<int>()},
                {"new_active", covid_data_json["update"]["penambahan"]["jumlah_dirawat"].get<int>()},
            }}
        });

        return result;
    });

    // GET "/daily/<int:year>/<int:month>/<int:date>"

    // GET ERROR
    CROW_CATCHALL_ROUTE(app)
    ([](crow::response& res)
    {
        res.add_header("Content-Type", "application/json");

        if (res.code == 404)
        {
            auto error_response = R"(
                {
                    "ok": false,
                    "message": "[ERROR] Alamat salah!",
                    "data": 0
                }
            )";
        }
        else if (res.code == 405)
        {
            auto error_response = R"(
                {
                    "ok": false,
                    "message": "[ERROR] Metode tidak diperbolehkan!",
                    "data": 0
                }
            )";
        }
        else
        {
            auto error_response = R"(
                {
                    "ok": false,
                    "message": "[ERROR] Server sedang bermasalah!",
                    "data": 0
                }
            )";
        }

        res.body = error_response;
        res.end();
    });

    // set log level
    crow::logger::setLogLevel(crow::LogLevel::SET_LOG_LEVEL);    

    // set port and run app
    app.port(PORT)
        .server_name(SERVER_NAME)
        .multithreaded()
        .run();
}
