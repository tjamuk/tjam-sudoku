//
// Created by Tate Moore on 29/07/2023.
//

#ifndef SUDOKUGAME_CELLEDITACTION_H
#define SUDOKUGAME_CELLEDITACTION_H

#include "Action.h"
#include "Cell.h"

class CellEditAction : public Action
{

    public:

        CellEditAction(
                int COL,
                int ROW,
                int OLD_VALUE);

        void
        undo(

        )
        override;

    [[nodiscard]]
    int
    getValue(

            )
    const;

    [[nodiscard]]
    int
    getCol(

            ) const;

    [[nodiscard]]
    int
    getRow(

            ) const;

protected:
        const int COL;
        const int ROW;
        const int OLD_VALUE;

};

#endif //SUDOKUGAME_CELLEDITACTION_H
