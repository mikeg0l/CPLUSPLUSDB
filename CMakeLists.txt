cmake_minimum_required(VERSION 3.26)
project(2324Z_19_s26525_TW)
set(CMAKE_CXX_STANDARD 20)
include(FetchContent)
FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG 10.2.1
)
FetchContent_MakeAvailable(fmt)
add_executable(2324Z_19_s26525_TW main.cpp
        table/table.cpp
        utils/parser.cpp
        utils/printer.cpp
        utils/mapper.cpp
        database/database.cpp
        handlers/handlers.cpp
        table/condition.cpp
        table/tablerow.cpp
)
target_link_libraries(2324Z_19_s26525_TW fmt)