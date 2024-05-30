#include "matrix_multiplication.h"
#include "../src/matrix_mult.cpp"
#include <iostream>
#include <vector>
#include <gtest/gtest.h>
#include <random>

// ######################### Source code of multiplyMatrices in src/matrix_mult


/*
TEST(MatrixMultiplicationTest, TestMultiplyMatrices) {
    std::vector<std::vector<int>> A = {
        {1, 2, 3},
        {4, 5, 6}
    };
    std::vector<std::vector<int>> B = {
        {7, 8},
        {9, 10},
        {11, 12}
    };
    std::vector<std::vector<int>> C(2, std::vector<int>(2, 0));

    multiplyMatrices(A, B, C, 2, 3, 2);

    std::vector<std::vector<int>> expected = {
        {58, 64},
        {139, 154}
    };

    ASSERT_EQ(C, expected) << "Matrix multiplication test failed! :(((()";
}*/


TEST(MatrixMultiplicationTest, TestIncreasingRandomMatrices){
    std::random_device rd;  // Seed for the random number engine
    std::mt19937 gen(rd()); // Mersenne Twister random number engine
    std::uniform_int_distribution<> dis(-15, 15);

    for(int i =5; i < 50; i += 5){
        std::vector<std::vector<int>> A(i,std::vector<int>(i, 0));
        std::vector<std::vector<int>> B(i,std::vector<int>(i, 0));
        std::vector<std::vector<int>> C(i,std::vector<int>(i, 0));

        for(int r = 0; r < i; r++){
            for(int c = 0; c < i; c++){   
                A[r][c] = dis(gen);
                B[r][c] = dis(gen);
            }
        }

        multiplyMatrices(A, B, C, i, i, i);
        std::vector<std::vector<int>> expected(i, std::vector<int>(i, 0));
        multiplyMatricesWithoutErrors(A, B, expected, i, i, i);
        EXPECT_EQ(C, expected) << "Matrix multiplication test failed! :(((()";
    }
}


TEST(MatrixMultiplicationTest, TestUnitaryMatrices){
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



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
