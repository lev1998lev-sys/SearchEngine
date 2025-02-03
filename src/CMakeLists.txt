cmake_minimum_required(VERSION 3.17)

set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)


add_executable(SearchEngine main.cpp
        ${MY_INCLUDE_DIR}/ConverterJSON.h
        ConverterJSON.cpp
        ${MY_INCLUDE_DIR}/InvertedIndex.h
        InvertedIndex.cpp
        SearchService.cpp
        ${MY_INCLUDE_DIR}/SearchService.h
)
target_include_directories(SearchEngine PUBLIC ${MY_INCLUDE_DIR})
