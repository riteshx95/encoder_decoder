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


#ifndef INCLUDED_RITESH_RI_CODER_QPSK_H
#define INCLUDED_RITESH_RI_CODER_QPSK_H

#include <ritesh/api.h>
#include <gnuradio/sync_interpolator.h>

namespace gr {
  namespace ritesh {

    /*!
     * \brief <+description of block+>
     * \ingroup ritesh
     *
     */
    class RITESH_API ri_coder_qpsk : virtual public gr::sync_interpolator
    {
     public:
      typedef boost::shared_ptr<ri_coder_qpsk> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of ritesh::ri_coder_qpsk.
       *
       * To avoid accidental use of raw pointers, ritesh::ri_coder_qpsk's
       * constructor is in a private implementation
       * class. ritesh::ri_coder_qpsk::make is the public interface for
       * creating new instances.
       */
      static sptr make(int N, int M);
    };

  } // namespace ritesh
} // namespace gr

#endif /* INCLUDED_RITESH_RI_CODER_QPSK_H */

