cmake -B ./build^
 -DCMAKE_BUILD_TYPE=Release^
 -DCMAKE_PREFIX_PATH="%PREFIX%"^
 -DCMAKE_INSTALL_PREFIX="%SP_DIR%"^
 -G="%CMAKE_GENERATOR%"

# Build and install
cmake --build ./build --config Release -j "%CPU_COUNT%"

cmake --install ./build
if errorlevel 1 exit 1
