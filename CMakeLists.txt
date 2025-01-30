cmake_minimum_required(VERSION 3.30)
project(search_engine)

set(CMAKE_CXX_STANDARD 17)

set(JSON_BuildTests OFF CACHE INTERNAL "")


add_subdirectory(nlohmann_json)

add_executable(search_engine main.cpp
        ConverterJSON.h
        ConverterJSON.cpp
        InvertedIndex.h
        InvertedIndex.cpp
        SearchService.cpp
        SearchService.h
)

target_link_libraries(search_engine PUBLIC nlohmann_json::nlohmann_json)