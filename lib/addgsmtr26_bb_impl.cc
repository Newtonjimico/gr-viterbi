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
#include "addgsmtr26_bb_impl.h"

namespace gr {
  namespace viterbi {

    addgsmtr26_bb::sptr
    addgsmtr26_bb::make()
    {
      return gnuradio::get_initial_sptr
        (new addgsmtr26_bb_impl());
    }

    /*
     * The private constructor
     */
    addgsmtr26_bb_impl::addgsmtr26_bb_impl()
      : gr::block("addgsmtr26_bb",
              gr::io_signature::make(1,1, sizeof(char)),
              gr::io_signature::make(1,1, sizeof(char)))
    {
	set_gsmtr26();  // d_gsmtr[26]
}

    /*
     * Our virtual destructor.
     */
    addgsmtr26_bb_impl::~addgsmtr26_bb_impl()
    {
    }

    void
    addgsmtr26_bb_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = noutput_items;
    }

    int
    addgsmtr26_bb_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
       const char *in = (const char *) input_items[0];
       char *out = (char *) output_items[0];
	static char gsmtrsent=0;
		if (gsmtrsent<26){
			out[0]=d_gsmtr[gsmtrsent]; gsmtrsent++;
			consume_each (0); 
			//std::cout<<"training being sent "<<(int)gsmtrsent<<"\t"<<noutput_items<<"\n"<<std::endl;
			return 1;			
			}
		else{
		//std::cout<<"26 bits training appended in the beginning, nout="<<noutput_items<<"\n"<<std::endl;
			for(int k=0;k<noutput_items;k++)
			out[k]=in[k];
			consume_each (noutput_items);
			return noutput_items;
		}
      
        
    }

  } /* namespace viterbi */
} /* namespace gr */

