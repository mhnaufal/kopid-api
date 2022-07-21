cmake_minimum_required(VERSION 3.15.0 FATAL_ERROR)

project(covid_app)

find_package(Crow)

add_executable(main_app src/main.cpp)
target_link_libraries(main_app PUBLIC Crow::Crow)
