//
// Created by Tate Moore on 07/08/2023.
//

#include <array>
#include <queue>
#include "SpecialCell.h"

#ifndef SUDOKUGAME_SOLVER_H
#define SUDOKUGAME_SOLVER_H

#endif //SUDOKUGAME_SOLVER_H

class Solver
{

    private:

        //--DATA MEMBERS--\\

        inline static std::vector<int> nums_copy;

        inline static std::array<std::queue<int>, 9> shuffled_nums_queues;

        inline static SpecialCell * conflict_cell_ptr;

        inline static const std::vector<int> NUMS = {1, 2, 3, 4, 5, 6, 7, 8, 9};

public:

        //--DATA MEMBERS--\\


        //--MEMBER FUNCTIONS--\\

        explicit Solver(SpecialCell * conflict_cell_ptr);

        /**
        * @paragraph Finds the remaining numbers (and assigns the to vector nums_copy)
        * @paragraph
        * @paragraph 1) Assigns num_copy to {1,2, .. , 9}
        * @paragraph 2) Searches the given column for numbers 1..9, if found they are removed from num_copy.
        *
         * @param is_grid_empty - if true, the grid is empty so no need to get remaining numbers from column, just [1,2..9]. Else there is a need to.
         * @param COL - the column to search.

        * @see nums_copy in Game.h
        */
        static
        void
        getRemainingNumbers(
                bool is_grid_empty,
                int COL
        );

        /**
        * @paragraph shuffled_nums_queues is an array of integer queues.
        *
        * @paragraph Each queue has a corresponding column in grid (same index, same size).
        *
        * @paragraph This function:
        * @paragraph 1) Finds the remaining numbers in each column (in case already filled grid)
        * @paragraph 2) For each column, randomly shuffles the numbers.
        * @paragraph 3) Puts the randomly shuffled numbers into each of the queues.
         *
        *
        * @see shuffled_nums_queues in Game.h
        */
        static
        void
        shuffleNumsIntoQueues(
                bool is_grid_empty
        );

        /**
         * @paragraph Shuffles shuffled_nums_queues by calling void shuffleNumsIntoQueues(bool is_grid_empty);
         *
         * @paragraph Then calls solve() to solve it.
        *
        */
        static
        bool
        shuffleThenSolve(
                bool is_grid_empty
        );

        /**
        * @paragraph Recursive function
        *
        * @paragraph Each queue has a corresponding column in grid (same index, same size).
        *
        * @paragraph This function places the numbers 1-9 randomly inside each of those queues.
        *
        */
        static
        bool
        solve(

        );


        /**
         * @paragraph This function checks to see if a given cell has the same number as any other cells in the same box.
         *
         * @paragraph It does this by finding the box of the cell, then checks every cell in that box.
         *
         * @param NUM_COL - the column of the cell containing the new number
         * @param NUM_ROW - the row of the cell containing the new number
         *
         * @returns conflict_cell - there is a rule break - same number in the same square.
         * @returns nullptr - no rule break.
         *
         * @warning Once box found, it could be more efficient to skip the cells already checked by the row and column rule-break checking.
        */
        static
        bool
        doesNumBreakBoxRule(
                int NUM_COL,
                int NUM_ROW
        );

        /**
        * @paragraph Checks to see if a given cell containing a number has broken one of the 3 rules - no same number in the same column, row or square.
        *
        * @paragraph Checks row [left -> right] -> column [top -> bottom] -> square.
        *
        * @param NUM_COL - the column of the cell containing the new number
        * @param NUM_ROW - the row of the cell containing the new number
        *
        * @returns conflict_cell - there is a rule break.
        * @returns nullptr - no rule break.
        *
        * @note Once square found, it could be more efficient to skip the cells already checked by the row and column rule-break checking.
        */
        static
        bool
        isNumRuleBreak(
                int NUM_COL,
                int NUM_ROW
        );

        /**
         * @return nums_copy
         */
        static
        const std::vector<int> &
        getNumsCopy(

        );

        /**
         *
         * @return shuffled_nums_queues
         */
        static
        const std::array<std::queue<int>, 9> &
        getShuffledNumsQueues(

        );

};