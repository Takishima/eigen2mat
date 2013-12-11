#ifndef TENSOR_TO_MATRIX_HPP_INCLUDED
#define TENSOR_TO_MATRIX_HPP_INCLUDED

#include "definitions.hpp"

namespace eigen2mat {
     enum DIR_T {X, Y, Z};

     real_matrix_t tensor_to_matrix(const real_tensor_t& t, 
				    DIR_T dim, 
				    size_t idx);

     cmplx_matrix_t tensor_to_matrix(const cmplx_tensor_t& t,
				     DIR_T dim, 
				     size_t idx);

     /*
      * The two functions below are used to reproduce the following in MATLAB :
      * WARNING function is NO-OP is tensor is empty (third dim == 0)
      *
      * For dim_lhs = X & dim_rhs = X
      * t_lhs(idx_lhs, :, :) = t_rhs(idx_rhs, :, :)
      *
      * For dim_lhs = Y & dim_rhs = Y
      * t_lhs(:, idx_lhs, :) = t_rhs(:, idx_rhs, :) 
      */
     void tensor_slice_assign(real_tensor_t& t_lhs, DIR_T dim_lhs, size_t idx_lhs,
			      const real_tensor_t& t_rhs, DIR_T dim_rhs, size_t idx_rhs);

     void tensor_slice_assign(cmplx_tensor_t& t_lhs, DIR_T dim_lhs, size_t idx_lhs,
			      const cmplx_tensor_t& t_rhs, DIR_T dim_rhs, size_t idx_rhs);

     /*
      * The two functions below are used to reproduce the following in MATLAB :
      * WARNING function is NO-OP is tensor is empty (third dim == 0)
      *
      * For dim_lhs = X
      * t_lhs(idx_lhs, :, :) = m_rhs
      *
      * For dim_lhs = Y
      * t_lhs(:, idx_lhs, :) = m_rhs
      *
      * For dim_lhs = Z
      * t_lhs(:, idx_lhs, :) = m_rhs
      */
     void tensor_slice_assign(real_tensor_t& t_lhs, DIR_T dim_lhs, size_t idx_lhs,
			      const real_matrix_t& m_rhs);

     void tensor_slice_assign(cmplx_tensor_t& t_lhs, DIR_T dim_lhs, size_t idx_lhs,
			      const cmplx_matrix_t& m_rhs);

} // namespace eigen2mat

#endif /* TENSOR_TO_MATRIX_HPP_INCLUDED */
