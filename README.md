# Reproject CSRS

This program converts Lidar point coordinates in .las, .sbet, and other lidar file formats from various ITRF realizations to NAD83(CSRS).

It does this with high accuracy by using the official Helmert transformation parameters and NAD83(CSRS) v7 Velocity Grid (NAD83v70VG) from Natural Resources Canada
([available here](https://webapp.geod.nrcan.gc.ca/geod/data-donnees/transformations.php?locale=en)).

## Installation

### Installation prerequisites

- [Git](https://git-scm.com/downloads) (for downloading source code)
- [PROJ 7 or 8](https://proj.org/download.html)
- [PDAL ~2.2](https://pdal.io/download.html)
- [CMake 3.16+](https://cmake.org/install/)

On Ubuntu install all dependencies with 
```shell
sudo apt install git libproj-dev libpdal-dev cmake
```

### Building from source

```shell
# Download the source code
git clone https://github.com/HakaiInstitute/reproject_csrs.git

cd reproject_csrs

# Configure CMake
cmake -B ./build -DCMAKE_BUILD_TYPE=Release

# Build
cmake --build ./build --config Release

# Copy the produced dynamic lib to your prefered location (.so on Linux, .dll on Windows)
cp ./build/libpdal_plugin_filter_reprojectcsrs.so ~/

cd -
```

## Usage
The produced dynamic library file implements a PDAL Filter module called `filters.reprojectcsrs` that can be used in any [PDAL Pipeline](https://pdal.io/pipeline.html)
workflow. An example pipeline.json for running just this reproject_csrs library would looks like this:

```json
[
  "your-input-file.laz",
  {
    "type": "filters.reprojectcsrs",
    "s_ref_frame": "itrf14",
    "s_crs": "EPSG:4326",
    "t_crs": "EPSG:4954",
    "s_epoch": 2021.000,
    "t_epoch": 1997.000
  },
  "output.laz"
]
```

Once you define workflow in a .json file (as above), run it with `pdal pipeline pipeline.json` in the command line.

If PDAL complains that `PDAL: Couldn't create filter stage of type 'filters.reprojectcsrs'`, make sure the built `libpdal_plugin_filter_reprojectcsrs.so` 
or `libpdal_plugin_filter_reprojectcsrs.dll` file is in the PDAL search path. By default, PDAL will search the following paths for plugins 
`.`, `./lib`, `../lib`, `./bin`, `../bin`. You can also add the file to the search path by defining the `PDAL_DRIVER_PATH` environment variable 
to point to the directory containing the plugin. [More information here](https://pdal.io/faq.html).

You can get the documentation for this filter using ` pdal --options=filters.reprojectcsrs`. It will print the following message:
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
      The source reference frame of the coordinates [itrf88|itrf89|itrf90|itrf91|itrf92|itrf93|itrf94|itrf96|itrf97|itrf00|itrf05|itrf08|itrf14]

  s_crs [EPSG:4326]
      The source CRS in 'AUTHORITY:CODE' format, or as a proj string like '+proj=longlat +datum=WGS84'or a CRS name found in the proj database

  t_crs [EPSG:4954]
      The target CRS in 'AUTHORITY:CODE' format, or as a proj string like '+proj=longlat +datum=WGS84' or a CRS name found in the proj database

  s_epoch [2010]
      The reference epoch for the input in decimal year format, e.g. '2020.5342'

  t_epoch
      Optional reference epoch for the output in decimal year format, e.g. '1997.0000'. By default, the output epoch will match the s_epoch value.
```

## Files
- `src/`
  - `PdalFilterReprojectCSRS.cpp` - The main library file that implements a PDAL Filter
  - `CSRSTransform.cpp` - Object that instantiates the PROJ pipeline to convert individual coordinates
  - `HelmertFactory.cpp` - Factory for creating a proj transform based on a specified ITRF reference frame
- `include/`
  - `constants.h` - Some constants used throughout the program
  - `Transform.h` - An abstract base class used by the CSRSTransform class
  
---
#### Acknowledgements

Thanks to [Rob Skelly](https://github.com/rskelly) for providing code to their [las2csrs](https://github.com/rskelly/las2csrs) program, which was very helpful
for developing this tool.
