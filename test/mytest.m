function mytest()
%MYTEST Summary of this function goes here
%   Detailed explanation goes here

a = sparse(100, 50);
a(1,1) = 1;
a(2,1) = 21;
a(1,2) = 12;
a(1,1) = 11;
a(5,7) = 57;

rows = [ 2 7 13 42 58 99 ];
cols = [ 1 3 5 25 50 ];

mat_result = a;
mat_result(rows, cols) = 1;

mex_result = test_sparse_slice_mex(a, rows, cols);

if ~isequal(mat_result, mex_result)
    error('MATLAB matrix & MEX matrix are not EQUAL !');
else
    fprintf('Everything looks fine ;-)\n');
end

end

