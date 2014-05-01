// This file is part of eigen2mat, a simple C++ library to use
// Eigen with MATLAB's MEX files
//
// Copyright (C) 2013 Nguyen Damien <damien.nguyen@a3.epfl.ch>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MACROS_HPP_INCLUDED
#define MACROS_HPP_INCLUDED

#define e2m_assert(x) \
     mxAssert(x, "eigen2mat assertion failed"); \
     assert(x)

// =============================================================================
// Compiler macros

#ifdef __clang__
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wc++98-compat-pedantic"
#endif /* __clang__ */

#ifdef _MSC_VER
#  define MSVC_IGNORE_WARNINGS(...)			\
     __pragma(warning(push))				\
     __pragma(warning (disable : __VA_ARGS__))
#  define MSVC_RESTORE_WARNINGS __pragma(warning(pop))
#else
#  define MSVC_IGNORE_WARNINGS(...)
#  define MSVC_RESTORE_WARNINGS
#endif /* _MSC_VER */

#ifdef __clang__
#  define _CLANG_DO_PRAGMA(x) _Pragma (#x) 
#  define _CLANG_IGNORE_ONE(w) _CLANG_DO_PRAGMA(clang diagnostic ignored #w)

#  define CLANG_IGNORE_WARNINGS_ONE(w1)		\
     _Pragma("clang diagnostic push")		\
     _CLANG_IGNORE_ONE(w1)			
#  define CLANG_IGNORE_WARNINGS_TWO(w1, w2)	\
     CLANG_IGNORE_WARNINGS_ONE(w1)		\
     _CLANG_IGNORE_ONE(w2)			
#  define CLANG_IGNORE_WARNINGS_THREE(w1, w2, w3)	\
     CLANG_IGNORE_WARNINGS_TWO(w1, w2)			\
     _CLANG_IGNORE_ONE(w3)
#  define CLANG_IGNORE_WARNINGS_FOUR(w1, w2, w3, w4)	\
     CLANG_IGNORE_WARNINGS_THREE(w1, w2, w3)		\
     _CLANG_IGNORE_ONE(w4)			
#  define CLANG_IGNORE_WARNINGS_FIVE(w1, w2, w3, w4, w5)	\
     CLANG_IGNORE_WARNINGS_FOUR(w1, w2, w3, w4)			\
     _CLANG_IGNORE_ONE(w5)			
#  define CLANG_IGNORE_WARNINGS_SIX(w1, w2, w3, w4, w5, w6)		\
     CLANG_IGNORE_WARNINGS_FIVE(w1, w2, w3, w4, w5)			\
     _CLANG_IGNORE_ONE(w6)			

#  define CLANG_RESTORE_WARNINGS _CLANG_DO_PRAGMA(clang diagnostic pop)
#else
#  define _CLANG_DO_PRAGMA(x) 
#  define _CLANG_IGNORE_ONE(w)
#  define CLANG_IGNORE_WARNINGS_ONE(w1)
#  define CLANG_IGNORE_WARNINGS_TWO(w1, w2)
#  define CLANG_IGNORE_WARNINGS_THREE(w1, w2, w3)
#  define CLANG_IGNORE_WARNINGS_FOUR(w1, w2, w3, w4)
#  define CLANG_IGNORE_WARNINGS_FIVE(w1, w2, w3, w4, w5)
#  define CLANG_IGNORE_WARNINGS_SIX(w1, w2, w3, w4, w5, w6)
#  define CLANG_RESTORE_WARNINGS
#endif /* __clang__ */

#ifdef __GNUC__
#  define _GCC_DO_PRAGMA(x) _Pragma (#x) 
#  define _GCC_IGNORE_ONE(w) _GCC_DO_PRAGMA(GCC diagnostic ignored #w)

#  define GCC_IGNORE_WARNINGS_ONE(w1)		\
     _Pragma("GCC diagnostic push")		\
     _GCC_IGNORE_ONE(w1)			
#  define GCC_IGNORE_WARNINGS_TWO(w1, w2)	\
     GCC_IGNORE_WARNINGS_ONE(w1)		\
     _GCC_IGNORE_ONE(w2)			
#  define GCC_IGNORE_WARNINGS_THREE(w1, w2, w3)	\
     GCC_IGNORE_WARNINGS_TWO(w1, w2)			\
     _GCC_IGNORE_ONE(w3)
#  define GCC_IGNORE_WARNINGS_FOUR(w1, w2, w3, w4)	\
     GCC_IGNORE_WARNINGS_THREE(w1, w2, w3)		\
     _GCC_IGNORE_ONE(w4)			
#  define GCC_IGNORE_WARNINGS_FIVE(w1, w2, w3, w4, w5)	\
     GCC_IGNORE_WARNINGS_FOUR(w1, w2, w3, w4)			\
     _GCC_IGNORE_ONE(w5)			
#  define GCC_IGNORE_WARNINGS_SIX(w1, w2, w3, w4, w5, w6)		\
     GCC_IGNORE_WARNINGS_FIVE(w1, w2, w3, w4, w5)			\
     _GCC_IGNORE_ONE(w6)			

#  define GCC_RESTORE_WARNINGS _GCC_DO_PRAGMA(GCC diagnostic pop)
#else
#  define _GCC_DO_PRAGMA(x) 
#  define _GCC_IGNORE_ONE(w)
#  define GCC_IGNORE_WARNINGS_ONE(w1)
#  define GCC_IGNORE_WARNINGS_TWO(w1, w2)
#  define GCC_IGNORE_WARNINGS_THREE(w1, w2, w3)
#  define GCC_IGNORE_WARNINGS_FOUR(w1, w2, w3, w4)
#  define GCC_IGNORE_WARNINGS_FIVE(w1, w2, w3, w4, w5)
#  define GCC_IGNORE_WARNINGS_SIX(w1, w2, w3, w4, w5, w6)
#  define GCC_RESTORE_WARNINGS
#endif /* __GNUC__ */

#ifdef __clang__
#  pragma clang diagnostic pop
#endif /* __clang__ */

#endif /* MACROS_HPP_INCLUDED */
