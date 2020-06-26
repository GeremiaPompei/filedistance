cmake_minimum_required(VERSION 3.16)
project(filedistance C)

set(CMAKE_C_STANDARD 99)

add_executable(filedistance main.c utility.h distance.h apply.h search.h utility.c distance.c apply.c search.c)