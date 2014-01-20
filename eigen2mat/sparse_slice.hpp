// This file is part of eigen2mat, a simple C++ library to use
// Eigen with MATLAB's MEX files
//
// Copyright (C) 2013 Nguyen Damien <damien.nguyen@a3.epfl.ch>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SPARSE_SLICE_HPP_INCLUDED
#define SPARSE_SLICE_HPP_INCLUDED

#include "eigen2mat/utils/macros.hpp"
#include "eigen2mat/comma_initializer.hpp"
#include "eigen2mat/sparse_slice_op.hpp"

#include "eigen2mat/utils/Eigen_Core"
#include "eigen2mat/utils/Eigen_Sparse"

#include <cassert>
#include <vector>

#ifdef EIGEN2MAT_RANGE_CHECK
#  include <stdexcept>
#endif /* EIGEN2MAT_RANGE_CHECK */

MSVC_IGNORE_WARNINGS(4267)
CLANG_IGNORE_WARNINGS_TWO(-Wshorten-64-to-32,-Wsign-conversion)

namespace eigen2mat {
     template<typename _Scalar, int _Options, typename _Index>
     class sparse_slice
     {
     public:
	  typedef Eigen::SparseMatrix<_Scalar, _Options, _Index> matrix_t;
	  typedef _Index Index;
	  typedef _Scalar Scalar;

	  enum {
	       Options = _Options,
	       IsRowMajor = matrix_t::IsRowMajor
	  };

	  typedef sparse_slice<_Scalar, _Options, _Index> self_t;

	  sparse_slice(matrix_t& m,
		       std::vector<Index> row_indices,
		       std::vector<Index> col_indices);

	  sparse_slice(matrix_t& m,
		       Index row,
		       std::vector<Index> col_indices);
	  sparse_slice(matrix_t& m,
		       std::vector<Index> row_indices,
		       Index col);
	  sparse_slice(matrix_t& m, Index row, Index col);
	  
	  inline Index matrix_rows() const { return row_size_; }
	  inline Index matrix_cols() const { return col_size_; }

	  inline Index innerSize() const
	       {return IsRowMajor ? col_size_ : row_size_;}
	  inline Index outerSize() const
	       {return IsRowMajor ? row_size_ : col_size_;}

	  inline Index rows() const
	       { return row_indices_.size(); }
	  inline Index cols() const
	       { return col_indices_.size(); }

	  inline Index innerSliceSize() const
	       {return IsRowMajor ? col_indices_.size() : row_indices_.size();}
	  inline Index outerSliceSize() const
	       {return IsRowMajor ? row_indices_.size() : col_indices_.size();}

	  binary_op_wrapper_t<self_t> array()
	       { return binary_op_wrapper_t<self_t>(*this); }
	  binary_op_wrapper_t<const self_t> array() const
	       { return binary_op_wrapper_t<const self_t>(*this); }

	  Scalar coeff(Index row, Index col) const
	       {
		    assert(mat_);
		    return mat_->coeff(row_indices_[row], col_indices_[col]);
	       }

	  Scalar& coeffRef(Index row, Index col) const
	       {
		    assert(mat_);
		    return mat_->coeffRef(row_indices_[row], col_indices_[col]);
	       }

	  /** For Eigen::SparseMatrix */
	  self_t& operator= (const matrix_t& rhs)
	       {
		    assign_helper_(rhs);
		    return *this;
	       }

	  /** For Eigen::Matrix */
	  template <typename Derived>
	  self_t& operator= (const Eigen::DenseBase<Derived>& rhs)
	       {
		    assign_helper_(rhs);
		    return *this;
	       }

	  // /** For Eigen::Matrix */
	  // template <int _Rows, int _Cols, int _Options2, int _MaxRows, int _MaxCols>
	  // self_t& operator= (const Eigen::Matrix<
	  // 		     _Scalar,
	  // 		     _Rows,
	  // 		     _Cols,
	  // 		     _Options2,
	  // 		     _MaxRows,
	  // 		     _MaxCols>& rhs)
	  //      {
	  // 	    assign_helper_(rhs);
	  // 	    return *this;
	  //      }

	  /** For Cwise operations with other slices */
	  template <typename lhs_t, typename rhs_t, typename binary_op_t>
	  self_t& operator= (const cwise_binary_op<lhs_t, rhs_t, binary_op_t>& op)
	       {
		    assign_helper_(op);
		    return *this;
	       }

	  comma_initializer<sparse_slice> operator<< (
	       const Scalar& s)
	       {
		    return comma_initializer<sparse_slice>(*this, s);
	       }

	  template<typename OtherDerived>
	  comma_initializer<sparse_slice> operator<< (
	       const Eigen::DenseBase<OtherDerived>& other)
	       {
		    return comma_initializer<sparse_slice>(*this, other);
	       }
     private:
	  template <typename T>
	  void assign_helper_(const T& other);

#ifdef EIGEN2MAT_RANGE_CHECK
	  void init_range_check_();
#endif /* EIGEN2MAT_RANGE_CHECK */


	  matrix_t* mat_;

	  // const typename XprType::Nested mat_;

	  const Index row_size_;
	  const Index col_size_;

	  const std::vector<Index> row_indices_;
	  const std::vector<Index> col_indices_;
     };

     MSVC_IGNORE_WARNINGS(4267)

#ifdef EIGEN2MAT_RANGE_CHECK
     template <typename _Scalar, int _Options, typename _Index>
     sparse_slice<_Scalar, _Option, _Index>::init_range_check_()
     {
	  for (auto i(0UL) ; i < row_indices_.size() ; ++i) {
	       if (row_indices_[i] > row_size_) {
		    throw std::out_of_range("sparse_slice: got row index out-of-range");
	       }
	  }
	  for (auto i(0UL) ; i < col_indices_.size() ; ++i) {
	       if (col_indices_[i] > col_size_) {
		    throw std::out_of_range("sparse_slice: got outer index out-of-range");
	       }
	  }
     }
#endif /* EIGEN2MAT_RANGE_CHECK */

     
     template<typename _Scalar, int _Options, typename _Index>
     sparse_slice<_Scalar, _Options, _Index>::sparse_slice(
	  matrix_t& m,
	  std::vector<Index> row_indices,
	  std::vector<Index> col_indices)
	  : mat_(&m),
	    row_size_(m.rows()),
	    col_size_(m.cols()),
	    row_indices_(row_indices),
	    col_indices_(col_indices)
     {
#ifdef EIGEN2MAT_RANGE_CHECK
	  init_range_check_();
#endif /* EIGEN2MAT_RANGE_CHECK */
     }

     template<typename _Scalar, int _Options, typename _Index>
     sparse_slice<_Scalar, _Options, _Index>::sparse_slice(
	  matrix_t& m,
	  Index row,
	  std::vector<Index> col_indices)
	  : mat_(&m),
	    row_size_(1),
	    col_size_(m.cols()),
	    row_indices_(row, 1),
	    col_indices_(col_indices)
     {
#ifdef EIGEN2MAT_RANGE_CHECK
	  init_range_check_();
#endif /* EIGEN2MAT_RANGE_CHECK */
     }
     template<typename _Scalar, int _Options, typename _Index>
     sparse_slice<_Scalar, _Options, _Index>::sparse_slice(
	  matrix_t& m,
	  std::vector<Index> row_indices,
	  Index col)
	  : mat_(&m),
	    row_size_(m.rows()),
	    col_size_(1),
	    row_indices_(row_indices),
	    col_indices_(col, 1)
     {
#ifdef EIGEN2MAT_RANGE_CHECK
	  init_range_check_();
#endif /* EIGEN2MAT_RANGE_CHECK */
     }

     template<typename _Scalar, int _Options, typename _Index>
     sparse_slice<_Scalar, _Options, _Index>::sparse_slice(
	  matrix_t& m, 
	  Index row, 
	  Index col)
	  : mat_(&m),
	    row_size_(1),
	    col_size_(1),
	    row_indices_(row, 1),
	    col_indices_(col, 1)
     {
#ifdef EIGEN2MAT_RANGE_CHECK
	  init_range_check_();
#endif /* EIGEN2MAT_RANGE_CHECK */
     }


     template<typename _Scalar, int _Options, typename _Index>
     template <typename T>
     void sparse_slice<_Scalar, _Options, _Index>::assign_helper_(const T& other)
     {
	  assert(mat_);
#ifdef EIGEN2MAT_RANGE_CHECK
	  assert(rows() == other.rows());
	  assert(cols() == other.cols());
#endif /* EIGEN2MAT_RANGE_CHECK */


	  const Index rsize = row_indices_.size();
	  const Index csize = col_indices_.size();

	  /*
	   * What we want to reproduce if column-major:
	   *
	   * for (auto i(0) ; i < other.rows() ; ++i) {
	   *     for (auto j(0) ; j < other.cols() ; ++i) {
	   *         ...
	   *     }
	   * }
	   */


	  for (Index j(0) ; j < csize ; ++j) {
	       for (Index i(0) ; i < rsize ; ++i) {
		    mat_->coeffRef(row_indices_[i], col_indices_[j]) =
		    	 other.coeff(i, j);
	       }
	  }
     }
     MSVC_RESTORE_WARNINGS

} // namespace eigen2mat

CLANG_RESTORE_WARNINGS
MSVC_RESTORE_WARNINGS

#endif /* SPARSE_SLICE_HPP_INCLUDED */
