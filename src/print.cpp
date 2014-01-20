#include "eigen2mat/print.hpp"
#include "eigen2mat/utils/macros.hpp"

#include "eigen2mat/utils/include_mex"

CLANG_IGNORE_WARNINGS_TWO(-Wsign-conversion,-Wsign-compare)

#ifdef EIGEN2MAT_NO_MATLAB
#  include <cstdio>
#  define PRINTF printf
#else
#  define PRINTF mexPrintf
#endif /* EIGEN2MAT_NO_MATLAB */

namespace e2m = eigen2mat;

void eigen2mat::print(const char* s)
{
     PRINTF("%s\n", s);
}

void eigen2mat::print(const std::string& s)
{
     PRINTF("%s\n", s.c_str());
}

// =============================================================================

void eigen2mat::print(double d) 
{
     PRINTF("%g\n", d);
}

// =====================================

void eigen2mat::print(int i) 
{
     PRINTF("%d\n", i);
}

// =====================================

void eigen2mat::print(e2m::size_t idx) 
{
     PRINTF("%d\n", idx);
}

// =====================================

void eigen2mat::print(const e2m::dcomplex& z)
{
     PRINTF("%g + %gi ", z.real(), z.imag());
}

// =============================================================================

void eigen2mat::print(const e2m::idx_array_t& v)
{
     for (auto i(0UL); i < v.size(); ++i) {
	  PRINTF("%d ", v[i]);
     }
     PRINTF("\n");
}

// =====================================

void eigen2mat::print(const e2m::int_array_t& v)
{
     for (auto i(0UL); i < v.size(); ++i) {
	  PRINTF("%d ", v[i]);
     }
     PRINTF("\n");
}

// =============================================================================

void eigen2mat::print(const e2m::real_vector_t& v) 
{
     for (auto i(0UL); i < v.size(); ++i) {
	  PRINTF("%g\n", v(i));
     }
}

// =====================================

void eigen2mat::print(const e2m::real_row_vector_t& v)
{
     for (auto i(0UL); i < v.size(); ++i) {
	  PRINTF("%g ", v(i));
     }
     PRINTF("\n");
}

// =====================================

void eigen2mat::print(const e2m::real_matrix_t& m) 
{
     for (auto i(0UL); i < m.rows(); ++i) {
	  for (auto j(0UL); j < m.cols(); ++j) {
	       PRINTF("%g ", m(i,j));
	  }
	  PRINTF("\n");
     }
     PRINTF("\n");
}

// =====================================

void eigen2mat::print(const e2m::real_sp_matrix_t& m) 
{
     for (auto k(0); k < m.outerSize(); ++k) {
	  for (e2m::real_sp_matrix_t::InnerIterator it(m,k); it; ++it) {
	       PRINTF("(%2d,%2d) = %g\n", it.row(), it.col(), it.value());
	  }
     }
}

// =====================================

void eigen2mat::print(const e2m::real_tensor_t& t) 
{
     for (auto i(0UL); i < t.size(); ++i) {
	  PRINTF("t(:,:,%d):\n", i);
	  print(t[i]);
     }
}

// =====================================

void eigen2mat::print(const e2m::real_sp_cell_t& c)
{
     for (auto i(0UL); i < c.size(); ++i) {
	  PRINTF("c{%d}:\n", i);
	  print(c[i]);
     }     
}

// =============================================================================

void eigen2mat::print(const e2m::cmplx_vector_t& v) 
{
     for (auto i(0UL); i < v.size(); ++i) {
	  print(v(i));
	  PRINTF("\n");
     }
}

// =====================================

void eigen2mat::print(const e2m::cmplx_row_vector_t& v)
{
     for (auto i(0UL); i < v.size(); ++i) {
	  print(v(i));
     }
     PRINTF("\n");
}

// =====================================

void eigen2mat::print(const e2m::cmplx_matrix_t& m) 
{
     for (auto i(0UL); i < m.rows(); ++i) {
	  for (auto j(0UL); j < m.cols(); ++j) {
	       print(m(i,j));
	  }
	  PRINTF("\n");
     }
     PRINTF("\n");
}

// =====================================

void eigen2mat::print(const e2m::cmplx_sp_matrix_t& m) 
{
     for (auto k(0); k < m.outerSize(); ++k) {
	  for (e2m::cmplx_sp_matrix_t::InnerIterator it(m,k); it; ++it) {
	       PRINTF("(%2d,%2d) = ", it.row(), it.col());
	       print(it.value());
	       PRINTF("\n");
	  }
     }
}

// =====================================

void eigen2mat::print(const e2m::cmplx_tensor_t& t) 
{
     for (auto i(0UL); i < t.size(); ++i) {
	  PRINTF("t(:,:,%d):\n", i);
	  print(t[i]);
     }
}


// =====================================

void eigen2mat::print(const e2m::cmplx_sp_cell_t& c)
{
     for (auto i(0UL); i < c.size(); ++i) {
	  PRINTF("c{%d}:\n", i);
	  print(c[i]);
     }     
}

CLANG_RESTORE_WARNINGS
