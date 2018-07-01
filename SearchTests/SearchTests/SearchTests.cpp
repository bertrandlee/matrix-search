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

static std::vector<std::vector<int> > g_matrix1;
static MyMatrix g_myMatrix1;
static bool g_created = false;


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

void CreateLargeMatrixGlobal()
{
    if (!g_created)
    {
        CreateLargeMatrix(g_matrix1, MAX_DIM);
        g_matrix1[1][1] = MAX_DIM;
        g_matrix1[3][0] = MAX_DIM;
        
        std::cout << "Creating large matrix...\n";
        g_myMatrix1.CreateWithVector(g_matrix1);
        std::cout << "Created large matrix\n";
        
        g_created = true;
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

TEST_CASE( "SearchSequenceNaive Singleton Match Negative", "[SearchSequenceNaive]" ) {
    MyMatrix matrix;
    SearchSequenceNaive search;
    std::vector<int> sequence = {-1};
    std::vector<int> expected = {0};
    std::vector<int> result;
    
    matrix.SetDimensions(1, 1);
    matrix.CreateWithSpecifiedValues("-1");
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

TEST_CASE( "SearchSequenceOptimized Singleton Match Negative", "[SearchSequenceOptimized]" ) {
    MyMatrix matrix;
    SearchSequenceOptimized search;
    std::vector<int> sequence = {-1};
    std::vector<int> expected = {0};
    std::vector<int> result;
    
    matrix.SetDimensions(1, 1);
    matrix.CreateWithSpecifiedValues("-1");
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

TEST_CASE( "SearchSequenceOptimized Basic MultipleCalls", "[SearchSequenceOptimized]" ) {
    MyMatrix matrix;
    SearchSequenceOptimized search;
    std::vector<int> sequence1 = {1,2,2,3};
    std::vector<int> expected1 = {0};
    std::vector<int> sequence2 = {2,4,2};
    std::vector<int> expected2 = {3};
    std::vector<int> sequence3 = {2,2,4};
    std::vector<int> expected3 = {};
    std::vector<int> result;
    
    matrix.SetDimensions(4, 4);
    matrix.CreateWithSpecifiedValues("1,2,2,3,5,6,3,2,9,10,2,3,2,4,2,2");
    
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence1, result);
    REQUIRE(result == expected1);
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence1, result);
    REQUIRE(result == expected1);
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence2, result);
    REQUIRE(result == expected2);
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence3, result);
    REQUIRE(result == expected3);
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

TEST_CASE( "SearchUnorderedNaive Singleton Match Negative", "[SearchUnorderedNaive]" ) {
    MyMatrix matrix;
    SearchUnorderedNaive search;
    std::vector<int> sequence = {-1};
    std::vector<int> expected = {0};
    std::vector<int> result;
    
    matrix.SetDimensions(1, 1);
    matrix.CreateWithSpecifiedValues("-1");
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

TEST_CASE( "SearchUnorderedNaive Basic Match Triplet", "[SearchUnorderedNaive]" ) {
    MyMatrix matrix;
    SearchUnorderedNaive search;
    std::vector<int> sequence = {3, 2, 2, 2};
    std::vector<int> expected = {};
    std::vector<int> result;
    
    matrix.SetDimensions(4, 4);
    matrix.CreateWithSpecifiedValues("1,2,2,3,5,6,3,2,9,10,2,3,2,4,2,2");
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


// SearchUnorderedOptimized tests

TEST_CASE( "SearchUnorderedOptimized Singleton Match", "[SearchUnorderedOptimized]" ) {
    MyMatrix matrix;
    std::vector<int> sequence = {1};
    std::vector<int> expected = {0};
    std::vector<int> result;
    
    matrix.SetDimensions(1, 1);
    matrix.CreateWithSpecifiedValues("1");
    
    SearchUnorderedOptimized search(&matrix);
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchUnorderedOptimized Singleton Match Negative", "[SearchUnorderedOptimized]" ) {
    MyMatrix matrix;
    std::vector<int> sequence = {-1};
    std::vector<int> expected = {0};
    std::vector<int> result;
    
    matrix.SetDimensions(1, 1);
    matrix.CreateWithSpecifiedValues("-1");
    
    SearchUnorderedOptimized search(&matrix);
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
    
    SearchUnorderedOptimized search(&matrix);
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
    
    SearchUnorderedOptimized search(&matrix);
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    std::sort(result.begin(), result.end());
    REQUIRE(result == expected);
}

TEST_CASE( "SearchUnorderedOptimized Basic Match Triplet", "[SearchUnorderedOptimized]" ) {
    MyMatrix matrix;
    std::vector<int> sequence = {3, 2, 2, 2};
    std::vector<int> expected = {};
    std::vector<int> result;
    
    matrix.SetDimensions(4, 4);
    matrix.CreateWithSpecifiedValues("1,2,2,3,5,6,3,2,9,10,2,3,2,4,2,2");
    
    SearchUnorderedOptimized search(&matrix);
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
    
    SearchUnorderedOptimized search(&matrix);
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchUnorderedOptimized Basic MultipleCalls", "[SearchUnorderedOptimized]" ) {
    MyMatrix matrix;
    std::vector<int> sequence1 = {3, 2, 2, 1};
    std::vector<int> expected1 = {0};
    std::vector<int> sequence2 = {2, 2, 2};
    std::vector<int> expected2 = {3};
    std::vector<int> sequence3 = {3, 2, 3};
    std::vector<int> expected3 = {};
    std::vector<int> result;
    
    matrix.SetDimensions(4, 4);
    matrix.CreateWithSpecifiedValues("1,2,3,2,5,6,3,2,9,10,2,3,2,3,2,2");
    
    SearchUnorderedOptimized search(&matrix);
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence1, result);
    REQUIRE(result == expected1);
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence1, result);
    REQUIRE(result == expected1);
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence2, result);
    REQUIRE(result == expected2);
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence3, result);
    REQUIRE(result == expected3);

}


// SearchBestMatchNaive tests

TEST_CASE( "SearchBestMatchNaive Singleton Match", "[SearchBestMatchNaive]" ) {
    MyMatrix matrix;
    SearchBestMatchNaive search;
    std::vector<int> sequence = {1};
    std::vector<int> expected = {0};
    std::vector<int> result;
    
    matrix.SetDimensions(1, 1);
    matrix.CreateWithSpecifiedValues("1");
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchBestMatchNaive Singleton Match Negative", "[SearchBestMatchNaive]" ) {
    MyMatrix matrix;
    SearchBestMatchNaive search;
    std::vector<int> sequence = {-1};
    std::vector<int> expected = {0};
    std::vector<int> result;
    
    matrix.SetDimensions(1, 1);
    matrix.CreateWithSpecifiedValues("-1");
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchBestMatchNaive Singleton NoMatch", "[SearchBestMatchNaive]" ) {
    MyMatrix matrix;
    SearchBestMatchNaive search;
    std::vector<int> sequence = {0};
    std::vector<int> expected = {};
    std::vector<int> result;
    
    matrix.SetDimensions(1, 1);
    matrix.CreateWithSpecifiedValues("1");
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchBestMatchNaive Basic NoMatch 1", "[SearchBestMatchNaive]" ) {
    MyMatrix matrix;
    SearchBestMatchNaive search;
    std::vector<int> sequence = {9};
    std::vector<int> expected = {};
    std::vector<int> result;
    
    matrix.SetDimensions(2, 4);
    matrix.CreateWithSpecifiedValues("1,2,3,4,5,6,7,8");
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchBestMatchNaive Basic NoMatch 2", "[SearchBestMatchNaive]" ) {
    MyMatrix matrix;
    SearchBestMatchNaive search;
    std::vector<int> sequence = {9,10};
    std::vector<int> expected = {};
    std::vector<int> result;
    
    matrix.SetDimensions(2, 4);
    matrix.CreateWithSpecifiedValues("1,2,3,4,5,6,7,8");
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchBestMatchNaive Basic Match SingleSeq 1", "[SearchBestMatchNaive]" ) {
    MyMatrix matrix;
    SearchBestMatchNaive search;
    std::vector<int> sequence = {4};
    std::vector<int> expected = {0};
    std::vector<int> result;
    
    matrix.SetDimensions(2, 4);
    matrix.CreateWithSpecifiedValues("1,2,3,4,5,6,7,8");
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchBestMatchNaive Basic Match SingleSeq 2", "[SearchBestMatchNaive]" ) {
    MyMatrix matrix;
    SearchBestMatchNaive search;
    std::vector<int> sequence = {5};
    std::vector<int> expected = {1};
    std::vector<int> result;
    
    matrix.SetDimensions(2, 4);
    matrix.CreateWithSpecifiedValues("1,2,3,4,5,6,7,8");
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchBestMatchNaive Basic Match DoubleSeq 1", "[SearchBestMatchNaive]" ) {
    MyMatrix matrix;
    SearchBestMatchNaive search;
    std::vector<int> sequence = {1,3};
    std::vector<int> expected = {0};
    std::vector<int> result;
    
    matrix.SetDimensions(2, 4);
    matrix.CreateWithSpecifiedValues("1,2,3,4,5,6,7,8");
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchBestMatchNaive Basic Match DoubleSeq 2", "[SearchBestMatchNaive]" ) {
    MyMatrix matrix;
    SearchBestMatchNaive search;
    std::vector<int> sequence = {7,6};
    std::vector<int> expected = {1};
    std::vector<int> result;
    
    matrix.SetDimensions(2, 4);
    matrix.CreateWithSpecifiedValues("1,2,3,4,5,6,7,8");
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchBestMatchNaive Basic Match DoubleSeq 3", "[SearchBestMatchNaive]" ) {
    MyMatrix matrix;
    SearchBestMatchNaive search;
    std::vector<int> sequence = {9,8};
    std::vector<int> expected = {1};
    std::vector<int> result;
    
    matrix.SetDimensions(2, 4);
    matrix.CreateWithSpecifiedValues("1,2,3,4,5,6,7,8");
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchBestMatchNaive Basic Match DoubleSeq 4", "[SearchBestMatchNaive]" ) {
    MyMatrix matrix;
    SearchBestMatchNaive search;
    std::vector<int> sequence = {1,0};
    std::vector<int> expected = {0};
    std::vector<int> result;
    
    matrix.SetDimensions(2, 4);
    matrix.CreateWithSpecifiedValues("1,2,3,4,5,6,7,8");
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}


TEST_CASE( "SearchBestMatchNaive Basic MultiMatch 1", "[SearchBestMatchNaive]" ) {
    MyMatrix matrix;
    SearchBestMatchNaive search;
    std::vector<int> sequence = {4,3};
    std::vector<int> expected = {0};
    std::vector<int> result;
    
    matrix.SetDimensions(2, 4);
    matrix.CreateWithSpecifiedValues("1,2,3,4,5,6,3,4");
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchBestMatchNaive Basic MultiMatch 2", "[SearchBestMatchNaive]" ) {
    MyMatrix matrix;
    SearchBestMatchNaive search;
    std::vector<int> sequence = {5,4,3};
    std::vector<int> expected = {1};
    std::vector<int> result;
    
    matrix.SetDimensions(2, 4);
    matrix.CreateWithSpecifiedValues("1,2,3,4,5,6,3,4");
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchBestMatchNaive Basic MultiMatch 3", "[SearchBestMatchNaive]" ) {
    MyMatrix matrix;
    SearchBestMatchNaive search;
    std::vector<int> sequence = {7,6,4};
    std::vector<int> expected = {1};
    std::vector<int> result;
    
    matrix.SetDimensions(2, 4);
    matrix.CreateWithSpecifiedValues("1,2,3,4,5,6,3,4");
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchBestMatchNaive Basic RepeatMatch 1", "[SearchBestMatchNaive]" ) {
    MyMatrix matrix;
    SearchBestMatchNaive search;
    std::vector<int> sequence = {4,2,2,1};
    std::vector<int> expected = {1};
    std::vector<int> result;
    
    matrix.SetDimensions(2, 6);
    matrix.CreateWithSpecifiedValues("1,2,9,9,3,4,1,2,9,9,2,4");
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchBestMatchNaive Basic RepeatMatch 2", "[SearchBestMatchNaive]" ) {
    MyMatrix matrix;
    SearchBestMatchNaive search;
    std::vector<int> sequence = {4,2,2,1};
    std::vector<int> expected = {0};
    std::vector<int> result;
    
    matrix.SetDimensions(2, 6);
    matrix.CreateWithSpecifiedValues("1,2,9,9,2,4,1,2,9,9,3,4");
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchBestMatchNaive Basic RepeatMatch 3", "[SearchBestMatchNaive]" ) {
    MyMatrix matrix;
    SearchBestMatchNaive search;
    std::vector<int> sequence = {4,2,2,1};
    std::vector<int> expected = {0};
    std::vector<int> result;
    
    matrix.SetDimensions(2, 6);
    matrix.CreateWithSpecifiedValues("1,2,9,9,9,4,1,9,9,9,3,4");
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchBestMatchNaive Basic RepeatMatch 4", "[SearchBestMatchNaive]" ) {
    MyMatrix matrix;
    SearchBestMatchNaive search;
    std::vector<int> sequence = {4,2,2,2,1};
    std::vector<int> expected = {1};
    std::vector<int> result;
    
    matrix.SetDimensions(2, 6);
    matrix.CreateWithSpecifiedValues("1,2,9,9,9,4,1,2,2,9,3,4");
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchBestMatchNaive Basic RepeatMatch 5", "[SearchBestMatchNaive]" ) {
    MyMatrix matrix;
    SearchBestMatchNaive search;
    std::vector<int> sequence = {4,2,2,2,1};
    std::vector<int> expected = {0};
    std::vector<int> result;
    
    matrix.SetDimensions(2, 6);
    matrix.CreateWithSpecifiedValues("1,2,4,9,2,2,1,2,2,9,3,4");
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchBestMatchNaive Basic RepeatMatch 6", "[SearchBestMatchNaive]" ) {
    MyMatrix matrix;
    SearchBestMatchNaive search;
    std::vector<int> sequence = {4,2,2,2,1};
    std::vector<int> expected = {0};
    std::vector<int> result;
    
    matrix.SetDimensions(2, 6);
    matrix.CreateWithSpecifiedValues("1,2,4,9,2,2,1,2,2,2,3,4");
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}


// SearchBestMatchOptimized tests

TEST_CASE( "SearchBestMatchOptimized Singleton Match", "[SearchBestMatchOptimized]" ) {
    MyMatrix matrix;
    std::vector<int> sequence = {1};
    std::vector<int> expected = {0};
    std::vector<int> result;
    
    matrix.SetDimensions(1, 1);
    matrix.CreateWithSpecifiedValues("1");
    
    SearchBestMatchOptimized search(matrix.GetMap());
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchBestMatchOptimized Singleton Match Negative", "[SearchBestMatchOptimized]" ) {
    MyMatrix matrix;
    std::vector<int> sequence = {-1};
    std::vector<int> expected = {0};
    std::vector<int> result;
    
    matrix.SetDimensions(1, 1);
    matrix.CreateWithSpecifiedValues("-1");

    SearchBestMatchOptimized search(matrix.GetMap());
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchBestMatchOptimized Singleton NoMatch", "[SearchBestMatchOptimized]" ) {
    MyMatrix matrix;
    std::vector<int> sequence = {0};
    std::vector<int> expected = {};
    std::vector<int> result;
    
    matrix.SetDimensions(1, 1);
    matrix.CreateWithSpecifiedValues("1");
    
    SearchBestMatchOptimized search(matrix.GetMap());
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchBestMatchOptimized Basic NoMatch 1", "[SearchBestMatchOptimized]" ) {
    MyMatrix matrix;
    std::vector<int> sequence = {9};
    std::vector<int> expected = {};
    std::vector<int> result;
    
    matrix.SetDimensions(2, 4);
    matrix.CreateWithSpecifiedValues("1,2,3,4,5,6,7,8");

    SearchBestMatchOptimized search(matrix.GetMap());
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchBestMatchOptimized Basic NoMatch 2", "[SearchBestMatchOptimized]" ) {
    MyMatrix matrix;
    std::vector<int> sequence = {9,10};
    std::vector<int> expected = {};
    std::vector<int> result;
    
    matrix.SetDimensions(2, 4);
    matrix.CreateWithSpecifiedValues("1,2,3,4,5,6,7,8");

    SearchBestMatchOptimized search(matrix.GetMap());
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchBestMatchOptimized Basic Match SingleSeq 1", "[SearchBestMatchOptimized]" ) {
    MyMatrix matrix;
    std::vector<int> sequence = {4};
    std::vector<int> expected = {0};
    std::vector<int> result;
    
    matrix.SetDimensions(2, 4);
    matrix.CreateWithSpecifiedValues("1,2,3,4,5,6,7,8");

    SearchBestMatchOptimized search(matrix.GetMap());
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchBestMatchOptimized Basic Match SingleSeq 2", "[SearchBestMatchOptimized]" ) {
    MyMatrix matrix;
    std::vector<int> sequence = {5};
    std::vector<int> expected = {1};
    std::vector<int> result;
    
    matrix.SetDimensions(2, 4);
    matrix.CreateWithSpecifiedValues("1,2,3,4,5,6,7,8");

    SearchBestMatchOptimized search(matrix.GetMap());
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchBestMatchOptimized Basic Match DoubleSeq 1", "[SearchBestMatchOptimized]" ) {
    MyMatrix matrix;
    std::vector<int> sequence = {1,3};
    std::vector<int> expected = {0};
    std::vector<int> result;
    
    matrix.SetDimensions(2, 4);
    matrix.CreateWithSpecifiedValues("1,2,3,4,5,6,7,8");

    SearchBestMatchOptimized search(matrix.GetMap());
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchBestMatchOptimized Basic Match DoubleSeq 2", "[SearchBestMatchOptimized]" ) {
    MyMatrix matrix;
    std::vector<int> sequence = {7,6};
    std::vector<int> expected = {1};
    std::vector<int> result;
    
    matrix.SetDimensions(2, 4);
    matrix.CreateWithSpecifiedValues("1,2,3,4,5,6,7,8");
    
    SearchBestMatchOptimized search(matrix.GetMap());
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchBestMatchOptimized Basic Match DoubleSeq 3", "[SearchBestMatchOptimized]" ) {
    MyMatrix matrix;
    std::vector<int> sequence = {9,8};
    std::vector<int> expected = {1};
    std::vector<int> result;
    
    matrix.SetDimensions(2, 4);
    matrix.CreateWithSpecifiedValues("1,2,3,4,5,6,7,8");
    
    SearchBestMatchOptimized search(matrix.GetMap());
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchBestMatchOptimized Basic Match DoubleSeq 4", "[SearchBestMatchOptimized]" ) {
    MyMatrix matrix;
    std::vector<int> sequence = {1,0};
    std::vector<int> expected = {0};
    std::vector<int> result;
    
    matrix.SetDimensions(2, 4);
    matrix.CreateWithSpecifiedValues("1,2,3,4,5,6,7,8");

    SearchBestMatchOptimized search(matrix.GetMap());
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}


TEST_CASE( "SearchBestMatchOptimized Basic MultiMatch 1", "[SearchBestMatchOptimized]" ) {
    MyMatrix matrix;
    std::vector<int> sequence = {4,3};
    std::vector<int> expected = {0};
    std::vector<int> result;
    
    matrix.SetDimensions(2, 4);
    matrix.CreateWithSpecifiedValues("1,2,3,4,5,6,3,4");

    SearchBestMatchOptimized search(matrix.GetMap());
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchBestMatchOptimized Basic MultiMatch 2", "[SearchBestMatchOptimized]" ) {
    MyMatrix matrix;
    std::vector<int> sequence = {5,4,3};
    std::vector<int> expected = {1};
    std::vector<int> result;
    
    matrix.SetDimensions(2, 4);
    matrix.CreateWithSpecifiedValues("1,2,3,4,5,6,3,4");
    
    SearchBestMatchOptimized search(matrix.GetMap());
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchBestMatchOptimized Basic MultiMatch 3", "[SearchBestMatchOptimized]" ) {
    MyMatrix matrix;
    std::vector<int> sequence = {7,6,4};
    std::vector<int> expected = {1};
    std::vector<int> result;
    
    matrix.SetDimensions(2, 4);
    matrix.CreateWithSpecifiedValues("1,2,3,4,5,6,3,4");
    
    SearchBestMatchOptimized search(matrix.GetMap());
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchBestMatchOptimized Basic RepeatMatch 1", "[SearchBestMatchOptimized]" ) {
    MyMatrix matrix;
    std::vector<int> sequence = {4,2,2,1};
    std::vector<int> expected = {1};
    std::vector<int> result;
    
    matrix.SetDimensions(2, 6);
    matrix.CreateWithSpecifiedValues("1,2,9,9,3,4,1,2,9,9,2,4");
    
    SearchBestMatchOptimized search(matrix.GetMap());
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchBestMatchOptimized Basic RepeatMatch 2", "[SearchBestMatchOptimized]" ) {
    MyMatrix matrix;
    std::vector<int> sequence = {4,2,2,1};
    std::vector<int> expected = {0};
    std::vector<int> result;
    
    matrix.SetDimensions(2, 6);
    matrix.CreateWithSpecifiedValues("1,2,9,9,2,4,1,2,9,9,3,4");
    
    SearchBestMatchOptimized search(matrix.GetMap());
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchBestMatchOptimized Basic RepeatMatch 3", "[SearchBestMatchOptimized]" ) {
    MyMatrix matrix;
    std::vector<int> sequence = {4,2,2,1};
    std::vector<int> expected = {0};
    std::vector<int> result;
    
    matrix.SetDimensions(2, 6);
    matrix.CreateWithSpecifiedValues("1,2,9,9,9,4,1,9,9,9,3,4");

    SearchBestMatchOptimized search(matrix.GetMap());
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchBestMatchOptimized Basic RepeatMatch 4", "[SearchBestMatchOptimized]" ) {
    MyMatrix matrix;
    std::vector<int> sequence = {4,2,2,2,1};
    std::vector<int> expected = {1};
    std::vector<int> result;
    
    matrix.SetDimensions(2, 6);
    matrix.CreateWithSpecifiedValues("1,2,9,9,9,4,1,2,2,9,3,4");
    
    SearchBestMatchOptimized search(matrix.GetMap());
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchBestMatchOptimized Basic RepeatMatch 5", "[SearchBestMatchOptimized]" ) {
    MyMatrix matrix;
    std::vector<int> sequence = {4,2,2,2,1};
    std::vector<int> expected = {0};
    std::vector<int> result;
    
    matrix.SetDimensions(2, 6);
    matrix.CreateWithSpecifiedValues("1,2,4,9,2,2,1,2,2,9,3,4");

    SearchBestMatchOptimized search(matrix.GetMap());
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchBestMatchOptimized Basic RepeatMatch 6", "[SearchBestMatchOptimized]" ) {
    MyMatrix matrix;
    std::vector<int> sequence = {4,2,2,2,1};
    std::vector<int> expected = {0};
    std::vector<int> result;
    
    matrix.SetDimensions(2, 6);
    matrix.CreateWithSpecifiedValues("1,2,4,9,2,2,1,2,2,2,3,4");
    
    SearchBestMatchOptimized search(matrix.GetMap());
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence, result);
    REQUIRE(result == expected);
}

TEST_CASE( "SearchBestMatchOptimized Basic MultipleCalls", "[SearchBestMatchOptimized]" ) {
    MyMatrix matrix;
    std::vector<int> sequence1 = {3, 2};
    std::vector<int> expected1 = {0};
    std::vector<int> sequence2 = {2, 2, 2};
    std::vector<int> expected2 = {3};
    std::vector<int> sequence3 = {3, 3, 2};
    std::vector<int> expected3 = {0};
    std::vector<int> result;
    
    matrix.SetDimensions(4, 4);
    matrix.CreateWithSpecifiedValues("1,2,3,2,5,6,3,2,9,10,2,3,2,3,2,2");
    
    SearchBestMatchOptimized search(matrix.GetMap());
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence1, result);
    REQUIRE(result == expected1);
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence1, result);
    REQUIRE(result == expected1);
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence2, result);
    REQUIRE(result == expected2);
    search.SearchMatrix(matrix.GetVectorMatrix(), sequence3, result);
    REQUIRE(result == expected3);
}



///////////////////////////
// Stress/performance tests
///////////////////////////

// Baseline stress tests

TEST_CASE( "Baseline Large 2D Vector Iterate", "[SearchUnorderedOptimized]" ) {
    std::vector<std::vector<int> > matrix;
    volatile bool condition = false; // Use volatile to ensure code is not optimized out
    
    CreateLargeMatrix(matrix, 3);
    
    clock_t time_a = clock();
    
    for (int i = 0; i < MAX_DIM; i++)
    {
        condition = matrix[i][2] >= 2;
    }
    
    clock_t time_b = clock();
    std::cout << "BaselineLarge2DVectorIterate: matrix iterate time = " << (time_b - time_a) << " us" << std::endl;
    condition = false;
    REQUIRE(condition == false);
    
}

TEST_CASE( "Baseline Large Flat Array Iterate", "[SearchUnorderedOptimized]" ) {
    unsigned int arraySize = MAX_DIM * MAX_DIM;
    volatile bool condition = false; // Use volatile to ensure code is not optimized out
    int *pArray = NULL;
    unsigned int rowOffset;
    int i, j;
    
    pArray = new int[arraySize];
    
    for (unsigned int i = 0; i < arraySize; i++)
    {
        pArray[i] = i % 3;
    }
    
    clock_t time_a = clock();
    
    for (i = 0; i < MAX_DIM; i++)
    {
        rowOffset = i * MAX_DIM;
        condition = pArray[rowOffset + 2] >= 2;
    }
    
    clock_t time_b = clock();
    std::cout << "BaselineLargeFlatArrayIterate: matrix iterate time = " << (time_b - time_a) << " us" << std::endl;
 
    delete [] pArray;

    condition = false;
    REQUIRE(condition == false);
    
    CreateLargeMatrixGlobal();
}



// SearchSequenceNaive stress tests

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



// SearchSequenceOptimized stress tests

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

// SearchUnorderedNaive stress tests

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

// SearchUnorderedOptimized stress tests


TEST_CASE( "SearchUnorderedOptimized Large Match", "[SearchUnorderedOptimized]" ) {
    std::vector<int> sequence = {2, MAX_DIM};
    std::vector<int> expected = {1, 3};
    std::vector<int> result;

    SearchUnorderedOptimized search(&g_myMatrix1);
    search.SearchMatrix(g_matrix1, sequence, result, true, "SearchUnorderedOptimized");
    std::sort(result.begin(), result.end());
    REQUIRE(result == expected);
}

TEST_CASE( "SearchUnorderedOptimized Large NoMatch", "[SearchUnorderedOptimized]" ) {
    std::vector<int> sequence = {MAX_DIM+1};
    std::vector<int> expected = {};
    std::vector<int> result;
    
    SearchUnorderedOptimized search(&g_myMatrix1);
    search.SearchMatrix(g_matrix1, sequence, result, true, "SearchUnorderedOptimized");
    REQUIRE(result == expected);
}

TEST_CASE( "SearchUnorderedOptimized Stress Match", "[SearchUnorderedOptimized]" ) {
    std::vector<int> sequence;
    std::vector<int> expected = {1, 3};
    std::vector<int> result;
    
    for (int i = MAX_DIM-1; i >= MAX_DIM-20; i--)
    {
        sequence.push_back(i);
    }
    
    sequence.push_back(MAX_DIM);
    
    SearchUnorderedOptimized search(&g_myMatrix1);
    search.SearchMatrix(g_matrix1, sequence, result, true, "SearchUnorderedOptimized");
    std::sort(result.begin(),result.end());
    REQUIRE(result == expected);
}

TEST_CASE( "SearchUnorderedOptimized Stress NoMatch", "[SearchUnorderedOptimized]" ) {
    std::vector<int> sequence;
    std::vector<int> expected = {};
    std::vector<int> result;
    
    for (int i = MAX_DIM-1; i >= MAX_DIM-20; i--)
    {
        sequence.push_back(i);
    }
    
    sequence.push_back(MAX_DIM+1);
    
    SearchUnorderedOptimized search(&g_myMatrix1);
    
    search.SearchMatrix(g_matrix1, sequence, result, true, "SearchUnorderedOptimized");
    REQUIRE(result == expected);
}

// SearchBestMatchNaive stress tests

TEST_CASE( "SearchBestMatchNaive Stress Match", "[SearchBestMatchNaive]" ) {
    std::vector<std::vector<int> > matrix;
    SearchBestMatchNaive search;
    std::vector<int> sequence = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    std::vector<int> expected = {MAX_DIM-1};
    std::vector<int> result;
    
    CreateLargeMatrix(matrix, 1);
    matrix[MAX_DIM-2][MAX_DIM-1] = 1;
    matrix[MAX_DIM-2][MAX_DIM-2] = 2;

    matrix[MAX_DIM-1][MAX_DIM-1] = 1;
    matrix[MAX_DIM-1][MAX_DIM-2] = 2;
    matrix[MAX_DIM-1][MAX_DIM-3] = 3;

    search.SearchMatrix(matrix, sequence, result, true, "SearchBestMatchNaive");
    REQUIRE(result == expected);
}

TEST_CASE( "SearchBestMatchNaive Stress NoMatch", "[SearchBestMatchNaive]" ) {
    std::vector<std::vector<int> > matrix;
    SearchBestMatchNaive search;
    std::vector<int> sequence = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    std::vector<int> expected = {};
    std::vector<int> result;
    
    CreateLargeMatrix(matrix, 1);
    
    search.SearchMatrix(matrix, sequence, result, true, "SearchBestMatchNaive");
    REQUIRE(result == expected);
}

// SearchBestMatchOptimized stress tests

TEST_CASE( "SearchBestMatchOptimized Stress Match", "[SearchBestMatchOptimized]" ) {
    std::vector<int> sequence = {MAX_DIM, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    std::vector<int> expected = {1};
    std::vector<int> result;
    
    SearchBestMatchOptimized search(g_myMatrix1.GetMap());
    search.SearchMatrix(g_matrix1, sequence, result, true, "SearchBestMatchOptimized");
    REQUIRE(result == expected);
}

TEST_CASE( "SearchBestMatchOptimized Stress NoMatch", "[SearchBestMatchOptimized]" ) {
    std::vector<int> sequence = {-1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11, -12, -13, -14, -15, -16, -17, -18, -19, -20};
    std::vector<int> expected = {};
    std::vector<int> result;
    
    SearchBestMatchOptimized search(g_myMatrix1.GetMap());
    search.SearchMatrix(g_matrix1, sequence, result, true, "SearchBestMatchOptimized");
    REQUIRE(result == expected);
}



