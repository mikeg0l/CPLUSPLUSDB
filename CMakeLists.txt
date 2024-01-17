cmake_minimum_required(VERSION 3.26)
project(2324Z_19_s26525_FK)
set(CMAKE_CXX_STANDARD 20)
include(FetchContent)
FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG 10.2.1
)
FetchContent_MakeAvailable(fmt)
add_executable(2324Z_19_s26525_FK main.cpp table/tablerow.cpp
        table/table.cpp
        parser/parser.cpp
        utils/printer.cpp
        utils/printer.h
        utils/mapper.cpp
        utils/mapper.h)
target_link_libraries(2324Z_19_s26525_FK fmt)