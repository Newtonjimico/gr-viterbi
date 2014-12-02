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
#include "bercount_b_impl.h"

namespace gr {
  namespace viterbi {

    bercount_b::sptr
    bercount_b::make(char *filename, bool append, float ebno, long int L)
    {
      return gnuradio::get_initial_sptr
        (new bercount_b_impl(filename, append, ebno, L));
    }

    /*
     * The private constructor
     */
    bercount_b_impl::bercount_b_impl(char *filename, bool append, float ebno, long int L)
      : gr::sync_block("bercount_b",
              gr::io_signature::make(2,2, sizeof(char)),
              gr::io_signature::make(0, 0, 0)), d_ebno(ebno), d_L(L)
    {

	if (append){
		d_file=fopen(filename,"a");
		if(d_file==NULL)
		printf("\n ERROR CANT OPEN FILE\n");
		}
	else{
		d_file=fopen(filename,"w");
		if(d_file==NULL)
		printf("\n ERROR CANT OPEN FILE\n");
		}

}

    /*
     * Our virtual destructor.
     */
    bercount_b_impl::~bercount_b_impl()
    {
//fclose(d_file); 
    }

    int    bercount_b_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
	static long int cnt=0;
	static long int be=0;
	static int m=0;
       //  printf("static value %ld %ld\n", cnt, be);
        const char *in = (const char *) input_items[0];
	const char *in1 = (const char *) input_items[1];
	for(int j=0;j<noutput_items;j++){
		cnt++;
//printf("%ld, %ld, %d\t%d\n", cnt, d_L, (int)in[j], (int)in1[j]);
		if(in[j]!=in1[j]){
		 be++;
		}
		if (cnt==d_L){	
			//printf("\t\t\t\tinside");
			m++;	
			double ber= (be*1.0)/(d_L*1.0);
			if(fork()==0){		
			int f=fprintf(d_file, "%2.1f\t%1.4e\t%ld\t%ld\n",d_ebno,ber,be,d_L);
			fclose(d_file);
			printf("\n \t\t wrote %2.1f\t%1.4e\t%ld\t%ld\n",d_ebno,ber,be,d_L);
			exit(0);
					}
		
			//printf("%2.1f\t%1.4e\t%ld\t%ld\t%d\n",d_ebno,ber,be,d_L, m);
			
			cnt=0;be=0;
			}
		}
	//printf("berc %d\n", noutput_items);
        return noutput_items;
    }

  } /* namespace viterbi */
} /* namespace gr */

