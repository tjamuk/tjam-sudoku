//
// Created by Tate Moore on 07/08/2023.
//

#include "SpecialCell.h"

SpecialCell::SpecialCell() : is_null(true), col(NULL_INDEX), row(NULL_INDEX) {}

void
SpecialCell::setCell(
        const int COL,
        const int ROW
        )
{
    col = COL;
    row = ROW;
    is_null = false;
}

int SpecialCell::getCol() const { return col; }

int SpecialCell::getRow() const { return row; }

void
SpecialCell::reset(

        )

{
    col = NULL_INDEX;
    row = NULL_INDEX;
    is_null = true;
}

bool SpecialCell::isNull() const { return is_null; }


