# Configure this build to use the PDAL and PROJ versions in the conda env
cmake -B ./build -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=$PREFIX -DCMAKE_INSTALL_PREFIX=$PREFIX

# Build and install
cmake --build ./build --config Release -j5
cmake --install ./build