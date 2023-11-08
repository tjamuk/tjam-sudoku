//
// Created by Tate Moore on 27/06/2023.
//

#include "gtest/gtest.h"
#include "Grid.h"

class GridTests : public ::testing::Test {

protected:

    Grid * grid;

    void virtual SetUp()
    {
        grid = new Grid();
    }

    void virtual TearDown() {
        delete grid;
    }
};

/**
 * @test if the game constructor correctly puts all the grid values to zero

 * @param GridTests - the name of the test suite
 * @param testCase_GridConstructor - the name of the test case
 *
 * @see Grid.h
*/
TEST_F(GridTests, testCase_GridConstructor)
{
    EXPECT_TRUE( Grid :: isCellEmpty(0,0) );
    EXPECT_TRUE( Grid :: isCellEmpty(8,0) );
    EXPECT_TRUE( Grid :: isCellEmpty(0,8) );
    EXPECT_TRUE( Grid :: isCellEmpty(8,8) );

    EXPECT_TRUE( Grid :: isCellEmpty(4,3) );
    EXPECT_TRUE( Grid :: isCellEmpty(3,4) );
}

/**
 * @test Tests Grid::setCellValue(..) and Grid::getCellValue(..)

 * @param GridTests - the name of the test suite
 * @param testCase_ChangingCellValues - the name of the test case
 *
 * @see Grid.h
*/
TEST_F(GridTests, testCase_ChangingCellValues)
{
    Grid::setCellValue(0,0,5);
    EXPECT_EQ( Grid :: getCellValue(0,0) , 5 );

    Grid::setCellValue(8,8,2);
    EXPECT_NE( Grid :: getCellValue(8,8) , 6 );
}

/**
 * @test Tests Grid::removeCellValue(..)

 * @param GridTests - the name of the test suite
 * @param testCase_RemovingCellValues - the name of the test case
 *
 * @see Grid.h
*/
TEST_F(GridTests, testCase_RemovingCellValues)
{
    Grid::setCellValue(0,0,8);
    EXPECT_FALSE( Grid :: isCellEmpty(0,0));

    Grid::removeCellValue(0,0);
    EXPECT_TRUE( Grid :: isCellEmpty(0,0));
}

