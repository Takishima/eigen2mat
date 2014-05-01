// This file is part of eigen2mat, a simple C++ library to use
// Eigen with MATLAB's MEX files
//
// Copyright (C) 2013 Nguyen Damien <damien.nguyen@a3.epfl.ch>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef E2M_CONVERSION_HPP_INCLUDED
#define E2M_CONVERSION_HPP_INCLUDED

#include "eigen2mat/definitions.hpp"
#include "eigen2mat/utils/include_mex"

namespace eigen2mat {
     // MATLAB to eigen2mat
     /*!
      * \brief Convert mxArray to \c bool
      * 
      * \param b mxArray to convert
      * \return converted value
      */
     bool mxArray_to_bool(const mxArray* b);
     /*!
      * \brief Convert mxArray to \c double
      * 
      * \param d mxArray to convert
      * \return converted value
      */
     double mxArray_to_double(const mxArray* d);
     /*!
      * \brief Convert mxArray to \link definitions::size_t size_t\endlink
      * 
      * \param i mxArray to convert
      * \return converted value
      */
     size_t mxArray_to_idx(const mxArray* i);
     /*!
      * \brief Convert mxArray to \c int
      * 
      * \param i mxArray to convert
      * \return converted value
      */
     int mxArray_to_int(const mxArray* i);
     /*!
      * \brief Convert mxArray to \link definitions::dcomplex dcomplex\endlink
      * 
      * \param z mxArray to convert
      * \return converted value
      */
     dcomplex mxArray_to_cmplx(const mxArray* z);

     /*!
      * \brief Convert mxArray to \link definitions::idx_array_t idx_array_t\endlink
      * 
      * \param v mxArray to convert
      * \return converted value
      */
     idx_array_t mxArray_to_idx_array(const mxArray* v);
     /*!
      * \brief Convert mxArray to \link definitions::int_array_t int_array_t\endlink
      * 
      * \param v mxArray to convert
      * \return converted value
      */
     int_array_t mxArray_to_int_array(const mxArray* v);

     /*!
      * \brief Convert mxArray to \link definitions::real_vector_t real_vector_t\endlink
      * 
      * \param v mxArray to convert
      * \return converted value
      */
     real_vector_t mxArray_to_real_vector(const mxArray* v);
     /*!
      * \brief Convert mxArray to \link definitions::real_row_vector_t real_row_vector_t\endlink
      * 
      * \param v mxArray to convert
      * \return converted value
      */
     real_row_vector_t mxArray_to_real_row_vector(const mxArray* v);
     /*!
      * \brief Convert mxArray to \link definitions::real_matrix_t real_matrix_t\endlink
      * 
      * \param m mxArray to convert
      * \return converted value
      */
     real_matrix_t mxArray_to_real_matrix(const mxArray* m);
     /*!
      * \brief Convert mxArray to \link definitions::real_sp_matrix_t real_sp_matrix_t\endlink
      * 
      * \param m mxArray to convert
      * \return converted value
      */
     real_sp_matrix_t mxArray_to_real_sp_matrix(const mxArray* m);
     /*!
      * \brief Convert mxArray to \link definitions::real_tensor_t real_tensor_t\endlink
      * 
      * \param t mxArray to convert
      * \return converted value
      */
     real_tensor_t mxArray_to_real_tensor(const mxArray* t);
     /*!
      * \brief Convert mxArray to \link definitions::real_sp_tensor_t real_sp_tensor_t\endlink
      * 
      * \param t mxArray to convert
      * \return converted value
      */
     real_sp_tensor_t mxArray_to_real_sp_tensor(const mxArray* t);
     /*!
      * \brief Convert mxArray to \link definitions::real_sp_cell_t real_sp_cell_t\endlink
      * 
      * \param c mxArray to convert
      * \return converted value
      */
     real_sp_cell_t mxArray_to_real_sp_cell(const mxArray* c);

     /*!
      * \brief Convert mxArray to \link definitions::cmplx_vector_t cmplx_vector_t\endlink
      * 
      * \param v mxArray to convert
      * \return converted value
      */
     cmplx_vector_t mxArray_to_cmplx_vector(const mxArray* v);
     /*!
      * \brief Convert mxArray to \link definitions::cmplx_row_vector_t cmplx_row_vector_t\endlink
      * 
      * \param v mxArray to convert
      * \return converted value
      */
     cmplx_row_vector_t mxArray_to_cmplx_row_vector(const mxArray* v);
     /*!
      * \brief Convert mxArray to \link definitions::cmplx_matrix_t cmplx_matrix_t\endlink
      * 
      * \param m mxArray to convert
      * \return converted value
      */
     cmplx_matrix_t mxArray_to_cmplx_matrix(const mxArray* m);
     /*!
      * \brief Convert mxArray to \link definitions::cmplx_sp_matrix_t cmplx_sp_matrix_t \endlink
      * 
      * \param m mxArray to convert
      * \return converted value
      */
     cmplx_sp_matrix_t mxArray_to_cmplx_sp_matrix(const mxArray* m);
     /*!
      * \brief Convert mxArray to \link definitions::cmplx_tensor_t cmplx_tensor_t\endlink
      * 
      * \param t mxArray to convert
      * \return converted value
      */
     cmplx_tensor_t mxArray_to_cmplx_tensor(const mxArray* t);
     /*!
      * \brief Convert mxArray to \link definitions::cmplx_sp_tensor_t cmplx_sp_tensor_t\endlink
      * 
      * \param t mxArray to convert
      * \return converted value
      */
     cmplx_sp_tensor_t mxArray_to_cmplx_sp_tensor(const mxArray* t);
     /*!
      * \brief Convert mxArray to \link definitions::cmplx_sp_cell_t cmplx_sp_cell_t\endlink
      * 
      * \param c mxArray to convert
      * \return converted value
      */
     cmplx_sp_cell_t mxArray_to_cmplx_sp_cell(const mxArray* c);

     // ========================================================================
     // eigen2mat to MATLAB
     /*!
      * \brief Convert \c bool to mxArray
      * 
      * \param b value to be converted
      * \return mxArray with data stored in it
      */
     mxArray* to_mxArray(bool b);
     /*!
      * \brief Convert \c double to mxArray
      * 
      * \param d value to be converted
      * \return mxArray with data stored in it
      */
     mxArray* to_mxArray(double d);
     /*!
      * \brief Convert \c int to mxArray
      * 
      * \param i value to be converted
      * \return mxArray with data stored in it
      */
     mxArray* to_mxArray(int i);
     /*!
      * \brief Convert \link definitions::size_t size_t\endlink to mxArray
      * 
      * \param idx value to be converted
      * \return mxArray with data stored in it
      */
     mxArray* to_mxArray(size_t idx);
     /*!
      * \brief Convert \link definitions::dcomplex dcomplex\endlink to mxArray
      * 
      * \param z value to be converted
      * \return mxArray with data stored in it
      */
     mxArray* to_mxArray(const dcomplex& z);

     /*!
      * \brief Convert \link definitions::idx_array_t idx_array_t\endlink to mxArray
      * 
      * \param v value to be converted
      * \return mxArray with data stored in it
      */
     mxArray* to_mxArray(const idx_array_t& v);
     /*!
      * \brief Convert \link definitions::int_array_t int_array_t\endlink to mxArray
      * 
      * \param v value to be converted
      * \return mxArray with data stored in it
      */
     mxArray* to_mxArray(const int_array_t& v);

     /*!
      * \brief Convert \link definitions::real_sp_matrix_t real_sp_matrix_t\endlink to mxArray
      * 
      * \param m value to be converted
      * \return mxArray with data stored in it
      */
     mxArray* to_mxArray(const real_sp_matrix_t& m);
     /*!
      * \brief Convert \link definitions::real_tensor_t real_tensor_t\endlink to mxArray
      * 
      * \param t value to be converted
      * \return mxArray with data stored in it
      */
     mxArray* to_mxArray(const real_tensor_t& t);
     /*!
      * \brief Convert \link definitions::real_sp_cell_t real_sp_cell_t\endlink to mxArray
      * 
      * \param t value to be converted
      * \return mxArray with data stored in it
      */
     mxArray* to_mxArray(const real_sp_cell_t& t);

     /*!
      * \brief Convert \link definitions::cmplx_sp_matrix_t cmplx_sp_matrix_t\endlink to mxArray
      * 
      * \param m value to be converted
      * \return mxArray with data stored in it
      */
     mxArray* to_mxArray(const cmplx_sp_matrix_t& m);
     /*!
      * \brief Convert \link definitions::cmplx_tensor_t cmplx_tensor_t\endlink to mxArray
      * 
      * \param t value to be converted
      * \return mxArray with data stored in it
      */
     mxArray* to_mxArray(const cmplx_tensor_t& t);
     /*!
      * \brief Convert \link definitions::cmplx_sp_cell_t cmplx_sp_cell_t\endlink to mxArray
      * 
      * \param t value to be converted
      * \return mxArray with data stored in it
      */
     mxArray* to_mxArray(const cmplx_sp_cell_t& t);
     
     /*!
      * \brief Get the sizes of a 3D mxArray
      *
      * \param a input array
      * \return dimension array
      */
     dim_array_t get_dimensions(const mxArray* a);
} // namespace eigen2mat

#include "details/eigen_expressions_conversions.hpp"
#include "details/generic_conversions.hpp"

#endif /* E2M_CONVERSION_HPP_INCLUDED */
