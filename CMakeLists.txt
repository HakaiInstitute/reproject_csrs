cmake_minimum_required(VERSION 3.16)
project(reproject_csrs
        VERSION 0.0.2
        DESCRIPTION "Convert to and from NAD83 CSRS coordinates")

set(CMAKE_CXX_STANDARD 20)
include(GNUInstallDirs)

add_subdirectory(LibCSRSTransform)
add_subdirectory(LibCSRSPy)
#add_subdirectory(LibPDALFilterReprojectCSRS)
