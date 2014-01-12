// #include "WCconstraint_types.hpp"
// #include "compprot_RFWC.hpp"

#include <iostream>
#include <iomanip>

#include "Eigen_Sparse"
#include "include_mex"

#include "conversion.hpp"
// #include "sys_t.hpp"
#include "print.hpp"
#include "sparse_slice.hpp"

#define EIGEN2MAT_NO_MATLAB

#ifdef EIGEN2MAT_NO_MATLAB
#  include <cstdio>
#  define PRINTF printf
#else
#  define PRINTF mexPrintf
#endif /* EIGEN2MAT_NO_MATLAB */

namespace eigen2mat {
void print(const Eigen::SparseMatrix<eigen2mat::dcomplex, 1>& m) 
{
     for (auto k(0); k < m.outerSize(); ++k) {
	  for (Eigen::SparseMatrix<eigen2mat::dcomplex, 1>::InnerIterator it(m,k); it; ++it) {
	       PRINTF("(%2d,%2d) = ", it.row(), it.col());
	       print(it.value());
	       PRINTF("\n");
	  }
     }
}
}

int main(int /*argc*/, char** /*argv*/)
{
     typedef Eigen::VectorXd real_vector_t;
     typedef Eigen::MatrixXd real_matrix_t;
     eigen2mat::cmplx_sp_matrix_t mat(10,7);
     // Eigen::SparseMatrix<eigen2mat::dcomplex, 1> mat(10,7);
     using eigen2mat::dcomplex;
     mat.insert(0,0) = dcomplex(-10, 0);
     mat.insert(1,0) = dcomplex(10, 0);
     mat.insert(5,0) = dcomplex(50, 0);
     mat.insert(0,1) = dcomplex(10, 0);
     mat.insert(3,1) = dcomplex(31, 0);
     mat.insert(4,4) = dcomplex(42, 0);
     mat.makeCompressed();
     eigen2mat::print(mat);
     eigen2mat::print("=================");

     mat.coeffRef(9, 6) = 100000;

     std::vector<int> rows(2); rows[0] = 1; rows[1] = 5;
     std::vector<int> cols(2); cols[0] = 5; cols[1] = 6;

     auto slice = mat.slice(rows, cols);    

     Eigen::MatrixXcd m = Eigen::MatrixXcd::Ones(2,1);
     Eigen::MatrixXcd m2 = Eigen::MatrixXcd::Ones(2,1);
     Eigen::MatrixXcd res = Eigen::MatrixXcd::Ones(2,2);

     m << 2,
	  6;
     m2 << 4,
	  8;

     slice.coeffRef(0, 0) = 10;
     slice.coeffRef(1, 0) = 110;
     slice.coeffRef(0, 1) = 11;
     slice.coeffRef(1, 1) = 111;

     eigen2mat::print(mat);
     eigen2mat::print("=================");

     // slice = m;
     slice << 1, 2,
	      3, 4;

     eigen2mat::print(mat);
     eigen2mat::print("=================");

     std::cout << std::flush;
     res << m, m2;
     eigen2mat::print(res);
     eigen2mat::print("=================");
     eigen2mat::print("=================");

     slice << m, m2;

     eigen2mat::print(mat);
     eigen2mat::print("=================");


     // std::cin.get();

     return 0;
}
