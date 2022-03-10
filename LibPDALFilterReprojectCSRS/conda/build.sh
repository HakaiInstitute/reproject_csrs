# Configure this build to use the PDAL and PROJ versions in the conda env
cmake -B ./build \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_PREFIX_PATH="$PREFIX" \
  -DCMAKE_INSTALL_PREFIX="$PREFIX" \
  -DCMAKE_TOOLCHAIN_FILE="${RECIPE_DIR}/cross-linux.cmake" \
  -DCMAKE_INSTALL_LIBDIR=lib \
  -DBUILD_SHARED_LIBS=ON

# Build and install
cmake --build ./build --config Release -j"${CPU_COUNT}"
cmake --install ./build