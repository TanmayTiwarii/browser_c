cmake_minimum_required(VERSION 3.20)

project(browser_c LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(browser_c
    src/main.cpp
    src/tokenizer.cpp
)
target_include_directories(browser_c PRIVATE include)
find_package(CURL REQUIRED)
target_link_libraries(browser_c PRIVATE CURL::libcurl)


