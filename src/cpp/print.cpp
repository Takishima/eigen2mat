#include "print.hpp"
#include "include_mex"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wsign-compare"

/*
  void print(double d);
  void print(real_vector_t v);
  void print(real_matrix_t m);
  void print(dcomplex z);
  void print(cmplx_vector_t v);
  void print(cmplx_matrix_t m);

*/

void mymex::print(const char* s)
{
     mexPrintf("%s\n", s);
}

void mymex::print(const std::string& s)
{
     mexPrintf("%s\n", s.c_str());
}

// =============================================================================

void mymex::print(double d) 
{
     mexPrintf("%g\n", d);
}

// =====================================

void mymex::print(int i) 
{
     mexPrintf("%d\n", i);
}

// =====================================

void mymex::print(size_t idx) 
{
     mexPrintf("%d\n", idx);
}

// =====================================

void mymex::print(const dcomplex& z)
{
     mexPrintf("%g + %gi ", z.real(), z.imag());
}

// =============================================================================

void mymex::print(const idx_array_t& v)
{
     for (auto i(0UL); i < v.size(); ++i) {
	  mexPrintf("%d ", v[i]);
     }
     mexPrintf("\n");
}

// =====================================

void mymex::print(const int_array_t& v)
{
     for (auto i(0UL); i < v.size(); ++i) {
	  mexPrintf("%d ", v[i]);
     }
     mexPrintf("\n");
}

// =============================================================================

void mymex::print(const real_vector_t& v) 
{
     for (auto i(0UL); i < v.size(); ++i) {
	  mexPrintf("%g\n", v(i));
     }
}

// =====================================

void mymex::print(const real_row_vector_t& v)
{
     for (auto i(0UL); i < v.size(); ++i) {
	  mexPrintf("%g ", v(i));
     }
     mexPrintf("\n");
}

// =====================================

void mymex::print(const real_matrix_t& m) 
{
     for (auto i(0UL); i < m.rows(); ++i) {
	  for (auto j(0UL); j < m.cols(); ++j) {
	       mexPrintf("%g ", m(i,j));
	  }
	  mexPrintf("\n");
     }
     mexPrintf("\n");
}

// =====================================

void mymex::print(const real_sp_matrix_t& m) 
{
     for (auto k(0); k < m.outerSize(); ++k) {
	  for (real_sp_matrix_t::InnerIterator it(m,k); it; ++it) {
	       mexPrintf("(%2d,%2d) = %g\n", it.row(), it.col(), it.value());
	  }
     }
}

// =====================================

void mymex::print(const real_tensor_t& t) 
{
     for (auto i(0UL); i < t.size(); ++i) {
	  mexPrintf("t(:,:,%d):\n", i);
	  print(t[i]);
     }
}

// =====================================

void mymex::print(const real_sp_cell_t& c)
{
     for (auto i(0UL); i < c.size(); ++i) {
	  mexPrintf("c{%d}:\n", i);
	  print(c[i]);
     }     
}

// =============================================================================

void mymex::print(const cmplx_vector_t& v) 
{
     for (auto i(0UL); i < v.size(); ++i) {
	  print(v(i));
	  mexPrintf("\n");
     }
}

// =====================================

void mymex::print(const cmplx_row_vector_t& v)
{
     for (auto i(0UL); i < v.size(); ++i) {
	  print(v(i));
     }
     mexPrintf("\n");
}

// =====================================

void mymex::print(const cmplx_matrix_t& m) 
{
     for (auto i(0UL); i < m.rows(); ++i) {
	  for (auto j(0UL); j < m.cols(); ++j) {
	       print(m(i,j));
	  }
	  mexPrintf("\n");
     }
     mexPrintf("\n");
}

// =====================================

void mymex::print(const cmplx_sp_matrix_t& m) 
{
     for (auto k(0); k < m.outerSize(); ++k) {
	  for (cmplx_sp_matrix_t::InnerIterator it(m,k); it; ++it) {
	       mexPrintf("(%2d,%2d) = ", it.row(), it.col());
	       print(it.value());
	       mexPrintf("\n");
	  }
     }
}

// =====================================

void mymex::print(const cmplx_tensor_t& t) 
{
     for (auto i(0UL); i < t.size(); ++i) {
	  mexPrintf("t(:,:,%d):\n", i);
	  print(t[i]);
     }
}


// =====================================

void mymex::print(const cmplx_sp_cell_t& c)
{
     for (auto i(0UL); i < c.size(); ++i) {
	  mexPrintf("c{%d}:\n", i);
	  print(c[i]);
     }     
}

#pragma clang diagnostic pop
