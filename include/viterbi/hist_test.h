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


#ifndef INCLUDED_VITERBI_HIST_TEST_H
#define INCLUDED_VITERBI_HIST_TEST_H

#include <viterbi/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace viterbi {

    /*!
     * \brief <+description of block+>
     * \ingroup viterbi
     *
     */
    class VITERBI_API hist_test : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<hist_test> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of viterbi::hist_test.
       *
       * To avoid accidental use of raw pointers, viterbi::hist_test's
       * constructor is in a private implementation
       * class. viterbi::hist_test::make is the public interface for
       * creating new instances.
       */
      static sptr make(int L);
    };

  } // namespace viterbi
} // namespace gr

#endif /* INCLUDED_VITERBI_HIST_TEST_H */

