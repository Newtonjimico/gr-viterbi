/* -*- c++ -*- */
/* 
 * Copyright 2014 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "awgn_cc_impl.h"
#include <complex>
#define SQRT1o2 0.707106781186548
namespace gr {
  namespace viterbi {

    awgn_cc::sptr
    awgn_cc::make(float std, int seed)
    {
      return gnuradio::get_initial_sptr
        (new awgn_cc_impl(std, seed));
    }

    /*
     * The private constructor
     */
    awgn_cc_impl::awgn_cc_impl(float std, int seed)
      : gr::sync_block("awgn_cc",
              gr::io_signature::make(1,1, sizeof(gr_complex)),
              gr::io_signature::make(1,1, sizeof(gr_complex))),d_std(std*SQRT1o2), d_seed(seed), d_rng( random((long) seed))
    {}

    /*
     * Our virtual destructor.
     */
    awgn_cc_impl::~awgn_cc_impl()
    {
    }

    int
    awgn_cc_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const gr_complex *in = (const gr_complex *) input_items[0];
        gr_complex *out = (gr_complex *) output_items[0];

for (int i = 0; i < noutput_items; i++)
   out[i] = in[i] +  d_rng.rayleigh_complex() * (float) d_std;
        return noutput_items;
    }

  } /* namespace viterbi */
} /* namespace gr */

