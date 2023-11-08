//
// Created by Tate Moore on 07/08/2023.
//

#include "UserSetCells.h"

UserSetCells::UserSetCells()
{
    reset();
}

bool
UserSetCells::isCellUserSet(
        const int COL,
        const int ROW
        )
{
    return user_set_cells[COL][ROW];
}

void
UserSetCells::setCellComputerPlaced(
        const int COL,
        const int ROW
        )
{
    user_set_cells[COL][ROW] = false;
}



void UserSetCells::reset() {
    int row; int col;

    for (col = 0; col < 9; col++)
    {
        for (row = 0; row < 9; row++)
        {
            user_set_cells[col][row] = true;
        }
    }
}
