find_package(pybind11 CONFIG REQUIRED)

pybind11_add_module(csrspy MODULE csrspy.cpp)

target_link_libraries(csrspy PUBLIC csrs_transform)

# Install shared lib to appropriate python site-packages directory
find_package(Python COMPONENTS Interpreter Development)
install(TARGETS csrspy DESTINATION ${Python_SITELIB})