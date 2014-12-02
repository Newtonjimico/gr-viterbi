INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_VITERBI viterbi)

FIND_PATH(
    VITERBI_INCLUDE_DIRS
    NAMES viterbi/api.h
    HINTS $ENV{VITERBI_DIR}/include
        ${PC_VITERBI_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREEFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    VITERBI_LIBRARIES
    NAMES gnuradio-viterbi
    HINTS $ENV{VITERBI_DIR}/lib
        ${PC_VITERBI_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(VITERBI DEFAULT_MSG VITERBI_LIBRARIES VITERBI_INCLUDE_DIRS)
MARK_AS_ADVANCED(VITERBI_LIBRARIES VITERBI_INCLUDE_DIRS)

