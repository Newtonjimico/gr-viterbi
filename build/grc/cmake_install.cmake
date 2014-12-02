# Install script for directory: /home/jagdish/Desktop/gr-viterbi/grc

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
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gnuradio/grc/blocks" TYPE FILE FILES
    "/home/jagdish/Desktop/gr-viterbi/grc/viterbi_vitsova.xml"
    "/home/jagdish/Desktop/gr-viterbi/grc/viterbi_convdec.xml"
    "/home/jagdish/Desktop/gr-viterbi/grc/viterbi_interleave_ff.xml"
    "/home/jagdish/Desktop/gr-viterbi/grc/viterbi_convenc_bf.xml"
    "/home/jagdish/Desktop/gr-viterbi/grc/viterbi_zeropad_bb.xml"
    "/home/jagdish/Desktop/gr-viterbi/grc/viterbi_bercount_b.xml"
    "/home/jagdish/Desktop/gr-viterbi/grc/viterbi_awgn_cc.xml"
    "/home/jagdish/Desktop/gr-viterbi/grc/viterbi_gmskmod_bc.xml"
    "/home/jagdish/Desktop/gr-viterbi/grc/viterbi_nrz_encoder.xml"
    "/home/jagdish/Desktop/gr-viterbi/grc/viterbi_gmskmf_cf.xml"
    "/home/jagdish/Desktop/gr-viterbi/grc/viterbi_addgsmtr26_bb.xml"
    "/home/jagdish/Desktop/gr-viterbi/grc/viterbi_dropfirstN_ff.xml"
    "/home/jagdish/Desktop/gr-viterbi/grc/viterbi_nrz_decode_fb.xml"
    "/home/jagdish/Desktop/gr-viterbi/grc/viterbi_hist_test.xml"
    "/home/jagdish/Desktop/gr-viterbi/grc/viterbi_framer_bb.xml"
    "/home/jagdish/Desktop/gr-viterbi/grc/viterbi_demod_cf.xml"
    "/home/jagdish/Desktop/gr-viterbi/grc/viterbi_sync_cc.xml"
    "/home/jagdish/Desktop/gr-viterbi/grc/viterbi_dropfirstN_bb.xml"
    "/home/jagdish/Desktop/gr-viterbi/grc/viterbi_addfirstN_bb.xml"
    "/home/jagdish/Desktop/gr-viterbi/grc/viterbi_channel_dop_cc.xml"
    "/home/jagdish/Desktop/gr-viterbi/grc/viterbi_doubleS_channel_dop_cc.xml"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

