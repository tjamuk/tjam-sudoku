//
// Created by Tate Moore on 07/08/2023.
//

#include <random>
#include "Grid.h"
#include "UserSetCells.h"
#include "Solver.h"

//--------------\\
//--CONSTRUCTORS--\\

Grid::Grid()
{
    int row; int col;
    for (col = 0; col < 9; col++)
    {
        for (row = 0; row < 9; row++)
        {
            grid[col][row] = NULL_CELL_VALUE;
        }
    }
}

  //------------------\\
 //--GRID CELL VALUES--\\

int
Grid::getCellValue(
        const int COL,
        const int ROW
        )
{
    return grid[COL][ROW];
}

void
Grid::setCellValue(
        const int COL,
        const int ROW,
        const int NEW_VALUE
        )
{
    grid[COL][ROW] = NEW_VALUE;
}

void
Grid::removeCellValue(
        const int COL,
        const int ROW
        )
{
    grid[COL][ROW] = NULL_CELL_VALUE;

    //resetConflictCell(); //remove probably.
}

bool
Grid::isCellEmpty(
        const int COL,
        const int ROW
        )
{
    if (grid[COL][ROW] == NULL_CELL_VALUE)
    {
        return true;
    }
    else
    {
        return false;
    }
}

 //-----------------\\
//--SETTING UP GRID--\\

void
Grid::setupEasyStart(

)
{

    UserSetCells::reset(); //need to clear
    Grid();

    Solver::shuffleThenSolve(true);

    int col, row;

    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(0, 8);

    for (int clues = 43; clues > 0; clues--)
    {
        col = uniform_dist(e1); row = uniform_dist(e1);

        if (grid[col][row] == NULL_CELL_VALUE)
        {
            clues++; //If under 50
        }
        else
        {
            grid[col][row] = NULL_CELL_VALUE;
        }
    }

    for (col = 0; col < 9; col++) {
        for (row = 0; row < 9; row++)
        {
            if (grid[col][row] != NULL_CELL_VALUE) {
                //computer_placed_nums[col][row] = true;
                UserSetCells::setCellComputerPlaced(col, row);
            }
        }
    }
}

bool
Grid::isValueNull(
        const int VALUE
        )
{
    return VALUE == NULL_CELL_VALUE;
}

bool
Grid::hintCellValue(
        int COL,
        int ROW
        )
{
    bool isHintPossible = false;

    int grid_copy[9][9];

    for (int col = 0; col < 9; col++)
    {
        for (int row = 0; row < 9; row++)
        {
            grid_copy[col][row] = grid[col][row];
        }
    }

    grid[COL][ROW] = NULL_CELL_VALUE;

    if (Solver::shuffleThenSolve(false))
    {
        grid_copy[COL][ROW] = grid[COL][ROW];
        UserSetCells::setCellComputerPlaced(COL,ROW);
        isHintPossible = true;
    }

    for (int col = 0; col < 9; col++)
    {
        for (int row = 0; row < 9; row++)
        {
            grid[col][row] = grid_copy[col][row];
        }
    }

    return isHintPossible;
}

void
Grid::clearUserPlacedValues()
{
    int row; int col;

    for (col = 0; col < 9; col++)
    {
        for (row = 0; row < 9; row++)
        {
            if (UserSetCells::isCellUserSet(col, row))
            {
//                Grid::removeCellValue(col, row);
                grid[col][row] = NULL_CELL_VALUE;
            }
        }
    }
}