INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_RITESH ritesh)

FIND_PATH(
    RITESH_INCLUDE_DIRS
    NAMES ritesh/api.h
    HINTS $ENV{RITESH_DIR}/include
        ${PC_RITESH_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    RITESH_LIBRARIES
    NAMES gnuradio-ritesh
    HINTS $ENV{RITESH_DIR}/lib
        ${PC_RITESH_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(RITESH DEFAULT_MSG RITESH_LIBRARIES RITESH_INCLUDE_DIRS)
MARK_AS_ADVANCED(RITESH_LIBRARIES RITESH_INCLUDE_DIRS)

