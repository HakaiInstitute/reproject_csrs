cmake_minimum_required(VERSION 3.16)
project(reproject_csrs)

set(CMAKE_CXX_STANDARD 20)

# Put FindPROJ.cmake in the search path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

#find_package(GDAL REQUIRED)
find_package(PROJ REQUIRED)
find_package(PDAL 1.0.0 REQUIRED CONFIG)

# Allow anything in src or include to be included
include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
)

# Get a list of all the source files
file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/include/*.hpp"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/*.c"
        )

# Set the library target
add_library(pdal_plugin_filter_reprojectcsrs SHARED ${all_SRCS})

# Setup linker and include directories for 3rd party packages
target_include_directories(
        pdal_plugin_filter_reprojectcsrs
        PRIVATE ${PDAL_INCLUDE_DIRS}
)
target_link_directories(pdal_plugin_filter_reprojectcsrs PRIVATE ${PDAL_LIBRARY_DIRS})
add_definitions(${PDAL_DEFINITIONS})
target_link_libraries(pdal_plugin_filter_reprojectcsrs PRIVATE ${PROJ_LIBRARIES} PRIVATE ${PDAL_LIBRARIES})
