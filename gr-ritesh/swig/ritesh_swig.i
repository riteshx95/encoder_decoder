/* -*- c++ -*- */

#define RITESH_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "ritesh_swig_doc.i"

%{
#include "ritesh/ri_coder.h"
#include "ritesh/ri_decoder.h"
#include "ritesh/ri_coder_qpsk.h"
%}


%include "ritesh/ri_coder.h"
GR_SWIG_BLOCK_MAGIC2(ritesh, ri_coder);
%include "ritesh/ri_decoder.h"
GR_SWIG_BLOCK_MAGIC2(ritesh, ri_decoder);
%include "ritesh/ri_coder_qpsk.h"
GR_SWIG_BLOCK_MAGIC2(ritesh, ri_coder_qpsk);
