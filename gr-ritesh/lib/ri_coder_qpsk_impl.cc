/* -*- c++ -*- */
/*
 * Copyright 2017 Venkat Ritesh Ghanta
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

#include <iostream>
#include <fstream>

#include <gnuradio/io_signature.h>
#include "ri_coder_qpsk_impl.h"

namespace gr {
  namespace ritesh {

    ri_coder_qpsk::sptr
    ri_coder_qpsk::make(int N, int M)
    {
      return gnuradio::get_initial_sptr
        (new ri_coder_qpsk_impl(N, M));
    }

    /*
     * The private constructor
     */
    ri_coder_qpsk_impl::ri_coder_qpsk_impl(int N, int M)
      : gr::sync_interpolator("ri_coder_qpsk",
              gr::io_signature::make(1, 1, sizeof(char)),
              gr::io_signature::make(1, 1, sizeof(gr_complex)), N)
    {
      qpsk_constellation[0] = gr_complex(1, 1);
      qpsk_constellation[1] = gr_complex(1, -1);
      qpsk_constellation[2] = gr_complex(-1, 1);
      qpsk_constellation[3] = gr_complex(-1, -1);
      eM = M;
      update_n(N);
      codebook = new gr_complex[eM * eN];
      update_codebook();
    }

    void ri_coder_qpsk_impl::update_n(int enn) {
      eN = enn;
    }

    /*
     * Our virtual destructor.
     */
    ri_coder_qpsk_impl::~ri_coder_qpsk_impl()
    {
    }

    int
    ri_coder_qpsk_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const char *in = (const char *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];

      // Do <+signal processing+>
      int i = 0;
      while(i < noutput_items) {
        for(int l = 0; l < eN; l++) {
          out[i + l] = codebook[(in[i/eN] * eN) + l];
          //std::cout << codebook[(in[i/eN] * eN) + l];
        }
        // std::cout << "input was: " << (int)in[i/eN] << std::endl;
        i += eN;
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

    void ri_coder_qpsk_impl::update_codebook() {
      //std::cout << "Generating codebook for the following values:" << std::endl;
      //std::cout << "M: " << eM << "\nN: " << eN << "\nvar: " << var << std::endl;
      gr::random randobj(0);
      randobj.set_integer_limits(0, 4);
      gr_complex temp;
      delete codebook;
      std::ofstream cbfile;
      cbfile.open("codebook_file", std::ios::trunc);
      codebook = new gr_complex[eM * eN];
      for(int i = 0; i < (eM * eN); i++) {
        codebook[i] = qpsk_constellation[randobj.ran_int()];
        if((i + 1)%eN == 0) { // indicates end of a codeword
          int check = check_repeat(i);
          if(i == check) {
            for(int k = (i - eN + 1); k <= i; k++) {
              temp = codebook[k];
              cbfile << temp.real() << " " << temp.imag() << "\n";
            }
          }
          else {
            i = (-1 * check) - 1;
          }
        }
      }
      cbfile.close();
    }

    int ri_coder_qpsk_impl::check_repeat(int index) {
      int k, cur_cw = index - eN + 1;
      for(int j = 0; j < (cur_cw/eN); j++) {
        for(k = 0; k < eN; k++) {
          if(codebook[(j * eN) + k] != codebook[(cur_cw * eN) + k]) {
            k = eN + 1;
          }
        }
        if(k == eN) {
          return (-1 * cur_cw); // negative allowed for eN = 1 case
        }
      }
      return index;
    }

  } /* namespace ritesh */
} /* namespace gr */
