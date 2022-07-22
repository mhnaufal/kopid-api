cmake_minimum_required(VERSION 3.15.0 FATAL_ERROR)

project(covid_app)

find_package(Crow)

add_executable(main_app src/main.cpp)
target_link_libraries(main_app PUBLIC Crow::Crow)

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG 871ed52d350214a034f6ef8a3b8f51c5ce1bd400) # The commit hash for 1.9.0. Replace with the latest from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)

target_link_libraries(main_app PRIVATE cpr::cpr)
