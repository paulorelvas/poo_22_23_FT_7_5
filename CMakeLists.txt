cmake_minimum_required(VERSION 3.23)
project(FT_7_5)

include_directories(
        .               # project base directory
        tarifario
        tarifario/apressado
        cliente
        cliente/sociavel
        ginasio
)
set(CMAKE_CXX_STANDARD 20)

add_executable(FT_7_5 main.cpp
        cliente/Cliente.cpp cliente/Cliente.h
        cliente/sociavel/Sociavel.cpp cliente/sociavel/Sociavel.h
        tarifario/Tarifario.cpp tarifario/Tarifario.h
        tarifario/apressado/Apressado.cpp tarifario/apressado/Apressado.h
        ginasio/Ginasio.cpp ginasio/Ginasio.h
        proj_includes.h )
