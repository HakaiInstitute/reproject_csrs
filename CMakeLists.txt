cmake_minimum_required(VERSION 3.20)
project(reproject_csrs)

set(CMAKE_CXX_STANDARD 20)

#find_package(GDAL REQUIRED)
find_package(PROJ REQUIRED)
find_package(PDAL 1.0.0 REQUIRED CONFIG)

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
)
link_directories(${PDAL_LIBRARY_DIRS})
add_definitions(${PDAL_DEFINITIONS})

file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/include/*.hpp"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/*.c"
        )

add_library(pdal_plugin_filter_reprojectcsrs SHARED ${all_SRCS})

target_include_directories(
        pdal_plugin_filter_reprojectcsrs
        PRIVATE ${PROJ_INCLUDE_DIRS}
        PRIVATE${PDAL_INCLUDE_DIRS}
)
target_link_libraries(pdal_plugin_filter_reprojectcsrs PRIVATE ${PDAL_LIBRARIES})
target_link_directories(pdal_plugin_filter_reprojectcsrs PRIVATE ${PDAL_LIBRARY_DIRS})
