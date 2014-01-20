#ifndef SPARSE_SLICE_OP_HPP_INCLUDED
#define SPARSE_SLICE_OP_HPP_INCLUDED

#include "eigen2mat/utils/forward_declarations.hpp"

namespace eigen2mat {

     CLANG_IGNORE_WARNINGS_ONE(-Wshorten-64-to-32)

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
	  };

	  template<>
	  struct traits_helper<double>
	  {
	       typedef double Scalar;
	       typedef int Index;

	       static Scalar coeff(const double& t, Index /*row*/, Index /*col*/) 
		    {
			 return t;
		    }
	  };
	  
	  template <typename T>
	  struct traits_helper<std::complex<T>>
	  {
	       typedef std::complex<T> Scalar;
	       typedef int Index;

	       static Scalar coeff(const T& t, Index /*row*/, Index /*col*/) 
		    {
			 return t;
		    }
	  };
	  
	  template <typename Scalar, typename T>
	  Scalar coeff(const T& t, typename T::Index row, typename T::Index col)
	  { return t.coeff(row, col); }

	  template <typename Scalar, typename T>
	  Scalar coeff(const T& t, int /*row*/, int /*col*/)
	  { return t; }
     } // namespace internal

     template <typename lhs_t, typename rhs_t, typename binary_op_t>
     class cwise_binary_op
     {
     public:
	  typedef typename internal::traits_helper<lhs_t> lhs_traits;
	  typedef typename internal::traits_helper<rhs_t> rhs_traits;
	  typedef typename lhs_traits::Index LIndex;
	  typedef typename rhs_traits::Index RIndex;
	  typedef typename lhs_traits::Scalar LScalar;
	  typedef typename rhs_traits::Scalar RScalar;
	  typedef LScalar Scalar;
	  typedef LIndex Index;

	  inline Index rows() const { return lhs_.rows(); }
	  inline Index cols() const { return lhs_.cols(); }

	  Scalar coeff(Index row, Index col) const
	       {
		    // return functor_(lhs_.coeff(row, col), rhs_.coeff(row, col));
		    return functor_(lhs_traits::coeff(lhs_, row, col), 
				    rhs_traits::coeff(rhs_, row, col));
	       }
	  
	  EIGEN_STRONG_INLINE 
	  cwise_binary_op(const lhs_t& lhs, 
			  const rhs_t& rhs, 
			  const binary_op_t& func = binary_op_t())
	       : lhs_(lhs), rhs_(rhs), functor_(func)
	       {
		    e2m_assert((lhs.rows() == rhs.rows()) && 
			       (lhs.cols() == rhs.cols()));
	       }
	  
     private:
	  const lhs_t& lhs_;
	  const rhs_t& rhs_;
	  const binary_op_t& functor_;
     };

     CLANG_RESTORE_WARNINGS

     struct scalar_sum_op {
	  EIGEN_EMPTY_STRUCT_CTOR(scalar_sum_op)

	  template<typename scalar_t>
	  EIGEN_STRONG_INLINE 
	  const scalar_t operator() (const scalar_t& a, const scalar_t& b) const
	       { return a + b; }
     };
     
     struct scalar_diff_op {
	  EIGEN_EMPTY_STRUCT_CTOR(scalar_diff_op)

	  template<typename scalar_t>
	  EIGEN_STRONG_INLINE 
	  const scalar_t operator() (const scalar_t& a, const scalar_t& b) const
	       { return a - b; }
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

     template <typename _Scalar>
     class scalar_wrapper_t
     {
     public:
	  typedef _Scalar Scalar;

	  scalar_wrapper_t(const Scalar& s)
	       : s_(s)
	       {}
	  
	  Scalar coeff() {return s_;}
	  const Scalar& coeff() const {return s_;}

     private:
	  Scalar s_;
     };

     template<typename lhs_t>
     class binary_op_wrapper_t
     {
     public:
	  typedef typename lhs_t::Scalar Scalar;

	  binary_op_wrapper_t(const lhs_t& lhs)
	       : lhs_(lhs)
	       {}

	  lhs_t& expression() {return lhs_;}
	  const lhs_t& expression() const {return lhs_;}
	  
	  template <typename rhs_t>
	  cwise_binary_op<lhs_t, rhs_t, scalar_sum_op> 
	  operator+ (const rhs_t& rhs) const
	       {
		    return cwise_binary_op<lhs_t, rhs_t, scalar_sum_op>(
			 lhs_, rhs);
	       }

	  template <typename rhs_t>
	  cwise_binary_op<lhs_t, rhs_t, scalar_diff_op> 
	  operator- (const rhs_t& rhs) const
	       {
		    return cwise_binary_op<lhs_t, rhs_t, scalar_diff_op>(
			 lhs_, rhs);
	       }

	  template <typename rhs_t>
	  cwise_binary_op<lhs_t, rhs_t, scalar_mult_op> 
	  operator* (const rhs_t& rhs) const
	       {
		    return cwise_binary_op<lhs_t, rhs_t, scalar_mult_op>(
			 lhs_, rhs);
	       }

	  template <typename rhs_t>
	  cwise_binary_op<lhs_t, rhs_t, scalar_div_op> 
	  operator/ (const rhs_t& rhs) const
	       {
		    return cwise_binary_op<lhs_t, rhs_t, scalar_div_op>(
			 lhs_, rhs);
	       }

     private:
	  const lhs_t& lhs_;
     };
     
     template <typename lhs_t, typename rhs_t>
     cwise_binary_op<lhs_t, rhs_t, scalar_sum_op> 
	  operator+ (const lhs_t& lhs, const binary_op_wrapper_t<rhs_t>& rhs)
     {
	  return cwise_binary_op<lhs_t, rhs_t, scalar_sum_op>(
	       lhs, rhs.expression());
     }

     template <typename lhs_t, typename rhs_t>
     cwise_binary_op<lhs_t, rhs_t, scalar_diff_op> 
	  operator- (const lhs_t& lhs, const binary_op_wrapper_t<rhs_t>& rhs)
     {
	  return cwise_binary_op<lhs_t, rhs_t, scalar_diff_op>(
	       lhs, rhs.expression());
     }

     template <typename lhs_t, typename rhs_t>
     cwise_binary_op<lhs_t, rhs_t, scalar_mult_op> 
	  operator* (const lhs_t& lhs, const binary_op_wrapper_t<rhs_t>& rhs)
     {
	  return cwise_binary_op<lhs_t, rhs_t, scalar_mult_op>(
	       lhs, rhs.expression());
     }

     template <typename lhs_t, typename rhs_t>
     cwise_binary_op<lhs_t, rhs_t, scalar_div_op> 
	  operator/ (const lhs_t& lhs, const binary_op_wrapper_t<rhs_t>& rhs)
     {
	  return cwise_binary_op<lhs_t, rhs_t, scalar_div_op>(
	       lhs, rhs.expression());
     }
     
     
} // namespace eigen2mat

#endif /* SPARSE_SLICE_OP_HPP_INCLUDED */
