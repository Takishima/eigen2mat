#ifndef SPARSE_SLICE_HPP_INCLUDED
#define SPARSE_SLICE_HPP_INCLUDED

#include "macros.hpp"

#include "Eigen_Sparse"

#include <cassert>
#include <vector>


#ifdef EIGEN2MAT_RANGE_CHECK
#  include <stdexcept>
#endif /* EIGEN2MAT_RANGE_CHECK */

CLANG_IGNORE_WARNINGS_ONE(-Wshorten-64-to-32)

namespace eigen2mat {
     /*
       inner indices = cols indices in RowMajor
       outer indices = rows indices in RowMajor
       exactly opposite for ColumnMajor
      */
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

	  sparse_slice(Eigen::SparseMatrix<_Scalar, _Options, _Index>& m,
		       std::vector<Index> row_indices,
		       std::vector<Index> col_indices);

	  inline Index rows() const 
	       { return IsRowMajor ? outer_size_ : inner_size_; }
	  inline Index cols() const
	       { return IsRowMajor ? inner_size_ : outer_size_; }

	  inline Index innerSize() const {return inner_size_;}
	  inline Index outerSize() const {return outer_size_;}

	  inline Index slice_rows() const 
	       { return IsRowMajor ? 
			 outer_indices_.size() : 
			 inner_indices_.size(); }
	  inline Index slice_cols() const 
	       { return IsRowMajor ? 
			 inner_indices_.size() :
			 outer_indices_.size(); }

	  inline Index innerSliceSize() const {return inner_indices_.size();}
	  inline Index outerSliceSize() const {return outer_indices_.size();}

	  /** For Eigen::SparseMatrix */
	  self_t& operator= (const matrix_t& rhs);
	  /** For Eigen::Matrix */
	  template <int _Rows, int _Cols>
	  self_t& operator= (const Eigen::Matrix<_Scalar, _Rows, _Cols>& rhs);


	  // template<typename OtherDerived>
	  // CommaInitializer<Derived> operator<< (const DenseBase<OtherDerived>& other);
     private:
	  template <typename T>
	  void assign_helper_(const T& other);

	  matrix_t* mat_;

	  const Index inner_size_;
	  const Index outer_size_;

	  const std::vector<Index> inner_indices_;
	  const std::vector<Index> outer_indices_;
     };

     template<typename _Scalar, int _Options, typename _Index>
     sparse_slice<_Scalar, _Options, _Index>::sparse_slice(
	  Eigen::SparseMatrix<_Scalar, _Options, _Index>& m,
	  std::vector<Index> row_indices,
	  std::vector<Index> cols_indices)
	  : mat_(&m),
	    inner_size_(m.innerSize()),
	    outer_size_(m.outerSize()), 
	    inner_indices_(IsRowMajor ? cols_indices : row_indices),
	    outer_indices_(IsRowMajor ? row_indices : cols_indices)
     {
#ifdef EIGEN2MAT_RANGE_CHECK
	  for (auto i(0UL) ; i < inner_indices_.size() ; ++i) {
	       if (inner_indices_[i] > inner_size_) {
		    throw std::out_of_range("sparse_slice: inner index out-of-range");
	       }
	  }
	  for (auto i(0UL) ; i < outer_indices_.size() ; ++i) {
	       if (outer_indices_[i] > outer_size_) {
		    throw std::out_of_range("sparse_slice: outer index out-of-range");
	       }
	  }
#endif /* EIGEN2MAT_RANGE_CHECK */
     }

     template<typename _Scalar, int _Options, typename _Index>
     template <typename T>
     void sparse_slice<_Scalar, _Options, _Index>::assign_helper_(const T& other)
     {
#ifdef EIGEN2MAT_RANGE_CHECK
	  assert(innerSliceSize() == other.innerSize());
	  assert(outerSliceSize() == other.outerSize());
#endif /* EIGEN2MAT_RANGE_CHECK */

	  const Index isize = inner_indices_.size();
	  const Index osize = outer_indices_.size();

	  /*
	   * What we want to reproduce if column-major:
	   *
	   * for (auto i(0) ; i < other.rows() ; ++i) {
	   *     for (auto j(0) ; j < other.cols() ; ++i) {
	   *         ...
	   *     }
	   * }
	   */
	  for (Index i(0UL) ; i < osize ; ++i) {
	       for (Index j(0UL) ; j < isize ; ++j) {
		    (*mat_).coeffRef(IsRowMajor ? j : i, IsRowMajor ? i : j) = 
			 other.coeff(IsRowMajor ? j : i, IsRowMajor ? i : j);
			 
	       }
	  }
     }

     template<typename _Scalar, int _Options, typename _Index>
     sparse_slice<_Scalar, _Options, _Index>& 
     sparse_slice<_Scalar, _Options, _Index>::operator=(
	  const Eigen::SparseMatrix<_Scalar, _Options, _Index>& rhs)
     {
	  assign_helper_(rhs);
	  return *this;
     }

     template<typename _Scalar, int _Options, typename _Index>
     template <int _Rows, int _Cols>
     sparse_slice<_Scalar, _Options, _Index>& 
     sparse_slice<_Scalar, _Options, _Index>::operator=(
	  const Eigen::Matrix<_Scalar, _Rows, _Cols>& rhs)
     {
	  assign_helper_(rhs);
	  return *this;
     }
} // namespace eigen2mat

CLANG_RESTORE_WARNINGS

#endif /* SPARSE_SLICE_HPP_INCLUDED */
