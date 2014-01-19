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
     void print(const char* s);
     void print(const std::string& s);

     void print(double d);
     void print(int i);
     void print(size_t idx);
     void print(const dcomplex& z);
     
     void print(const idx_array_t& v);
     void print(const int_array_t& v);
     
     void print(const real_vector_t& v);
     void print(const real_row_vector_t& v);
     void print(const real_matrix_t& m);
     void print(const real_sp_matrix_t& m);
     void print(const real_tensor_t& m);
     void print(const real_sp_cell_t& m);

     void print(const cmplx_vector_t& v);
     void print(const cmplx_row_vector_t& v);
     void print(const cmplx_matrix_t& m);
     void print(const cmplx_sp_matrix_t& m);
     void print(const cmplx_tensor_t& m);
     void print(const cmplx_sp_cell_t& m);
} // namespace eigen2mat

#endif /* PRINT_HPP_INCLUDED */
