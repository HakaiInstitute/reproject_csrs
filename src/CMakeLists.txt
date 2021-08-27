#find_package(GDAL REQUIRED)
find_package(PROJ REQUIRED)
find_package(PDAL 1.0.0 REQUIRED CONFIG)

include_directories(${PDAL_INCLUDE_DIRS})
link_directories(${PDAL_LIBRARY_DIRS})
add_definitions(${PDAL_DEFINITIONS})

add_library(pdal_plugin_filter_reprojectcsrs SHARED PdalFilterReprojectCSRS.cpp Transform.h Nad83CSRSTransform.cpp Nad83CSRSTransform.h constants.h Helmert.cpp Helmert.h)
target_link_libraries(pdal_plugin_filter_reprojectcsrs PRIVATE ${PROJ_LIBRARIES} PRIVATE ${PDAL_LIBRARIES})
target_include_directories(pdal_plugin_filter_reprojectcsrs PRIVATE ${PDAL_INCLUDE_DIRS})
target_link_directories(pdal_plugin_filter_reprojectcsrs PRIVATE ${PDAL_LIBRARY_DIRS})
