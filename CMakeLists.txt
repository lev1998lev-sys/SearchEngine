cmake_minimum_required(VERSION 3.30)
project(SearchEngine VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)

set(JSON_BuildTests OFF CACHE INTERNAL "")

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)


add_subdirectory(src)

add_subdirectory(tests)


target_link_libraries(SearchEngine PUBLIC nlohmann_json::nlohmann_json)