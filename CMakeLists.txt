project(qrcode_recorder
    LANGUAGES CXX)
cmake_minimum_required(VERSION 3.6.2)

set(CMAKE_INSTALL_PREFIX ../)
set(CMAKE_CXX_STANDARD 11)

add_executable(qrcode_recorder src/main.cpp)

install(TARGETS qrcode_recorder)