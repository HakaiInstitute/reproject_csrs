cmake_minimum_required(VERSION 3.16)
project(reproject_csrs)

set(CMAKE_CXX_STANDARD 20)

# Build proj source
include(ExternalProject)
set(PROJ_PREFIX proj81)
set(PROJ_URL https://download.osgeo.org/proj/proj-8.1.1.tar.gz)
set(PROJ_MD5 f017fd7d35311b0d65b2cf0503844690)

set(PROJ_INSTALL_PREFIX $ENV{HOME}/${PROJ_PREFIX})
set(PROJ_LIB_DIR ${PROJ_INSTALL_PREFIX}/lib)
set(PROJ_BINARY_DIR ${PROJ_INSTALL_PREFIX}/bin)
set(PROJ_INCLUDE_DIR ${PROJ_INSTALL_PREFIX}/include)

ExternalProject_Add(${PROJ_PREFIX}
        PREFIX ${PROJ_PREFIX}
        URL ${PROJ_URL}
        URL_MD5 ${PROJ_MD5}
        CMAKE_CACHE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${PROJ_INSTALL_PREFIX} -DBUILD_SHARED_LIBS:BOOL=ON)

ExternalProject_Add_Step(${PROJ_PREFIX} sync
        COMMAND ${PROJ_BINARY_DIR}/projsync --area-of-use Canada
        DEPENDEES install
        )

add_library(Proj SHARED IMPORTED)
set_target_properties(Proj PROPERTIES IMPORTED_LOCATION ${PROJ_LIB_DIR}/libproj.so)

#find_package(GDAL REQUIRED)
#find_package(PROJ REQUIRED)
find_package(PDAL 1.0.0 REQUIRED CONFIG)

# Allow anything in src or include to be included
include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
        ${PDAL_INCLUDE_DIRS}
        ${PROJ_INCLUDE_DIR}
)

# Setup PDAL
link_directories(${PDAL_LIBRARY_DIRS})
add_definitions(${PDAL_DEFINITIONS})

# Get a list of all the source files
file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/include/*.hpp"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/*.c"
        )

# Set the library target
add_library(pdal_plugin_filter_reprojectcsrs SHARED ${all_SRCS})

# Link PDAL and PROJ
target_link_libraries(pdal_plugin_filter_reprojectcsrs PRIVATE Proj ${PDAL_LIBRARIES})
add_dependencies(pdal_plugin_filter_reprojectcsrs ${PROJ_PREFIX})

# Install
install(TARGETS pdal_plugin_filter_reprojectcsrs DESTINATION ${PDAL_LIBRARIES_DIRECTORY})
