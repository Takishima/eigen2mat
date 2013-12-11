#ifndef TENSOR_BLOCK_HPP_INCLUDED
#define TENSOR_BLOCK_HPP_INCLUDED

#include "include_mex"

#include <vector>

namespace mymex {
     template <typename tensor_t>
     class tensor_block_t
     {
	  typedef std::size_t size_t;
	  typedef typename tensor_t::value_type value_type;
	  typedef typename tensor_t::iterator iterator;
	  typedef typename tensor_t::const_iterator const_iterator;
	  typedef typename tensor_t::reverse_iterator reverse_iterator;
	  typedef typename tensor_t::const_reverse_iterator const_reverse_iterator;

     public:
	  tensor_block_t(tensor_t& t, 
			 size_t start,
			 size_t n_mat)
	       : begin_(t.begin() + start), end_(t.begin() + start + n_mat)
	       {}

	  value_type& operator[] (size_t k)
	       { 
#ifdef MYMEX_RANGE_CHECK
		    if (k > (end_ - begin_) ) {
			 mexErrMsgTxt("tensor_block_t::operator[]: index out of range!");
		    }
#endif /* MYMEX_RANGE_CHECK */
		    return *(begin_ + k);
	       }

	  value_type operator[] (size_t k) const
	       { 
#ifdef MYMEX_RANGE_CHECK
		    if (k > (end_ - begin_) ) {
			 mexErrMsgTxt("tensor_block_t::operator[]: index out of range!");
			 return value_type();
		    }
#endif /* MYMEX_RANGE_CHECK */
		    return *(begin_ + k);
	       }

	  size_t size() const {return (end_ - begin_);}

     private:
	  const iterator begin_;
	  const iterator end_;
     };
} // namespace mymex

#endif /* TENSOR_BLOCK_HPP_INCLUDED */
