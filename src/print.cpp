// This file is part of eigen2mat, a simple C++ library to use
// Eigen with MATLAB's MEX files
//
// Copyright (C) 2013 Nguyen Damien <damien.nguyen@a3.epfl.ch>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "eigen2mat/print.hpp"
#include "eigen2mat/utils/macros.hpp"

#include "eigen2mat/utils/include_mex"

CLANG_IGNORE_WARNINGS_TWO(-Wsign-conversion,-Wsign-compare)

namespace e2m = eigen2mat;

void eigen2mat::print(const char* s)
{
     print("%s\n", s);
}

void eigen2mat::print(const std::string& s)
{
     print("%s\n", s.c_str());
}

// =============================================================================

void eigen2mat::print(double d) 
{
     print("%.12g", d);
}

// =====================================

void eigen2mat::print(const e2m::dcomplex& z)
{
     print("%g + %gi", z.real(), z.imag());
}

// =============================================================================

void eigen2mat::print(const e2m::real_tensor_t& t) 
{
     for (auto i(0UL); i < t.size(); ++i) {
	  print("t(:,:,%d):\n", i);
	  print(t[i]);
     }
}

// =====================================

void eigen2mat::print(const e2m::real_sp_cell_t& c)
{
     for (auto i(0UL); i < c.size(); ++i) {
	  print("c{%d}:\n", i);
	  print(c[i]);
     }     
}

// =============================================================================

void eigen2mat::print(const e2m::cmplx_tensor_t& t) 
{
     for (auto i(0UL); i < t.size(); ++i) {
	  print("t(:,:,%d):\n", i);
	  print(t[i]);
     }
}


// =====================================

void eigen2mat::print(const e2m::cmplx_sp_cell_t& c)
{
     for (auto i(0UL); i < c.size(); ++i) {
	  print("c{%d}:\n", i);
	  print(c[i]);
     }     
}

CLANG_RESTORE_WARNINGS
