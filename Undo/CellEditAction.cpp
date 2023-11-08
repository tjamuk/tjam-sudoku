//
// Created by Tate Moore on 29/07/2023.
//

#include "CellEditAction.h"
#include "Grid.h"

CellEditAction::CellEditAction (
        const int COL,
        const int ROW,
        const int OLD_VALUE
) : Action(CELL_EDIT), COL(COL), ROW(ROW), OLD_VALUE(OLD_VALUE)
{}

void
CellEditAction::undo(

        )
{
    Grid::setCellValue(COL,ROW,OLD_VALUE);
}

int
CellEditAction::getValue(

        )
const
{
    return OLD_VALUE;
}

int CellEditAction::getCol() const {
    return COL;
}

int CellEditAction::getRow() const {
    return ROW;
}
