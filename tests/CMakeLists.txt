cmake_minimum_required(VERSION 3.30)

project(testsOfSearchEngine)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set(gtest_disable_pthreads on)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest json)

enable_testing()


set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(MY_SRC_DIR ${CMAKE_SOURCE_DIR}/src)

add_executable(${PROJECT_NAME}
        testsOfCommonClasses.cpp
        ${MY_INCLUDE_DIR}/InvertedIndex.h
        ${MY_SRC_DIR}/InvertedIndex.cpp
        ${MY_INCLUDE_DIR}/ConverterJSON.h
        ${MY_SRC_DIR}/ConverterJSON.cpp
        ${MY_INCLUDE_DIR}/SearchService.h
        ${MY_SRC_DIR}/SearchService.cpp
)



target_include_directories(testsOfSearchEngine PUBLIC ${MY_INCLUDE_DIR})

target_link_libraries(testsOfSearchEngine PUBLIC

        gtest

        gtest_main

        nlohmann_json::nlohmann_json
)

target_link_libraries(testsOfSearchEngine PUBLIC gtest_main)

include(GoogleTest)