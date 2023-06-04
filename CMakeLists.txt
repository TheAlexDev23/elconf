cmake_minimum_required(VERSION 3.26.0)
project(elconf)


include_directories(lib)
include_directories(**/lib)

add_executable(
    ${PROJECT_NAME}
    src/elconf.c
)

add_subdirectory(lib/pttui)

target_link_libraries(${PROJECT_NAME} pel png pttui cwalk)