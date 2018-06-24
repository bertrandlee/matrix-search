//
//  main.cpp
//  SearchTests
//
//  Created by Bertrand Lee on 23/6/18.
//  Copyright © 2018 Bertrand Lee. All rights reserved.
//

#define CATCH_CONFIG_RUNNER
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

int main( int argc, char* argv[] ) {
    // global set-up...
    
    int result = Catch::Session().run( argc, argv );
    
    // global clean-up...
    
    return result;
}


// SearchBase tests

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

// SearchSequenceNaive tests

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

TEST_CASE( "SearchSequenceNaive Basic FirstMatch", "[SearchSequenceNaive]" ) {
    MyMatrix matrix;
    SearchSequenceNaive search;
    std::vector<int> sequence = {1};
    std::vector<int> expected = {0};
    std::vector<int> result;
    
    matrix.SetDimensions(4, 4);
    matrix.CreateWithSpecifiedValues("1,2,3,4,5,6,3,2,9,10,2,3,2,3,11,12");
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchSequenceNaive Basic LastMatch", "[SearchSequenceNaive]" ) {
    MyMatrix matrix;
    SearchSequenceNaive search;
    std::vector<int> sequence = {12};
    std::vector<int> expected = {3};
    std::vector<int> result;
    
    matrix.SetDimensions(4, 4);
    matrix.CreateWithSpecifiedValues("1,2,3,4,5,6,3,2,9,10,2,3,2,3,11,12");
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchSequenceNaive Basic WholeMatch", "[SearchSequenceNaive]" ) {
    MyMatrix matrix;
    SearchSequenceNaive search;
    std::vector<int> sequence = {5, 6, 3, 2};
    std::vector<int> expected = {1};
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
    search.SearchMatrix(matrix, sequence, result, true, "SearchSequenceNaive");
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
    search.SearchMatrix(matrix, sequence, result, true, "SearchSequenceNaive");
    REQUIRE(result == expected);
}

TEST_CASE( "SearchSequenceNaive Stress NoMatch", "[SearchSequenceNaive]" ) {
    std::vector<std::vector<int> > matrix;
    SearchSequenceNaive search;
    std::vector<int> sequence = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,19};
    std::vector<int> expected = {};
    std::vector<int> result;
    
    CreateLargeMatrix(matrix, 20);
    search.SearchMatrix(matrix, sequence, result, true, "SearchSequenceNaive");
    REQUIRE(result == expected);
}

TEST_CASE( "SearchSequenceNaive Stress Match", "[SearchSequenceNaive]" ) {
    std::vector<std::vector<int> > matrix;
    SearchSequenceNaive search;
    std::vector<int> sequence = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,19};
    std::vector<int> expected = {0,1,MAX_DIM-1};
    std::vector<int> result;
    
    CreateLargeMatrix(matrix, 20);
    matrix[0][18] = 19;
    matrix[1][18] = 19;
    matrix[MAX_DIM-1][18] = 19;
    search.SearchMatrix(matrix, sequence, result, true, "SearchSequenceNaive");
    REQUIRE(result == expected);
}

TEST_CASE( "SearchSequenceNaive Stress Plus NoMatch", "[SearchSequenceNaive]" ) {
    std::vector<std::vector<int> > matrix;
    SearchSequenceNaive search;
    std::vector<int> sequence = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
    std::vector<int> expected = {};
    std::vector<int> result;
    
    CreateLargeMatrix(matrix, 1);
    search.SearchMatrix(matrix, sequence, result, true, "SearchSequenceNaive");
    REQUIRE(result == expected);
}

TEST_CASE( "SearchSequenceNaive Stress Plus Match", "[SearchSequenceNaive]" ) {
    std::vector<std::vector<int> > matrix;
    SearchSequenceNaive search;
    std::vector<int> sequence = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
    std::vector<int> expected = {2};
    std::vector<int> result;
    
    CreateLargeMatrix(matrix, 1);
    matrix[2][19] = 1;
    search.SearchMatrix(matrix, sequence, result, true, "SearchSequenceNaive");
    REQUIRE(result == expected);
}


// SearchSequenceOptimized tests

TEST_CASE( "SearchSequenceOptimized Singleton Match", "[SearchSequenceOptimized]" ) {
    MyMatrix matrix;
    SearchSequenceOptimized search;
    std::vector<int> sequence = {1};
    std::vector<int> expected = {0};
    std::vector<int> result;
    
    matrix.SetDimensions(1, 1);
    matrix.CreateWithSpecifiedValues("1");
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchSequenceOptimized Singleton NoMatch", "[SearchSequenceOptimized]" ) {
    MyMatrix matrix;
    SearchSequenceOptimized search;
    std::vector<int> sequence = {0};
    std::vector<int> expected = {};
    std::vector<int> result;
    
    matrix.SetDimensions(1, 1);
    matrix.CreateWithSpecifiedValues("1");
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}


TEST_CASE( "SearchSequenceOptimized Basic Match", "[SearchSequenceOptimized]" ) {
    MyMatrix matrix;
    SearchSequenceOptimized search;
    std::vector<int> sequence = {2, 3};
    std::vector<int> expected = {0, 2, 3};
    std::vector<int> result;
    
    matrix.SetDimensions(4, 4);
    matrix.CreateWithSpecifiedValues("1,2,3,4,5,6,3,2,9,10,2,3,2,3,11,12");
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchSequenceOptimized Basic FirstMatch", "[SearchSequenceOptimized]" ) {
    MyMatrix matrix;
    SearchSequenceOptimized search;
    std::vector<int> sequence = {1};
    std::vector<int> expected = {0};
    std::vector<int> result;
    
    matrix.SetDimensions(4, 4);
    matrix.CreateWithSpecifiedValues("1,2,3,4,5,6,3,2,9,10,2,3,2,3,11,12");
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchSequenceOptimized Basic LastMatch", "[SearchSequenceOptimized]" ) {
    MyMatrix matrix;
    SearchSequenceOptimized search;
    std::vector<int> sequence = {12};
    std::vector<int> expected = {3};
    std::vector<int> result;
    
    matrix.SetDimensions(4, 4);
    matrix.CreateWithSpecifiedValues("1,2,3,4,5,6,3,2,9,10,2,3,2,3,11,12");
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchSequenceOptimized Basic WholeMatch", "[SearchSequenceOptimized]" ) {
    MyMatrix matrix;
    SearchSequenceOptimized search;
    std::vector<int> sequence = {5, 6, 3, 2};
    std::vector<int> expected = {1};
    std::vector<int> result;
    
    matrix.SetDimensions(4, 4);
    matrix.CreateWithSpecifiedValues("1,2,3,4,5,6,3,2,9,10,2,3,2,3,11,12");
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}


TEST_CASE( "SearchSequenceOptimized Basic NoMatch", "[SearchSequenceOptimized]" ) {
    MyMatrix matrix;
    SearchSequenceOptimized search;
    std::vector<int> sequence = {2, 1};
    std::vector<int> expected = {};
    std::vector<int> result;
    
    matrix.SetDimensions(4, 4);
    matrix.CreateWithSpecifiedValues("1,2,3,4,5,6,3,2,9,10,2,3,2,3,11,12");
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchSequenceOptimized Large NoMatch", "[SearchSequenceOptimized]" ) {
    std::vector<std::vector<int> > matrix;
    SearchSequenceOptimized search;
    std::vector<int> sequence = {3, 2};
    std::vector<int> expected = {};
    std::vector<int> result;
    
    CreateLargeMatrix(matrix, 4);
    search.SearchMatrix(matrix, sequence, result, true, "SearchSequenceOptimized");
    REQUIRE(result == expected);
}

TEST_CASE( "SearchSequenceOptimized Large Match", "[SearchSequenceOptimized]" ) {
    std::vector<std::vector<int> > matrix;
    SearchSequenceOptimized search;
    std::vector<int> sequence = {1, 2, 4};
    std::vector<int> expected = {0, 1, MAX_DIM-1};
    std::vector<int> result;
    
    CreateLargeMatrix(matrix, 4);
    matrix[0][MAX_DIM-3] = 1;
    matrix[0][MAX_DIM-2] = 2;
    matrix[0][MAX_DIM-1] = 4;
    matrix[1][3] = 4;
    matrix[MAX_DIM-1][3] = 4;
    search.SearchMatrix(matrix, sequence, result, true, "SearchSequenceOptimized");
    REQUIRE(result == expected);
}

TEST_CASE( "SearchSequenceOptimized Stress NoMatch", "[SearchSequenceOptimized]" ) {
    std::vector<std::vector<int> > matrix;
    SearchSequenceOptimized search;
    std::vector<int> sequence = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,19};
    std::vector<int> expected = {};
    std::vector<int> result;
    
    CreateLargeMatrix(matrix, 20);
    search.SearchMatrix(matrix, sequence, result, true, "SearchSequenceOptimized");
    REQUIRE(result == expected);
}

TEST_CASE( "SearchSequenceOptimized Stress Match", "[SearchSequenceOptimized]" ) {
    std::vector<std::vector<int> > matrix;
    SearchSequenceOptimized search;
    std::vector<int> sequence = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,19};
    std::vector<int> expected = {0,1,MAX_DIM-1};
    std::vector<int> result;
    
    CreateLargeMatrix(matrix, 20);
    matrix[0][18] = 19;
    matrix[1][18] = 19;
    matrix[MAX_DIM-1][18] = 19;
    search.SearchMatrix(matrix, sequence, result, true, "SearchSequenceOptimized");
    REQUIRE(result == expected);
}

TEST_CASE( "SearchSequenceOptimized Stress Plus NoMatch", "[SearchSequenceOptimized]" ) {
    std::vector<std::vector<int> > matrix;
    SearchSequenceOptimized search;
    std::vector<int> sequence = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
    std::vector<int> expected = {};
    std::vector<int> result;
    
    CreateLargeMatrix(matrix, 1);
    search.SearchMatrix(matrix, sequence, result, true, "SearchSequenceOptimized");
    REQUIRE(result == expected);
}

TEST_CASE( "SearchSequenceOptimized Stress Plus Match", "[SearchSequenceOptimized]" ) {
    std::vector<std::vector<int> > matrix;
    SearchSequenceOptimized search;
    std::vector<int> sequence = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
    std::vector<int> expected = {2};
    std::vector<int> result;
    
    CreateLargeMatrix(matrix, 1);
    matrix[2][19] = 1;
    search.SearchMatrix(matrix, sequence, result, true, "SearchSequenceOptimized");
    REQUIRE(result == expected);
}

// SearchUnorderedNaive tests

TEST_CASE( "SearchUnorderedNaive Singleton Match", "[SearchUnorderedNaive]" ) {
    MyMatrix matrix;
    SearchUnorderedNaive search;
    std::vector<int> sequence = {1};
    std::vector<int> expected = {0};
    std::vector<int> result;
    
    matrix.SetDimensions(1, 1);
    matrix.CreateWithSpecifiedValues("1");
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchUnorderedNaive Singleton NoMatch", "[SearchUnorderedNaive]" ) {
    MyMatrix matrix;
    SearchUnorderedNaive search;
    std::vector<int> sequence = {0};
    std::vector<int> expected = {};
    std::vector<int> result;
    
    matrix.SetDimensions(1, 1);
    matrix.CreateWithSpecifiedValues("1");
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchUnorderedNaive Basic Match", "[SearchUnorderedNaive]" ) {
    MyMatrix matrix;
    SearchUnorderedNaive search;
    std::vector<int> sequence = {3, 2, 2};
    std::vector<int> expected = {0, 3};
    std::vector<int> result;
    
    matrix.SetDimensions(4, 4);
    matrix.CreateWithSpecifiedValues("1,2,2,3,5,6,3,2,9,10,2,3,2,3,2,2");
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchUnorderedNaive Basic NoMatch", "[SearchUnorderedNaive]" ) {
    MyMatrix matrix;
    SearchUnorderedNaive search;
    std::vector<int> sequence = {3, 2, 2};
    std::vector<int> expected = {};
    std::vector<int> result;
    
    matrix.SetDimensions(4, 4);
    matrix.CreateWithSpecifiedValues("1,2,3,4,5,6,3,2,9,10,2,3,2,3,11,12");
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchUnorderedNaive Large Match", "[SearchUnorderedNaive]" ) {
    std::vector<std::vector<int> > matrix;
    SearchUnorderedNaive search;
    std::vector<int> sequence = {4, 4};
    std::vector<int> expected = {1, 3};
    std::vector<int> result;
    
    CreateLargeMatrix(matrix, 4);
    matrix[1][1] = 4;
    matrix[1][MAX_DIM-1] = 4;
    matrix[3][1] = 4;
    matrix[3][MAX_DIM-1] = 4;
    search.SearchMatrix(matrix, sequence, result, true, "SearchUnorderedNaive");
    REQUIRE(result == expected);
}

TEST_CASE( "SearchUnorderedNaive Large NoMatch", "[SearchUnorderedNaive]" ) {
    std::vector<std::vector<int> > matrix;
    SearchUnorderedNaive search;
    std::vector<int> sequence = {4};
    std::vector<int> expected = {};
    std::vector<int> result;
    
    CreateLargeMatrix(matrix, 4);
    search.SearchMatrix(matrix, sequence, result, true, "SearchUnorderedNaive");
    REQUIRE(result == expected);
}

TEST_CASE( "SearchUnorderedNaive Stress Match", "[SearchUnorderedNaive]" ) {
    std::vector<std::vector<int> > matrix;
    SearchUnorderedNaive search;
    std::vector<int> sequence;
    std::vector<int> expected = {1, 3};
    std::vector<int> result;
    
    for (int i = MAX_DIM-1; i >= MAX_DIM-20; i--)
    {
        sequence.push_back(i);
    }
    
    sequence.push_back(MAX_DIM);
    
    CreateLargeMatrix(matrix, MAX_DIM);
    matrix[1][1] = MAX_DIM;
    matrix[3][0] = MAX_DIM;
    search.SearchMatrix(matrix, sequence, result, true, "SearchUnorderedNaive");
    REQUIRE(result == expected);
}

TEST_CASE( "SearchUnorderedNaive Stress NoMatch", "[SearchUnorderedNaive]" ) {
    std::vector<std::vector<int> > matrix;
    SearchUnorderedNaive search;
    std::vector<int> sequence;
    std::vector<int> expected = {};
    std::vector<int> result;

    for (int i = MAX_DIM-1; i >= MAX_DIM-20; i--)
    {
        sequence.push_back(i);
    }
    
    sequence.push_back(MAX_DIM);
    
    CreateLargeMatrix(matrix, MAX_DIM);
    search.SearchMatrix(matrix, sequence, result, true, "SearchUnorderedNaive");
    REQUIRE(result == expected);
}

// SearchUnorderedOptimized tests

TEST_CASE( "SearchUnorderedOptimized Singleton Match", "[SearchUnorderedOptimized]" ) {
    MyMatrix matrix;
    std::vector<int> sequence = {1};
    std::vector<int> expected = {0};
    std::vector<int> result;
    
    matrix.SetDimensions(1, 1);
    matrix.CreateWithSpecifiedValues("1");
    
    SearchUnorderedOptimized search(matrix.GetMap());
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchUnorderedOptimized Singleton NoMatch", "[SearchUnorderedOptimized]" ) {
    MyMatrix matrix;
    std::vector<int> sequence = {0};
    std::vector<int> expected = {};
    std::vector<int> result;
    
    matrix.SetDimensions(1, 1);
    matrix.CreateWithSpecifiedValues("1");
    
    SearchUnorderedOptimized search(matrix.GetMap());
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchUnorderedOptimized Basic Match", "[SearchUnorderedOptimized]" ) {
    MyMatrix matrix;
    std::vector<int> sequence = {3, 2, 2};
    std::vector<int> expected = {0, 3};
    std::vector<int> result;
    
    matrix.SetDimensions(4, 4);
    matrix.CreateWithSpecifiedValues("1,2,2,3,5,6,3,2,9,10,2,3,2,3,2,2");
    
    SearchUnorderedOptimized search(matrix.GetMap());
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchUnorderedOptimized Basic NoMatch", "[SearchUnorderedOptimized]" ) {
    MyMatrix matrix;
    std::vector<int> sequence = {3, 2, 2};
    std::vector<int> expected = {};
    std::vector<int> result;
    
    matrix.SetDimensions(4, 4);
    matrix.CreateWithSpecifiedValues("1,2,3,4,5,6,3,2,9,10,2,3,2,3,11,12");
    
    SearchUnorderedOptimized search(matrix.GetMap());
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchUnorderedOptimized Large Match", "[SearchUnorderedOptimized]" ) {
    std::vector<std::vector<int> > matrix;
    std::vector<int> sequence = {4, 4};
    std::vector<int> expected = {1, 3};
    std::vector<int> result;
    
    CreateLargeMatrix(matrix, 4);
    matrix[1][1] = 4;
    matrix[1][MAX_DIM-1] = 4;
    matrix[3][1] = 4;
    matrix[3][MAX_DIM-1] = 4;
    
    MyMatrix mymatrix;
    mymatrix.CreateWithVector(matrix);
    SearchUnorderedOptimized search(mymatrix.GetMap());
    search.SearchMatrix(matrix, sequence, result, true, "SearchUnorderedOptimized");
    REQUIRE(result == expected);
}

TEST_CASE( "SearchUnorderedOptimized Large NoMatch", "[SearchUnorderedOptimized]" ) {
    std::vector<std::vector<int> > matrix;
    std::vector<int> sequence = {4};
    std::vector<int> expected = {};
    std::vector<int> result;
    
    CreateLargeMatrix(matrix, 4);
    
    MyMatrix mymatrix;
    mymatrix.CreateWithVector(matrix);
    SearchUnorderedOptimized search(mymatrix.GetMap());
    search.SearchMatrix(matrix, sequence, result, true, "SearchUnorderedOptimized");
    REQUIRE(result == expected);
}

TEST_CASE( "SearchUnorderedOptimized Stress Match", "[SearchUnorderedOptimized]" ) {
    std::vector<std::vector<int> > matrix;
    std::vector<int> sequence;
    std::vector<int> expected = {1, 3};
    std::vector<int> result;
    
    for (int i = MAX_DIM-1; i >= MAX_DIM-20; i--)
    {
        sequence.push_back(i);
    }
    
    sequence.push_back(MAX_DIM);
    
    CreateLargeMatrix(matrix, MAX_DIM);
    matrix[1][1] = MAX_DIM;
    matrix[3][0] = MAX_DIM;
    
    MyMatrix mymatrix;
    mymatrix.CreateWithVector(matrix);
    SearchUnorderedOptimized search(mymatrix.GetMap());
    
    search.SearchMatrix(matrix, sequence, result, true, "SearchUnorderedOptimized");
    REQUIRE(result == expected);
}

TEST_CASE( "SearchUnorderedOptimized Stress NoMatch", "[SearchUnorderedOptimized]" ) {
    std::vector<std::vector<int> > matrix;
    std::vector<int> sequence;
    std::vector<int> expected = {};
    std::vector<int> result;
    
    for (int i = MAX_DIM-1; i >= MAX_DIM-20; i--)
    {
        sequence.push_back(i);
    }
    
    sequence.push_back(MAX_DIM);
    
    CreateLargeMatrix(matrix, MAX_DIM);

    MyMatrix mymatrix;
    mymatrix.CreateWithVector(matrix);
    SearchUnorderedOptimized search(mymatrix.GetMap());
    
    search.SearchMatrix(matrix, sequence, result, true, "SearchUnorderedOptimized");
    REQUIRE(result == expected);
}

