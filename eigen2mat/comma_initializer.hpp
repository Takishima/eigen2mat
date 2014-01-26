// This file is part of eigen2mat, a simple C++ library to use
// Eigen with MATLAB's MEX files
//
// Greatly inspired by its equivalent in Eigen
//
// Copyright (C) 2013 Nguyen Damien <damien.nguyen@a3.epfl.ch>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef COMMA_INITIALIZER_HPP_INCLUDED
#define COMMA_INITIALIZER_HPP_INCLUDED

#include "eigen2mat/utils/macros.hpp"

#include "eigen2mat/utils/Eigen_Core"

#include <cassert>

MSVC_IGNORE_WARNINGS(4244)
CLANG_IGNORE_WARNINGS_TWO(-Wpadded,-Wshorten-64-to-32)

namespace eigen2mat {
     template <typename XprType>
     class comma_initializer
     {
     public:
	  typedef typename XprType::Scalar Scalar;
	  typedef typename XprType::Index Index;

	  inline comma_initializer(XprType& xpr, const Scalar& s)
	       : xpr_(xpr), row_(0), col_(1), cur_block_rows_(1)
	       {
		    xpr_.coeffRef(0,0) = s;
	       }

	  template<typename OtherDerived>
	  inline comma_initializer(XprType& xpr,
				   const Eigen::DenseBase<OtherDerived>& other)
	       : xpr_(xpr), row_(0), col_(other.cols()), 
		 cur_block_rows_(other.rows())
	       {
		    block_assign_(0, 0, other.rows(), other.cols(), other);
		    // m_xpr.block(0, 0, other.rows(), other.cols()) = other;
	       }


	  inline ~comma_initializer()
	       {
		    assert((row_ + cur_block_rows_) == xpr_.rows() 
			   && col_ == xpr_.cols()
			   && "Too few coefficients passed to comma initializer (operator<<)");
	       }

	  /* inserts a scalar value in the target matrix */
	  comma_initializer& operator,(const Scalar& s)
	       {
		    if (col_==xpr_.cols())
		    {
			 row_+= cur_block_rows_;
			 col_ = 0;
			 cur_block_rows_ = 1;
			 assert(row_<xpr_.rows()
				&& "Too many rows passed to comma initializer (operator<<)");
		    }
		    assert(col_<xpr_.cols()
			   && "Too many coefficients passed to comma initializer (operator<<)");
		    eigen_assert(cur_block_rows_==1);
		    xpr_.coeffRef(row_, col_) = s;
		    ++col_;
		    return *this;
	       }

	  /* inserts a matrix expression in the target matrix */
	  template<typename OtherDerived>
	  comma_initializer& operator,(const Eigen::DenseBase<OtherDerived>& other)
	       {
		    if(other.cols()==0 || other.rows()==0) {
			 return *this;
		    }
		    if (col_==xpr_.cols()) {
			 row_+= cur_block_rows_;
			 col_ = 0;
			 cur_block_rows_ = other.rows();
			 assert(row_+cur_block_rows_<=xpr_.rows()
				      && "Too many rows passed to comma initializer (operator<<)");
		    }
		    assert(col_<xpr_.cols()
				 && "Too many coefficients passed to comma initializer (operator<<)");
		    assert(cur_block_rows_==other.rows());
		    if (OtherDerived::SizeAtCompileTime != Eigen::Dynamic)
			 block_assign_(row_,
				       col_,
				       OtherDerived::RowsAtCompileTime != Eigen::Dynamic ? 
				       OtherDerived::RowsAtCompileTime : 1,
				       OtherDerived::ColsAtCompileTime != Eigen::Dynamic ? 
				       OtherDerived::ColsAtCompileTime : 1,
				       other);
		    else {
			 block_assign_(row_, col_, other.rows(), other.cols(), other);
		    }
		    col_ += other.cols();
		    return *this;
	       }

     private:
	  template <typename T>
	  void block_assign_(Index row_start, 
			     Index col_start,
			     Index nrows,
			     Index ncols,
			     const T& other);

	  XprType& xpr_;
	  Index row_;              // current row id
	  Index col_;              // current col id
	  Index cur_block_rows_; // current block height
     };

     template <typename XprType> template <typename T>
     void comma_initializer<XprType>::block_assign_(
	  Index row_start, 
	  Index col_start,
	  Index nrows,
	  Index ncols,
	  const T& other)
     {
	  const auto row_end = row_start + nrows;
	  const auto col_end = col_start + ncols;

#ifdef EIGEN2MAT_RANGE_CHECK
	  assert(row_start < xpr_.rows());
	  assert(col_start < xpr_.cols());
	  assert(row_end <= xpr_.rows());
	  assert(col_end <= xpr_.cols());
#endif /* EIGEN2MAT_RANGE_CHECK */

	  for (Index i(row_start), io(0); i < row_end ; ++i, ++io) {
	       for (Index j(col_start), jo(0) ; j < col_end ; ++j, ++jo) {
#ifdef NDEBUG
		    xpr_.coeffRef(i, j) = other.coeff(io, jo);
#else
		    xpr_.coeffRef(i, j) = other(io, jo);
#endif /* NDEBUG */
	       }
	  }
     }
} // namespace eigen2mat

CLANG_RESTORE_WARNINGS
MSVC_RESTORE_WARNINGS

#endif /* COMMA_INITIALIZER_HPP_INCLUDED */
