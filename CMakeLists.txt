cmake_minimum_required(VERSION 3.5)

project(Praktikum04 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Praktikum04 main.cpp
    spielfald.h spielfald.cpp
    random.h random.cpp)

include(GNUInstallDirs)
install(TARGETS Praktikum04
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
