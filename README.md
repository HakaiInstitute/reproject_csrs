# Reproject CSRS

Convert geodetic coordinates to NAD83 (CSRS).

This program converts Lidar point coordinates in .las, .sbet, and other lidar file formats from various ITRF realizations to NAD83(CSRS)
using the Helmert transformation parameters and NAD83(CSRS) v7 Velocity Grid (NAD83v70VG) provided by Natural Resources Canada
([available here](https://webapp.geod.nrcan.gc.ca/geod/data-donnees/transformations.php?locale=en)).

## Installation

### Prerequisites

1. [Git](https://git-scm.com/downloads)
2. [PROJ ~8.1](https://proj.org/download.html)
3. [PDAL ~2.3](https://pdal.io/download.html)
4. [CMake](https://cmake.org/install/)

### Building

```shell
git clone https://github.com/HakaiInstitute/reproject_csrs.git

cd reproject_csrs

# Configure CMake
cmake -B ./build -DCMAKE_BUILD_TYPE=Release

# Build
cmake --build ./build --config Release

# Copy the produced dynamic lib to your prefered location (.so on Linux, .dll on Windows)
cp ./build/libpdal_plugin_filter_reprojectcsrs.so ~/

```

## Usage
The produced dynamic library is a PDAL filter module that can be used in any [PDAL Pipeline](https://pdal.io/pipeline.html)
workflow. An example pipeline file is included in this repository [here](https://github.com/HakaiInstitute/reproject_csrs/blob/main/pdal_pipeline_example.json)

Simply define your workflow and run it using `pdal pipeline pipeline-def.json`.

If PDAL complains that `PDAL: Couldn't create filter stage of type 'filters.reprojectcsrs'`, make sure the built .so or .dll
file is in PDALs search path. By default, PDAL will search the following paths for plugins `.`, `./lib`, `../lib`, `./bin`, `../bin`.
You can also add the file to the search path by defining the `PDAL_DRIVER_PATH` environment variable to point to the directory containing
the plugin. [More information here](https://pdal.io/faq.html).

You can get the documentation for this filter using ` PDAL_DRIVER_PATH=./build pdal --options=filters.reprojectcsrs`. It will print the following message:
```text
filters.reprojectcsrs -- https://github.com/HakaiInstitute/hakai-las2csrs
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  user_data
      User JSON

  log
      Debug output filename

  option_file
      File from which to read additional options

  where
      Expression describing points to be passed to this filter

  where_merge [auto]
      If 'where' option is set, describes how skipped points should be merged with kept points in standard mode.

  s_ref_frame [itrf14]
      The source reference frame of the coordinates (e.g. 'itrf14')

  s_crs [EPSG:4326]
      The source CRS in 'AUTHORITY:CODE' format, or as a proj string like '+proj=longlat +datum=WGS84'or a CRS name found in the proj database

  t_crs [EPSG:4954]
      The target CRS in 'AUTHORITY:CODE' format, or as a proj string like '+proj=longlat +datum=WGS84' or a CRS name found in the proj database

  s_epoch [2010]
      The reference epoch for the input in decimal year format, e.g. '2020.5342'

  t_epoch [2010]
      The reference epoch for the output in decimal year format, e.g. '2020.5342'
```