#include "matrix_multiplication.h"
#include "../src/matrix_mult.cpp"
#include <iostream>
#include <vector>
#include <gtest/gtest.h>
#include <random>

// ######################### Source code of multiplyMatrices in src/matrix_mult


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

//random 

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

//invalid_input

TEST(MatrixMultiplicationTest, invalid){
    std::vector<std::vector<int>> C(4,std::vector<int>(4, 0));
    

   
        std::stringstream buffer;
        std::streambuf *sbuf = std::cerr.rdbuf();
        std::cerr.rdbuf(buffer.rdbuf());
         std::vector<std::vector<int>> A = {
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1},
         };
        
         std::vector<std::vector<int>> B = {
            {'a', 0, 0, 0},
            {0, 'b', 0, 0},
            {0, 0, 'c', 0},
            {0, 0, 0, 'd'},
         };
           
        multiplyMatrices(A, B, C, 4, 4, 4);
        std::cerr.rdbuf(sbuf);
        std::cout << buffer.str()<<std::endl;
        //std::vector<std::vector<int>> expected(5, std::vector<int>(5, 0));
        // multiplyMatricesWithoutErrors(A, B, expected, 10, 10, 10);
        EXPECT_EQ(C, B) << "Matrix multiplication test failed! :(((()";
}

/*TEST(MatrixMultiplicationTest, TestInvalidInputs){
    /* Test for invalid dimensions: it should give an error for 
       non-matching dimensions instead it does segmentation fault.*/
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

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
