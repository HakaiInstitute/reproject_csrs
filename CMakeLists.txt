cmake_minimum_required(VERSION 3.16)
project(reproject_csrs)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(LibCSRSTransform)
add_subdirectory(LibPDALFilterReprojectCSRS)
add_subdirectory(LibCSRSPy)
