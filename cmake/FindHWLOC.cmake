find_path(
    HWLOC_INCLUDE_DIR
    NAMES hwloc.h
    PATHS "${KITTENPAW_DEPS}" ENV "KITTENPAW_DEPS"
    PATH_SUFFIXES "include"
    NO_DEFAULT_PATH
)

find_path(HWLOC_INCLUDE_DIR NAMES hwloc.h)

find_library(
    HWLOC_LIBRARY
    NAMES hwloc.a hwloc libhwloc
    PATHS "${KITTENPAW_DEPS}" ENV "KITTENPAW_DEPS"
    PATH_SUFFIXES "lib"
    NO_DEFAULT_PATH
)

find_library(HWLOC_LIBRARY NAMES hwloc.a hwloc libhwloc)

set(HWLOC_LIBRARIES ${HWLOC_LIBRARY})
set(HWLOC_INCLUDE_DIRS ${HWLOC_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(HWLOC DEFAULT_MSG HWLOC_LIBRARY HWLOC_INCLUDE_DIR)
