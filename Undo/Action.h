//
// Created by Tate Moore on 28/07/2023.
//

#include "ActionType.h"

#ifndef SUDOKUGAME_ACTION_H
#define SUDOKUGAME_ACTION_H

class Action
{
    public:
        /**
         *
         * @paragraph The constructor for the Action type.
         *
         * @param at - The ActionType that data member ACTION_TYPE will be set to.
         * @see ActionType.h
         */
        explicit
        Action(
                ActionType at
                );

        /**
         *
         * @param grid - Game.h's
         */
        virtual
        void
        undo(

                );

        [[nodiscard]]
        ActionType
        getActionType(

                )
        const;

protected:
        const ActionType ACTION_TYPE;
};

#endif //SUDOKUGAME_ACTION_H
