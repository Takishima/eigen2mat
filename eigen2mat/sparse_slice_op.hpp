// This file is part of eigen2mat, a simple C++ library to use
// Eigen with MATLAB's MEX files
//
// Copyright (C) 2013 Nguyen Damien <damien.nguyen@a3.epfl.ch>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SPARSE_SLICE_OP_HPP_INCLUDED
#define SPARSE_SLICE_OP_HPP_INCLUDED

#include "eigen2mat/utils/forward_declarations.hpp"

namespace eigen2mat {

     CLANG_IGNORE_WARNINGS_TWO(-Wshorten-64-to-32, -Wpadded)

     template <typename _Scalar>
     class scalar_wrapper_t
     {
     public:
	  typedef _Scalar Scalar;
	  typedef int Index;

	  scalar_wrapper_t(const Scalar& s)
	       : s_(s)
	       {}

	  Scalar coeff(Index, Index) {return s_;}
	  const Scalar& coeff(Index, Index) const {return s_;}

	  Index rows() const {return 1;}
	  Index cols() const {return 1;}

     private:
	  const Scalar s_;
     };


     namespace internal {
	  template <typename T>
	  struct traits_helper
	  {
	       typedef typename T::Scalar Scalar;
	       typedef typename T::Index Index;

	       static Scalar coeff(const T& t, Index row, Index col)
		    {
			 return t.coeff(row, col);
		    }

	       static Index rows(const T& t) { return t.rows(); }
	       static Index cols(const T& t) { return t.cols(); }
	  };

	  template <typename T>
	  struct is_scalar
	  {
	       enum { value = 0 };
	  };

	  template <typename T>
	  struct is_scalar<scalar_wrapper_t<T>>
	  {
	       enum { value = 1 };
	  };

	  struct assign_op {
	       EIGEN_EMPTY_STRUCT_CTOR(assign_op)

	       template<typename scalar_t>
	       EIGEN_STRONG_INLINE
	       void operator() (scalar_t& a, const scalar_t& b) const
		    { a = b; }
	  };

	  struct scalar_sum_op {
	       EIGEN_EMPTY_STRUCT_CTOR(scalar_sum_op)

	       template<typename scalar_t>
	       EIGEN_STRONG_INLINE
	       const scalar_t operator() (const scalar_t& a, const scalar_t& b) const
		    { return a + b; }
	  };

	  struct scalar_sum_assign_op {
	       EIGEN_EMPTY_STRUCT_CTOR(scalar_sum_assign_op)

	       template<typename scalar_t>
	       EIGEN_STRONG_INLINE
	       void operator() (scalar_t& a, const scalar_t& b) const
		    { a += b; }
	  };

	  struct scalar_diff_op {
	       EIGEN_EMPTY_STRUCT_CTOR(scalar_diff_op)

	       template<typename scalar_t>
	       EIGEN_STRONG_INLINE
	       const scalar_t operator() (const scalar_t& a, const scalar_t& b) const
		    { return a - b; }
	  };

	  struct scalar_diff_assign_op {
	       EIGEN_EMPTY_STRUCT_CTOR(scalar_diff_assign_op)

	       template<typename scalar_t>
	       EIGEN_STRONG_INLINE
	       void operator() (scalar_t& a, const scalar_t& b) const
		    { a -= b; }
	  };

	  struct scalar_mult_op {
	       EIGEN_EMPTY_STRUCT_CTOR(scalar_mult_op)

	       template<typename scalar_t>
	       EIGEN_STRONG_INLINE
	       const scalar_t operator() (const scalar_t& a, const scalar_t& b) const
		    { return a * b; }
	  };

	  struct scalar_div_op {
	       EIGEN_EMPTY_STRUCT_CTOR(scalar_div_op)

	       template<typename scalar_t>
	       EIGEN_STRONG_INLINE
	       const scalar_t operator() (const scalar_t& a, const scalar_t& b) const
		    { return a / b; }
	  };

     } // namespace internal

     MSVC_IGNORE_WARNINGS(4244)

     template <typename lhs_t, typename rhs_t, typename binary_op_t>
     class cwise_binary_op
     {
     public:
	  typedef typename internal::traits_helper<cwise_binary_op> this_traits;
	  typedef typename lhs_t::Index LIndex;
	  typedef typename rhs_t::Index RIndex;
	  typedef typename lhs_t::Scalar LScalar;
	  typedef typename rhs_t::Scalar RScalar;
	  typedef LScalar Scalar;
	  typedef LIndex Index;

	  EIGEN_STRONG_INLINE
	  cwise_binary_op(const lhs_t& lhs,
			  const rhs_t& rhs,
			  const binary_op_t& func = binary_op_t())
	       : lhs_(lhs), rhs_(rhs), functor_(func)
	       {
		    e2m_assert((
				    (lhs.rows() == 1 && lhs.cols() == 1) ||
				    (rhs.rows() == 1 && rhs.cols() == 1)
				    ) || // avoid scalars...
			       (lhs.rows() == rhs.rows()) &&
			       (lhs.cols() == rhs.cols())
		    	 );
	       }

	  inline Index rows() const
	       {
		    return internal::is_scalar<lhs_t>::value ? rhs_.rows() : lhs_.rows();
	       }
	  inline Index cols() const
	       { 
		    return internal::is_scalar<lhs_t>::value ? rhs_.cols() : lhs_.cols();
	       }

	  Scalar coeff(Index row, Index col) const
	       {
		    // return functor_(lhs_.coeff(row, col), rhs_.coeff(row, col));
		    return functor_(lhs_.coeff(row, col),
				    rhs_.coeff(row, col));
	       }

     private:
	  const lhs_t lhs_;
	  const rhs_t rhs_;
	  const binary_op_t functor_;
     };

     MSVC_RESTORE_WARNINGS
     CLANG_RESTORE_WARNINGS

     template<typename lhs_t>
     class expression_wrapper_t
     {
     public:
	  typedef typename lhs_t::Scalar Scalar;

	  expression_wrapper_t(const lhs_t& lhs)
	       : lhs_(lhs)
	       {}

	  lhs_t& expression() {return lhs_;}
	  const lhs_t& expression() const {return lhs_;}

	  template <typename rhs_t>
	  cwise_binary_op<lhs_t, rhs_t, internal::scalar_sum_op>
	  operator+ (const rhs_t& rhs) const
	       {
		    return cwise_binary_op<lhs_t, 
					   rhs_t, 
					   internal::scalar_sum_op>(
						lhs_, rhs);
	       }

	  // ======================================

	  template <typename rhs_t>
	  cwise_binary_op<lhs_t, rhs_t, internal::scalar_diff_op>
	  operator- (const rhs_t& rhs) const
	       {
		    return cwise_binary_op<lhs_t, 
					   rhs_t, 
					   internal::scalar_diff_op>(
						lhs_, rhs);
	       }

	  // ======================================

	  template <typename rhs_t>
	  cwise_binary_op<lhs_t, rhs_t, internal::scalar_mult_op>
	  operator* (const rhs_t& rhs) const
	       {
		    
		    return cwise_binary_op<lhs_t, 
					   rhs_t, 
					   internal::scalar_mult_op>(
			 lhs_, rhs);
	       }

	  cwise_binary_op<lhs_t, scalar_wrapper_t<double>, internal::scalar_mult_op>
	  operator* (const double& scalar) const
	       {
		    return cwise_binary_op<lhs_t, 
					   scalar_wrapper_t<double>, 
					   internal::scalar_mult_op>(
						lhs_, scalar
						);
	       }
	  template <typename T>
	  cwise_binary_op<lhs_t, 
			  scalar_wrapper_t<std::complex<T>>, 
			  internal::scalar_mult_op>
	       operator* (const std::complex<T>& scalar) const
	       {
		    return cwise_binary_op<lhs_t, 
					   scalar_wrapper_t<std::complex<T>>, 
					   internal::scalar_mult_op>(
						lhs_, scalar
						);
	       }

	  // ======================================

	  template <typename rhs_t>
	  cwise_binary_op<lhs_t, rhs_t, internal::scalar_div_op>
	  operator/ (const rhs_t& rhs) const
	       {
 		    return cwise_binary_op<lhs_t, 
					   rhs_t, 
					   internal::scalar_div_op>(
			 lhs_, rhs);
	       }

	  cwise_binary_op<lhs_t, scalar_wrapper_t<double>, internal::scalar_div_op>
	  operator/ (const double& scalar) const
	       {
		    return cwise_binary_op<lhs_t, 
					   scalar_wrapper_t<double>, 
					   internal::scalar_div_op>(
						lhs_, scalar
						);
	       }
	  template <typename T>
	  cwise_binary_op<lhs_t, 
			  scalar_wrapper_t<std::complex<T>>, 
			  internal::scalar_div_op>
	  operator/ (const std::complex<T>& scalar) const
	       {
		    return cwise_binary_op<lhs_t, 
					   scalar_wrapper_t<std::complex<T>>, 
					   internal::scalar_div_op>(
						lhs_, scalar
						);
	       }

     private:
	  const lhs_t& lhs_;
     };

     // ========================================================================
     
     template <typename lhs_t, typename rhs_t>
     cwise_binary_op<lhs_t, rhs_t, internal::scalar_sum_op>
	  operator+ (const lhs_t& lhs, const expression_wrapper_t<rhs_t>& rhs)
     {
	  return cwise_binary_op<lhs_t, rhs_t, internal::scalar_sum_op>(
	       lhs, rhs.expression());
     }

     // ======================================

     template <typename lhs_t, typename rhs_t>
     cwise_binary_op<lhs_t, rhs_t, internal::scalar_diff_op>
	  operator- (const lhs_t& lhs, const expression_wrapper_t<rhs_t>& rhs)
     {
	  return cwise_binary_op<lhs_t, rhs_t, internal::scalar_diff_op>(
	       lhs, rhs.expression());
     }

     // ======================================

     template <typename lhs_t, typename rhs_t>
     cwise_binary_op<lhs_t, rhs_t, internal::scalar_mult_op>
	  operator* (const lhs_t& lhs, const expression_wrapper_t<rhs_t>& rhs)
     {
	  return cwise_binary_op<lhs_t, rhs_t, internal::scalar_mult_op>(
	       lhs, rhs.expression());
     }

     template <typename rhs_t>
     cwise_binary_op<scalar_wrapper_t<double>, rhs_t, internal::scalar_mult_op>
	  operator* (const double& lhs, const expression_wrapper_t<rhs_t>& rhs)
     {
	  return cwise_binary_op<scalar_wrapper_t<double>, 
				 rhs_t, 
				 internal::scalar_mult_op>(
				      lhs, rhs.expression()
				      );
     }
     template <typename T, typename rhs_t>
     cwise_binary_op<
	  scalar_wrapper_t<std::complex<T>>, 
	  rhs_t, 
	  internal::scalar_mult_op>
     operator* (const std::complex<T>& lhs, const expression_wrapper_t<rhs_t>& rhs)
     {
	  return cwise_binary_op<scalar_wrapper_t<std::complex<T>>,
				 rhs_t,
				 internal::scalar_mult_op>(
				      lhs,rhs.expression()
				      );
     }

     // ======================================

     template <typename lhs_t, typename rhs_t>
     cwise_binary_op<lhs_t, rhs_t, internal::scalar_div_op>
	  operator/ (const lhs_t& lhs, const expression_wrapper_t<rhs_t>& rhs)
     {
	  return cwise_binary_op<lhs_t, rhs_t, internal::scalar_div_op>(
	       lhs, rhs.expression());
     }
     template <typename rhs_t>
     cwise_binary_op<scalar_wrapper_t<double>, rhs_t, internal::scalar_div_op>
	  operator/ (const double& lhs, const expression_wrapper_t<rhs_t>& rhs)
     {
	  return cwise_binary_op<scalar_wrapper_t<double>, 
				 rhs_t, 
				 internal::scalar_div_op>(
				      lhs, rhs.expression()
				      );
     }
     template <typename T, typename rhs_t>
     cwise_binary_op<
	  scalar_wrapper_t<std::complex<T>>, 
	  rhs_t,
	  internal::scalar_div_op>
     operator/ (const std::complex<T>& lhs, const expression_wrapper_t<rhs_t>& rhs)
     {
	  return cwise_binary_op<scalar_wrapper_t<std::complex<T>>,
				 rhs_t,
				 internal::scalar_div_op>(
				      lhs,rhs.expression()
				      );
     }

     // ========================================================================

} // namespace eigen2mat

#endif /* SPARSE_SLICE_OP_HPP_INCLUDED */
