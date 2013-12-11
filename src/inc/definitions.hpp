#ifndef DEFINITIONS_HPP_INCLUDED
#define DEFINITIONS_HPP_INCLUDED

#include <cstddef>

#ifdef WITH_CPP11
#  define NULLPTR nullptr
#else
#  define NULLPTR NULL
#endif // WITH_CPP11

#define concat(a, b) a # b
#define myassert(x) \
     mxAssert(x, concat(concat(_FILE__,":"),__LINE__)); \
     assert(x)

#include "tensor_block.hpp"

#include "Eigen_Core"
#include "Eigen_Sparse"

#include <array>
#include <complex>
#include <vector>

namespace eigen2mat {
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
     typedef real_matrix_t::ConstColsBlockXpr const_real_cblock_t;
     typedef cmplx_matrix_t::ConstColsBlockXpr const_cmplx_cblock_t;
     typedef Eigen::Block<const real_matrix_t> const_real_mblock_t;
     typedef Eigen::Block<const cmplx_matrix_t> const_cmplx_mblock_t;

     // Sparse matrices
     typedef Eigen::SparseMatrix<double> real_sp_matrix_t;
     typedef Eigen::SparseMatrix<dcomplex> cmplx_sp_matrix_t;

     // Sparse matrix blocks
     typedef Eigen::Block<real_sp_matrix_t> real_spblock_t;
     typedef Eigen::Block<cmplx_sp_matrix_t> cmplx_spblock_t;

     // Tensors
     typedef std::vector<real_matrix_t> real_tensor_t;
     typedef std::vector<cmplx_matrix_t> cmplx_tensor_t;

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
} // namespace eigen2mat

#endif //DEFINITIONS_HPP_INCLUDED
