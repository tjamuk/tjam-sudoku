//
// Created by Tate Moore on 28/07/2023.
//

#include "Action.h"

Action::Action(
        ActionType at
        ) : ACTION_TYPE(at)
{}

void
Action::undo(

        )
{}

ActionType
Action::getActionType(

        )
const
{
    return ACTION_TYPE;
}


