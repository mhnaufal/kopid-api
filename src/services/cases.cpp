#include "headers/service.hpp"

crow::json::wvalue get_all_cases_service()
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
}