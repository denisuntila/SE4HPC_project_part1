#include "matrix_multiplication.h"
#include "../src/matrix_mult.cpp"
#include <iostream>
#include <vector>
#include <gtest/gtest.h>
#include <random>

// ######################### Source code of multiplyMatrices in src/matrix_mult

/* 1-RANDOM TEST
we performed an initial random test. 
Although it's not the most efficient technique to find and understand errors in the code,
it was initially very useful for us to see some errors and understand how to proceed with a more structured analysis*/

TEST(MatrixMultiplicationTest, first_random_values){
    std::random_device rd;  // Seed for the random number engine
    std::mt19937 gen(rd()); // Mersenne Twister random number engine
    std::uniform_int_distribution<> dis(-1000, 1000);
    std::vector<std::vector<int>> A(10,std::vector<int>(10, 0));
    std::vector<std::vector<int>> B(10,std::vector<int>(10, 0));
    std::vector<std::vector<int>> C(10,std::vector<int>(10, 0));
    

    for(int i = 0; i <= 5; i++){
        std::stringstream buffer;
        std::streambuf *sbuf = std::cerr.rdbuf();
        std::cerr.rdbuf(buffer.rdbuf());
        for(int r = 0; r < 10; r++){
            for(int c = 0; c < 10; c++){   
                A[r][c] = dis(gen);
                B[r][c] = dis(gen);
            }
        }

        multiplyMatrices(A, B, C,10, 10, 10);
        std::cerr.rdbuf(sbuf);
        std::cout << buffer.str()<<std::endl;
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

These errors are mainly related to matrix's dimensions or to the values within the three matrices. 
So all next tests will consider these issues. 
*/

//2-TEST ABOUT SIZE'S ERRORS:
//2.1
TEST(MatrixMultiplicationTest, TestRectangularMatrices){
    /*Test with different dimensions of the 2 matrices to see
      if rectangular matrices give errors.*/
    std::random_device rd;  // Seed for the random number engine
    std::mt19937 gen(rd()); // Mersenne Twister random number engine
    std::uniform_int_distribution<> dis(-1000, 1000);

    for(int i = 1; i <= 5; i++){
        /*std::stringstream buffer;
        std::streambuf *sbuf = std::cerr.rdbuf();
        std::cerr.rdbuf(buffer.rdbuf());*/

        //in this way we change size at each iteration, we also try a square matrix.
        std::vector<std::vector<int>> A(3,std::vector<int>(i, 0));
        std::vector<std::vector<int>> B(i,std::vector<int>(3, 0));
        std::vector<std::vector<int>> C(3,std::vector<int>(3, 0));
        std::vector<std::vector<int>> C2(i,std::vector<int>(i, 0));
        //std:: cout << A.size() << " "<< B.size()<<std::endl;

        for(int r = 0; r < 3; r++){
            for(int c = 0; c < i; c++){   
                A[r][c] = dis(gen);
                B[c][r] = dis(gen);
            }
        }

        /*we try both with the product A*B and also B*A, in order to catch more size errors */

        multiplyMatrices(A, B, C, 3, i, 3);
        multiplyMatrices(B, A, C2, i, 3, i);
        /*std::cerr.rdbuf(sbuf);
        std::cout << buffer.str()<<std::endl;*/
        std::vector<std::vector<int>> expected(3, std::vector<int>(3, 0));
        std::vector<std::vector<int>> expected2(i, std::vector<int>(i, 0));
        multiplyMatricesWithoutErrors(A, B, expected, 3, i, 3);
        multiplyMatricesWithoutErrors(B, A, expected2, i, 3, i);
        EXPECT_EQ(C, expected) << "Matrix multiplication test failed! :(((()";
        EXPECT_EQ(C2, expected2) << "Matrix multiplication test failed! :(((()";
    }
}
//2.2
TEST(MatrixMultiplicationTest, TestMaxDimensionsMatrices){
    /*Test to check if over a certain dimension there are errors. 
      If you try a 1000x1000 matrix it gets stuck and it takes too much time. */
    std::vector<std::vector<int>> A(200,std::vector<int>(200, 0));
    std::vector<std::vector<int>> C(200,std::vector<int>(200, 0));

    std::stringstream buffer;
    std::streambuf *sbuf = std::cerr.rdbuf();
    std::cerr.rdbuf(buffer.rdbuf());

    for(int i=0; i < 200 ; i++){
        A[i][i]=1;  
    }
    multiplyMatrices(A, A, C, 200, 200, 200);
    std::cerr.rdbuf(sbuf);
    std::cout << buffer.str()<<std::endl;
    EXPECT_EQ(C, A) << "Matrix multiplication test failed! :(((()";
}




//3-TEST ABOUT VALUES ERRORS:
//3.1
/*Unitary matrices are particulary usefull because they  have many generic properties. 
ex: "matrix has an entire row of ...(number), it's a diagonal matrix,  ecc..."*/
TEST(MatrixMultiplicationTest, TestUnitaryMatrices){
    /*Test with unitary matrices*/
    std::vector<std::vector<int>> A1(1,std::vector<int>(1, 0));
    std::vector<std::vector<int>> B1(1,std::vector<int>(1, 0));
    std::vector<std::vector<int>> C1(1,std::vector<int>(1, 0));
    std::vector<std::vector<int>> expected1(1, std::vector<int>(1, 0));

    std::vector<std::vector<int>> A(2,std::vector<int>(2, 0));
    std::vector<std::vector<int>> B(2,std::vector<int>(2, 0));
    std::vector<std::vector<int>> C(2,std::vector<int>(2, 0));
    std::vector<std::vector<int>> expected(2,std::vector<int>(2, 0));

    for(int i=-10 ; i < 10 ; i++){
       /*std::stringstream buffer;
        std::streambuf *sbuf = std::cerr.rdbuf();
        std::cerr.rdbuf(buffer.rdbuf());*/
        A1[0][0]=i;
        B1[0][0]=i;
        //we also try with some 2x2 homogeneus matrices
        A = {{i,i},{i,i}};
        B = {{i,i},{i,i}};
        multiplyMatrices(A1, B1, C1, 1,1,1);
        
        multiplyMatrices(A, B, C, 2, 2, 2);
       /* std::cerr.rdbuf(sbuf);
        std::cout << buffer.str()<<std::endl;*/
        multiplyMatricesWithoutErrors(A1, B1, expected1, 1,1,1);
        multiplyMatricesWithoutErrors(A, B, expected, 2, 2, 2);
        EXPECT_EQ(C1, expected1) << "Matrix multiplication test failed! :(((()";
        EXPECT_EQ(C, expected) << "Matrix multiplication test failed! :(((()";
    }
}

//3.2
//test for possible max value: 

TEST(MatrixMultiplicationTest, TestOutputMatrices){
    /*Test to see valid inputs: try to see if inputs in a range
      between 0 and 10000 give errors. We don't try negative numbers
      since we already saw that they generate a problem.*/
    std::vector<std::vector<int>> A(100,std::vector<int>(100, 0));
    std::vector<std::vector<int>> B(100,std::vector<int>(100, 0));
    std::vector<std::vector<int>> C(100,std::vector<int>(100, 0));
    int count = 0;

    std::stringstream buffer;
    std::streambuf *sbuf = std::cerr.rdbuf();
    std::cerr.rdbuf(buffer.rdbuf());

    for(int i=0; i < 100 ; i++){
        A[i][i]=1;     
        for(int j=0;j<10;j++){
            B[i][j] = count;
            count++;
        }
    }
    multiplyMatrices(A, B, C, 100, 100, 100);
    std::cerr.rdbuf(sbuf);
    std::cout << buffer.str()<<std::endl;
    EXPECT_EQ(C, B) << "Matrix multiplication test failed! :(((()";
}


//4-INVALID INPUTS TEST
//we made some tests about possible invalid inputs such as  dimensional incompatibilities between A and B:

TEST(MatrixMultiplicationTest, TestInvalidInputs){
    /* Test for invalid dimensions: it should give an error for 
       non-matching dimensions instead it does segmentation fault.*/
    std::vector<std::vector<int>> A(4,std::vector<int>(4, 0));
    std::vector<std::vector<int>> B(2,std::vector<int>(4, 0));
    std::vector<std::vector<int>> C(4,std::vector<int>(4, 0));

    std::stringstream buffer;
    std::streambuf *sbuf = std::cerr.rdbuf();
    std::cerr.rdbuf(buffer.rdbuf());

    // Invalid dimensions
    A = {{1, 2, 3, 4},{5, 6, 7, 8},{9, 10, 11, 12},{13, 14, 15, 16}};
    B = {{1, 2, 3, 4},{5, 6, 7, 8}};
    multiplyMatrices(A, B, C, 4, 4, 4);

}

//5-ERROR 17

/*Now we have one last error (error No. 17: "Result matrix C contains the number 17!") that we've seen during the random test,
but we can't reproduce it with a specific test.
In fact, if we try to create a test case to have a 17 in the C matrix, we encounter other errors but not error 17.
This is probably because some errors can modify the output matrix. 
In this particular case, if we want to get error 17, we necessarily have to go through error 7: "Result matrix contains a number between 11 and 20."
After the modification of the result matrix, we no longer have a 17 in the C matrix.

After some attempts, we probably understand how error 7 impacts the C matrix, and so we managed to create a specific test for error 17. 
Basically, if i have the number 13 in the C matrix, I get error 7, and this error adds 4 to my entry so that I obtain a 17 in the output matrix and finally get error 17
However, if we try to run this test in a for loop, we see that sometimes I just get error 7 without error 17, so we don't know if maybe it's not deterministic or if we don't understand the pattern.
*/

//error n° 17 is probably not deterministic 
TEST(MatrixMultiplicationTest, TestMultiplyMatrices) {
    for(int i =0; i< 20; i++){
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
        {12, 13},
        {13, 13},
        {13, 13},
        {13, 13},
        {13, 13},
        {13, 13},
        
    };
    std::vector<std::vector<int>> C(7, std::vector<int>(2, 0));

    multiplyMatrices(A, B, C, 7, 7, 2);

    /*std::vector<std::vector<int>> expected = {
        {58, 64},
        {139, 154}
    };*/

    multiplyMatricesWithoutErrors(A, B, expected, 7,7,2);

    EXPECT_EQ(C, expected) << "Matrix multiplication test failed! :(((()";
    }
}



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


