//
// Created by Tate Moore on 29/07/2023.
//

#ifndef SUDOKUGAME_CLEARACTION_H
#define SUDOKUGAME_CLEARACTION_H

#include <array>
#include <forward_list>
#include "CellEditAction.h"

class ClearAction : public Action {
    public:
        ClearAction();

        void
        undo(

        ) override;

        void
        addClearedNum(
                const CellEditAction & REMOVE_ACTION
                );

        [[nodiscard]]
        const
        std::forward_list<CellEditAction> *
        getClearedNums(

                ) const;

        bool
        isEmpty(

                );

    protected:
        std::forward_list<CellEditAction> cleared_nums;
};

#endif //SUDOKUGAME_CLEARACTION_H
