function mytest()
%MYTEST Summary of this function goes here
%   Detailed explanation goes here

a = sparse(11, 13);
a(1,1) = 1;
a(1,2) = 12;
a(1,1) = 11;
a(5,7) = 57;

tmp = test_sparse_slice_mex(a);

a
tmp

end

