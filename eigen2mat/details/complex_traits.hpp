#ifndef COMPLEX_TRAITS_HPP_INCLUDED
#define COMPLEX_TRAITS_HPP_INCLUDED

namespace eigen2mat {
     namespace internal {
	  //! Helper traits struct for complex numbers
	  template <typename T>
	  struct complex_traits
	  {
	       static const bool is_cmplx = false;
	       typedef T type;
	  };
	  //! Specialisation for std::complex<T>
	  template <typename T>
	  struct complex_traits<std::complex<T>>
	  {
	       typedef T type;
	       static const bool is_cmplx = true;
	  };
     } // namespace internal
} // namespace eigen2mat

#endif /* COMPLEX_TRAITS_HPP_INCLUDED */
