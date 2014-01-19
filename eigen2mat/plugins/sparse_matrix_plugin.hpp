// This file is part of eigen2mat, a simple C++ library to use
// Eigen with MATLAB's MEX files
//
// Copyright (C) 2013 Nguyen Damien <damien.nguyen@a3.epfl.ch>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SPARSE_MATRIX_PLUGIN_HPP_INCLUDED
#define SPARSE_MATRIX_PLUGIN_HPP_INCLUDED
     
eigen2mat::sparse_slice<Scalar, Options, Index> slice(const std::vector<Index>& row_indices,
						      const std::vector<Index>& col_indices)
{
     return eigen2mat::sparse_slice<Scalar, Options, Index>(*this, row_indices, col_indices);
}

#endif /* SPARSE_MATRIX_PLUGIN_HPP_INCLUDED */
