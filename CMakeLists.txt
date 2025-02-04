cmake_minimum_required(VERSION 3.30)
project(SearchEngine VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)

set(JSON_BuildTests OFF CACHE INTERNAL "")

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set(gtest_disable_pthreads on)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_subdirectory(nlohmann_json)

add_subdirectory(src)

add_subdirectory(tests)


target_link_libraries(SearchEngine PUBLIC nlohmann_json::nlohmann_json gtest_main)
include(GoogleTest)