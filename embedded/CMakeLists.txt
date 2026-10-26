cmake_minimum_required(VERSION 3.14)
project(skyguard_embedded C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(include)

add_library(skyguard SHARED
    src/skyguard_api.c
)

set_target_properties(skyguard PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)