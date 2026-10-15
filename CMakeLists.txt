cmake_minimum_required(VERSION 4.3)
project(tictactoe C)

set(CMAKE_C_STANDARD 11)

add_executable(tictactoe
        main.c
        include/board.h
        src/board.c
        include/game.h
)

target_include_directories(tictactoe PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)