#include "conversion.hpp"
#include "sparse_slice.hpp"

#include "Eigen_Sparse"

#include "include_mex"

void mexFunction( int nlhs, mxArray *plhs[],
		  int nrhs, const mxArray*prhs[] )

{
     if (nrhs != 3) {
	  mexErrMsgTxt("Function requires three arguments (sparse matrix + range1 + range2)!");
     }
     if (nlhs != 1) {
     	  mexErrMsgTxt("Function requires one output argument!");
     }

     const auto a     = prhs[0];
     const auto mrows = prhs[1];
     const auto mcols = prhs[2];

     if (!mxIsSparse(a)) {
	  mexErrMsgTxt("Input argument is not sparse!");	  
     }

     eigen2mat::int_array_t rows = eigen2mat::mxArray_to_int_array(mrows);
     eigen2mat::int_array_t cols = eigen2mat::mxArray_to_int_array(mcols);

     // convert MATLAB indices to C++ indices...
     for (auto i(0UL) ; i < rows.size() ; ++i) {
	  rows[i] -= 1;
     }
     for (auto i(0UL) ; i < cols.size() ; ++i) {
	  cols[i] -= 1;
     }
     
     if (mxIsComplex(a)) {
	  auto m = eigen2mat::mxArray_to_cmplx_sp_matrix(a);
	  eigen2mat::sparse_slice<eigen2mat::dcomplex, 0, int> slice(m, rows, cols);
	  eigen2mat::cmplx_matrix_t oc = eigen2mat::cmplx_matrix_t::Ones(rows.size(), cols.size());
	  slice = oc;
	  plhs[0] = eigen2mat::to_mxArray(m);
     }
     else {
	  auto m = eigen2mat::mxArray_to_real_sp_matrix(a);
	  eigen2mat::sparse_slice<double, 0, int> slice(m, rows, cols);
	  eigen2mat::real_matrix_t o = eigen2mat::real_matrix_t::Ones(rows.size(), cols.size());
	  slice = o;
	  plhs[0] = eigen2mat::to_mxArray(m);
     }
}
