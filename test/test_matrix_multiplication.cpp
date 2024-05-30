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


TEST(MatrixMultiplicationTest, TestUnitaryMatrices){
    std::vector<std::vector<int>> A1(1,std::vector<int>(1, 0));
    std::vector<std::vector<int>> B1(1,std::vector<int>(1, 0));
    std::vector<std::vector<int>> C1(1,std::vector<int>(1, 0));
    std::vector<std::vector<int>> expected1(1, std::vector<int>(1, 0));

    std::vector<std::vector<int>> A(2,std::vector<int>(2, 0));
    std::vector<std::vector<int>> B(2,std::vector<int>(2, 0));
    std::vector<std::vector<int>> C(2,std::vector<int>(2, 0));
    std::vector<std::vector<int>> expected(2,std::vector<int>(2, 0));

    for(int i=17; i < 18 ; i++){
        std::stringstream buffer;
        std::streambuf *sbuf = std::cerr.rdbuf();
        std::cerr.rdbuf(buffer.rdbuf());
        A1[0][0]=1;
        B1[0][0]=i;
        //A = {{i,i},{i,i}};
        //B = {{i,i},{i,i}};
        multiplyMatrices(A1, B1, C1, 1,1,1);
        std::cerr.rdbuf(sbuf);
        std::cout << buffer.str()<<std::endl;
        //multiplyMatrices(A, B, C, 2, 2, 2);
        multiplyMatricesWithoutErrors(A1, B1, expected1, 1,1,1);
        //multiplyMatricesWithoutErrors(A, B, expected, 2, 2, 2);
        EXPECT_EQ(C1, expected1) << "Matrix multiplication test failed! :(((()";
        //EXPECT_EQ(C, expected) << "Matrix multiplication test failed! :(((()";
    }
}

/*TEST(MatrixMultiplicationTest, TestRectangularMatrices){
    std::random_device rd;  // Seed for the random number engine
    std::mt19937 gen(rd()); // Mersenne Twister random number engine
    std::uniform_int_distribution<> dis(-1000, 1000);

    for(int i = 1; i <= 5; i++){
        std::vector<std::vector<int>> A(3,std::vector<int>(i, 0));
        std::vector<std::vector<int>> B(i,std::vector<int>(3, 0));
        std::vector<std::vector<int>> C(3,std::vector<int>(3, 0));
        //std:: cout << A.size() << " "<< B.size()<<std::endl;

        for(int r = 0; r < 3; r++){
            for(int c = 0; c < i; c++){   
                A[r][c] = dis(gen);
                B[c][r] = dis(gen);
            }
        }

        multiplyMatrices(A, B, C, 3, i, 3);
        std::vector<std::vector<int>> expected(3, std::vector<int>(3, 0));
        multiplyMatricesWithoutErrors(A, B, expected, 3, i, 3);
        EXPECT_EQ(C, expected) << "Matrix multiplication test failed! :(((()";
    }
}*/
/*
TEST(MatrixMultiplicationTest, TestOutputMatrices){
    std::vector<std::vector<int>> A(10,std::vector<int>(10, 0));
    std::vector<std::vector<int>> B(10,std::vector<int>(10, 0));
    std::vector<std::vector<int>> C(10,std::vector<int>(10, 0));
    std::vector<std::vector<int>> expected(10,std::vector<int>(10, 0));
    int count =0;

    for(int i=0; i < 10 ; i++){
        A[i][i]=1;
        B[i][1] = 17;
        for(int j=0;j<10;j++){
            
            count++;
        }
    }
    multiplyMatrices(A, B, C, 10, 10, 10);
    multiplyMatricesWithoutErrors(A, B, expected, 10, 10, 10);
    EXPECT_EQ(C, expected) << "Matrix multiplication test failed! :(((()";
}*/

/*TEST(MatrixMultiplicationTest, TestRectangularMatrices2){
    std::random_device rd;  // Seed for the random number engine
    std::mt19937 gen(rd()); // Mersenne Twister random number engine
    std::uniform_int_distribution<> dis(-15, 15);

    for(int i = 1; i <= 5; i++){
        std::vector<std::vector<int>> A(i,std::vector<int>(3, 0));
        std::vector<std::vector<int>> B(3,std::vector<int>(i, 0));
        std::vector<std::vector<int>> C(i,std::vector<int>(i, 0));
        //std:: cout << A.size() << " "<< B.size()<<std::endl;

        for(int r = 0; r < i; r++){
            for(int c = 0; c < 3; c++){   
                A[r][c] = dis(gen);
                B[c][r] = dis(gen);
            }
        }

        multiplyMatrices(A, B, C, i, 3, i);
        std::vector<std::vector<int>> expected(i, std::vector<int>(i, 0));
        multiplyMatricesWithoutErrors(A, B, expected, i, 3, i);
        EXPECT_EQ(C, expected) << "Matrix multiplication test failed! :(((()";
    }
}*/

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
