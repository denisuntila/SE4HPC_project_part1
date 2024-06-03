# SE4HPCproject

To compile the tests:
```
cd build
make && ./test_multiplication | grep -e 'Error' | sort -t: -u -k1.1 | sort --version-sort
```

## Tests

First we did a test on square random matrices to get some initial errors and understand how to organize the next tests.

From these tests we obtained some errors:
- Error 3: Matrix A contains a negative number!
- Error 5: Matrix B contains a negative number!
- Error 6: Result matrix contains a number bigger than 100!
- Error 12: The number of rows in A is equal to the number of columns in B!
- Error 14: The result matrix C has an even number of rows!
- Error 18: Matrix A is a square matrix!

So we decided to divide the tests into 2 main categories: tests on the dimensions and on the values in the three matrices.

### Tests on dimensions
These tests are performed multiple times with random inputs.
1. We performed some tests on rectangular matrices. In these tests both the first and second matrix change their size at every iteration.
2. We then performed some tests on a matrix-vector multiplication to see if the vector creates problems.
3. After that we also did some tests on vector-vector multiplication.
4. Then we performed a test to check if over a certain dimensions there are errors.

### Tests on values
These tests focus more on the input values of the matrices to understand if certain inputs trigger an error.

1. We performed a test with unitary matrices both for negative and positive values. In fact these matrices embody many generic properties of the matrices such as diagonal matrix, an entire row of the same number...
2. Then we performed some tests on 2x2 matrices of the same value to understand if the repetition of the same number creates some problems.
3. Finally, we performed a test on a matrix full of increasing numbers to have an understanding of the possible input values. We used a metamorfic relation to obtain the results of this test since we multiplied the matrix for the identity.

### Test with invalid inputs
We also tried to compute the multiplication between matrices with non compatible dimensions to see if it would give an error, instead it goes into segmentation fault.


### Error 17
Now we have one last error (error No. 17: "Result matrix C contains the number 17!") that we've seen during the random test.
We have created a specific test to obtain this error, in fact, some errors can modify the output matrix. 
In this particular case, if we want to get error 17, we necessarily have to go through error 7: "Result matrix contains a number between 11 and 20."
After the modification of the result matrix, we no longer have a 17 in the C matrix.
With this test almost everytime we obtain the error.
