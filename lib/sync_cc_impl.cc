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
#include "sync_cc_impl.h"

namespace gr {
  namespace viterbi {

    sync_cc::sptr
    sync_cc::make(int nslot,int fcchsize,int schsize,int dssize)
    {
      return gnuradio::get_initial_sptr
        (new sync_cc_impl(nslot,fcchsize,schsize,dssize));
    }

    /*
     * The private constructor
     */
    sync_cc_impl::sync_cc_impl(int nslot,int fcchsize,int schsize,int dssize)
      : gr::block("sync_cc",
              gr::io_signature::make(1,1, sizeof(gr_complex)),
              gr::io_signature::make(1,1, sizeof(gr_complex))), d_nslot(nslot), d_fcchsize(fcchsize),d_schsize(schsize),d_dssize(dssize),
d_rng( random((long) 124))
    {	
	 	
	initialize();		// d_framesize= 64+32+32*nslot
	set_output_multiple(d_framemfcchsize); //give output only sch32 and data slots per frame
	std::cout<<"omultiple"<<d_framemfcchsize<<std::endl;
	
	}

    /*
     * Our virtual destructor.
     */
    sync_cc_impl::~sync_cc_impl()
    {
	std::cout<<"Killed-fmax="<<d_fmax<<"Hz\n";
	sleep(2);
    }

    void
    sync_cc_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
	ninput_items_required[0] = noutput_items/(d_framemfcchsize)*d_framesize+5; // input item should be multiple of d_framesize

    }

    int
    sync_cc_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        const gr_complex *in = (const gr_complex *) input_items[0];
        gr_complex *out = (gr_complex *) output_items[0];
	//std::cout<<"nout"<<noutput_items<<"frmprocessed"<<noutput_items/d_framemfcchsize<<std::endl;
	

	for(int j=0;j<noutput_items/(d_framemfcchsize);j++){
		get_freqsync(&in[j*d_framesize+d_syncindex]);
		get_timesync(&in[j*d_framesize+d_syncindex+d_fcchsize], &out[j*d_framemfcchsize]);
		//std::cout<<d_syncindex<<"\t"<<d_framesize*noutput_items/(d_framemfcchsize)+d_syncindex<<" nin="<<(int)ninput_items[0]<<std::endl;
		}

	//for(int j=0;j<noutput_items;j++)
	//	std::cout<<"op"<<out[j]<<std::endl;
	//std::cout<<"consumed"<<d_framesize*noutput_items/(d_framemfcchsize)+d_syncindex<<std::endl;
	//std::cout<<"\t"<<d_syncindex<<"\t"<<d_wo_est<<std::endl;
        consume_each (d_framesize*noutput_items/(d_framemfcchsize)+d_syncindex);
	d_syncindex=0;
        return noutput_items;
    }

  } /* namespace viterbi */
} /* namespace gr */

