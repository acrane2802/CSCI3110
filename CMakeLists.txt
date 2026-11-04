cmake_minimum_required(VERSION 4.3)
project(CSCI3110)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

add_executable(CSCI3110 "main.cpp"
        "Record.cpp"
        "Record.h")

add_custom_command(TARGET CSCI3110 PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/dataset.csv $<TARGET_FILE_DIR:CSCI3110>/)