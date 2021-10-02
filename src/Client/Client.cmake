cmake_minimum_required(VERSION 3.8)

file(GLOB clientSource
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Client/Client.cpp
)

add_library(client
    SHARED
        ${clientSource}
)

target_include_directories(client
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ComModule
)

target_compile_options(client
    PRIVATE
        -fPIC
        -g
        -std=c++11
        -fvisibility-inlines-hidden
        -Wall
        -Werror
)
