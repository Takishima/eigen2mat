// This file is part of eigen2mat, a simple C++ library to use
// Eigen with MATLAB's MEX files
//
// Copyright (C) 2013 Nguyen Damien <damien.nguyen@a3.epfl.ch>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef TENSOR_BLOCK_HPP_INCLUDED
#define TENSOR_BLOCK_HPP_INCLUDED

#include "eigen2mat/utils/macros.hpp"
#include "eigen2mat/utils/include_mex"

#include <vector>

namespace eigen2mat {
     CLANG_IGNORE_WARNINGS_ONE(-Wsign-conversion)

     template <typename tensor_t>
     class tensor_block_t
     {
	  typedef std::size_t size_t;
	  typedef typename tensor_t::value_type value_type;
	  typedef typename tensor_t::iterator iterator;
	  typedef typename tensor_t::const_iterator const_iterator;
	  typedef typename tensor_t::reverse_iterator reverse_iterator;
	  typedef typename tensor_t::const_reverse_iterator const_reverse_iterator;

     public:
	  tensor_block_t(tensor_t& t, 
			 size_t start,
			 size_t n_mat)
	       : begin_(t.begin() + start), end_(t.begin() + start + n_mat)
	       {}

	  value_type& operator[] (size_t k)
	       { 
#ifdef EIGEN2MAT_RANGE_CHECK
		    if (k > (end_ - begin_) ) {
			 mexErrMsgTxt("tensor_block_t::operator[]: index out of range!");
		    }
#endif /* EIGEN2MAT_RANGE_CHECK */
		    return *(begin_ + k);
	       }

	  value_type operator[] (size_t k) const
	       { 
#ifdef EIGEN2MAT_RANGE_CHECK
		    if (k > (end_ - begin_) ) {
			 mexErrMsgTxt("tensor_block_t::operator[]: index out of range!");
			 return value_type();
		    }
#endif /* EIGEN2MAT_RANGE_CHECK */
		    return *(begin_ + k);
	       }

	  size_t size() const {return (end_ - begin_);}

	  CLANG_RESTORE_WARNINGS

     private:
	  const iterator begin_;
	  const iterator end_;
     };
} // namespace eigen2mat

#endif /* TENSOR_BLOCK_HPP_INCLUDED */
