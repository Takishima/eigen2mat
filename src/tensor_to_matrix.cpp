// This file is part of eigen2mat, a simple C++ library to use
// Eigen with MATLAB's MEX files
//
// Copyright (C) 2013 Nguyen Damien <damien.nguyen@a3.epfl.ch>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "eigen2mat/tensor_to_matrix.hpp"
#include "eigen2mat/utils/macros.hpp"

#include "eigen2mat/utils/include_mex"

namespace e2m = eigen2mat;

CLANG_IGNORE_WARNINGS_ONE(-Wsign-conversion)

template <typename matrix_t>
matrix_t tensor_to_matrix_helper(const std::vector<matrix_t>& t,
				 e2m::DIR_T dim,
				 size_t idx)
{
     const auto P = t.size();

     if (P == 0) {
	  return matrix_t();
     }

     const auto M = t[0].rows();
     const auto N = t[0].cols();
     if (dim == eigen2mat::X) {
	  matrix_t r(N, P);
	  for (auto j(0); j < N; ++j) {
	       for (auto k(0UL); k < P; ++k) {
		    r(j,k) = t[k](idx,j);
	       }
	  }
	  return r;
     }
     else if (dim == eigen2mat::Y) {
	  matrix_t r(M, P);
	  for (auto i(0); i < N; ++i) {
	       for (auto k(0UL); k < P; ++k) {
		    r(i,k) = t[k](i,idx);
	       }
	  }
	  return r;
     }
     else if (dim == eigen2mat::Z) {
	  return t[idx];
     }
     else {
	  return matrix_t();
     }
}

// =====================================

eigen2mat::real_matrix_t eigen2mat::tensor_to_matrix(const e2m::real_tensor_t& t, 
						     e2m::DIR_T dim, 
						     e2m::size_t idx)
{
     return tensor_to_matrix_helper<e2m::real_matrix_t>(t, dim, idx);
}

// =====================================

eigen2mat::cmplx_matrix_t eigen2mat::tensor_to_matrix(const e2m::cmplx_tensor_t& t, 
						      e2m::DIR_T dim, 
						      e2m::size_t idx)
{
     return tensor_to_matrix_helper<e2m::cmplx_matrix_t>(t, dim, idx);
}

// =============================================================================

template <typename matrix_t>
void tensor_slice_assign_helper(std::vector<matrix_t>& t_lhs,
				e2m::DIR_T dim_lhs,
				e2m::size_t idx_lhs,
				const std::vector<matrix_t>& t_rhs,
				e2m::DIR_T dim_rhs,
				e2m::size_t idx_rhs)
{
     const e2m::size_t P_lhs = t_lhs.size();
     const e2m::size_t P_rhs = t_rhs.size();

     if (P_lhs == 0 || P_rhs == 0) {
	  // if either tensor has no elements, do nothing
	  return;
     }

     const e2m::size_t M_lhs = t_lhs[0].rows();
     const e2m::size_t N_lhs = t_lhs[0].cols();

#ifndef NDEBUG
     const e2m::size_t M_rhs = t_rhs[0].rows();
     const e2m::size_t N_rhs = t_rhs[0].cols();     
#endif /* NDEBUG */

     if (dim_lhs == e2m::Z && dim_rhs == e2m::Z) {
	  assert(M_lhs == M_rhs && N_lhs == N_rhs);
	  t_lhs[idx_lhs] = t_rhs[idx_rhs];
     }
     else if (dim_lhs == e2m::X && dim_rhs == e2m::X) {
	  // t_lhs(i1, :, :) = t_rhs(i2, :, :);
	  assert(N_lhs == N_rhs && P_lhs == P_rhs);
	  for (auto j(0UL); j < N_lhs; ++j) {
	       for (auto k(0UL); k < P_lhs; ++k) {
		    t_lhs[k](idx_lhs, j) = t_rhs[k](idx_rhs, j);
	       }
	  }
     }
     else if (dim_lhs == e2m::Y && dim_rhs == e2m::Y) {
	  // t_lhs(:, i1, :) = t_rhs(:, i2, :);
	  assert(M_lhs == M_rhs && P_lhs == P_rhs);
	  for (auto i(0UL); i < M_lhs; ++i) {
	       for (auto k(0UL); k < P_lhs; ++k) {
		    t_lhs[k](i, idx_lhs) = t_rhs[k](i, idx_rhs);
	       }
	  }
     }
     else {
	  mexErrMsgTxt("tensor_slice_assign_helper(): unsupported operation");
     }


     // else if (dim_lhs == e2m::X && dim_rhs == e2m::Z) {
     //		  // t_lhs(i1, :, :) = t_rhs(:,:,i2);
     //		  assert(N_lhs == M_rhs && P_lhs == N_rhs);
     //		  auto& mat = t_rhs[idx_rhs];
     //		  for (auto j(0UL); j < N_lhs; ++j) {
     //		       for (auto k(0UL); k < P_lhs; ++k) {
     //			    t_lhs[k](idx_lhs, j) = mat(j, k);
     //		       }
     //		  }
     // }
     // else if (dim_lhs == e2m::Y && dim_rhs == e2m::Z) {
     //		  // t_lhs(:, i1, :) = t_rhs(:,:,i2);
     //		  assert(M_lhs == M_rhs && P_lhs == N_rhs);
     //		  auto& mat = t_rhs[idx_rhs];
     //		  for (auto i(0UL); i < N_lhs; ++i) {
     //		       for (auto k(0UL); k < P_lhs; ++k) {
     //			    t_lhs[k](i, idx_lhs) = mat(i, k);
     //		       }
     //		  }
     // }
     // else if (dim_lhs == e2m::Z && dim_rhs == e2m::X) {
     //		  // t_lhs(:, :, i1) = t_rhs(i1, :, :);
     //		  assert(M_lhs == N_rhs && N_lhs == P_rhs);
     //		  auto& mat = t_lhs[idx_lhs];
     //		  for (auto i(0UL); i < M_lhs; ++i) {
     //		       for (auto j(0UL); j < N_lhs; ++j) {
     //			    mat(i, j) = t_rhs[j](idx_rhs, i);
     //		       }
     //		  }
     // }
     // else if (dim_lhs ==  e2m::Z && dim_rhs == e2m::Y) {
     //		  // t_lhs(:, :, i1) = t_rhs(:, i1, :);
     //		  assert(M_lhs == M_rhs && N_lhs == P_rhs);
     //		  auto& mat = t_lhs[idx_lhs];
     //		  for (auto i(0UL); i < M_lhs; ++i) {
     //		       for (auto j(0UL); j < N_lhs; ++j) {
     //			    mat(i, j) = t_rhs[j](i, idx_rhs);
     //		       }
     //		  }
     // }
     // else if (dim_lhs == e2m::X && dim_rhs == e2m::Y) {
     //		  // t_lhs(i1, :, :) = t_rhs(:, i2, :);
     //		  assert(N_lhs == M_rhs && P_lhs == P_rhs);
     //		  for (auto j(0UL); j < N_lhs; ++j) {
     //		       for (auto k(0UL); k < P_lhs; ++k) {
     //			    t_lhs[k](idx_lhs, j) = t_rhs[k](j, idx_rhs);
     //		       }
     //		  }
     // }
     // else {
     //		  // dim_lhs == e2m::Y && dim_rhs == e2m::X
     //		  // t_lhs(:, i1, :) = t_rhs(i2, :, :);
     //		  assert(M_lhs == N_rhs && P_lhs == P_rhs);
     //		  for (auto j(0UL); j < M_lhs; ++j) {
     //		       for (auto k(0UL); k < P_lhs; ++k) {
     //			    t_lhs[k](j, idx_lhs) = t_rhs[k](idx_rhs, j);
     //		       }
     //		  }
     // }
}

// =====================================

void e2m::tensor_slice_assign(e2m::real_tensor_t& t_lhs, e2m::DIR_T dim_lhs, e2m::size_t idx_lhs,
			      const e2m::real_tensor_t& t_rhs, e2m::DIR_T dim_rhs, e2m::size_t idx_rhs)
{
     tensor_slice_assign_helper<real_matrix_t>(t_lhs, dim_lhs, idx_lhs,
					       t_rhs, dim_rhs, idx_rhs);
}

// =====================================

void e2m::tensor_slice_assign(e2m::cmplx_tensor_t& t_lhs, e2m::DIR_T dim_lhs, e2m::size_t idx_lhs,
			      const e2m::cmplx_tensor_t& t_rhs, e2m::DIR_T dim_rhs, e2m::size_t idx_rhs)
{
     tensor_slice_assign_helper<cmplx_matrix_t>(t_lhs, dim_lhs, idx_lhs,
						t_rhs, dim_rhs, idx_rhs);
}

// =============================================================================

template <typename matrix_t>
void tensor_slice_assign_helper(std::vector<matrix_t>& t_lhs,
				e2m::DIR_T dim_lhs,
				e2m::size_t idx_lhs,
				const matrix_t& m_rhs)
{
     const size_t P_lhs = t_lhs.size();

     if (P_lhs == 0) {
	  // if tensor has no elements, do nothing
	  return;
     }

     const size_t M_lhs = t_lhs[0].rows();
     const size_t N_lhs = t_lhs[0].cols();

#ifndef NDEBUG
     const size_t M_rhs = m_rhs.rows();
     const size_t N_rhs = m_rhs.cols();     
#endif /* NDEBUG */
     
     if (dim_lhs == e2m::Z) {
	  // t_lhs(:, :, i1) = m_rhs(:, :);
	  assert(M_lhs == M_rhs && N_lhs == N_rhs);
	  t_lhs[idx_lhs] = m_rhs;
     }
     else if (dim_lhs == e2m::X) {
	  // t_lhs(i1, :, :) = m_rhs(:, :);
	  assert(N_lhs == N_rhs && P_lhs == M_rhs);
	  for (auto j(0UL); j < N_lhs; ++j) {
	       for (auto k(0UL); k < P_lhs; ++k) {
		    t_lhs[k](idx_lhs, j) = m_rhs(j, k);
	       }
	  }
     }
     else if (dim_lhs == e2m::Y) {
	  // t_lhs(:, i1, :) = m_rhs(:, :);
	  assert(M_lhs == M_rhs && P_lhs == M_rhs);
	  for (auto i(0UL); i < M_lhs; ++i) {
	       for (auto k(0UL); k < P_lhs; ++k) {
		    t_lhs[k](i, idx_lhs) = m_rhs(i, k);
	       }
	  }
     }
     else {
	  mexErrMsgTxt("tensor_slice_assign_helper(matrix version): unsupported operation");
     }
}
// =====================================

void e2m::tensor_slice_assign(e2m::real_tensor_t& t_lhs, e2m::DIR_T dim_lhs, e2m::size_t idx_lhs,
			      const e2m::real_matrix_t& m_rhs)
{
     tensor_slice_assign_helper(t_lhs, dim_lhs, idx_lhs, m_rhs);
}

// =====================================

void e2m::tensor_slice_assign(e2m::cmplx_tensor_t& t_lhs, e2m::DIR_T dim_lhs, e2m::size_t idx_lhs,
			      const e2m::cmplx_matrix_t& m_rhs)
{
     tensor_slice_assign_helper(t_lhs, dim_lhs, idx_lhs, m_rhs);
}

// =============================================================================

CLANG_RESTORE_WARNINGS
