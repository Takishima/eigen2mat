// This file is part of eigen2mat, a simple C++ library to use
// Eigen with MATLAB's MEX files
//
// Copyright (C) 2013 Nguyen Damien <damien.nguyen@a3.epfl.ch>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CONVERSION_HPP_INCLUDED
#define CONVERSION_HPP_INCLUDED

#include "definitions.hpp"
#include "include_mex"

namespace eigen2mat {
     // MATLAB to eigen2mat
     bool mxArray_to_bool(const mxArray* b);
     double mxArray_to_double(const mxArray* d);
     size_t mxArray_to_idx(const mxArray* d);
     int mxArray_to_int(const mxArray* d);
     dcomplex mxArray_to_cmplx(const mxArray* d);

     idx_array_t mxArray_to_idx_array(const mxArray* v);
     int_array_t mxArray_to_int_array(const mxArray* v);

     real_vector_t mxArray_to_real_vector(const mxArray* v);
     real_row_vector_t mxArray_to_real_row_vector(const mxArray* v);
     real_matrix_t mxArray_to_real_matrix(const mxArray* m);
     real_sp_matrix_t mxArray_to_real_sp_matrix(const mxArray* m);
     real_tensor_t mxArray_to_real_tensor(const mxArray* m);
     real_sp_cell_t mxArray_to_real_sp_cell(const mxArray* c);

     cmplx_vector_t mxArray_to_cmplx_vector(const mxArray* v);
     cmplx_row_vector_t mxArray_to_cmplx_row_vector(const mxArray* v);
     cmplx_matrix_t mxArray_to_cmplx_matrix(const mxArray* m);
     cmplx_sp_matrix_t mxArray_to_cmplx_sp_matrix(const mxArray* m);
     cmplx_tensor_t mxArray_to_cmplx_tensor(const mxArray* m);
     cmplx_sp_cell_t mxArray_to_cmplx_sp_cell(const mxArray* c);

     // eigen2mat to MATLAB
     mxArray* to_mxArray(bool b);
     mxArray* to_mxArray(double d);
     mxArray* to_mxArray(int i);
     mxArray* to_mxArray(size_t idx);
     mxArray* to_mxArray(const dcomplex& z);

     mxArray* to_mxArray(const idx_array_t& v);
     mxArray* to_mxArray(const int_array_t& v);

     mxArray* to_mxArray(const real_vector_t& v);
     mxArray* to_mxArray(const real_row_vector_t& v);
     mxArray* to_mxArray(const real_matrix_t& m);
     mxArray* to_mxArray(const real_sp_matrix_t& m);
     mxArray* to_mxArray(const real_tensor_t& t);
     mxArray* to_mxArray(const real_sp_cell_t& t);

     mxArray* to_mxArray(const cmplx_vector_t& v);
     mxArray* to_mxArray(const cmplx_row_vector_t& v);
     mxArray* to_mxArray(const cmplx_matrix_t& m);
     mxArray* to_mxArray(const cmplx_sp_matrix_t& m);
     mxArray* to_mxArray(const cmplx_tensor_t& t);
     mxArray* to_mxArray(const cmplx_sp_cell_t& t);
     
     // others
     dim_array_t get_dimensions(const mxArray* a);
} // namespace eigen2mat

#endif /* CONVERSION_HPP_INCLUDED */
