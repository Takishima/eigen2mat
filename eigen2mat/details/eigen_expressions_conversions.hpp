// This file is part of eigen2mat, a simple C++ library to use
// Eigen with MATLAB's MEX files
//
// Copyright (C) 2013 Nguyen Damien <damien.nguyen@a3.epfl.ch>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef EIGEN_EXPRESSIONS_CONVERSIONS_HPP_INCLUDED
#define EIGEN_EXPRESSIONS_CONVERSIONS_HPP_INCLUDED

#include "complex_traits.hpp"

#include <type_traits>

namespace eigen2mat {
     // mxArray to Eigen
     
     /*!
      * \brief Convert an mxArray to a (integer) matrix
      * 
      * \tparam integer_mat_t type of matrix to return
      * \param m mxArray to convert
      * \return converted value
      */
     template <typename integer_mat_t>
     integer_mat_t mxArray_to_integer(const mxArray* m)
     {
	  e2m_assert(m);
	  e2m_assert(mxGetPr(m));
#ifdef EIGEN2MAT_TYPE_CHECK
	  if (mxIsComplex(m)) {
	       mexWarnMsgTxt("mxArray_to_real(): argument is complex!");
	  }
	  const auto id = mxGetClassID(m);
	  if (id != mxDOUBLE_CLASS) {
	       mexWarnMsgTxt("mxArray_to_real(): data type of m is not double!");
	  }
#endif /* EIGEN2MAT_TYPE_CHECK */
	  
	  typedef typename integer_mat_t::Scalar Scalar;
	       
	  CLANG_IGNORE_WARNINGS_ONE(-Wsign-conversion)
	  return Eigen::Map<integer_mat_t>(reinterpret_cast<Scalar*>(mxGetPr(m)), 
					   mxGetM(m), 
					   mxGetN(m));
	  CLANG_RESTORE_WARNINGS
     }

     /*!
      * \brief Convert an mxArray to a (real) matrix
      * 
      * \tparam real_mat_t type of matrix to return
      * \param m mxArray to convert
      * \return converted value
      */
     template <typename real_mat_t>
     real_mat_t mxArray_to_real(const mxArray* m)
     {
	  e2m_assert(m);
	  e2m_assert(mxGetPr(m));
#ifdef EIGEN2MAT_TYPE_CHECK
	  if (mxIsComplex(m)) {
	       mexWarnMsgTxt("mxArray_to_real(): argument is complex!");
	  }
	  const auto id = mxGetClassID(m);
	  if (id != mxDOUBLE_CLASS) {
	       mexWarnMsgTxt("mxArray_to_real(): data type of m is not double!");
	  }
	  if ((real_mat_t::RowsAtCompileTime != Eigen::Dynamic) &&
	      (real_mat_t::RowsAtCompileTime != mxGetM(m))) {
	       mexErrMsgIdAndTxt("eigen2mat:invalid_argument",
				 "mxArray_to_real: invalid size; needs to be %dx## is %dx%d", 
				 real_mat_t::RowsAtCompileTime, 
				 mxGetM(m), 
				 mxGetN(m));
	       
	  }
	  if ((real_mat_t::ColsAtCompileTime != Eigen::Dynamic) &&
	      (real_mat_t::ColsAtCompileTime != mxGetN(m))) {
	       mexErrMsgIdAndTxt("eigen2mat:invalid_argument",
				 "mxArray_to_real: invalid size; needs to be ##x%d is %dx%d", 
				 real_mat_t::ColsAtCompileTime, 
				 mxGetM(m), 
				 mxGetN(m));
	       
	  }
#endif /* EIGEN2MAT_TYPE_CHECK */

	  typedef typename real_mat_t::Scalar Scalar;
	       
	  CLANG_IGNORE_WARNINGS_ONE(-Wsign-conversion)
	  return Eigen::Map<real_mat_t>(reinterpret_cast<Scalar*>(mxGetPr(m)), 
					mxGetM(m), 
					mxGetN(m));
	  CLANG_RESTORE_WARNINGS
     }

     /*!
      * \brief Convert an mxArray to a (real) 1D vector
      * 
      * This version differs from mxArray_to_real<T> in that it will always read
      * a one-dimensional vector. It will make sure the input is 1-dimensional
      * and if necessary, silently convert a 1D row vector mxArray to a 1D
      * column vector or vice-versa.
      *
      * Moreover, this function requires that the type returned be a compile-time
      * vector.
      *
      * \tparam real_vec_t type of matrix to return
      * \param m mxArray to convert
      * \return converted value
      */
     template <typename real_vec_t>
     typename std::enable_if<
	  real_vec_t::RowsAtCompileTime != Eigen::Dynamic ||
	  real_vec_t::ColsAtCompileTime != Eigen::Dynamic,
	  real_vec_t>::type
     mxArray_to_1dreal(const mxArray* m)
     {
	  e2m_assert(m);
	  e2m_assert(mxGetPr(m));

	  const auto numel(mxGetNumberOfElements(m));

#ifdef EIGEN2MAT_TYPE_CHECK
	  if (mxIsComplex(m)) {
	       mexWarnMsgTxt("mxArray_to_1dreal(): argument is complex!");
	  }
	  const auto id = mxGetClassID(m);
	  if (id != mxDOUBLE_CLASS) {
	       mexWarnMsgTxt("mxArray_to_1dreal(): data type of m is not double!");
	  }
	  if (mxGetM(m) != 1 && mxGetN(m) != 1) {
	       mexErrMsgIdAndTxt("eigen2mat:invalid_argument",
				 "mxArray_to_1dreal<T>: input is not a vector!");
	  }
	  if ((real_vec_t::SizeAtCompileTime != Eigen::Dynamic) &&
	      (real_vec_t::SizeAtCompileTime != numel)) {
	       mexErrMsgIdAndTxt("eigen2mat:invalid_argument",
				 "mxArray_to_1dreal<T>: invalid size; required %d elements, got %d", 
				 real_vec_t::SizeAtCompileTime, 
				 numel);
	       
	  }
#endif /* EIGEN2MAT_TYPE_CHECK */

	  typedef typename real_vec_t::Scalar Scalar;

	  CLANG_IGNORE_WARNINGS_ONE(-Wsign-conversion)
	  return Eigen::Map<real_vec_t>(reinterpret_cast<Scalar*>(mxGetPr(m)), numel);
	  CLANG_RESTORE_WARNINGS
     }

     /*!
      * \brief Convert an mxArray to a (complex) matrix
      * 
      * \tparam cmplx_mat_t type of matrix to return
      * \param m mxArray to convert
      * \return converted value
      */
     template <typename cmplx_mat_t>
     cmplx_mat_t mxArray_to_cmplx(const mxArray* m)
     {
	  typedef Eigen::Matrix<
	       typename internal::complex_traits<typename cmplx_mat_t::Scalar>::type,
	       cmplx_mat_t::RowsAtCompileTime,
	       cmplx_mat_t::ColsAtCompileTime,
	       cmplx_mat_t::Options,
	       cmplx_mat_t::MaxRowsAtCompileTime,
	       cmplx_mat_t::MaxColsAtCompileTime>
	       real_mat_t;
	  
	  e2m_assert(m);
	  e2m_assert(mxGetPr(m));
	  
#ifdef EIGEN2MAT_TYPE_CHECK
	  const auto id = mxGetClassID(m);
	  if (id != mxDOUBLE_CLASS) {
	       mexWarnMsgTxt("mxArray_to_cmplx(): data type of m is not double!");
	  }
	  if ((cmplx_mat_t::RowsAtCompileTime != Eigen::Dynamic) &&
	      (cmplx_mat_t::RowsAtCompileTime != mxGetM(m))) {
	       mexErrMsgIdAndTxt("eigen2mat:invalid_argument",
				 "mxArray_to_cmplx<T>: invalid size; needs to be %dx## is %dx%d", 
				 cmplx_mat_t::RowsAtCompileTime, 
				 mxGetM(m), 
				 mxGetN(m));
	       
	  }
	  if ((cmplx_mat_t::ColsAtCompileTime != Eigen::Dynamic) &&
	      (cmplx_mat_t::ColsAtCompileTime != mxGetN(m))) {
	       mexErrMsgIdAndTxt("eigen2mat:invalid_argument",
				 "mxArray_to_cmplx<T>: invalid size; needs to be ##x%d is %dx%d", 
				 cmplx_mat_t::ColsAtCompileTime, 
				 mxGetM(m), 
				 mxGetN(m));
	       
	  }
#endif /* EIGEN2MAT_TYPE_CHECK */

	  const auto rows(mxGetM(m));
	  const auto cols(mxGetN(m));
	  
	  CLANG_IGNORE_WARNINGS_ONE(-Wsign-conversion)
	       
	  const auto real(Eigen::Map<real_mat_t>(mxGetPr(m), rows, cols));
	  auto* imag_data = mxGetPi(m);
	  if (imag_data == nullptr) {
	       return real.template cast<dcomplex>();
	  }
	  else {
	       const auto imag(Eigen::Map<real_mat_t>(imag_data, rows, cols));
	       return (real.template cast<dcomplex>() + 
		       dcomplex(0,1) * imag.template cast<dcomplex>());
	  }
	  CLANG_RESTORE_WARNINGS
     }

     /*!
      * \brief Convert an mxArray to a (complex) 1D vector
      * 
      * This version differs from mxArray_to_cmplx<T> in that it will always read
      * a one-dimensional vector. It will make sure the input is 1-dimensional
      * and if necessary, silently convert a 1D row vector mxArray to a 1D
      * column vector or vice-versa.
      *
      * Moreover, this function requires that the type returned be a compile-time
      * vector.
      *
      * \tparam cmplx_vec_t type of matrix to return
      * \param m mxArray to convert
      * \return converted value
      */
     template <typename cmplx_vec_t>
     typename std::enable_if<
	  cmplx_vec_t::RowsAtCompileTime != Eigen::Dynamic ||
	  cmplx_vec_t::ColsAtCompileTime != Eigen::Dynamic,
	  cmplx_vec_t>::type
     mxArray_to_1dcmplx(const mxArray* m)
     {
	  typedef Eigen::Matrix<
	       typename internal::complex_traits<typename cmplx_vec_t::Scalar>::type,
	       cmplx_vec_t::RowsAtCompileTime,
	       cmplx_vec_t::ColsAtCompileTime,
	       cmplx_vec_t::Options,
	       cmplx_vec_t::MaxRowsAtCompileTime,
	       cmplx_vec_t::MaxColsAtCompileTime>
	       real_vec_t;

	  e2m_assert(m);
	  e2m_assert(mxGetPr(m));

#ifdef EIGEN2MAT_TYPE_CHECK
	  const auto id = mxGetClassID(m);
	  if (id != mxDOUBLE_CLASS) {
	       mexWarnMsgTxt("mxArray_to_1dcmplx<T>(): data type of m is not double!");
	  }
	  if (mxGetM(m) != 1 && mxGetN(m) != 1) {
	       mexErrMsgIdAndTxt("eigen2mat:invalid_argument",
				 "mxArray_to_1dcmplx<T>: input is not a vector!");
	  }
	  if ((cmplx_vec_t::SizeAtCompileTime != Eigen::Dynamic) &&
	      (cmplx_vec_t::SizeAtCompileTime != numel)) {
	       mexErrMsgIdAndTxt("eigen2mat:invalid_argument",
				 "mxArray_to_1dcmplx<T>: invalid size; required %d elements, got %d", 
				 cmplx_vec_t::SizeAtCompileTime, 
				 numel);
	       
	  }
#endif /* EIGEN2MAT_TYPE_CHECK */
	  
	  const auto numel(mxGetNumberOfElements(m));

	  auto* imag_data = mxGetPi(m);
	  const auto real(Eigen::Map<real_vec_t>(mxGetPr(m), numel));
	  
	  if (imag_data == nullptr) {
	       return real.template cast<dcomplex>();
	  }
	  else {
	       const auto imag(Eigen::Map<real_vec_t>(imag_data, numel));
	       return (real.template cast<dcomplex>() + 
		       dcomplex(0,1) * imag.template cast<dcomplex>());
	  }
     }

     // ========================================================================
     // Eigen to mxArray

     /*!
      * \brief Convert Eigen matrices & expressions of int, float, double and 
      *        the like to mxArray
      * 
      * \param xpr matrix/expression to convert
      * \return converted value
      */
     template<typename Derived>
     typename std::enable_if<
	  std::is_arithmetic<typename Eigen::DenseBase<Derived>::Scalar>::value,
	  mxArray*>::type
     to_mxArray(const Eigen::DenseBase<Derived>& xpr)
     {
	  typedef Eigen::DenseBase<Derived> mat_t;
	  const auto O = xpr.outerSize();
	  const auto I = xpr.innerSize();

	  auto ret = mxCreateDoubleMatrix(xpr.rows(), xpr.cols(), mxREAL);
	  auto real = mxGetPr(ret);
	  e2m_assert(ret);

	  for (auto o(0UL) ; o < O ; ++o) {
	       for (auto i(0UL) ; i < I ; ++i) {
		    real[i + I*o] = xpr.coeff(mat_t::IsRowMajor ? o : i,
					      mat_t::IsRowMajor ? i : o);
	       }
	  }

	  return ret;
     }

     /*!
      * \brief Overload for PlainObjectBase<Derived> objects.
      *
      * This overloads makes use of the data() accessor method to speed thins up
      * 
      * \param m matrix/expression to convert
      * \return converted value
      */
     template<typename Derived>
     typename std::enable_if<
	  std::is_arithmetic<
	       typename Eigen::PlainObjectBase<Derived>::Scalar>::value,
	  mxArray*>::type
     to_mxArray(const Eigen::PlainObjectBase<Derived>& m)
     {
	  const auto M = m.rows();
	  const auto N = m.cols();

	  auto ret = mxCreateDoubleMatrix(M, N, mxREAL);
	  e2m_assert(ret);

	  std::copy(m.data(), m.data() + M*N, mxGetPr(ret));
	  return ret;
     }


     /*!
      * \brief Overload for complex matrices or expressions
      *
      * \param xpr matrix/expression to convert
      * \return converted value
      */
     template<typename Derived>
     typename std::enable_if<
	  internal::complex_traits<
	       typename Eigen::DenseBase<Derived>::Scalar>::is_cmplx,
	  mxArray*>::type
     to_mxArray(const Eigen::DenseBase<Derived>& xpr)
     {
	  typedef Eigen::DenseBase<Derived> mat_t;
	  const auto O = xpr.outerSize();
	  const auto I = xpr.innerSize();

	  auto ret = mxCreateDoubleMatrix(xpr.rows(), xpr.cols(), mxCOMPLEX);
	  e2m_assert(ret);

	  auto real = mxGetPr(ret);
	  auto imag = mxGetPi(ret);
	  e2m_assert(real);
	  e2m_assert(imag);

	  for (auto o(0UL) ; o < O ; ++o) {
	       for (auto i(0UL) ; i < I ; ++i) {
		    const auto tmp = xpr.coeff(mat_t::IsRowMajor ? o : i,
					       mat_t::IsRowMajor ? i : o);
		    
		    real[i + I*o] = tmp.real();
		    imag[i + I*o] = tmp.imag();
	       }
	  }

	  return ret;
     }

     /*!
      * \brief Overload for PlainObjectBase<Derived> containing complex numbers
      *
      * This overloads makes use of the data() accessor method to speed thins up
      *
      * \param m matrix/expression to convert
      * \return converted value
      */
     template<typename Derived>
     typename std::enable_if<
	  internal::complex_traits<
	       typename Eigen::PlainObjectBase<Derived>::Scalar>::is_cmplx,
	  mxArray*>::type
     to_mxArray(const Eigen::PlainObjectBase<Derived>& m)
     {
	  const size_t M = m.rows();
	  const size_t N = m.cols();
	  const size_t S = M * N;

	  auto ret = mxCreateDoubleMatrix(M, N, mxCOMPLEX);
	  e2m_assert(ret);

	  auto real = mxGetPr(ret);
	  auto imag = mxGetPi(ret);
	  e2m_assert(real);
	  e2m_assert(imag);

	  const auto data = m.data();
	  for (auto i(0UL) ; i < S ;++i) {
	       real[i] = data[i].real();
	       imag[i] = data[i].imag();
	  }

	  return ret;
     }

} // namespace eigen2mat

#endif /* EIGEN_EXPRESSIONS_CONVERSIONS_HPP_INCLUDED */
