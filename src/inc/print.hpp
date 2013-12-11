#ifndef PRINT_HPP_INCLUDED
#define PRINT_HPP_INCLUDED

#include "definitions.hpp"

#include <string>

namespace mymex {
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
} // namespace mymex

#endif /* PRINT_HPP_INCLUDED */
