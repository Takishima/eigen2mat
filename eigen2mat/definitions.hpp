// This file is part of eigen2mat, a simple C++ library to use
// Eigen with MATLAB's MEX files
//
// Copyright (C) 2013 Nguyen Damien <damien.nguyen@a3.epfl.ch>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef EIGEN2MAT_DEFINITIONS_HPP_INCLUDED
#define EIGEN2MAT_DEFINITIONS_HPP_INCLUDED

#include <cstddef>

#include "eigen2mat/utils/Eigen_Core"
#include "eigen2mat/utils/Eigen_Sparse"
#include "eigen2mat/utils/forward_declarations.hpp"

#include <array>
#include <complex>
#include <vector>

namespace eigen2mat {
namespace definitions {
     // Scalars
     typedef std::size_t size_t;
     typedef std::complex<double> dcomplex;

     // Arrays
     typedef std::array<size_t, 3> dim_array_t;
     typedef std::vector<size_t> idx_array_t;
     typedef std::vector<int> int_array_t;

     // Vectors
     typedef Eigen::VectorXd real_vector_t;
     typedef Eigen::RowVectorXd real_row_vector_t;
     typedef Eigen::VectorXcd cmplx_vector_t;
     typedef Eigen::RowVectorXcd cmplx_row_vector_t;

     // Vector blocks
     typedef Eigen::VectorBlock<real_vector_t> real_vblock_t;
     typedef Eigen::VectorBlock<real_row_vector_t> real_row_vblock_t;
     typedef Eigen::VectorBlock<cmplx_vector_t> cmplx_vblock_t;
     typedef Eigen::VectorBlock<cmplx_row_vector_t> cmplx_row_vblock_t;

     // Matrices
     typedef Eigen::MatrixXd real_matrix_t;
     typedef Eigen::MatrixXcd cmplx_matrix_t;

     // Matrix blocks
     typedef Eigen::Block<real_matrix_t> real_mblock_t;
     typedef Eigen::Block<cmplx_matrix_t> cmplx_mblock_t;
     typedef real_matrix_t::RowXpr real_row_t;
     typedef cmplx_matrix_t::RowXpr cmplx_row_t;
     typedef real_matrix_t::ConstRowXpr const_real_row_t;
     typedef cmplx_matrix_t::ConstRowXpr const_cmplx_row_t;
     typedef real_matrix_t::ConstColsBlockXpr const_real_cblock_t;
     typedef cmplx_matrix_t::ConstColsBlockXpr const_cmplx_cblock_t;
     typedef Eigen::Block<const real_matrix_t> const_real_mblock_t;
     typedef Eigen::Block<const cmplx_matrix_t> const_cmplx_mblock_t;

     // Sparse matrices
     typedef Eigen::SparseMatrix<double,   0, int> real_sp_matrix_t;
     typedef Eigen::SparseMatrix<dcomplex, 0, int> cmplx_sp_matrix_t;

     // Sparse matrix blocks & slices
     typedef Eigen::Block<real_sp_matrix_t> real_spblock_t;
     typedef Eigen::Block<cmplx_sp_matrix_t> cmplx_spblock_t;
     typedef sparse_slice<real_sp_matrix_t> real_spslice_t;
     typedef sparse_slice<cmplx_sp_matrix_t> cmplx_spslice_t;

     // Tensors
     typedef std::vector<real_matrix_t> real_tensor_t;
     typedef std::vector<cmplx_matrix_t> cmplx_tensor_t;
     typedef std::vector<real_sp_matrix_t> real_sp_tensor_t;
     typedef std::vector<cmplx_sp_matrix_t> cmplx_sp_tensor_t;

     // Tensor blocks
     typedef tensor_block_t<real_tensor_t> real_tblock_t;
     typedef tensor_block_t<cmplx_tensor_t> cmplx_tblock_t;

     // Cell arrays
     typedef std::vector<real_sp_matrix_t> real_sp_cell_t;
     typedef std::vector<cmplx_sp_matrix_t> cmplx_sp_cell_t;

     // Cell arrays block
     typedef tensor_block_t<real_sp_cell_t> real_spcblock_t;
     typedef tensor_block_t<cmplx_sp_cell_t> cmplx_spcblock_t;

     // Eigen Maps
     typedef Eigen::Map<real_vector_t> real_map_vec_t;
     typedef Eigen::Map<cmplx_vector_t> cmplx_map_vec_t;
     typedef Eigen::Map<real_matrix_t> real_map_mat_t;
     typedef Eigen::Map<cmplx_matrix_t> cmplx_map_mat_t;     
} // namespace definitions

     using namespace definitions;
} // namespace eigen2mat

#include "tensor_block.hpp"
#include "sparse_slice.hpp"

#endif //EIGEN2MAT_DEFINITIONS_HPP_INCLUDED
