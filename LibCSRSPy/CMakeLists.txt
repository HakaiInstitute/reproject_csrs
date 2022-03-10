set(LIBNAME csrspy)

add_subdirectory(extern/pybind11)
pybind11_add_module(${LIBNAME} MODULE src/csrspy.cpp)

#find_library(CSRS_TRANSFORM NAMES csrs_transform)
add_dependencies(${LIBNAME} csrs_transform)
target_link_libraries(${LIBNAME} LINK_PUBLIC csrs_transform)

# Install shared lib to appropriate python site-packages directory
find_package(Python COMPONENTS Interpreter Development REQUIRED)
install(TARGETS ${LIBNAME}
        DESTINATION .
#        LIBRARY DESTINATION ${CMAKE_PREFIX_PATH}/Lib/site-packages
#        DESTINATION ${Python_SITELIB}
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_WRITE GROUP_EXECUTE WORLD_READ WORLD_WRITE WORLD_EXECUTE
        )