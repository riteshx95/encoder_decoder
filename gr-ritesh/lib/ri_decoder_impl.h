/* -*- c++ -*- */
/*
 * Copyright 2017 <+YOU OR YOUR COMPANY+>.
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

#ifndef INCLUDED_RITESH_RI_DECODER_IMPL_H
#define INCLUDED_RITESH_RI_DECODER_IMPL_H

#include <ritesh/ri_decoder.h>

namespace gr {
  namespace ritesh {

    class ri_decoder_impl : public ri_decoder
    {
     private:
      // Nothing to declare in this block.
      int eN, eM, ber, total, cur_count;
      gr_complex *codebook;

     public:
      ri_decoder_impl(int N, int M);
      ~ri_decoder_impl();


      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
      char decode(gr_complex *yy);
    };

  } // namespace ritesh
} // namespace gr

#endif /* INCLUDED_RITESH_RI_DECODER_IMPL_H */
