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

int main(int /*argc*/, char** /*argv*/)
{
     typedef Eigen::VectorXd real_vector_t;
     typedef Eigen::MatrixXd real_matrix_t;
     eigen2mat::cmplx_sp_matrix_t mat(10,7);
     using eigen2mat::dcomplex;
     mat.insert(0,0) = dcomplex(0, 0);
     mat.insert(1,0) = dcomplex(10, 0);
     mat.insert(5,0) = dcomplex(50, 0);
     mat.insert(0,1) = dcomplex(1, 0);
     mat.insert(3,1) = dcomplex(31, 0);
     mat.insert(4,4) = dcomplex(42, 0);
     mat.makeCompressed();
     eigen2mat::print(mat);

     std::vector<int> rows = {1, 2};
     std::vector<int> cols = {3, 7};

     eigen2mat::sparse_slice<dcomplex, 0, int> slice(mat, rows, cols);

     Eigen::MatrixXcd m = Eigen::MatrixXcd::Identity(2,2);

     slice = m;

     eigen2mat::print("=================");

     eigen2mat::print(mat);

     return 0;
}
