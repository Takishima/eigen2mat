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
     template<typename matrix_t>
     class sparse_slice
     {
     public:
	  typedef typename matrix_t::Index Index;
	  typedef typename matrix_t::Scalar Scalar;

	  enum {
	       Options = matrix_t::Options
	  };

	  typedef sparse_slice<matrix_t> self_t;

	  template <typename index_t>
	  sparse_slice(matrix_t& m,
		       std::vector<index_t> row_indices,
		       std::vector<index_t> col_indices);
	  template <typename index_t>
	  sparse_slice(matrix_t& m,
		       index_t row,
		       std::vector<index_t> col_indices);
	  template <typename index_t>
	  sparse_slice(matrix_t& m,
		       std::vector<index_t> row_indices,
		       index_t col);
	  template <typename index_t>
	  sparse_slice(matrix_t& m, index_t row, index_t col);
	  
	  inline Index matrix_rows() const { return row_size_; }
	  inline Index matrix_cols() const { return col_size_; }

	  inline Index innerSize() const
	       {return matrix_t::IsRowMajor ? col_size_ : row_size_;}
	  inline Index outerSize() const
	       {return matrix_t::IsRowMajor ? row_size_ : col_size_;}

	  inline Index rows() const
	       { return row_indices_.size(); }
	  inline Index cols() const
	       { return col_indices_.size(); }

	  inline Index innerSliceSize() const
	       {return matrix_t::IsRowMajor ? col_indices_.size() : row_indices_.size();}
	  inline Index outerSliceSize() const
	       {return matrix_t::IsRowMajor ? row_indices_.size() : col_indices_.size();}
	  
	  expression_wrapper_t<self_t> array()
	       { return expression_wrapper_t<self_t>(*this); }
	  expression_wrapper_t<const self_t> array() const
	       { return expression_wrapper_t<const self_t>(*this); }


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

	  /** For Cwise operations with other slices */
	  template <typename lhs_t, typename rhs_t, typename binary_op_t>
	  self_t& operator= (const cwise_binary_op<lhs_t, rhs_t, binary_op_t>& op)
	       {
		    assign_helper_(op);
		    return *this;
	       }

	  /** For other slices */
	  self_t& operator= (const self_t& other)
	       {
		    assign_helper_(other);
		    return *this;
	       }

	  // =====================================

	  /** For Eigen::Matrix */
	  template <typename Derived>
	  self_t& operator+= (const Eigen::DenseBase<Derived>& rhs)
	       {
		    apply_<Eigen::DenseBase<Derived>,
			   internal::scalar_sum_assign_op>(rhs);
		    return *this;
	       }

	  /** For Cwise operations with other slices */
	  template <typename lhs_t, typename rhs_t, typename binary_op_t>
	  self_t& operator+= (const cwise_binary_op<lhs_t, rhs_t, binary_op_t>& op)
	       {
		    apply_<cwise_binary_op<lhs_t, rhs_t, binary_op_t>,
			   internal::scalar_sum_assign_op>(op);
		    return *this;
	       }

	  /** For other slices */
	  self_t& operator+= (const self_t& other)
	       {
		    apply_<self_t, internal::scalar_sum_assign_op>(other);
		    return *this;
	       }

	  // =====================================

	  /** For Eigen::Matrix */
	  template <typename Derived>
	  self_t& operator-= (const Eigen::DenseBase<Derived>& rhs)
	       {
		    apply_<Eigen::DenseBase<Derived>,
			   internal::scalar_diff_assign_op>(rhs);
		    return *this;
	       }

	  /** For Cwise operations with other slices */
	  template <typename lhs_t, typename rhs_t, typename binary_op_t>
	  self_t& operator-= (const cwise_binary_op<lhs_t, rhs_t, binary_op_t>& op)
	       {
		    apply_<cwise_binary_op<lhs_t, rhs_t, binary_op_t>,
			   internal::scalar_diff_assign_op>(op);
		    return *this;
	       }

	  /** For other slices */
	  self_t& operator-= (const self_t& other)
	       {
		    apply_<self_t, internal::scalar_diff_assign_op>(other);
		    return *this;
	       }

	  // =====================================

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

	  template <typename T, typename functor_t>
	  void apply_(const T& other, functor_t f = functor_t());

	  void init_check_() const;


	  matrix_t* mat_;

	  // const typename XprType::Nested mat_;

	  const Index row_size_;
	  const Index col_size_;

	  const std::vector<Index> row_indices_;
	  const std::vector<Index> col_indices_;
     };

     MSVC_IGNORE_WARNINGS(4267)

     template<typename matrix_t>
     void sparse_slice<matrix_t>::init_check_() const
     {
	  for (auto i(0UL) ; i < row_indices_.size() ; ++i) {
	       e2m_assert(row_indices_[i] >= 0);
#ifdef EIGEN2MAT_RANGE_CHECK
	       e2m_assert(row_indices_[i] < row_size_);
	       if (row_indices_[i] >= row_size_) {
		    throw std::out_of_range("sparse_slice: got row index out-of-range");
	       }
#endif /* EIGEN2MAT_RANGE_CHECK */
	  }
	  for (auto i(0UL) ; i < col_indices_.size() ; ++i) {
	       e2m_assert(col_indices_[i] >= 0);
#ifdef EIGEN2MAT_RANGE_CHECK
	       e2m_assert(col_indices_[i] < col_size_);
	       if (col_indices_[i] >= col_size_) {
		    throw std::out_of_range("sparse_slice: got outer index out-of-range");
	       }
#endif /* EIGEN2MAT_RANGE_CHECK */
	  }
     }

     template <typename matrix_t>
     template <typename index_t>
     sparse_slice<matrix_t>::sparse_slice(
	  matrix_t& m,
	  std::vector<index_t> row_indices,
	  std::vector<index_t> col_indices)
	  : mat_(&m),
	    row_size_(m.rows()),
	    col_size_(m.cols()),
	    row_indices_(row_indices.begin(), row_indices.end()),
	    col_indices_(col_indices.begin(), col_indices.end())
     {
	  init_check_();
     }

     template<typename matrix_t>
     template <typename index_t>
     sparse_slice<matrix_t>::sparse_slice(
	  matrix_t& m,
	  index_t row,
	  std::vector<index_t> col_indices)
	  : mat_(&m),
	    row_size_(1),
	    col_size_(m.cols()),
	    row_indices_(1, row),
	    col_indices_(col_indices.begin(), col_indices.end())
     {
	  init_check_();
     }
     template <typename matrix_t>
     template <typename index_t>
     sparse_slice<matrix_t>::sparse_slice(
	  matrix_t& m,
	  std::vector<index_t> row_indices,
	  index_t col)
	  : mat_(&m),
	    row_size_(m.rows()),
	    col_size_(1),
	    row_indices_(row_indices.begin(), row_indices.end()),
	    col_indices_(1, col)
     {
	  init_check_();
     }

     template<typename matrix_t>
     template <typename index_t>
     sparse_slice<matrix_t>::sparse_slice(
	  matrix_t& m, 
	  index_t row, 
	  index_t col)
	  : mat_(&m),
	    row_size_(1),
	    col_size_(1),
	    row_indices_(1, row),
	    col_indices_(1, col)
     {
	  init_check_();
     }


     template<typename matrix_t>
     template <typename T>
     void sparse_slice<matrix_t>::assign_helper_(const T& other)
     {
	  apply_<T, internal::assign_op>(other);
     }

     template<typename matrix_t>
     template <typename T, typename functor_t>
     void sparse_slice<matrix_t>::apply_(const T& other, functor_t op)
     {
	  e2m_assert(mat_);
	  e2m_assert(rows() != 0 && cols() != 0 && "this matrix is empty");
	  e2m_assert(other.rows() != 0 && other.cols() != 0 &&
		     "other matrix is empty");     
	  e2m_assert(rows() == other.rows());
	  e2m_assert(cols() == other.cols());

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
		    op(
			 mat_->coeffRef(row_indices_[i], col_indices_[j]),
			 other.coeff(i, j)
			 );
	       }
	  }
     }
     MSVC_RESTORE_WARNINGS

} // namespace eigen2mat

CLANG_RESTORE_WARNINGS
MSVC_RESTORE_WARNINGS

#endif /* SPARSE_SLICE_HPP_INCLUDED */
