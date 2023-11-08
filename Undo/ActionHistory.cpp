//
// Created by Tate Moore on 01/08/2023.
//

#include "ActionHistory.h"
//#include "PlaceAction.h"
#include "ClearAction.h"

///DEPRECATED
//void
//ActionHistory::addPlaceAction(
//        int col,
//        int row
//        )
//{
//    action_history.push(
//            new PlaceAction(col, row)
//            );
//}

void
ActionHistory::addCellEditAction(
        const int COL,
        const int ROW,
        const int VALUE
        )
{
    action_history.push(
            new CellEditAction(COL, ROW, VALUE)
            );
}

void
ActionHistory::addClearAction(

        )
{
    action_history.push(
            new ClearAction()
            );
}

void
ActionHistory::addOntoClearAction(
        const int COL,
        const int ROW,
        const int VALUE
        )
{
    if (action_history.top() -> getActionType() == CLEAR)
    {
        ((ClearAction *) action_history.top())->addClearedNum(*(new CellEditAction(COL, ROW, VALUE)));
    }
}

void
ActionHistory::undoLastAction(

        )
{
    if (not action_history.empty())
    {
        action_history.top() -> undo();

        action_history.pop();
    }
}

ActionHistory::~ActionHistory(

        )
{
    clear();
}

void
ActionHistory::clear(

        )
{
    while (not action_history.empty())
    {
        delete action_history.top();
        action_history.pop();
    }
}

Action *
ActionHistory::getLastAction(

        )
{
    if (action_history.empty())
    {
        return nullptr;
    }
    else
    {
        return action_history.top();
    }

}

bool ActionHistory::isEmpty() {
    return action_history.empty();
}

bool ActionHistory::isLastClearActionEmpty() {
    if (action_history.top()->getActionType() == CLEAR)
    {
        return ( (ClearAction * ) action_history.top() ) -> isEmpty();
    }
    return false; //make exception.
}

void
ActionHistory::removeLastAction(

        )
{
    if (not action_history.empty())
    {
        delete action_history.top();
        action_history.pop();
    }
}

ActionHistory::ActionHistory(

        ) = default;

