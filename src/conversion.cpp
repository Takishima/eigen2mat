// This file is part of eigen2mat, a simple C++ library to use
// Eigen with MATLAB's MEX files
//
// Copyright (C) 2013 Nguyen Damien <damien.nguyen@a3.epfl.ch>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "eigen2mat/utils/macros.hpp"

MSVC_IGNORE_WARNINGS(4018 4068 4244 4267 4800)

CLANG_IGNORE_WARNINGS_FOUR(-Wundefined-reinterpret-cast,	\
			   -Wconversion,			\
			   -Wsign-conversion,			\
			   -Wc++98-compat-pedantic)

// =============================================================================

#include "eigen2mat/conversion.hpp"

#include <algorithm>
#include <type_traits> 

namespace e2m = eigen2mat;

// =============================================================================

template <typename T>
T mxArray_to_single_helper(const mxArray* a)
{
     const auto M = mxGetM(a);
     const auto N = mxGetN(a);

     if (M != 1 || N != 1) {
	  mexErrMsgTxt("Input is not a scalar");
     }

     mxClassID id = mxGetClassID(a);
     T r(0);
     if (id == mxSINGLE_CLASS) {
	  r = *reinterpret_cast<float*>(mxGetPr(a));
     }
     else if (id == mxDOUBLE_CLASS) {
	  r = *mxGetPr(a);
     }
     else if (id == mxLOGICAL_CLASS) { 
	  r = *reinterpret_cast<mxLogical*>(mxGetPr(a));
     }
     else if (id == mxINT8_CLASS) { 
	  r = *reinterpret_cast<char*>(mxGetPr(a));
     }
     else if (id == mxINT16_CLASS) {
	  r = *reinterpret_cast<short*>(mxGetPr(a));
     }
     else if (id == mxINT32_CLASS) {
	  r = *reinterpret_cast<int*>(mxGetPr(a));
     } 
     else if (id == mxINT64_CLASS) {
	  r = *reinterpret_cast<long long*>(mxGetPr(a));
     }
     else if (id == mxUINT8_CLASS) { 
	  r = *reinterpret_cast<unsigned char*>(mxGetPr(a));
     }
     else if (id == mxUINT16_CLASS) {
	  r = *reinterpret_cast<unsigned short*>(mxGetPr(a));
     }
     else if (id == mxUINT32_CLASS) {
	  r = *reinterpret_cast<unsigned int*>(mxGetPr(a));
     } 
     else if (id == mxUINT64_CLASS) {
	  r = *reinterpret_cast<unsigned long long*>(mxGetPr(a));
     }
     else {
	  mexErrMsgTxt("mxArray_to_single_helper(): argument is not numeric!");
     }

     return r;
}


// Copy SIZE elements from a to dest
template <typename pointer_t>
void copy_from_mxArray_helper(const mxArray* a, 
			      eigen2mat::size_t SIZE, 
			      pointer_t dest)
{
     mxClassID id = mxGetClassID(a);
     if (id == mxSINGLE_CLASS) {
	  float* data = reinterpret_cast<float*>(mxGetPr(a));
	  std::copy(data, data + SIZE, dest);
     }
     else if ( id == mxDOUBLE_CLASS) {
	  double* data = mxGetPr(a);
	  std::copy(data, data + SIZE, dest);
     }
     else if (id == mxINT8_CLASS) {
	  char* data = reinterpret_cast<char*>(mxGetPr(a));
	  std::copy(data, data + SIZE, dest);
     }
     else if (id == mxINT16_CLASS) {
	  short* data = reinterpret_cast<short*>(mxGetPr(a));
	  std::copy(data, data + SIZE, dest);
     }
     else if (id == mxINT32_CLASS) {
	  int* data = reinterpret_cast<int*>(mxGetPr(a));
	  std::copy(data, data + SIZE, dest);
     }
     else if (id == mxINT64_CLASS) {
	  long long* data = reinterpret_cast<long long*>(mxGetPr(a));
	  std::copy(data, data + SIZE, dest);
     }
     else if (id == mxUINT8_CLASS) {
	  unsigned char* data = 
	       reinterpret_cast<unsigned char*>(mxGetPr(a));
	  std::copy(data, data + SIZE, dest);
     }
     else if (id == mxUINT16_CLASS) {
	  unsigned short* data = 
	       reinterpret_cast<unsigned short*>(mxGetPr(a));
	  std::copy(data, data + SIZE, dest);
     }
     else if (id == mxUINT32_CLASS) {
	  unsigned int* data = reinterpret_cast<unsigned int*>(mxGetPr(a));
	  std::copy(data, data + SIZE, dest);
     }
     else if (id == mxUINT64_CLASS) {
	  unsigned long long* data = 
	       reinterpret_cast<unsigned long long*>(mxGetPr(a));
	  std::copy(data, data + SIZE, dest);
     }
     else {
	  mexErrMsgTxt("copy_from_mxArray_helper(): argument is not numeric!");
     }     
}

template <typename cell_array_t>
mxArray* to_1Dcell_array_helper(const cell_array_t& t)
{
     const mwSize dims[1] = {t.size()};
     
     auto ret = mxCreateCellArray(1, dims);
     e2m_assert(ret);

     for (auto i(0UL) ; i < dims[0] ; ++i) {
	  // mxSetCell(mxArray *pm, mwIndex index, mxArray *value);
	  mxSetCell(ret, i, eigen2mat::to_mxArray(t[i]));
     }
     return ret;
}

// =============================================================================

bool eigen2mat::mxArray_to_bool(const mxArray* b)
{
     e2m_assert(b);
#ifdef EIGEN2MAT_TYPE_CHECK
     if (mxIsComplex(b)) {
	  mexWarnMsgTxt("mxArray_to_bool(): argument is complex!");
     }

     const auto M = mxGetM(b);
     const auto N = mxGetN(b);
     
     if (M != 1 || N != 1) {
	  mexErrMsgTxt("mxArray_to_bool(): value received is not a scalar!");
     }
#endif /* EIGEN2MAT_TYPE_CHECK */
     return mxArray_to_single_helper<bool>(b);
}

// =====================================

double eigen2mat::mxArray_to_double(const mxArray* d)
{
     e2m_assert(d);
#ifdef EIGEN2MAT_TYPE_CHECK
     if (mxIsComplex(d)) {
	  mexWarnMsgTxt("mxArray_to_double(): argument is complex!");
     }

     const auto M = mxGetM(d);
     const auto N = mxGetN(d);
     
     if (M != 1 || N != 1) {
	  mexErrMsgTxt("mxArray_to_double(): value received is not a scalar!");
     }
#endif /* EIGEN2MAT_TYPE_CHECK */
     return mxArray_to_single_helper<double>(d);
}

// =====================================

size_t eigen2mat::mxArray_to_idx(const mxArray* d)
{
     e2m_assert(d);
#ifdef EIGEN2MAT_TYPE_CHECK     
     const auto M = mxGetM(d);
     const auto N = mxGetN(d);
     if (M != 1 || N != 1) {
	  mexErrMsgTxt("mxArray_to_idx(): value received is not a scalar!");
     }

     const auto id = mxGetClassID(d);
     if (id == mxSINGLE_CLASS || id == mxDOUBLE_CLASS) {
	  mexWarnMsgTxt("mxArray_to_idx(): got floating-point intput!");
     }
     else if (id == mxINT8_CLASS || id == mxINT16_CLASS ||
	      id == mxINT32_CLASS || id == mxINT64_CLASS) {
	  mexWarnMsgTxt("mxArray_to_idx(): conversion from signed to unsigned!");
     }
     else if (id == mxLOGICAL_CLASS) {
	  mexWarnMsgTxt("mxArray_to_idx(): conversion from logical to int!");
     }
     else if (id != mxUINT8_CLASS && id != mxUINT16_CLASS &&
	      id != mxUINT32_CLASS && id != mxUINT64_CLASS) {
	  mexErrMsgTxt("mxArray_to_idx(): input is not unsigned integer!");
     }
#endif /* EIGEN2MAT_TYPE_CHECK */
     return mxArray_to_single_helper<size_t>(d);
}

// =====================================

int eigen2mat::mxArray_to_int(const mxArray* d)
{
     e2m_assert(d);
#ifdef EIGEN2MAT_TYPE_CHECK     
     const auto M = mxGetM(d);
     const auto N = mxGetN(d);
     
     if (M != 1 || N != 1) {
	  mexErrMsgTxt("mxArray_to_int(): value received is not a scalar!");
     }

     const auto id = mxGetClassID(d);
     if (id == mxSINGLE_CLASS || id == mxDOUBLE_CLASS) {
	  mexWarnMsgTxt("mxArray_to_int(): got floating-point intput!");
     }
     else if (id == mxUINT8_CLASS || id == mxUINT16_CLASS ||
	      id == mxUINT32_CLASS || id == mxUINT64_CLASS) {
	  mexWarnMsgTxt("mxArray_to_int(): conversion from unsigned to signed!");
     }
     else if (id == mxLOGICAL_CLASS) {
	  mexWarnMsgTxt("mxArray_to_int(): conversion from logical to int!");
     }
     else if (id != mxINT8_CLASS && id != mxINT16_CLASS &&
	      id != mxINT32_CLASS && id != mxINT64_CLASS) {
	  mexErrMsgTxt("mxArray_to_int(): input is not integer!");
     }
#endif /* EIGEN2MAT_TYPE_CHECK */

     return mxArray_to_single_helper<int>(d);
}

eigen2mat::dcomplex eigen2mat::mxArray_to_cmplx(const mxArray* d)
{
#ifdef EIGEN2MAT_TYPE_CHECK
     if (!mxIsComplex(d)) {
	  mexWarnMsgTxt("mxArray_to_cmplx(): argument is real!");
     }
#endif /* EIGEN2MAT_TYPE_CHECK */
     if (!mxIsComplex(d)) {
	  return dcomplex(mxGetPr(d)[0], 0.0);
     }
     else {
	  return dcomplex(mxGetPr(d)[0], mxGetPi(d)[0]);
     }
}

// =============================================================================

eigen2mat::idx_array_t eigen2mat::mxArray_to_idx_array(const mxArray* v)
{
     e2m_assert(v);
     const auto M = mxGetM(v);
     const auto N = mxGetN(v);

#ifdef EIGEN2MAT_TYPE_CHECK
     if (mxIsComplex(v)) {
	  mexWarnMsgTxt("mxArray_to_idx_array(): argument is complex!");
     }
     const auto id = mxGetClassID(v);
     if (id == mxSINGLE_CLASS || id == mxDOUBLE_CLASS) {
	  mexWarnMsgTxt("mxArray_to_idx_array(): got floating-point intput!");
     }
     else if (id == mxINT8_CLASS || id == mxINT16_CLASS ||
	      id == mxINT32_CLASS || id == mxINT64_CLASS) {
	  mexWarnMsgTxt("mxArray_to_idx_array(): conversion from signed to unsigned!");
     }
     else if (id != mxUINT8_CLASS && id != mxUINT16_CLASS &&
	      id != mxUINT32_CLASS && id != mxUINT64_CLASS) {
	  mexErrMsgTxt("mxArray_to_idx_array(): input is not array of integers!");
     }
     if (M == 1) {
	  mexWarnMsgTxt("mxArray_to_idx_array(): v is row-vector, converting to column vector");
     }
#endif /* EIGEN2MAT_TYPE_CHECK */

     /*
      * Need to be a little careful here when copying data from the mxArray
      * depending on the type of data that is actually stored.
      */
     idx_array_t ret;
     if (M == 1) {
	  ret = idx_array_t(N, int_array_t::value_type());
	  copy_from_mxArray_helper(v, N, ret.begin());
     }
     else {
	  ret = idx_array_t(M, int_array_t::value_type());
	  copy_from_mxArray_helper(v, M, ret.begin());
     }
     return ret;
}

// =====================================

eigen2mat::int_array_t eigen2mat::mxArray_to_int_array(const mxArray* v)
{
     e2m_assert(v);
     const auto M = mxGetM(v);
     const auto N = mxGetN(v);

#ifdef EIGEN2MAT_TYPE_CHECK
     if (mxIsComplex(v)) {
	  mexWarnMsgTxt("mxArray_to_int_array(): argument is complex!");
     }
     const auto id = mxGetClassID(v);
     if (id == mxSINGLE_CLASS || id == mxDOUBLE_CLASS) {
	  mexWarnMsgTxt("mxArray_to_int_array(): got floating-point intput!");
     }
     else if (id == mxUINT8_CLASS || id == mxUINT16_CLASS ||
	      id == mxUINT32_CLASS || id == mxUINT64_CLASS) {
	  mexWarnMsgTxt("mxArray_to_int_array(): conversion from unsigned to signed!");
     }
     else if (id != mxINT8_CLASS && id != mxINT16_CLASS &&
	      id != mxINT32_CLASS && id != mxINT64_CLASS) {
	  mexErrMsgTxt("mxArray_to_int_array(): input is not array of integers!");
     }
     if (M == 1) {
	  mexWarnMsgTxt("mxArray_to_int_array(): v is row-vector, converting to column vector");
     }
#endif /* EIGEN2MAT_TYPE_CHECK */
     
     /*
      * Need to be a little careful here when copying data from the mxArray
      * depending on the type of data that is actually stored.
      */
     int_array_t ret;
     if (M == 1) {
	  ret = int_array_t(N, int_array_t::value_type());
	  copy_from_mxArray_helper(v, N, ret.begin());
     }
     else {
	  ret = int_array_t(M, int_array_t::value_type());
	  copy_from_mxArray_helper(v, M, ret.begin());
     }
     return ret;
}


// =============================================================================

eigen2mat::real_vector_t eigen2mat::mxArray_to_real_vector(const mxArray* v)
{
     e2m_assert(v);
#ifdef EIGEN2MAT_TYPE_CHECK
     if (mxIsComplex(v)) {
	  mexWarnMsgTxt("mxArray_to_real_vector(): argument is complex!");
     }

     if (mxGetN(v) != 1) {
	  mexErrMsgTxt("mxArray_to_real_vector(): argument is not a column vector!");
     }

     const auto id = mxGetClassID(v);
     if (id != mxDOUBLE_CLASS) {
	  mexWarnMsgTxt("mxArray_to_real_vector(): data type of v is not double!");
     }
#endif /* EIGEN2MAT_TYPE_CHECK */

     return Eigen::Map<real_vector_t>(mxGetPr(v), mxGetM(v));
}

// =====================================

eigen2mat::real_row_vector_t eigen2mat::mxArray_to_real_row_vector(const mxArray* v)
{
     e2m_assert(v);
#ifdef EIGEN2MAT_TYPE_CHECK
     if (mxIsComplex(v)) {
	  mexWarnMsgTxt("mxArray_to_real_row_vector(): argument is complex!");
     }

     if (mxGetM(v) != 1) {
	  mexErrMsgTxt("mxArray_to_real_row_vector(): argument is not a row vector!");
     }
     const auto id = mxGetClassID(v);
     if (id != mxDOUBLE_CLASS) {
	  mexWarnMsgTxt("mxArray_to_real_row_vector(): data type of v is not double!");
     }
#endif /* EIGEN2MAT_TYPE_CHECK */

     return Eigen::Map<real_row_vector_t>(mxGetPr(v), mxGetN(v));
}

// =====================================

eigen2mat::real_matrix_t eigen2mat::mxArray_to_real_matrix(const mxArray* m)
{
     return mxArray_to_real<eigen2mat::real_matrix_t>(m);
}

// =====================================

eigen2mat::real_sp_matrix_t eigen2mat::mxArray_to_real_sp_matrix(const mxArray* m)
{
     e2m_assert(m);
     const auto M = mxGetM(m);
     const auto N = mxGetN(m);
#ifdef EIGEN2MAT_TYPE_CHECK
     if (mxIsComplex(m)) {
	  mexWarnMsgTxt("mxArray_to_real_sp_matrix(): argument is complex!");
     }
     if (!mxIsSparse(m)) {
	  mexErrMsgTxt("mxArray_to_real_sp_matrix(): argument is not sparse!");
     }
     const auto id = mxGetClassID(m);
     if (id != mxDOUBLE_CLASS) {
	  mexWarnMsgTxt("mxArray_to_real_matrix(): data type of v is not double!");
     }
#endif /* EIGEN2MAT_TYPE_CHECK */
     auto* values = mxGetPr(m);
     auto* ic = mxGetIr(m);
     auto* jc = mxGetJc(m);
     e2m_assert(values);
     e2m_assert(ic);
     e2m_assert(jc);

     const auto nzmax = mxGetNzmax(m);

     // not optimal insertion method, but should do for now...
     typedef Eigen::Triplet<double> t_t;
     std::vector<t_t> triplet_list;
     triplet_list.reserve(nzmax);
     for (auto col(0UL) ; col < N ; ++col) {
	  for (auto l(jc[col]) ; l < jc[col+1] ; ++l) {
	       triplet_list.push_back(t_t(ic[l],col,values[l]));
	  }
     }

     real_sp_matrix_t ret(M, N);
     ret.setFromTriplets(triplet_list.begin(), triplet_list.end());
     ret.makeCompressed();
     return ret;
}


// =====================================

eigen2mat::real_tensor_t eigen2mat::mxArray_to_real_tensor(const mxArray* t)
{
     e2m_assert(t);
     const auto dims = eigen2mat::get_dimensions(t);

#ifdef EIGEN2MAT_TYPE_CHECK
     if (dims[2] == 0) {
	  mexErrMsgTxt("mxArray_to_cmplx_tensor(): argument is not a tensor!");
     }          
     const auto id = mxGetClassID(t);
     if (id != mxDOUBLE_CLASS) {
	  mexWarnMsgTxt("mxArray_to_real_tensor(): data type of v is not double!");
     }
#endif /* EIGEN2MAT_TYPE_CHECK */

     real_tensor_t ret(dims[2], real_matrix_t(dims[0], dims[1]));
     const auto mat_size = dims[0] * dims[1];
     auto* data = mxGetPr(t);
     for (auto i(0UL) ; i < dims[2] ; ++i, data += mat_size) {
	  std::copy(data, data + mat_size, ret[i].data());
     }
     return ret;
}

// =====================================

eigen2mat::real_sp_tensor_t
eigen2mat::mxArray_to_real_sp_tensor(const mxArray* t)
{
     return eigen2mat::mxArray_to_real_sp_cell(t);
}

// =====================================

eigen2mat::real_sp_cell_t eigen2mat::mxArray_to_real_sp_cell(const mxArray* c)
{
     e2m_assert(c);
#ifdef EIGEN2MAT_TYPE_CHECK
     if (!mxIsCell(c)) {
	  mexErrMsgTxt("mxArray_to_real_sp_cell(): argument is not a cell array");
     }     

     if (mxGetN(c) > 1) {
	  mexErrMsgTxt("mxArray_to_real_sp_cell(): argument is not a 1D cell array");
     }
#endif /* EIGEN2MAT_TYPE_CHECK */

     const auto numel = mxGetNumberOfElements(c);
     real_sp_cell_t ret(numel);

     for (auto i(0UL) ; i < numel ; ++i) {
	  const auto* const data = mxGetCell(c, i);
	  e2m_assert(data);
	  ret[i] = mxArray_to_real_sp_matrix(data);
     }
     return ret;
}

// =============================================================================
// complex data

eigen2mat::cmplx_vector_t eigen2mat::mxArray_to_cmplx_vector(const mxArray* v)
{
     e2m_assert(v);
#ifdef EIGEN2MAT_TYPE_CHECK
     if (mxGetN(v) != 1) {
	  mexErrMsgTxt("mxArray_to_real_vector(): argument is not a column vector!");
     }

     const auto id = mxGetClassID(v);
     if (id != mxDOUBLE_CLASS) {
	  mexWarnMsgTxt("mxArray_to_cmplx_vector(): data type of v is not double!");
     }
#endif /* EIGEN2MAT_TYPE_CHECK */

     auto size(mxGetM(v));
     if (size == 1) {
	  size = mxGetN(v);
     }
     const auto real(Eigen::Map<real_vector_t>(mxGetPr(v), size));
     auto* imag_data = mxGetPi(v);
     if (imag_data == NULL) {
	  return real.cast<dcomplex>();
     }
     else {
	  const auto imag(Eigen::Map<real_vector_t>(imag_data, size));     
	  return (real.cast<dcomplex>() + dcomplex(0,1) * imag.cast<dcomplex>());
     }
}

// =====================================

eigen2mat::cmplx_row_vector_t eigen2mat::mxArray_to_cmplx_row_vector(const mxArray* v)
{
     e2m_assert(v);
#ifdef EIGEN2MAT_TYPE_CHECK
     if (mxGetM(v) != 1) {
	  mexErrMsgTxt("mxArray_to_real_row_vector(): argument is not a row vector!");
     }
     const auto id = mxGetClassID(v);
     if (id != mxDOUBLE_CLASS) {
	  mexWarnMsgTxt("mxArray_to_cmplx_row_vector(): data type of v is not double!");
     }
#endif /* EIGEN2MAT_TYPE_CHECK */

     auto size(mxGetM(v));
     if (size == 1) {
	  size = mxGetN(v);
     }
     const auto real(Eigen::Map<real_row_vector_t>(mxGetPr(v), size));
     auto* imag_data = mxGetPi(v);
     if (imag_data == NULL) {
	  return real.cast<dcomplex>();
     }
     else {
	  const auto imag(Eigen::Map<real_row_vector_t>(imag_data, size));	  
	  return (real.cast<dcomplex>() + dcomplex(0,1) * imag.cast<dcomplex>());
     }
}

// =====================================

eigen2mat::cmplx_matrix_t eigen2mat::mxArray_to_cmplx_matrix(const mxArray* m)
{
     return mxArray_to_cmplx<eigen2mat::cmplx_matrix_t>(m);
}

// =====================================

eigen2mat::cmplx_sp_matrix_t eigen2mat::mxArray_to_cmplx_sp_matrix(const mxArray* m)
{
     e2m_assert(m);
#ifdef EIGEN2MAT_TYPE_CHECK
     if (!mxIsComplex(m)) {
	  mexWarnMsgTxt("mxArray_to_cmplx_sp_matrix(): argument is real!");
     }
     if (!mxIsSparse(m)) {
	  mexErrMsgTxt("mxArray_to_cmplx_sp_matrix(): argument is not sparse!");
     }
     const auto id = mxGetClassID(m);
     if (id != mxDOUBLE_CLASS) {
	  mexWarnMsgTxt("mxArray_to_cmplx_sp_matrix(): data type of m is not double!");
     }
#endif /* EIGEN2MAT_TYPE_CHECK */
     auto* real = mxGetPr(m);
     auto* imag = mxGetPi(m);
     auto* ic = mxGetIr(m);
     auto* jc = mxGetJc(m);

     const auto M = mxGetM(m);
     const auto N = mxGetN(m);
     const auto nzmax = mxGetNzmax(m);

     // not optimal insertion method, but should do for now...
     typedef Eigen::Triplet<dcomplex> t_t;
     std::vector<t_t> triplet_list;
     triplet_list.reserve(nzmax);
     for (auto col(0UL) ; col < N ; ++col) {
	  for (auto l(jc[col]) ; l < jc[col+1] ; ++l) {
	       if (imag == nullptr) {
		    triplet_list.push_back(t_t(ic[l],
					       col,
					       dcomplex(real[l],0.0)
						)
			 );
	       }
	       else {
		    triplet_list.push_back(t_t(ic[l],
					       col,
					       dcomplex(real[l],imag[l])
						)
			 );
	       }
	  }
     }

     cmplx_sp_matrix_t ret(M, N);
     ret.setFromTriplets(triplet_list.begin(), triplet_list.end());
     ret.makeCompressed();
     return ret;
}

// =====================================

eigen2mat::cmplx_tensor_t eigen2mat::mxArray_to_cmplx_tensor(const mxArray* t)
{
     e2m_assert(t);
     const auto dims = eigen2mat::get_dimensions(t);
#ifdef EIGEN2MAT_TYPE_CHECK
     const auto id = mxGetClassID(t);
     if (id != mxDOUBLE_CLASS) {
	  mexWarnMsgTxt("mxArray_to_cmplx_tensor(): data type of v is not double!");
     }
#endif /* EIGEN2MAT_TYPE_CHECK */

     cmplx_tensor_t ret(dims[2], cmplx_matrix_t(dims[0], dims[1]));
     const auto mat_size = dims[0] * dims[1];
     auto* real = mxGetPr(t);
     auto* imag = mxGetPi(t);
     for (auto i(0UL) ; i < dims[2] ; ++i, real += mat_size, imag += mat_size) {
	  auto* data = ret[i].data();
	  for (auto j(0UL) ; j < mat_size ; ++j) {
	       if (imag == 0) {
		    data[j] = dcomplex(real[j], 0);
	       }
	       else {
		    data[j] = dcomplex(real[j], imag[j]);
	       }
	  }
     }
     return ret;
}

// =====================================

eigen2mat::cmplx_sp_tensor_t
eigen2mat::mxArray_to_cmplx_sp_tensor(const mxArray* t)
{
     return eigen2mat::mxArray_to_cmplx_sp_cell(t);
}

// =====================================

eigen2mat::cmplx_sp_cell_t eigen2mat::mxArray_to_cmplx_sp_cell(const mxArray* c)
{
     e2m_assert(c);
#ifdef EIGEN2MAT_TYPE_CHECK
     if (!mxIsCell(c)) {
	  mexErrMsgTxt("mxArray_to_cmplx_sp_cell(): argument is not a cell array");
     }     
     if (mxGetN(c) > 1) {
	  mexErrMsgTxt("mxArray_to_cmplx_sp_cell(): argument is not a 1D cell array");
     }
#endif /* EIGEN2MAT_TYPE_CHECK */

     const auto numel = mxGetNumberOfElements(c);
     cmplx_sp_cell_t ret(numel);

     for (auto i(0UL) ; i < numel ; ++i) {
	  const mxArray* data = mxGetCell(c, i);
	  e2m_assert(data);
	  ret[i] = mxArray_to_cmplx_sp_matrix(data);
     }
     return ret;
}

// #############################################################################
// eigen2mat to MATLAB

mxArray* eigen2mat::to_mxArray(bool b)
{
     auto ret = mxCreateNumericMatrix(1, 1, mxLOGICAL_CLASS, mxREAL);
     e2m_assert(ret);

     auto* data = reinterpret_cast<int*>(mxGetPr(ret));
     data[0] = b;
     return ret;
}

// =====================================

mxArray* eigen2mat::to_mxArray(double d)
{
     auto ret = mxCreateDoubleMatrix(1, 1, mxREAL);
     e2m_assert(ret);

     *mxGetPr(ret) = d;
     return ret;
}

// =====================================

mxArray* eigen2mat::to_mxArray(int i)
{
     auto ret = mxCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
     e2m_assert(ret);

     auto* data = reinterpret_cast<int*>(mxGetPr(ret));
     data[0] = i;
     return ret;
}

// =====================================

mxArray* eigen2mat::to_mxArray(e2m::size_t idx)
{
     auto ret = mxCreateNumericMatrix(1, 1, mxUINT32_CLASS, mxREAL);
     e2m_assert(ret);

     auto* data = reinterpret_cast<unsigned int*>(mxGetPr(ret));
     data[0] = idx;
     return ret;
}

// =====================================

mxArray* eigen2mat::to_mxArray(const e2m::dcomplex& z)
{
     auto ret = mxCreateDoubleMatrix(1, 1, mxCOMPLEX);
     e2m_assert(ret);

     *mxGetPr(ret) = z.real();
     *mxGetPi(ret) = z.imag();
     return ret;
}

// =============================================================================

mxArray* eigen2mat::to_mxArray(const e2m::idx_array_t& v)
{
     auto ret = mxCreateNumericMatrix(v.size(), 1, mxUINT32_CLASS, mxREAL);
     e2m_assert(ret);

     // this is ugly, but apparently there's no way around it...
     typedef unsigned int v_t;
     v_t* data = reinterpret_cast<v_t*>(mxGetPr(ret));

     std::copy(v.begin(), v.end(), data);
     return ret;
}

// =====================================

mxArray* eigen2mat::to_mxArray(const e2m::int_array_t& v)
{
     auto ret = mxCreateNumericMatrix(v.size(), 1, mxINT32_CLASS, mxREAL);
     e2m_assert(ret);

     // this is ugly, but apparently there's no way around it...
     typedef int v_t;
     v_t* data = reinterpret_cast<v_t*>(mxGetPr(ret));

     std::copy(v.begin(), v.end(), data);
     return ret;
}


// =============================================================================

mxArray* eigen2mat::to_mxArray(const e2m::real_sp_matrix_t& m)

{
     const size_t nzmax = m.nonZeros();
     mxArray* ret = mxCreateSparse(m.rows(), m.cols(), nzmax, mxREAL);

     if (m.rows() == 0 || m.cols() == 0) {
	  return ret;
     }

     auto* values = m.valuePtr();
     auto* ic = m.innerIndexPtr();
     auto* jc = m.outerIndexPtr();
     e2m_assert(values);
     e2m_assert(ic);
     e2m_assert(jc);

     auto* other_values = mxGetPr(ret);
     auto* other_ic = mxGetIr(ret);
     auto* other_jc = mxGetJc(ret);
     e2m_assert(other_values);
     e2m_assert(other_ic);
     e2m_assert(other_jc);

     e2m_assert(m.cols() == m.outerSize());
     if (m.isCompressed()) {
	  // matrix is compressed => easy !
	  std::copy(values, values + nzmax, other_values);
	  std::copy(ic, ic + nzmax, other_ic);
	  std::copy(jc, jc + m.outerSize()+1, other_jc);
     }
     else {
	  /*
	   * Matrix not in compressed mode => pain in the #@!%#!
	   *
	   * Basically the problem is that the inner index array of the matrix
	   * 'm' is not contiguous, it has holes:
	   *    values: 22 7 _ 3 5 14 _ _ 1 _ 17 8	
	   *    inner:   1 2 _ 0 2  4 _ _ 2 _  1 4
	   *    outer:   0 3 5 8 10 12
	   *    innz:    2 2 1 1 2
	   * where _ are empty elements for fast insertion (cf. Eigen doc)
	   *
	   * And then we still need to correct the outer index array...
	   *
	   * Explanation of the variables below:
	   * - i:     index in ret's inner index array
	   * - o_idx: index in m's outer index array
	   * - k:     index in m's inner index array
	   */
	  auto* inz = m.innerNonZeroPtr();
	  e2m_assert(inz);
	  size_t i(0);
	  other_jc[0] = 0;
	  for (int o_idx(0); o_idx < m.outerSize() ; ++o_idx) {
	       const auto pe = jc[o_idx]+inz[o_idx];
	       for (int k(jc[o_idx]) ; k < pe ; ++k, ++i) {
		    other_values[i] = values[k];
		    other_ic[i]     = ic[k];
	       }
	       other_jc[o_idx+1] = other_jc[o_idx] + inz[o_idx];
	  }
	  e2m_assert(i == nzmax);
     }
     return ret;
}

// =====================================

mxArray* eigen2mat::to_mxArray(const e2m::real_tensor_t& t)
{
     dim_array_t dims;
     dims.fill(0);
     dims[2] = t.size();

     if (dims[2] == 0) {
	  dims[0] = 0;
	  dims[1] = 0;
     }
     else {
	  dims[0] = t[0].rows();
	  dims[1] = t[0].cols();
     }
     const auto mat_size = dims[0] * dims[1];

     auto ret = mxCreateNumericArray(dims.size(),
				     dims.data(),
				     mxDOUBLE_CLASS,
				     mxREAL);
     e2m_assert(ret);

     auto* data = mxGetPr(ret);
     for (auto i(0UL) ; i < dims[2] ; ++i, data += mat_size) {
	  std::copy(t[i].data(), t[i].data() + mat_size, data);
     }

     return ret;

}
// =====================================

mxArray* eigen2mat::to_mxArray(const e2m::real_sp_cell_t& t)
{
     return to_1Dcell_array_helper<e2m::real_sp_cell_t>(t);
}

// =============================================================================

mxArray* eigen2mat::to_mxArray(const e2m::cmplx_sp_matrix_t& m)
{
     const size_t nzmax = m.nonZeros();
     auto* ret = mxCreateSparse(m.rows(), m.cols(), nzmax, mxCOMPLEX);

     if (m.rows() == 0 || m.cols() == 0) {
	  return ret;
     }

     auto* values = m.valuePtr();
     auto* ic = m.innerIndexPtr();
     auto* jc = m.outerIndexPtr();
     e2m_assert(values);
     e2m_assert(ic);
     e2m_assert(jc);
	  
     auto* real = mxGetPr(ret);
     auto* imag = mxGetPi(ret);
     auto* other_ic = mxGetIr(ret);
     auto* other_jc = mxGetJc(ret);
     e2m_assert(real);
     e2m_assert(imag);
     e2m_assert(other_ic);
     e2m_assert(other_jc);

     e2m_assert(m.cols() == m.outerSize());
     if (m.isCompressed()) {
	  // matrix is compressed => easy !
	  for (auto i(0UL) ; i < nzmax ; ++i) {
	       real[i] = values[i].real();
	       imag[i] = values[i].imag();
	  }
	  std::copy(ic, ic + nzmax, mxGetIr(ret));
	  std::copy(jc, jc + m.outerSize()+1, mxGetJc(ret));
     }
     else {
	  /*
	   * Matrix not in compressed mode => pain in the #@!%#!
	   *
	   * Basically the problem is that the inner index array of the matrix
	   * 'm' is not contiguous, it has holes:
	   *    values: 22 7 _ 3 5 14 _ _ 1 _ 17 8	
	   *    inner:   1 2 _ 0 2  4 _ _ 2 _  1 4
	   *    outer:   0 3 5 8 10 12
	   *    innz:    2 2 1 1 2
	   * where _ are empty elements for fast insertion (cf. Eigen doc)
	   *
	   * And then we still need to correct the outer index array...
	   *
	   * Explanation of the variables below:
	   * - i:     index in ret's inner index array
	   * - o_idx: index in m's outer index array
	   * - k:     index in m's inner index array
	   */
     	  auto* inz = m.innerNonZeroPtr();
	  e2m_assert(inz);
	  size_t i(0);
	  other_jc[0] = 0;
	  for (auto o_idx(0); o_idx < m.outerSize() ; ++o_idx) {
	       const auto pe = jc[o_idx]+inz[o_idx];
	       for (auto k(jc[o_idx]) ; k < pe ; ++k, ++i) {
		    real[i] = values[k].real();
		    imag[i] = values[k].imag();
		    other_ic[i]     = ic[k];
	       }
	       other_jc[o_idx+1] = other_jc[o_idx] + inz[o_idx];
	  }
	  e2m_assert(i == nzmax);
     }

     return ret;
}

// =====================================

mxArray* eigen2mat::to_mxArray(const e2m::cmplx_tensor_t& t)
{
     dim_array_t dims;
     dims.fill(0);
     dims[2] = t.size();

     if (dims[2] == 0) {
	  dims[0] = 0;
	  dims[1] = 0;
     }
     else {
	  dims[0] = t[0].rows();
	  dims[1] = t[0].cols();
     }
     const auto mat_size = dims[0] * dims[1];

     auto ret = mxCreateNumericArray(dims.size(),
				     dims.data(),
				     mxDOUBLE_CLASS,
				     mxCOMPLEX);
     e2m_assert(ret);

     auto* real = mxGetPr(ret);
     auto* imag = mxGetPi(ret);
     e2m_assert(real);
     e2m_assert(imag);

     for (auto i(0UL) ; i < dims[2] ; ++i, real += mat_size, imag += mat_size) {
	  auto* data = t[i].data();
	  for (auto j(0UL) ; j < mat_size ; ++j) {
	       real[j] = data[j].real();
	       imag[j] = data[j].imag();
	  }
     }

     return ret;
}

mxArray* eigen2mat::to_mxArray(const e2m::cmplx_sp_cell_t& t)
{
     return to_1Dcell_array_helper<e2m::cmplx_sp_cell_t>(t);
}

// #############################################################################

eigen2mat::dim_array_t eigen2mat::get_dimensions(const mxArray* a)
{
     const auto ndims = mxGetNumberOfDimensions(a);
     
     if (ndims > 3) {
	  mexErrMsgTxt("get_dimensions(): more than 3D not supported!");
     }

     dim_array_t ret;
     ret.fill(0);
     std::copy(mxGetDimensions(a), mxGetDimensions(a)+ndims, ret.data());
     return ret;
}


// =====================================

CLANG_RESTORE_WARNINGS
MSVC_RESTORE_WARNINGS


