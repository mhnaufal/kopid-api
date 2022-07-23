#include <iostream>
#include <string>
#include <cpr/cpr.h>
#include "crow.h"
#include "json.hpp"

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

        // std::string data_string = covid_data_json.at("data").at("jumlah_odp").dump();
        // std::cout << std::setw(4) << "VALUE => " << std::stoi(data_string) + 1000 << "\n\n";

        // crow::json::wvalue result({
        //     covid_data_json.at("data").at("jumlah_odp").dump()
            // j_array.dump()
        // });

        return result;
    });

    // GET "/daily/<int:year>/<int:month>/<int:date>"

    // GET ERROR
    CROW_CATCHALL_ROUTE(app)
    ([](crow::response& res)
    {
        res.manual_length_header = true;
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
            res.body = error_response;
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
            res.body = error_response;
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
            res.body = error_response;
        }
    res.end();
    });

    // set port and run app
    app.loglevel(crow::LogLevel::Debug)
        .port(18080)
        .server_name("Indonesia COVID 19 API")
        .multithreaded()
        .run();
}
