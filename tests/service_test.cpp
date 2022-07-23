// NOT YET WORKING
// Still trying to figure out how to create and run test in C++

#include "../include/acutest.hpp"
#include "../src/headers/service.hpp"
#include "crow.h"

void test_get_all_cases_service(void)
{
    crow::json::wvalue expected_result({
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

    auto actual_result = get_all_cases_service();

    TEST_CHECK(actual_result == expected_result);
}

TEST_LIST = {
    { "get_all_cases_service", test_get_all_cases_service },
    { NULL, NULL }
};
