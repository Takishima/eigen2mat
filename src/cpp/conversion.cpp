#include "conversion.hpp"

#include <algorithm>

// =============================================================================

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wundefined-reinterpret-cast"
#pragma clang diagnostic ignored "-Wconversion"
#pragma clang diagnostic ignored "-Wc++98-compat-pedantic"
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
			      mymex::size_t SIZE, 
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
     for (auto i(0UL) ; i < dims[0] ; ++i) {
	  // mxSetCell(mxArray *pm, mwIndex index, mxArray *value);
	  mxSetCell(ret, i, mymex::to_mxArray(t[i]));
     }
     return ret;
}

#pragma clang diagnostic pop

// =============================================================================

bool mymex::mxArray_to_bool(const mxArray* b)
{
#ifdef MYMEX_TYPE_CHECK
     if (mxIsComplex(b)) {
	  mexWarnMsgTxt("mxArray_to_bool(): argument is complex!");
     }

     const auto M = mxGetM(b);
     const auto N = mxGetN(b);
     
     if (M != 1 or N != 1) {
	  mexErrMsgTxt("mxArray_to_bool(): value received is not a scalar!");
     }
#endif /* MYMEX_TYPE_CHECK */
     return mxArray_to_single_helper<bool>(b);
}

// =====================================

double mymex::mxArray_to_double(const mxArray* d)
{
#ifdef MYMEX_TYPE_CHECK
     if (mxIsComplex(d)) {
	  mexWarnMsgTxt("mxArray_to_double(): argument is complex!");
     }

     const auto M = mxGetM(d);
     const auto N = mxGetN(d);
     
     if (M != 1 or N != 1) {
	  mexErrMsgTxt("mxArray_to_double(): value received is not a scalar!");
     }
#endif /* MYMEX_TYPE_CHECK */
     return mxArray_to_single_helper<double>(d);
}

// =====================================

size_t mymex::mxArray_to_idx(const mxArray* d)
{
#ifdef MYMEX_TYPE_CHECK     
     const auto M = mxGetM(d);
     const auto N = mxGetN(d);
     if (M != 1 or N != 1) {
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
#endif /* MYMEX_TYPE_CHECK */
     return mxArray_to_single_helper<size_t>(d);
}

// =====================================

int mymex::mxArray_to_int(const mxArray* d)
{
#ifdef MYMEX_TYPE_CHECK     
     const auto M = mxGetM(d);
     const auto N = mxGetN(d);
     
     if (M != 1 or N != 1) {
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
#endif /* MYMEX_TYPE_CHECK */

     return mxArray_to_single_helper<int>(d);
}

mymex::dcomplex mymex::mxArray_to_cmplx(const mxArray* d)
{
#ifdef MYMEX_TYPE_CHECK
     if (!mxIsComplex(d)) {
	  mexWarnMsgTxt("mxArray_to_cmplx(): argument is real!");
     }
#endif /* MYMEX_TYPE_CHECK */
     if (!mxIsComplex(d)) {
	  return dcomplex(mxGetPr(d)[0], 0.0);
     }
     else {
	  return dcomplex(mxGetPr(d)[0], mxGetPi(d)[0]);
     }
}

// =============================================================================

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++98-compat-pedantic"

mymex::idx_array_t mymex::mxArray_to_idx_array(const mxArray* v)
{
     const auto M = mxGetM(v);
     const auto N = mxGetN(v);

#ifdef MYMEX_TYPE_CHECK
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
#endif /* MYMEX_TYPE_CHECK */

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

mymex::int_array_t mymex::mxArray_to_int_array(const mxArray* v)
{
     const auto M = mxGetM(v);
     const auto N = mxGetN(v);

#ifdef MYMEX_TYPE_CHECK
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
#endif /* MYMEX_TYPE_CHECK */
     
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

#pragma clang diagnostic pop

// =============================================================================

mymex::real_vector_t mymex::mxArray_to_real_vector(const mxArray* v)
{
#ifdef MYMEX_TYPE_CHECK
     if (mxIsComplex(v)) {
	  mexWarnMsgTxt("mxArray_to_real_vector(): argument is complex!");
     }

     if (mxGetN(v) != 1) {
	  mexErrMsgTxt("mxArray_to_real_vector(): argument is not a column vector!");
     }

     const auto id = mxGetClassID(v);
     if (id != mxDOUBLE_CLASS) {
	  mexErrMsgTxt("mxArray_to_real_vector(): data type of v is not double!");
     }
#endif /* MYMEX_TYPE_CHECK */

     return Eigen::Map<real_vector_t>(mxGetPr(v), mxGetM(v));
}

// =====================================

mymex::real_row_vector_t mymex::mxArray_to_real_row_vector(const mxArray* v)
{
#ifdef MYMEX_TYPE_CHECK
     if (mxIsComplex(v)) {
	  mexWarnMsgTxt("mxArray_to_real_row_vector(): argument is complex!");
     }

     if (mxGetM(v) != 1) {
	  mexErrMsgTxt("mxArray_to_real_row_vector(): argument is not a row vector!");
     }
     const auto id = mxGetClassID(v);
     if (id != mxDOUBLE_CLASS) {
	  mexErrMsgTxt("mxArray_to_real_row_vector(): data type of v is not double!");
     }
#endif /* MYMEX_TYPE_CHECK */

     return Eigen::Map<real_row_vector_t>(mxGetPr(v), mxGetN(v));
}

// =====================================

mymex::real_matrix_t mymex::mxArray_to_real_matrix(const mxArray* m)
{
#ifdef MYMEX_TYPE_CHECK
     if (mxIsComplex(m)) {
	  mexWarnMsgTxt("mxArray_to_real_matrix(): argument is complex!");
     }
     const auto id = mxGetClassID(m);
     if (id != mxDOUBLE_CLASS) {
	  mexErrMsgTxt("mxArray_to_real_matrix(): data type of v is not double!");
     }
#endif /* MYMEX_TYPE_CHECK */

     return Eigen::Map<real_matrix_t>(mxGetPr(m), mxGetM(m), mxGetN(m));
}

// =====================================

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
mymex::real_sp_matrix_t mymex::mxArray_to_real_sp_matrix(const mxArray* m)
{
     const auto M = mxGetM(m);
     const auto N = mxGetN(m);
#ifdef MYMEX_TYPE_CHECK
     if (mxIsComplex(m)) {
	  mexWarnMsgTxt("mxArray_to_real_sp_matrix(): argument is complex!");
     }
     if (!mxIsSparse(m)) {
	  mexErrMsgTxt("mxArray_to_real_sp_matrix(): argument is not sparse!");
     }
     const auto id = mxGetClassID(m);
     if (id != mxDOUBLE_CLASS) {
	  mexErrMsgTxt("mxArray_to_real_matrix(): data type of v is not double!");
     }
#endif /* MYMEX_TYPE_CHECK */
     auto* values = mxGetPr(m);
     auto* ic = mxGetIr(m);
     auto* jc = mxGetJc(m);

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
#pragma clang diagnostic pop


// =====================================

mymex::real_tensor_t mymex::mxArray_to_real_tensor(const mxArray* t)
{
     const auto dims = mymex::get_dimensions(t);

#ifdef MYMEX_TYPE_CHECK
     if (dims[2] == 0) {
	  mexErrMsgTxt("mxArray_to_cmplx_tensor(): argument is not a tensor!");
     }          
     const auto id = mxGetClassID(t);
     if (id != mxDOUBLE_CLASS) {
	  mexErrMsgTxt("mxArray_to_real_tensor(): data type of v is not double!");
     }
#endif /* MYMEX_TYPE_CHECK */

     real_tensor_t ret(dims[2], real_matrix_t(dims[0], dims[1]));
     const auto mat_size = dims[0] * dims[1];
     auto* data = mxGetPr(t);
     for (auto i(0UL) ; i < dims[2] ; ++i, data += mat_size) {
	  std::copy(data, data + mat_size, ret[i].data());
     }
     return ret;
}

// =====================================

mymex::real_sp_cell_t mymex::mxArray_to_real_sp_cell(const mxArray* c)
{
#ifdef MYMEX_TYPE_CHECK
     if (!mxIsCell(c)) {
	  mexErrMsgTxt("mxArray_to_real_sp_cell(): argument is not a cell array");
     }     

     if (mxGetN(c) > 1) {
	  mexErrMsgTxt("mxArray_to_real_sp_cell(): argument is not a 1D cell array");
     }
#endif /* MYMEX_TYPE_CHECK */

     const auto numel = mxGetNumberOfElements(c);
     real_sp_cell_t ret(numel);

     for (auto i(0UL) ; i < numel ; ++i) {
	  const auto* const data = mxGetCell(c, i);
	  mxAssert(data, "Pointer is null!");
	  ret[i] = mxArray_to_real_sp_matrix(data);
     }
     return ret;
}

// =============================================================================
// complex data

mymex::cmplx_vector_t mymex::mxArray_to_cmplx_vector(const mxArray* v)
{
#ifdef MYMEX_TYPE_CHECK
     if (mxGetN(v) != 1) {
	  mexErrMsgTxt("mxArray_to_real_vector(): argument is not a column vector!");
     }

     const auto id = mxGetClassID(v);
     if (id != mxDOUBLE_CLASS) {
	  mexErrMsgTxt("mxArray_to_cmplx_vector(): data type of v is not double!");
     }
#endif /* MYMEX_TYPE_CHECK */

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

mymex::cmplx_row_vector_t mymex::mxArray_to_cmplx_row_vector(const mxArray* v)
{
#ifdef MYMEX_TYPE_CHECK
     if (mxGetM(v) != 1) {
	  mexErrMsgTxt("mxArray_to_real_row_vector(): argument is not a row vector!");
     }
     const auto id = mxGetClassID(v);
     if (id != mxDOUBLE_CLASS) {
	  mexErrMsgTxt("mxArray_to_cmplx_row_vector(): data type of v is not double!");
     }
#endif /* MYMEX_TYPE_CHECK */

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

mymex::cmplx_matrix_t mymex::mxArray_to_cmplx_matrix(const mxArray* m)
{
#ifdef MYMEX_TYPE_CHECK
     const auto id = mxGetClassID(m);
     if (id != mxDOUBLE_CLASS) {
	  mexErrMsgTxt("mxArray_to_cmplx_matrix(): data type of v is not double!");
     }
#endif /* MYMEX_TYPE_CHECK */

     const auto rows(mxGetM(m));
     const auto cols(mxGetN(m));

     const auto real(Eigen::Map<real_matrix_t>(mxGetPr(m), rows, cols));
     auto* imag_data = mxGetPi(m);
     if (imag_data == NULL) {
	  return real.cast<dcomplex>();
     }
     else {
	  const auto imag(Eigen::Map<real_matrix_t>(imag_data, rows, cols));
	  return (real.cast<dcomplex>() + dcomplex(0,1) * imag.cast<dcomplex>());
     }
}

// =====================================

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshorten-64-to-32"

mymex::cmplx_sp_matrix_t mymex::mxArray_to_cmplx_sp_matrix(const mxArray* m)
{
#ifdef MYMEX_TYPE_CHECK
     if (!mxIsComplex(m)) {
	  mexWarnMsgTxt("mxArray_to_cmplx_sp_matrix(): argument is real!");
     }
     if (!mxIsSparse(m)) {
	  mexErrMsgTxt("mxArray_to_cmplx_sp_matrix(): argument is not sparse!");
     }
     const auto id = mxGetClassID(m);
     if (id != mxDOUBLE_CLASS) {
	  mexErrMsgTxt("mxArray_to_cmplx_sp_matrix(): data type of m is not double!");
     }
#endif /* MYMEX_TYPE_CHECK */
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
	       if (imag == NULLPTR) {
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
#pragma clang diagnostic pop

// =====================================

mymex::cmplx_tensor_t mymex::mxArray_to_cmplx_tensor(const mxArray* t)
{
     const auto dims = mymex::get_dimensions(t);
#ifdef MYMEX_TYPE_CHECK
     const auto id = mxGetClassID(t);
     if (id != mxDOUBLE_CLASS) {
	  mexErrMsgTxt("mxArray_to_cmplx_tensor(): data type of v is not double!");
     }
#endif /* MYMEX_TYPE_CHECK */

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
mymex::cmplx_sp_cell_t mymex::mxArray_to_cmplx_sp_cell(const mxArray* c)
{
#ifdef MYMEX_TYPE_CHECK
     if (!mxIsCell(c)) {
	  mexErrMsgTxt("mxArray_to_cmplx_sp_cell(): argument is not a cell array");
     }     
     if (mxGetN(c) > 1) {
	  mexErrMsgTxt("mxArray_to_cmplx_sp_cell(): argument is not a 1D cell array");
     }
#endif /* MYMEX_TYPE_CHECK */

     const auto numel = mxGetNumberOfElements(c);
     cmplx_sp_cell_t ret(numel);

     for (auto i(0UL) ; i < numel ; ++i) {
	  const mxArray* data = mxGetCell(c, i);
	  myassert(data);
	  ret[i] = mxArray_to_cmplx_sp_matrix(data);
     }
     return ret;
}

// #############################################################################
// mymex to MATLAB

mxArray* mymex::to_mxArray(bool b)
{
     auto ret = mxCreateNumericMatrix(1, 1, mxLOGICAL_CLASS, mxREAL);
     auto* data = reinterpret_cast<int*>(mxGetPr(ret));
     data[0] = b;
     return ret;
}

// =====================================

mxArray* mymex::to_mxArray(double d)
{
     auto ret = mxCreateDoubleMatrix(1, 1, mxREAL);
     *mxGetPr(ret) = d;
     return ret;
}

// =====================================

mxArray* mymex::to_mxArray(int i)
{
     auto ret = mxCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
     auto* data = reinterpret_cast<int*>(mxGetPr(ret));
     data[0] = i;
     return ret;
}

// =====================================

mxArray* mymex::to_mxArray(size_t idx)
{
     auto ret = mxCreateNumericMatrix(1, 1, mxUINT32_CLASS, mxREAL);
     auto* data = reinterpret_cast<unsigned int*>(mxGetPr(ret));
     data[0] = idx;
     return ret;
}

// =====================================

mxArray* mymex::to_mxArray(const dcomplex& z)
{
     auto ret = mxCreateDoubleMatrix(1, 1, mxCOMPLEX);
     *mxGetPr(ret) = z.real();
     *mxGetPi(ret) = z.imag();
     return ret;
}

// =============================================================================

mxArray* mymex::to_mxArray(const idx_array_t& v)
{
     auto ret = mxCreateNumericMatrix(v.size(), 1, mxUINT32_CLASS, mxREAL);

     // this is ugly, but apparently there's no way around it...
     typedef unsigned int v_t;
     v_t* data = reinterpret_cast<v_t*>(mxGetPr(ret));

     std::copy(v.begin(), v.end(), data);
     return ret;
}

// =====================================

mxArray* mymex::to_mxArray(const int_array_t& v)
{
     auto ret = mxCreateNumericMatrix(v.size(), 1, mxINT32_CLASS, mxREAL);

     // this is ugly, but apparently there's no way around it...
     typedef int v_t;
     v_t* data = reinterpret_cast<v_t*>(mxGetPr(ret));

     std::copy(v.begin(), v.end(), data);
     return ret;
}


// =============================================================================

mxArray* mymex::to_mxArray(const real_vector_t& v)
{
     auto ret = mxCreateDoubleMatrix(v.rows(), 1, mxREAL);
     std::copy(v.data(), v.data() + v.rows(), mxGetPr(ret));
     return ret;
}

// =====================================

mxArray* mymex::to_mxArray(const real_row_vector_t& v)
{
     auto ret = mxCreateDoubleMatrix(1, v.cols(), mxREAL);
     std::copy(v.data(), v.data() + v.cols(), mxGetPr(ret));
     return ret;
}

// =====================================

mxArray* mymex::to_mxArray(const real_matrix_t& m)
{
     const auto M = m.rows();
     const auto N = m.cols();

     auto ret = mxCreateDoubleMatrix(M, N, mxREAL);
     std::copy(m.data(), m.data() + M*N, mxGetPr(ret));
     return ret;
}

// =====================================

mxArray* mymex::to_mxArray(const real_sp_matrix_t& m)
{
     const auto nzmax = m.nonZeros();
     auto* ret = mxCreateSparse(m.rows(), m.cols(), nzmax, mxREAL);

     auto* values = m.valuePtr();
     auto* ic = m.innerIndexPtr();
     auto* jc = m.outerIndexPtr();
     std::copy(values, values + nzmax, mxGetPr(ret));
     std::copy(ic, ic + nzmax, mxGetIr(ret));
     std::copy(jc, jc + m.outerSize()+1, mxGetJc(ret));
     return ret;
}

// =====================================

mxArray* mymex::to_mxArray(const real_tensor_t& t)
{
     dim_array_t dims;
     dims.fill(0);
     dims[2] = t.size();

#ifdef MYMEX_TYPE_CHECK
  if (dims[2] == 0) {
       mexErrMsgTxt("to_mxArray(real_tensor_t): argument is not a tensor!");
  }     
#endif /* MYMEX_TYPE_CHECK */

     dims[0] = t[0].rows();
     dims[1] = t[0].cols();
     const auto mat_size = dims[0] * dims[1];

     auto ret = mxCreateNumericArray(dims.size(),
				     dims.data(),
				     mxDOUBLE_CLASS,
				     mxREAL);

     auto* data = mxGetPr(ret);
     for (auto i(0UL) ; i < dims[2] ; ++i, data += mat_size) {
	  std::copy(t[i].data(), t[i].data() + mat_size, data);
     }

     return ret;
}

// =====================================

mxArray* mymex::to_mxArray(const real_sp_cell_t& t)
{
     return to_1Dcell_array_helper<real_sp_cell_t>(t);
}

// =============================================================================

mxArray* mymex::to_mxArray(const cmplx_vector_t& v)
{
     auto ret = mxCreateDoubleMatrix(v.rows(), 1, mxCOMPLEX);

     auto real = mxGetPr(ret);
     auto imag = mxGetPi(ret);
     myassert(real);
     myassert(imag);

     const auto S = v.size();
     const auto data = v.data();
     for (auto i(0) ; i < S ; ++i) {
	  real[i] = data[i].real();
	  imag[i] = data[i].imag();
     }
     return ret;
}

// =====================================

mxArray* mymex::to_mxArray(const cmplx_row_vector_t& v)
{
     auto ret = mxCreateDoubleMatrix(1, v.cols(), mxCOMPLEX);

     auto real = mxGetPr(ret);
     auto imag = mxGetPi(ret);
     myassert(real);
     myassert(imag);

     const auto S = v.size();
     const auto data = v.data();
     for (auto i(0) ; i < S ; ++i) {
	  real[i] = data[i].real();
	  imag[i] = data[i].imag();
     }
     return ret;
}

// =====================================

mxArray* mymex::to_mxArray(const cmplx_matrix_t& m)
{
     const auto M = m.rows();
     const auto N = m.cols();
     const auto S = m.rows() * m.cols();

     auto ret = mxCreateDoubleMatrix(M, N, mxCOMPLEX);

     auto real = mxGetPr(ret);
     auto imag = mxGetPi(ret);
     myassert(real);
     myassert(imag);

     const auto data = m.data();
     for (auto i(0) ; i < S ;++i) {
	  real[i] = data[i].real();
	  imag[i] = data[i].imag();
     }

     return ret;
}

// =====================================

mxArray* mymex::to_mxArray(const cmplx_sp_matrix_t& m)
{
     const auto nzmax = m.nonZeros();
     auto* ret = mxCreateSparse(m.rows(), m.cols(), nzmax, mxCOMPLEX);

     auto* values = m.valuePtr();
     auto* ic = m.innerIndexPtr();
     auto* jc = m.outerIndexPtr();

     auto* real = mxGetPr(ret);
     auto* imag = mxGetPi(ret);
     myassert(real);
     myassert(imag);

     for (auto i(0UL) ; i < nzmax ; ++i) {
	  real[i] = values[i].real();
	  imag[i] = values[i].imag();
     }
     std::copy(ic, ic + nzmax, mxGetIr(ret));
     std::copy(jc, jc + m.outerSize()+1, mxGetJc(ret));
     return ret;
}

// =====================================

mxArray* mymex::to_mxArray(const cmplx_tensor_t& t)
{
     dim_array_t dims;
     dims.fill(0);
     dims[2] = t.size();

#ifdef MYMEX_TYPE_CHECK
  if (dims[2] == 0) {
       mexErrMsgTxt("to_mxArray(real_tensor_t): argument is not a tensor!");
  }     
#endif /* MYMEX_TYPE_CHECK */

     dims[0] = t[0].rows();
     dims[1] = t[0].cols();
     const auto mat_size = dims[0] * dims[1];

     auto ret = mxCreateNumericArray(dims.size(),
				     dims.data(),
				     mxDOUBLE_CLASS,
				     mxCOMPLEX);

     auto* real = mxGetPr(ret);
     auto* imag = mxGetPi(ret);
     myassert(real);
     myassert(imag);

     for (auto i(0UL) ; i < dims[2] ; ++i, real += mat_size, imag += mat_size) {
	  auto* data = t[i].data();
	  for (auto j(0UL) ; j < mat_size ; ++j) {
	       real[j] = data[j].real();
	       imag[j] = data[j].imag();
	  }
     }

     return ret;
}

mxArray* mymex::to_mxArray(const cmplx_sp_cell_t& t)
{
     return to_1Dcell_array_helper<cmplx_sp_cell_t>(t);
}

// #############################################################################

mymex::dim_array_t mymex::get_dimensions(const mxArray* a)
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

