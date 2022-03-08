# Put FindPROJ.cmake in the search path
list(APPEND CMAKE_MODULE_PATH ./cmake)

find_package(PROJ 8.0.1 REQUIRED)

# Get a list of all the source files
file(GLOB_RECURSE _HDRS "include/*.h")
file(GLOB_RECURSE _SRCS "src/*.cpp" "src/*.h")

# Set the library target
add_library(csrs_transform SHARED ${_HDRS} ${_SRCS})

# Allow anything in include to be included
target_include_directories(csrs_transform PUBLIC include)

# Link PROJ
target_link_libraries(csrs_transform PRIVATE ${PROJ_LIBRARIES})

install(TARGETS csrs_transform DESTINATION lib
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_WRITE GROUP_EXECUTE WORLD_READ WORLD_WRITE WORLD_EXECUTE)
install(FILES ${_HDRS} DESTINATION include/csrs_tranform)