# Copyright 2011,2012 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

########################################################################
# Setup library
########################################################################
include(GrPlatform) #define LIB_SUFFIX

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})
list(APPEND viterbi_sources
    vitsova_impl.cc
    convdec_impl.cc
    interleave_ff_impl.cc
    convenc_bf_impl.cc
    zeropad_bb_impl.cc
    bercount_b_impl.cc
    awgn_cc_impl.cc
    gmskmod_bc_impl.cc
    nrz_encoder_impl.cc
    gmskmf_cf_impl.cc
    addgsmtr26_bb_impl.cc
    dropfirstN_ff_impl.cc
    nrz_decode_fb_impl.cc
    hist_test_impl.cc
    framer_bb_impl.cc
    demod_cf_impl.cc
    sync_cc_impl.cc
    dropfirstN_bb_impl.cc
    addfirstN_bb_impl.cc
    channel_dop_cc_impl.cc
    doubleS_channel_dop_cc_impl.cc )

add_library(gnuradio-viterbi SHARED ${viterbi_sources})
target_link_libraries(gnuradio-viterbi ${Boost_LIBRARIES} ${GNURADIO_RUNTIME_LIBRARIES})
set_target_properties(gnuradio-viterbi PROPERTIES DEFINE_SYMBOL "gnuradio_viterbi_EXPORTS")

########################################################################
# Install built library files
########################################################################
install(TARGETS gnuradio-viterbi
    LIBRARY DESTINATION lib${LIB_SUFFIX} # .so/.dylib file
    ARCHIVE DESTINATION lib${LIB_SUFFIX} # .lib file
    RUNTIME DESTINATION bin              # .dll file
)

########################################################################
# Build and register unit test
########################################################################
include(GrTest)

include_directories(${CPPUNIT_INCLUDE_DIRS})

list(APPEND test_viterbi_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/test_viterbi.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_viterbi.cc
)

add_executable(test-viterbi ${test_viterbi_sources})

target_link_libraries(
  test-viterbi
  ${GNURADIO_RUNTIME_LIBRARIES}
  ${Boost_LIBRARIES}
  ${CPPUNIT_LIBRARIES}
  gnuradio-viterbi
)

GR_ADD_TEST(test_viterbi test-viterbi)
