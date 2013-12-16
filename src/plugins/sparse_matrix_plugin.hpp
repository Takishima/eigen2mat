#ifndef SPARSE_MATRIX_PLUGIN_HPP_INCLUDED
#define SPARSE_MATRIX_PLUGIN_HPP_INCLUDED
     
eigen2mat::sparse_slice<Scalar, Options, Index> slice(const std::vector<Index>& row_indices,
						      const std::vector<Index>& col_indices)
{
     return eigen2mat::sparse_slice<Scalar, Options, Index>(*this, row_indices, col_indices);
}

#endif /* SPARSE_MATRIX_PLUGIN_HPP_INCLUDED */
