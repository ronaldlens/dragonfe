cmake_minimum_required(VERSION 3.13)
project(dragonfe C)

set(CMAKE_C_STANDARD 11)

add_executable(dragonfe main.c lex.c lex.h)