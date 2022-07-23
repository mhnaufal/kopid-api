#include "headers/service.hpp"

void error_service(crow::response &res)
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
}