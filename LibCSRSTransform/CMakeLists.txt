# Put FindPROJ.cmake in the search path
#list(APPEND CMAKE_MODULE_PATH ./cmake)

find_package(PROJ 9 REQUIRED)

#include(ExternalProject)
#ExternalProject_Add(
#        proj
#        GIT_REPOSITORY  https://github.com/OSGeo/PROJ.git
#        GIT_TAG         9.0.0
#        GIT_SHALLOW     TRUE
#)
#set(PROJ_LIBRARIES ${CMAKE_CURRENT_BINARY_DIR}/proj)

# Get a list of all the source files
file(GLOB_RECURSE _HDRS "include/*.h")
file(GLOB_RECURSE _SRCS "src/*.cpp" "src/*.h")

# Set the library target
add_library(csrs_transform)
target_sources(csrs_transform PRIVATE ${_SRCS} ${_HDRS})
# Simplify paths for includes statements
target_include_directories(csrs_transform PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

set_property(TARGET csrs_transform PROPERTY VERSION ${PROJECT_VERSION})
set_property(TARGET csrs_transform PROPERTY PUBLIC_HEADER ${_HDRS})

# Link PROJ
target_link_libraries(csrs_transform PUBLIC ${PROJ_LIBRARIES})

install(TARGETS csrs_transform
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/csrs_transform
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_WRITE GROUP_EXECUTE WORLD_READ WORLD_WRITE WORLD_EXECUTE
        )
#install(FILES ${_HDRS} DESTINATION include/csrs_tranform)