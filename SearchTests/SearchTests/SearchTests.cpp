//
//  main.cpp
//  SearchTests
//
//  Created by Bertrand Lee on 23/6/18.
//  Copyright © 2018 Bertrand Lee. All rights reserved.
//

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"
#include "MyMatrix.h"
#include "Search.h"

#define MAX_DIM 10000

void CreateLargeMatrix(std::vector<std::vector<int> >& matrix, int mod)
{
    matrix.resize(MAX_DIM);
    
    for (int i = 0; i < MAX_DIM; i++)
    {
        matrix[i].resize(MAX_DIM);
        
        for (int j = 0; j < MAX_DIM; j++)
        {
            matrix[i][j] = j % mod;
        }
    }
}

TEST_CASE( "SearchBase EmptyMatrix", "[SearchBase]" ) {
    SearchSequenceNaive search;
    std::vector<int> sequence = {1, 2};
    std::vector<int> result;
    std::vector<std::vector<int> > empty;
    
    REQUIRE_THROWS_AS(search.SearchMatrix(empty, sequence, result), std::invalid_argument);
}

TEST_CASE( "SearchBase EmptySequence", "[SearchBase]" ) {
    MyMatrix matrix;
    SearchSequenceNaive search;
    std::vector<int> sequence = {};
    std::vector<int> result;
    
    matrix.SetDimensions(1, 1);
    matrix.CreateWithSpecifiedValues("1");
    REQUIRE_THROWS_AS(search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result), std::invalid_argument);
}

TEST_CASE( "SearchBase TooLargeSequence", "[SearchBase]" ) {
    MyMatrix matrix;
    SearchSequenceNaive search;
    std::vector<int> sequence = {1, 2};
    std::vector<int> result;
    
    matrix.SetDimensions(1, 1);
    matrix.CreateWithSpecifiedValues("1");
    REQUIRE_THROWS_AS(search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result), std::invalid_argument);
}


TEST_CASE( "SearchSequenceNaive Singleton Match", "[SearchSequenceNaive]" ) {
    MyMatrix matrix;
    SearchSequenceNaive search;
    std::vector<int> sequence = {1};
    std::vector<int> expected = {0};
    std::vector<int> result;
    
    matrix.SetDimensions(1, 1);
    matrix.CreateWithSpecifiedValues("1");
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchSequenceNaive Singleton NoMatch", "[SearchSequenceNaive]" ) {
    MyMatrix matrix;
    SearchSequenceNaive search;
    std::vector<int> sequence = {0};
    std::vector<int> expected = {};
    std::vector<int> result;
    
    matrix.SetDimensions(1, 1);
    matrix.CreateWithSpecifiedValues("1");
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}


TEST_CASE( "SearchSequenceNaive Basic Match", "[SearchSequenceNaive]" ) {
    MyMatrix matrix;
    SearchSequenceNaive search;
    std::vector<int> sequence = {2, 3};
    std::vector<int> expected = {0, 2, 3};
    std::vector<int> result;
    
    matrix.SetDimensions(4, 4);
    matrix.CreateWithSpecifiedValues("1,2,3,4,5,6,3,2,9,10,2,3,2,3,11,12");
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchSequenceNaive Basic NoMatch", "[SearchSequenceNaive]" ) {
    MyMatrix matrix;
    SearchSequenceNaive search;
    std::vector<int> sequence = {2, 1};
    std::vector<int> expected = {};
    std::vector<int> result;
    
    matrix.SetDimensions(4, 4);
    matrix.CreateWithSpecifiedValues("1,2,3,4,5,6,3,2,9,10,2,3,2,3,11,12");
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}


TEST_CASE( "SearchSequenceNaive Large NoMatch", "[SearchSequenceNaive]" ) {
    std::vector<std::vector<int> > matrix;
    SearchSequenceNaive search;
    std::vector<int> sequence = {3, 2};
    std::vector<int> expected = {};
    std::vector<int> result;

    CreateLargeMatrix(matrix, 4);
    search.SearchMatrix(matrix, sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchSequenceNaive Large Match", "[SearchSequenceNaive]" ) {
    std::vector<std::vector<int> > matrix;
    SearchSequenceNaive search;
    std::vector<int> sequence = {1, 2, 4};
    std::vector<int> expected = {0, 1, MAX_DIM-1};
    std::vector<int> result;
    
    CreateLargeMatrix(matrix, 4);
    matrix[0][MAX_DIM-3] = 1;
    matrix[0][MAX_DIM-2] = 2;
    matrix[0][MAX_DIM-1] = 4;
    matrix[1][3] = 4;
    matrix[MAX_DIM-1][3] = 4;
    search.SearchMatrix(matrix, sequence, result);
    REQUIRE(result == expected);
}

