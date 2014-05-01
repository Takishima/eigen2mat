#ifndef EIGEN_MAT_ARRAY_CONVERSION_HPP_INCLUDED
#define EIGEN_MAT_ARRAY_CONVERSION_HPP_INCLUDED

#include "eigen2mat/utils/Eigen_Core"

namespace eigen2mat {
     /*!
      * \brief Helper class to convert Matrix types to Array types
      *
      */
     template <typename mat_t>
     struct mat_to_array
     {
	  typedef Eigen::Array<typename mat_t::Scalar, 
			       mat_t::RowsAtCompileTime, 
			       mat_t::ColsAtCompileTime, 
			       mat_t::Options,
			       mat_t::MaxRowsAtCompileTime, 
			       mat_t::MaxColsAtCompileTime> type;
     };

     /*!
      * \brief Helper class to convert Array types to Matrix types
      *
      */
     template <typename array_t>
     struct array_to_mat
     {
	  typedef Eigen::Matrix<typename array_t::Scalar, 
				array_t::RowsAtCompileTime, 
				array_t::ColsAtCompileTime, 
				array_t::Options,
				array_t::MaxRowsAtCompileTime, 
				array_t::MaxColsAtCompileTime> type;
     };
} // namespace eigen2mat

#endif /* EIGEN_MAT_ARRAY_CONVERSION_HPP_INCLUDED */
