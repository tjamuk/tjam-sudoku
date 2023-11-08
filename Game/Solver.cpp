//
// Created by Tate Moore on 07/08/2023.
//

#include <algorithm>
#include <ctime>
#include <random>
#include <iostream>
#include "Solver.h"
#include "Grid.h"

void
Solver::getRemainingNumbers(
        bool is_grid_empty,
        const int COL
)
{
    nums_copy = NUMS; //vector of 1..9

    if (not is_grid_empty)
    {

        auto nums_copy_end = nums_copy.end();

//        int row; int col;
//
//        for (col = 0; col < 9; col++)
//        {
//            for (row = 0; row < 9; row++)
//            {
//                if (not Grid::isCellEmpty(col,row))
//                {
//                    nums_copy_end = std::remove(
//                            nums_copy.begin(),
//                            nums_copy_end,
//                            Grid::getCellValue(col,row)
//                            );
//                    nums_copy.pop_back();
//                }
//            }
//        }

        for (int row = 0; row < 9; row++)
        {
            //changed to not
            if (not Grid::isCellEmpty(COL, row))
            {
                nums_copy_end = std::remove(
                            nums_copy.begin(),
                            nums_copy_end,
                            Grid::getCellValue(COL,row)
                            );
                nums_copy.pop_back();
            }
        }
    }
}

//------------------------------------------------------------------
//==================================================================
//------------------------------------------------------------------

void
Solver::shuffleNumsIntoQueues(
        bool is_grid_empty
)
{
    shuffled_nums_queues = std::array<std::queue<int>, 9>();

    unsigned seed;

    //for each queue
    for (int queue_index = 0; queue_index < 9; queue_index++)
    {
        //-- 1) FIND REMAINING NUMBERS --\\

        getRemainingNumbers(is_grid_empty, queue_index);

        //-- 2) SHUFFLE REMAINING NUMBERS --\\

        seed = time(nullptr) + queue_index;

        shuffle(
                nums_copy.begin(),
                nums_copy.end(),
                std::default_random_engine(seed)
                );

        //-- 3) PLACE INTO CORRESPONDING QUEUE --\\

        for (int num : nums_copy)
        {
            shuffled_nums_queues[queue_index].push(num);
        }
    }
}

//------------------------------------------------------------------
//==================================================================
//------------------------------------------------------------------

bool
Solver::shuffleThenSolve(
        bool is_grid_empty
)
{
    shuffleNumsIntoQueues(is_grid_empty);

    return solve();
}

//------------------------------------------------------------------
//==================================================================
//------------------------------------------------------------------

bool
Solver::solve(

)
{

    for (int col = 0; col < 9; col++)
    {
        for (int row = 0; row < 9; row++)
        {
            if (Grid::isCellEmpty(col,row))
            {
                const unsigned int size = shuffled_nums_queues[col].size();

                for (int tries = 0; tries < size; tries++)
                {
//                    grid[col][row] = shuffled_nums_queues[col].front();
                    Grid::setCellValue(
                            col,
                            row,
                            shuffled_nums_queues[col].front()
                            );

                    shuffled_nums_queues[col].pop();

                    if (not isNumRuleBreak(col,row))
                    {
                        bool result = solve();
                        if (result) { return true; }
                    }

//                    shuffled_nums_queues[col].push(grid[col][row]);
                    shuffled_nums_queues[col].push( Grid::getCellValue(col, row) );
//                    grid[col][row] = NULL_CELL_NUM;
                    Grid::removeCellValue(col, row);
                }
                return false;
            }
        }
    }
    return true;
}

//------------------------------------------------------------------
//==================================================================
//------------------------------------------------------------------

bool
Solver::doesNumBreakBoxRule(
        const int NUM_COL,
        const int NUM_ROW
)
{
    //Boxes holds index values: 0-2, 3-5, 6-8
    //3 = width and height of box.
    //For index values 0-8, do integer division, 0/3 = 0, 1/3 = 0, 2/3 = 0, 3/3 = 1, 4/3 = 1, 5/3 = 1, 6/3 = 2, 7/3 = 2, 8/3 = 2
    //If we multiply these results by 3, (index 0) 0*3 = 0, (1) 0*3 = 0, ... , (3) 1*3 = 3, ... , (6) 2*3 = 6, ...
    //These results are the starting index values of the boxes.
    //So we can use the formula (<index>/3)*3 to find this ^
    //THen the starting index + 2 = end index for the boxes.

    //This all comes down to, given the row and col of a num, we can find its local box and search it (using the starting and end indexes as limits)

    const int BOX_START_COL = (NUM_COL / 3) * 3;
    const int BOX_END_COL = BOX_START_COL + 2;

    const int BOX_START_ROW = (NUM_ROW / 3) * 3;
    const int BOX_END_ROW = BOX_START_ROW + 2;

//    const int NUM_VALUE = grid[NUM_COL][NUM_ROW];
    const int NUM_VALUE = Grid::getCellValue(NUM_COL, NUM_ROW);

    int row; int col;

    //Checks every cell in the square (incl. new number's cell)
    for (col = BOX_START_COL; col <= BOX_END_COL; col++)
    {
        for (row = BOX_START_ROW; row <= BOX_END_ROW; row++)
        {
            if (Grid::getCellValue(col, row) == NUM_VALUE)
            {
                if (col != NUM_COL && row != NUM_ROW)
                {
                    //setConflictCell(col, row);
                    //return conflict_cell;

                    conflict_cell_ptr -> setCell(col, row);
                    return true;
                }
            }
        }
    }

    //resetConflictCell();
    conflict_cell_ptr -> reset();
    return false;
}

//------------------------------------------------------------------
//==================================================================
//------------------------------------------------------------------

bool
Solver::isNumRuleBreak(
        const int NUM_COL,
        const int NUM_ROW
)
{

//    conflict_cell;

    //const int NUM_VALUE = grid[NUM_COL][NUM_ROW];
    const int NUM_VALUE = Grid::getCellValue(NUM_COL, NUM_ROW);
    int index = -1;

    //--CHECKING COLUMN--\\

    ///does above not left

    //Checking cells left of number
    while (++index < NUM_COL) {
//        if (grid[index][NUM_ROW] == NUM_VALUE)
        if (Grid::getCellValue(index, NUM_ROW) == NUM_VALUE)
        {
            conflict_cell_ptr -> setCell(index, NUM_ROW);
            return true;
//            setConflictCell(index, NUM_ROW);
//            return conflict_cell;

        }
    }

    //Checking cells right of number
    while (++index < 9) {
//        if (grid[index][NUM_ROW] == NUM_VALUE)
        if (Grid::getCellValue(index, NUM_ROW) == NUM_VALUE)
        {
            conflict_cell_ptr -> setCell(index, NUM_ROW);
            return true;
//            setConflictCell(index, NUM_ROW);
//            return conflict_cell;
        }
    }

    //--CHECKING ROW--\\

    index = -1;

    //Checking cells above number
    while (++index < NUM_ROW) {
//        if (grid[NUM_COL][index] == NUM_VALUE)
        if (Grid::getCellValue(NUM_COL, index) == NUM_VALUE)
        {
            conflict_cell_ptr -> setCell(NUM_COL, index);
            return true;
//            setConflictCell(NUM_COL, index);
//            return conflict_cell;
        }
    }

    //Checking cells below number
    while (++index < 9) {
//        if (grid[NUM_COL][index] == NUM_VALUE)
        if (Grid::getCellValue(NUM_COL, index) == NUM_VALUE)
        {
            conflict_cell_ptr -> setCell(NUM_COL, index);
            return true;
//            setConflictCell(NUM_COL, index);
//            return conflict_cell;
        }
    }

    //--CHECKING SQUARE--\\

    return doesNumBreakBoxRule(NUM_COL, NUM_ROW);
}

Solver::Solver(SpecialCell * ccp)
{
    conflict_cell_ptr = ccp;
}

const std::vector<int> &
Solver::getNumsCopy()
{
    return nums_copy;
}

const std::array<std::queue<int>, 9> &
Solver::getShuffledNumsQueues()
{
    return shuffled_nums_queues;
}
