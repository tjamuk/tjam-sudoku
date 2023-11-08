//
// Created by Tate Moore on 01/08/2023.
//

#ifndef SUDOKUGAME_ACTIONHISTORY_H
#define SUDOKUGAME_ACTIONHISTORY_H

#include <stack>
#include "Action.h"

class ActionHistory {
    private:
        inline static std::stack<Action *> action_history;

    public:

    ActionHistory();

    ~ActionHistory();

    ///DEPRECATED
//    static
//        void
//        addPlaceAction(
//                int col,
//                int row
//                );

        static
        void
        addCellEditAction(
                int COL,
                int ROW,
                int VALUE
                );

        static
        void
        addClearAction(

                );

        static
        void
        addOntoClearAction(
                int COL,
                int ROW,
                int VALUE
                );

        static
        void
        undoLastAction(

                );

        static
        void
        clear(

                );

        static
        Action *
        getLastAction(

                );

        static
        bool
        isEmpty(

                );

        static
        bool
        isLastClearActionEmpty(

                );

        static
        void
        removeLastAction(

                );
};

#endif //SUDOKUGAME_ACTIONHISTORY_H
