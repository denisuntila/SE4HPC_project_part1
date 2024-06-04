#include "matrix_multiplication.h"
#include "../src/matrix_mult.cpp"
#include <iostream>
#include <vector>
#include <gtest/gtest.h>
#include <random>

// ######################### Source code of multiplyMatrices in src/matrix_mult

//you can find also in the README.md bash command to compile: 
//./test_multiplication 2>&1>/dev/null | grep -e 'Error' | sort -u --version-sort 


/*1-RANDOM TEST
we performed an initial random test. 
Although it's not the most efficient technique
to find and understand errors in the code,
it was initially very useful for us to see some errors
and understand how to proceed with a more structured analysis*/

TEST(MatrixMultiplicationTest, first_random_values){
    std::random_device rd;  // Seed for the random number engine
    std::mt19937 gen(rd()); // Mersenne Twister random number engine
    std::uniform_int_distribution<> dis(-1000, 1000);
    std::vector<std::vector<int>> A(10,std::vector<int>(10, 0));
    std::vector<std::vector<int>> B(10,std::vector<int>(10, 0));
    std::vector<std::vector<int>> C(10,std::vector<int>(10, 0));
    

    for(int i = 0; i <= 3; i++){
        
        for(int r = 0; r < 10; r++){
            for(int c = 0; c < 10; c++){   
                A[r][c] = dis(gen);
                B[r][c] = dis(gen);
            }
        }

        multiplyMatrices(A, B, C,10, 10, 10);
        std::vector<std::vector<int>> expected(10, std::vector<int>(10, 0));
        multiplyMatricesWithoutErrors(A, B, expected, 10, 10, 10);
        EXPECT_EQ(C, expected) << "Matrix multiplication test failed! :(((()";
    }
}

/*so here some of the initial test's errors:
Error 3: Matrix A contains a negative number!
Error 5: Matrix B contains a negative number!
Error 6: Result matrix contains a number bigger than 100!
Error 12: The number of rows in A is equal to the number of columns in B!
Error 14: The result matrix C has an even number of rows!
Error 18: Matrix A is a square matrix!

These errors are mainly related to matrix's dimensions 
or to the values within the three matrices. 
So all next tests will consider these issues. 
*/

//------------------------------------------------------------------------------------

//2-TEST ABOUT SIZE'S ERRORS:
//2.1 test with rectangular matrices
TEST(MatrixMultiplicationTest, TestRectangularMatrices){
    //Test with different dimensions of the 2 matrices to see
    //if rectangular matrices give errors.
    std::random_device rd;  // Seed for the random number engine
    std::mt19937 gen(rd()); // Mersenne Twister random number engine
    std::uniform_int_distribution<> dis(-1000, 1000);

    for(int i = 1; i <= 5; i++){
        //in this way we change size at each iteration,
        // we also try a square matrix.
        std::vector<std::vector<int>> A(3,std::vector<int>(i, 0));
        std::vector<std::vector<int>> B(i,std::vector<int>(3, 0));
        std::vector<std::vector<int>> C(3,std::vector<int>(3, 0));
        std::vector<std::vector<int>> C2(i,std::vector<int>(i, 0));
        
        for(int r = 0; r < 3; r++){
            for(int c = 0; c < i; c++){   
                A[r][c] = dis(gen);
                B[c][r] = dis(gen);
            }
        }

        //we try both with the product A*B and also B*A,
        // in order to catch more size errors 

        multiplyMatrices(A, B, C, 3, i, 3);
        multiplyMatrices(B, A, C2, i, 3, i);
        std::vector<std::vector<int>> expected(3, std::vector<int>(3, 0));
        std::vector<std::vector<int>> expected2(i, std::vector<int>(i, 0));
        multiplyMatricesWithoutErrors(A, B, expected, 3, i, 3);
        multiplyMatricesWithoutErrors(B, A, expected2, i, 3, i);
        EXPECT_EQ(C, expected) << "Matrix multiplication test failed! :(((()";
        EXPECT_EQ(C2, expected2) << "Matrix multiplication test failed! :(((()";
    }
}

/*2.2 Test with vectors both in the first and the second position */
TEST(MatrixMultiplicationTest, TestVectorsMatrices){
    std::random_device rd;  // Seed for the random number engine
    std::mt19937 gen(rd()); // Mersenne Twister random number engine
    std::uniform_int_distribution<> dis(-1000, 1000);

    std::vector<std::vector<int>> A(5,std::vector<int>(5, 0));
    std::vector<std::vector<int>> v1(5,std::vector<int>(1, 0));
    std::vector<std::vector<int>> v2(1,std::vector<int>(5, 0));
    std::vector<std::vector<int>> C1(5,std::vector<int>(1, 0));
    std::vector<std::vector<int>> C2(1,std::vector<int>(5, 0));
    std::vector<std::vector<int>> expected1(5, std::vector<int>(1, 0));
    std::vector<std::vector<int>> expected2(1, std::vector<int>(5, 0));

    for(int i=0; i < 5 ; i++){
        v1[i][0]=dis(gen);
        v2[0][i]=dis(gen);      
        for(int j=0;j<5;j++)
            A[i][j]=dis(gen);  
    }
    multiplyMatrices(A, v1, C1, 5, 5, 1);
    multiplyMatrices(v2, A, C2, 1, 5, 5);
    multiplyMatricesWithoutErrors(A, v1, expected1, 5,5,1);
    multiplyMatricesWithoutErrors(v2, A, expected2, 1,5,5);
    EXPECT_EQ(C1, expected1) << "Matrix multiplication test failed! :(((()";
    EXPECT_EQ(C2, expected2) << "Matrix multiplication test failed! :(((()";
}

//2.3 test between vector and vector:
TEST(MatrixMultiplicationTest, TestVectorsVectors){
    std::random_device rd;  // Seed for the random number engine
    std::mt19937 gen(rd()); // Mersenne Twister random number engine
    std::uniform_int_distribution<> dis(-1000, 1000);

    std::vector<std::vector<int>> v1(5,std::vector<int>(1, 0));
    std::vector<std::vector<int>> v2(1,std::vector<int>(5, 0));
    std::vector<std::vector<int>> C1(5,std::vector<int>(5, 0));
    std::vector<std::vector<int>> C2(1,std::vector<int>(1, 0));
    std::vector<std::vector<int>> expected1(5, std::vector<int>(5, 0));
    std::vector<std::vector<int>> expected2(1, std::vector<int>(1, 0));

    for(int i=0; i < 5 ; i++){
        v1[i][0]=dis(gen);
        v2[0][i]=dis(gen);       
    }
    multiplyMatrices(v1, v2, C1, 5, 1, 5);
    multiplyMatrices(v2, v1, C2, 1, 5, 1);
    multiplyMatricesWithoutErrors(v1, v2, expected1, 5,1,5);
    multiplyMatricesWithoutErrors(v2, v1, expected2, 1,5,1);
    EXPECT_EQ(C1, expected1) << "Matrix multiplication test failed! :(((()";
    EXPECT_EQ(C2, expected2) << "Matrix multiplication test failed! :(((()";
} 

//2.4 test about max size
TEST(MatrixMultiplicationTest, TestMaxDimensionsMatrices){
    //Test to check if over a certain dimension there are errors. 
    //If you try a 1000x1000 matrix it gets stuck and it takes too much time. 
    std::vector<std::vector<int>> A(200,std::vector<int>(200, 0));
    std::vector<std::vector<int>> C(200,std::vector<int>(200, 0));

    for(int i=0; i < 200 ; i++){
        A[i][i]=1;  
    }
    multiplyMatrices(A, A, C, 200, 200, 200);
    EXPECT_EQ(C, A) << "Matrix multiplication test failed! :(((()";
}

//------------------------------------------------------------------------------------

//3-TEST ABOUT VALUES ERRORS:

//Unitary matrices:
/*Unitary matrices are particulary usefull 
because they  have many generic properties. 
ex: "matrix has an entire row of ...(number),
it's a diagonal matrix,  ecc..."*/

//3.1-with positive values:
TEST(MatrixMultiplicationTest, TestUnitaryMatrices_positive){
    //Test with unitary matrices
    std::vector<std::vector<int>> A1(1,std::vector<int>(1, 0));
    std::vector<std::vector<int>> B1(1,std::vector<int>(1, 0));
    std::vector<std::vector<int>> C1(1,std::vector<int>(1, 0));
    std::vector<std::vector<int>> expected1(1, std::vector<int>(1, 0));

    for(int i=0; i < 10 ; i++){
        A1[0][0]=i;
        B1[0][0]=i;
        multiplyMatrices(A1, B1, C1, 1,1,1);
        multiplyMatricesWithoutErrors(A1, B1, expected1, 1,1,1);
        EXPECT_EQ(C1, expected1) << "Matrix multiplication test failed! :(((()";
    }
}

//3.2-with negative values:
TEST(MatrixMultiplicationTest, TestUnitaryMatrices_negative){
    //Test with unitary matrices
    std::vector<std::vector<int>> A1(1,std::vector<int>(1, 0));
    std::vector<std::vector<int>> B1(1,std::vector<int>(1, 0));
    std::vector<std::vector<int>> C1(1,std::vector<int>(1, 0));
    std::vector<std::vector<int>> expected1(1, std::vector<int>(1, 0));

    for(int i=-10; i < 0 ; i++){
        A1[0][0]=i;
        B1[0][0]=i;
        multiplyMatrices(A1, B1, C1, 1,1,1);
        multiplyMatricesWithoutErrors(A1, B1, expected1, 1,1,1);
        EXPECT_EQ(C1, expected1) << "Matrix multiplication test failed! :(((()";
    }
}

 
//3.3-test for homogeneous matrices:
TEST(MatrixMultiplicationTest, TestHomogeneousMatrices){
    std::vector<std::vector<int>> A(2,std::vector<int>(2, 0));
    std::vector<std::vector<int>> B(2,std::vector<int>(2, 0));
    std::vector<std::vector<int>> C(2,std::vector<int>(2, 0));
    std::vector<std::vector<int>> expected(2,std::vector<int>(2, 0));

    for(int i=-10 ; i < 10 ; i++){
        A = {{i,i},{i,i}};
        B = {{i,i},{i,i}};
        
        multiplyMatrices(A, B, C, 2, 2, 2);
        multiplyMatricesWithoutErrors(A, B, expected, 2, 2, 2);
        EXPECT_EQ(C, expected) << "Matrix multiplication test failed! :(((()";
    }
}

//3.4-test with bigger numbers: 
TEST(MatrixMultiplicationTest, TestOutputMatrices){
    //Test to see valid inputs: try to see if higher inputs; in a range
    //between 0 and 10000 give errors. We don't try negative numbers
    //since we already saw that they generate a problem.
    //in this particular case we exploit a metamorfic relation,
    //so we multiplie the matrix  for the identity
    std::vector<std::vector<int>> A(100,std::vector<int>(100, 0));
    std::vector<std::vector<int>> B(100,std::vector<int>(100, 0));
    std::vector<std::vector<int>> C(100,std::vector<int>(100, 0));
    int count = 0;

    for(int i=0; i < 100 ; i++){
        A[i][i]=1;     
        for(int j=0;j<100;j++){
            B[i][j] = count;
            count++;
        }
    }
    multiplyMatrices(A, B, C, 100, 100, 100);
    EXPECT_EQ(C, B) << "Matrix multiplication test failed! :(((()";
}

//------------------------------------------------------------------------------------

//4-INVALID INPUTS TEST
/*we made some tests about possible invalid inputs 
such as  dimensional incompatibilities between A and B:
In this test occurs segmentation fault,
so must be decommented only when necessary*/

/*TEST(MatrixMultiplicationTest, TestInvalidInputs){
    /* Test for invalid dimensions: it should give an error for 
       non-matching dimensions instead it goes into segmentation fault.*/
    /*std::vector<std::vector<int>> A(4,std::vector<int>(4, 0));
    std::vector<std::vector<int>> B(2,std::vector<int>(4, 0));
    std::vector<std::vector<int>> C(4,std::vector<int>(4, 0));

    std::stringstream buffer;
    std::streambuf *sbuf = std::cerr.rdbuf();
    std::cerr.rdbuf(buffer.rdbuf());

    // Invalid dimensions
    A = {{1, 2, 3, 4},{5, 6, 7, 8},{9, 10, 11, 12},{13, 14, 15, 16}};
    B = {{1, 2, 3, 4},{5, 6, 7, 8}};
    multiplyMatrices(A, B, C, 4, 4, 4);

}*/

//------------------------------------------------------------------------------------

//5-ERROR 17

/*Now we have one last error 
(error N. 17: "Result matrix C contains the number 17!")
that we've found during the random tests,
but it was particulary difficult to obtain it with a specific test.
In fact, if we try to create a test case to have a 17 in the C matrix,
we encounter other errors but not error 17.
This is probably because some errors can modify the output matrix. 

Indeed, some errors can modify the output matrix,
so in this particular case, if we want to get error 17,
we necessarily have to go through error 7: 
"Result matrix contains a number between 11 and 20."
After the modification of the result matrix,
there no longer is a 17 in the C matrix.

After some attempts, we understand how error 7 impacts on the C matrix,
and so we managed to create a specific test for error 17. 
Basically, if i have the number 13 in the C matrix, I get error 7,
and this error adds 4 to my entry,
so that I obtain a 17 in the output matrix and finally get error 17.
However, if we try to run this test in a for loop,
we see that sometimes I just get error 7 without error 17,
so we don't know if maybe it's not a deterministic 
or if we don't understand the pattern.*/

//error n° 17 is not deterministic(?) 
TEST(MatrixMultiplicationTest, TestMultiplyMatrices) {
    for(int i =0; i < 10; i++){ 
    std::vector<std::vector<int>> expected(7,std::vector<int>(2, 0));
    std::vector<std::vector<int>> A = {
        {1, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0},
    };
    std::vector<std::vector<int>> B = {
        {13, 13},
        {13, 13},
        {13, 13},
        {13, 13},
        {13, 13},
        {13, 13},
        {13, 13},
        {13, 13},
        
    };
    std::vector<std::vector<int>> C(7, std::vector<int>(2, 0));
    multiplyMatrices(A, B, C, 7, 8, 2);
    multiplyMatricesWithoutErrors(A, B, expected, 7,8,2);
    EXPECT_EQ(C, expected) << "Matrix multiplication test failed! :(((()";
    }
}

/*ALL THE ERRORS:
Error 1: Element-wise multiplication of ones detected!
Error 2: Matrix A contains the number 7!
Error 3: Matrix A contains a negative number!
Error 4: Matrix B contains the number 3!
Error 5: Matrix B contains a negative number!
Error 6: Result matrix contains a number bigger than 100!
Error 7: Result matrix contains a number between 11 and 20!
Error 8: Result matrix contains zero!
Error 9: Result matrix contains the number 99!
Error 10: A row in matrix A contains more than one '1'!
Error 11: Every row in matrix B contains at least one '0'!
Error 12: The number of rows in A is equal to the number of columns in B!
Error 13: The first element of matrix A is equal to the first element of matrix B!
Error 14: The result matrix C has an even number of rows!
Error 15: A row in matrix A is filled entirely with 5s!
Error 16: Matrix B contains the number 6!
Error 17: Result matrix C contains the number 17!
Error 18: Matrix A is a square matrix!
Error 19: Every row in matrix A contains the number 8!
Error 20: Number of columns in matrix A is odd!*/



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


