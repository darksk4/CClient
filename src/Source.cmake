cmake_minimum_required(VERSION 3.8)

include(${CMAKE_CURRENT_SOURCE_DIR}/src/Client/Client.cmake)

add_executable(clientExe ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

target_include_directories(clientExe
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Client
)

target_compile_options(clientExe
    PRIVATE
        -std=c++11
        -g
        -Wall
        -Werror
)

target_link_libraries(clientExe
    PRIVATE
        client
)
