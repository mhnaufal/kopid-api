#include <iostream>
#include "headers/service.hpp"

crow::json::wvalue get_all_cases_service()
{
    cpr::Response covid_data_raw = cpr::Get(cpr::Url{MAIN_URL});
    json covid_data_json = json::parse(covid_data_raw.text); // change string to JSON
    json covid_data_array = json::array({covid_data_json}); // change JSON to array

    crow::json::wvalue result({
        {"ok", true},
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
}

crow::json::wvalue get_cases_by_date(std::string year, std::string month, std::string date)
{
    if (std::stoi(year) < 2020 ||
        std::stoi(month) < 1 ||
        std::stoi(month) > 12 ||
        std::stoi(date) < 1 || 
        std::stoi(date) > 31 ||
        ((std::stoi(month) == 2 || std::stoi(month) == 02) && std::stoi(date) > 29))
    {
        crow::json::wvalue result({
            {"ok", false},
            {"message", "[FAILED] Format tanggal salah"},
            {"data", 0},
        });

        return result;
    }

    std::string date_format = "\"" + year + "-" + month + "-" + date + "T00:00:00.000Z" + "\"";
    std::string date_format_short = year + "-" + month + "-" + date;

    cpr::Response covid_data_raw = cpr::Get(cpr::Url{MAIN_URL});
    json covid_data_json = json::parse(covid_data_raw.text);
    json covid_data_daily = covid_data_json["update"]["harian"];

    int index = 0;

    while (covid_data_daily[index]["key_as_string"].dump() != date_format)
    {
        index++;
    }

    if (covid_data_daily[index]["key_as_string"].dump() != date_format)
    {
        crow::json::wvalue result({
            {"ok", false},
            {"message", "[FAILED] Gagal menemukan data di tanggal " + date_format_short},
            {"data", 0},
        });

        return result;
    }

    covid_data_daily = covid_data_daily[index];

    crow::json::wvalue result({
        {"ok", true},
        {"message", "[SUCCESS] Berhasil mendapatkan data COVID di tanggal " + date_format_short},
        {"data", {
            {"date", date_format_short},
            {"positive", covid_data_daily["jumlah_positif"]["value"].get<int>()},
            {"recovered", covid_data_daily["jumlah_sembuh"]["value"].get<int>()},
            {"deaths", covid_data_daily["jumlah_meninggal"]["value"].get<int>()},
            {"active", covid_data_daily["jumlah_dirawat"]["value"].get<int>()},
        }}
    });

    return result;
}
