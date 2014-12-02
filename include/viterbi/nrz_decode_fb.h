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


#ifndef INCLUDED_VITERBI_NRZ_DECODE_FB_H
#define INCLUDED_VITERBI_NRZ_DECODE_FB_H

#include <viterbi/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace viterbi {

    /*!
     * \brief <+description of block+>
     * \ingroup viterbi
     *
     */
    class VITERBI_API nrz_decode_fb : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<nrz_decode_fb> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of viterbi::nrz_decode_fb.
       *
       * To avoid accidental use of raw pointers, viterbi::nrz_decode_fb's
       * constructor is in a private implementation
       * class. viterbi::nrz_decode_fb::make is the public interface for
       * creating new instances.
       */
      static sptr make(int set0);
    };

  } // namespace viterbi
} // namespace gr

#endif /* INCLUDED_VITERBI_NRZ_DECODE_FB_H */

