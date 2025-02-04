cmake_minimum_required(VERSION 3.30)

project(tests)

set(CMAKE_CXX_STANDARD 11)


set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(MY_SRC_DIR ${CMAKE_SOURCE_DIR}/src)

add_executable(${PROJECT_NAME}
        test_inverted_index.cpp
        ${MY_INCLUDE_DIR}/InvertedIndex.h
        ${MY_SRC_DIR}/InvertedIndex.cpp
        ${MY_INCLUDE_DIR}/ConverterJSON.h
        ${MY_SRC_DIR}/ConverterJSON.cpp
        ${MY_INCLUDE_DIR}/SearchService.h
        ${MY_SRC_DIR}/SearchService.cpp
)



target_include_directories(${PROJECT_NAME} PUBLIC ${MY_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC

        gtest

        gtest_main

        nlohmann_json::nlohmann_json
)