//
// Created by Tate Moore on 29/07/2023.
//

#include "ClearAction.h"


ClearAction::ClearAction(

        ) : Action(CLEAR)
{}

void
ClearAction::undo(

        )
{
    for (CellEditAction & remove_action : cleared_nums)
    {
        remove_action.undo();
    }
}

void
ClearAction::addClearedNum(
        const CellEditAction& REMOVE_ACTION
        )
{
    cleared_nums.push_front(REMOVE_ACTION);
}

const
std::forward_list<CellEditAction> *
ClearAction::getClearedNums(

        ) const
{
    return & cleared_nums;
}

bool
ClearAction::isEmpty(

        )
{
    return cleared_nums.empty();
}