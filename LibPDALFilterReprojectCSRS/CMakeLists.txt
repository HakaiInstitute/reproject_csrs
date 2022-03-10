find_package(PDAL 2 REQUIRED CONFIG)

# Get a list of all the source files
file(GLOB_RECURSE _HDRS "include/*.h")
file(GLOB_RECURSE _SRCS "src/*.cpp" "src/*.h")

# Set the library target
add_library(pdal_plugin_filter_reprojectcsrs SHARED ${_HDRS} ${_SRCS})

# Link PDAL and csrs_transform
target_link_libraries(pdal_plugin_filter_reprojectcsrs PUBLIC csrs_transform PRIVATE ${PDAL_LIBRARIES})

# Allow anything in src or include to be included
target_include_directories(pdal_plugin_filter_reprojectcsrs PRIVATE ${PDAL_INCLUDE_DIRS})

# Setup PDAL
target_link_directories(pdal_plugin_filter_reprojectcsrs PUBLIC ${PDAL_LIBRARY_DIRS})
add_definitions(${PDAL_DEFINITIONS})

# Install
install(
        TARGETS pdal_plugin_filter_reprojectcsrs
        DESTINATION lib
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_WRITE GROUP_EXECUTE WORLD_READ WORLD_WRITE WORLD_EXECUTE
)
