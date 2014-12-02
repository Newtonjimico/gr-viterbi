# Install script for directory: /home/jagdish/Desktop/gr-viterbi/include/viterbi

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Release")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/viterbi" TYPE FILE FILES
    "/home/jagdish/Desktop/gr-viterbi/include/viterbi/api.h"
    "/home/jagdish/Desktop/gr-viterbi/include/viterbi/vitsova.h"
    "/home/jagdish/Desktop/gr-viterbi/include/viterbi/convdec.h"
    "/home/jagdish/Desktop/gr-viterbi/include/viterbi/interleave_ff.h"
    "/home/jagdish/Desktop/gr-viterbi/include/viterbi/convenc_bf.h"
    "/home/jagdish/Desktop/gr-viterbi/include/viterbi/zeropad_bb.h"
    "/home/jagdish/Desktop/gr-viterbi/include/viterbi/bercount_b.h"
    "/home/jagdish/Desktop/gr-viterbi/include/viterbi/awgn_cc.h"
    "/home/jagdish/Desktop/gr-viterbi/include/viterbi/gmskmod_bc.h"
    "/home/jagdish/Desktop/gr-viterbi/include/viterbi/nrz_encoder.h"
    "/home/jagdish/Desktop/gr-viterbi/include/viterbi/gmskmf_cf.h"
    "/home/jagdish/Desktop/gr-viterbi/include/viterbi/addgsmtr26_bb.h"
    "/home/jagdish/Desktop/gr-viterbi/include/viterbi/dropfirstN_ff.h"
    "/home/jagdish/Desktop/gr-viterbi/include/viterbi/nrz_decode_fb.h"
    "/home/jagdish/Desktop/gr-viterbi/include/viterbi/hist_test.h"
    "/home/jagdish/Desktop/gr-viterbi/include/viterbi/framer_bb.h"
    "/home/jagdish/Desktop/gr-viterbi/include/viterbi/demod_cf.h"
    "/home/jagdish/Desktop/gr-viterbi/include/viterbi/sync_cc.h"
    "/home/jagdish/Desktop/gr-viterbi/include/viterbi/dropfirstN_bb.h"
    "/home/jagdish/Desktop/gr-viterbi/include/viterbi/addfirstN_bb.h"
    "/home/jagdish/Desktop/gr-viterbi/include/viterbi/channel_dop_cc.h"
    "/home/jagdish/Desktop/gr-viterbi/include/viterbi/doubleS_channel_dop_cc.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

