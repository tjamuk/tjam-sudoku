//
// Created by Tate Moore on 27/06/2023.
//

#include "gtest/gtest.h"
#include "Grid.h"
#include "Solver.h"

class SolverTests : public ::testing::Test {

protected:

    Grid * grid;
    Solver * solver;

    void virtual SetUp()
    {
        SpecialCell * conflict_cell_ptr = new SpecialCell();

        grid = new Grid();
        solver = new Solver(conflict_cell_ptr);

    }

    void virtual TearDown() {
        delete grid;
    }
};

/**
 * @test Tests the function: bool isNewNumRuleBreak(int newNumCol, int newNumRow) from Game

 * @param SolverTests - the name of the test suite
 * @param testCase_isNewNumRuleBreak - the name of the test case
 *
 * @see Solver.h
*/
TEST_F(SolverTests, testCase_isNewNumRuleBreak)
{
    //new num (top left corner)
    Grid::setCellValue(0,0,3);

    //conflicting num (top right) - row rule break;
    Grid::setCellValue(8,0,3);
    EXPECT_TRUE(Solver::isNumRuleBreak(0,0));

    //randomly picked number (no more rulebreak)
    Grid::setCellValue(8,0,2);

    //conflicting num (bottom left) - column rule break;
    Grid::setCellValue(0,8,3);
    EXPECT_TRUE(Solver::isNumRuleBreak(0,0));

    //randomly picked number (no more rulebreak)
    Grid::setCellValue(0,8,4);

    //conflicting num (bottom right of same square) - square rule break;
    Grid::setCellValue(2,2,3);
    EXPECT_TRUE(Solver::isNumRuleBreak(0,0)); //randomly picked number (no more rulebreak)

    Grid::setCellValue(0,0,0);

    //non-conflicting num with the 3 @ 2,2 (adjacent but not in same square) - no rule break.
    Grid::setCellValue(3,1,3);
    EXPECT_FALSE(Solver::isNumRuleBreak(2,2));
}

/**
 * @test Tests the function: getRemainingNumbers(int COL, int ROW) from Solver with standard values.

 * @param SolverTests - the name of the test suite
 * @param testCase_getRemainingNumbers_standard - the name of the test case
 *
 * @see Solver.h
*/
TEST_F(SolverTests, testCase_getRemainingNumbers_standard)
{
    Grid::setCellValue(8,8,1);
    Grid::setCellValue(8,5,9);
    Grid::setCellValue(8,0,5);


    std::vector<int> expected_remaining_nums = {2,3,4,6,7,8};

    Solver::getRemainingNumbers(false, 8);

//    for (int num : game -> nums_copy) {
//        std::cout<<num<<std::endl;
//    }

    EXPECT_EQ(Solver::getNumsCopy(),expected_remaining_nums);
}

/**
 * @test Tests the function: getRemainingNumbers(int COL, int ROW) from Solver with all the numbers taken in a column.

 * @param SolverTests - the name of the test suite
 * @param testCase_getRemainingNumbers_all - the name of the test case
 *
 * @see Solver.h
*/
TEST_F(SolverTests, testCase_getRemainingNumbers_all)
{
    const int RANDOMLY_ORDERED_NUMS[9] = {5,9,4,6,7,2,8,1,3};

    for (int row = 0; row < 9; row++)
    {
        Grid::setCellValue(0,row,RANDOMLY_ORDERED_NUMS[row]);
    }

    std::vector<int> expected_remaining_nums = {};

    Solver::getRemainingNumbers(false, 0);

    EXPECT_EQ(Solver::getNumsCopy(),expected_remaining_nums);
}

/**
 * @test Tests the function: getRemainingNumbers(int COL, int ROW) from Solver with no the numbers taken in a column.

 * @param SolverTests - the name of the test suite
 * @param testCase_getRemainingNumbers_none - the name of the test case
 *
 * @see Solver.h
*/
TEST_F(SolverTests, testCase_getRemainingNumbers_none)
{

    std::vector<int> expected_remaining_nums = {1,2,3,4,5,6,7,8,9};

    Solver::getRemainingNumbers(false, 3);

    EXPECT_EQ(Solver::getNumsCopy(),expected_remaining_nums);
}

/**
 * @test Tests the function: shuffleNumsIntoQueues(bool is_grid_empty) from Solver.

 * @param SolverTests - the name of the test suite
 * @param testCase_shuffleNumsIntoQueues - the name of the test case
 *
 * @see Solver.h
*/
TEST_F(SolverTests, testCase_shuffleNumsIntoQueues)
{
    ///Test flawed as there is a small ()

    std::queue<int> nums_ascending;

    const std::vector<int> NUMS_COPY = {1,2,3,4,5,6,7,8,9};

    for (int num = 0; num < 9; num++)
    {
        nums_ascending.push(NUMS_COPY[num]);
    }

    Solver::shuffleNumsIntoQueues(false);

    int repeats = 0;

    for (auto & q : Solver::getShuffledNumsQueues())
    {
        EXPECT_EQ(q.size(),9);

        if (q == nums_ascending) {
            repeats++;
        }
    }

    EXPECT_NE(repeats,9);
}

/**
 * @test Tests the function: solve() from Solver on an empty grid. Tests to see if it is a correct completely filled grid.

 * @param SolverTests - the name of the test suite
 * @param testCase_solve_emptyGrid - the name of the test case
 *
 * @see Solver.h
*/
TEST_F(SolverTests, testCase_solve_emptyGrid) {
    Solver::shuffleThenSolve(false);

    std::cout<<"\n\n\n";

    for (int col = 0; col < 9; col++)
    {
        for (int row = 0; row < 9; row++)
        {
            std::cout<<Grid::getCellValue(col,row) << " ";

            EXPECT_FALSE(Solver::isNumRuleBreak(col, row));
        }
        std::cout<<std::endl;
    }
}

/**
 * @test Tests the function: solve() from Solver on an partially filled grid. Tests to see if it is a correct completely filled grid.

 * @param SolverTests - the name of the test suite
 * @param testCase_solve_emptyGrid - the name of the test case
 *
 * @see Solver.h
*/
TEST_F(SolverTests, testCase_solve_partialGrid)
{
    for (int row = 0; row < 9; row++)
    {
        Grid::setCellValue(0,row,row+1);
    }

    Grid::setCellValue(1,0,9);
    Grid::setCellValue(2,0,8);
    Grid::setCellValue(3,0,7);
    Grid::setCellValue(4,0,6);
    Grid::setCellValue(5,0,5);
    Grid::setCellValue(6,0,4);
    Grid::setCellValue(7,0,3);
    Grid::setCellValue(8,0,2);

    Solver::shuffleThenSolve(false);

    std::cout<<"\n\n\n";

    for (int col = 0; col < 9; col++)
    {
        for (int row = 0; row < 9; row++)
        {
            std::cout<<Grid::getCellValue(col,row) << " ";

            //EXPECT_FALSE(game->isNumRuleBreak(col, row));
        }
        std::cout<<std::endl;
    }
}