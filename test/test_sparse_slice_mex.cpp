#include "conversion.hpp"
#include "sparse_slice.hpp"

#include "Eigen_Sparse"

#include "include_mex"

void mexFunction( int nlhs, mxArray *plhs[],
		  int nrhs, const mxArray*prhs[] )

{
     if (nrhs != 1) {
	  mexErrMsgTxt("Function requires only one argument!");
     }
     if (nlhs != 1) {
	  mexErrMsgTxt("Function requires one output argument!");
     }

     const auto a = prhs[0];

     if (!mxIsSparse(a)) {
	  mexErrMsgTxt("Input argument is not sparse!");	  
     }

     std::vector<int> rows(2); rows[0] = 1; rows[1] = 5;
     std::vector<int> cols(2); cols[0] = 5; cols[1] = 6;

     if (mxIsComplex(a)) {
	  mexPrintf("Got a complex sparse matrix...\n");
	  auto m = eigen2mat::mxArray_to_cmplx_sp_matrix(a);
	  mexPrintf("  creating slice...\n");
	  eigen2mat::sparse_slice<eigen2mat::dcomplex, decltype(m)::Options, int> slice(m, rows, cols);
	  eigen2mat::cmplx_matrix_t oc = eigen2mat::cmplx_matrix_t::Ones(rows.size(), cols.size());
	  mexPrintf("  assigning to slice...\n");
	  // slice = oc;
	  mexPrintf("  creating output...\n");
	  plhs[0] = eigen2mat::to_mxArray(m);
     }
     else {
	  mexPrintf("Got a real sparse matrix...\n");
	  Eigen::SparseMatrix<double> m(14, 14);
	  m.insert(1, 5) = 10;
	  // auto m = eigen2mat::mxArray_to_real_sp_matrix(a);
	  mexPrintf("  creating slice...\n");
	  eigen2mat::sparse_slice<double, decltype(m)::Options, int> slice(m, rows, cols);
	  eigen2mat::real_matrix_t o = eigen2mat::real_matrix_t::Ones(rows.size(), cols.size());
	  mexPrintf("  assigning to slice...\n");
	  
	  // m.insert(1, 5) = 10;
	  // slice = o;
	  mexPrintf("  creating output...\n");
	  plhs[0] = eigen2mat::to_mxArray(m);
     }
}
