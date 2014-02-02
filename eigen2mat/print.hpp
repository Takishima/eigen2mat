// This file is part of eigen2mat, a simple C++ library to use
// Eigen with MATLAB's MEX files
//
// Copyright (C) 2013 Nguyen Damien <damien.nguyen@a3.epfl.ch>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PRINT_HPP_INCLUDED
#define PRINT_HPP_INCLUDED

#include "eigen2mat/definitions.hpp"

#include <string>

namespace eigen2mat {

     /*!
      * \brief Helper functions to print a value
      *
      * \param format format string to pass onto mexPrintf
      * \param value value to print
      */
     template <typename T>
     void print(const char* format, const T& value)
     {
	  mexPrintf(format, value);
     }

     /*!
      * \brief Overload to print two values
      *
      * \param format format string to pass onto mexPrintf
      * \param t first value to print
      * \param u second value to print
      */
     template <typename T, typename U>
     void print(const char* format, 
		const T& t,
		const U& u)
     {
	  mexPrintf(format, t, u);
     }

     /*!
      * \brief Overload for C-style strings
      * 
      * \param s string to print
      */
     void print(const char* s);
     /*!
      * \brief Overload for \c std::string
      * 
      * \param s string to print
      */
     void print(const std::string& s);

     /*!
      * \brief Overload for \c double
      * 
      * \param d value to print
      */
     void print(double d);

     /*!
      * \brief Overload for integral types
      * 
      * \param value value to print
      */
     template<typename T>
     typename std::enable_if<std::is_integral<T>::value, void>::type
     print(T value)
     {
	  print("%d", value);
     }

     /*!
      * \brief Overload for \link definitions::dcomplex dcomplex\endlink
      * 
      * \param z value to print
      */
     void print(const dcomplex& z);
 
     /*!
      * \brief Overload for std::vector of integers and the like
      * 
      * \param v vector to print
      */
     template<typename T>
     typename std::enable_if<std::is_integral<T>::value, void>::type
     print(const std::vector<T>& v)
     {
	  for (auto i(0UL); i < v.size(); ++i) {
	       print(v[i]);
	  }
     }
    
     /*!
      * \brief Overload for Eigen vectors, matrices and expressions
      * 
      * \param xpr vector, matrix, expression to print
      */
     template<typename Derived>
     void print(const Eigen::DenseBase<Derived>& xpr)
     {
	  CLANG_IGNORE_WARNINGS_TWO(-Wsign-conversion, -Wsign-compare)
	  for (auto i(0UL); i < xpr.rows(); ++i) {
	       for (auto j(0UL); j < xpr.cols(); ++j) {
		    print(xpr(i,j));
	       }
	       print("");
	  }
	  CLANG_RESTORE_WARNINGS
     }

     /*!
      * \brief Overload for Eigen sparse matrices
      * 
      * \param m matrix to print
      */
     template<typename _Scalar, int _Options, typename _Index>
     void print(const Eigen::SparseMatrix< _Scalar, _Options, _Index >& m)
     {
	  typedef Eigen::SparseMatrix< _Scalar, _Options, _Index > mat_t;
	  for (auto k(0); k < m.outerSize(); ++k) {
	       for (typename mat_t::InnerIterator it(m,k); it; ++it) {
		    print("(%2d,%2d) = ", it.row(), it.col());
		    print(it.value());
		    print("");
	       }
	  }
     }
     
     /*!
      * \brief Overload for \link definitions::real_tensor_t real_tensor_t\endlink
      * 
      * \param t tensor to print
      */
     void print(const real_tensor_t& t);
     /*!
      * \brief Overload for \link definitions::real_sp_cell_t real_sp_cell_t\endlink
      * 
      * \param c cell array to print
      */
     void print(const real_sp_cell_t& c);

     /*!
      * \brief Overload for \link definitions::cmplx_tensor_t cmplx_tensor_t\endlink
      * 
      * \param t tensor to print
      */
     void print(const cmplx_tensor_t& t);
     /*!
      * \brief Overload for \link definitions::cmplx_sp_cell_t cmplx_sp_cell_t\endlink
      * 
      * \param c cell array to print
      */
     void print(const cmplx_sp_cell_t& c);
} // namespace eigen2mat

#endif /* PRINT_HPP_INCLUDED */
