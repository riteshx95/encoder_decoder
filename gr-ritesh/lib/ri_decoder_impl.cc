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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <iostream>
#include <fstream>

//#include <math.h>
#include <gnuradio/io_signature.h>
#include "ri_decoder_impl.h"

namespace gr {
  namespace ritesh {

    ri_decoder::sptr
    ri_decoder::make(int N, int M)
    {
      return gnuradio::get_initial_sptr
        (new ri_decoder_impl(N, M));
    }

    /*
     * The private constructor
     */
    ri_decoder_impl::ri_decoder_impl(int N, int M)
      : gr::sync_decimator("ri_decoder",
              gr::io_signature::make(1, 2, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(char)), N)
    {
      total = 0;
      cur_count = 0;
      eN = N;
      eM = M;
      codebook = new gr_complex[eM * eN];
    }

    /*
     * Our virtual destructor.
     */
    ri_decoder_impl::~ri_decoder_impl()
    {
    }

    int
    ri_decoder_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      const gr_complex *in2 = (const gr_complex *) input_items[1];
      char *out = (char *) output_items[0];

      int k;
      std::ifstream cbfile("codebook_file");
      if(cbfile.is_open()) {
        delete codebook;
        codebook = new gr_complex[eM * eN];
        float a, b;
        //std::cout << "Codebook(R): " << std::endl;
        for(k = 0; k < (eM * eN); k++) {
            cbfile >> a >> b;
            codebook[k] = gr_complex(a, b);
            //std::cout << codebook[k] << std::endl;
        }
        cbfile.close();
      }

      // std::cout << "its coming here\n" << std::endl;

      // Do <+signal processing+>
      gr_complex y[eN];
      gr_complex y2[eN];
      int l = 0;
      for(int i = 0; i < noutput_items; i++) {
        //std::cout << "running " << i << std::endl;
        for(int j = 0; j < eN; j++) {
          y[j] = in[l];
          y2[j] = in2[l];
          l++;
        }
        // eN length vector acquired
        std::cout << "rec: " << std::endl;
        for(int j = 0; j < eN; j++) {
          std::cout << y[j] << std::endl;
          std::cout << y2[j] << std::endl;
        }
        out[i] = decode(y);
        char temp;
        temp = decode(y2);

        total++;
        if((temp - out[i]) != 0) {
          cur_count++;
          //std::cout << "error count: " << cur_count <<std::endl;
          //std::cout << "total: " << total <<std::endl;
        }
        if(total == 16000) {
          ber = 2 * cur_count;
          std::cout << "ber: " << ber << " bits/second" << std::endl;
          total = 0;
          cur_count = 0;
        }

        //std::cout << "sent: " << (int)temp << std::endl;
        //std::cout << "decoded: " << (int)out[i] << std::endl;
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

    char ri_decoder_impl::decode(gr_complex *yy) {
      float min = 1000, temp;
      char decoded;
      for(int ii = 0; ii < eM; ii++) {
        temp = 0;
        for(int j = 0; j < eN; j++) {
          gr_complex x;
          float xf;
          x = yy[j] - codebook[ii*eN + j];
          xf = (x.real() * x.real()) + (x.imag() * x.imag());
          // x = sqrt(x);
          temp += xf;
        }
        temp = sqrt(temp);
        if(temp < min) {
          min = temp;
          decoded = (char)ii;
        }
      }
      return decoded;
    }

  } /* namespace ritesh */
} /* namespace gr */
