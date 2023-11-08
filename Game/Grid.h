//
// Created by Tate Moore on 02/08/2023.
//

#ifndef SUDOKUGAME_GRID_H
#define SUDOKUGAME_GRID_H

class Grid {

    private:
        inline static int grid[9][9];
        static const int NULL_CELL_VALUE = 0;

    public:

         //--------------\\
        //--CONSTRUCTORS--\\

        Grid();

         //------------------\\
        //--GRID CELL VALUES--\\

        /**
             *
             * @param col - the column of the cell
             * @param row - the column of the cell
             * @return the number/value in the given cell.
             */
        static
        int
        getCellValue(
                int COL,
                int ROW
        );

        /**
         *
         * @param col - the column of the cell
         * @param row - the column of the cell
         * @param new_value - the new value to set the cell to.
         */
        static
        void
        setCellValue(
                int col,
                int row,
                int new_value
        );

        /**
             * @paragraph a given cell's value to show that nothing is in the cell.
             * @param COL - column of the given cell.
             * @param ROW - row of the given cell.
             */
        static
        void
        removeCellValue(
                int COL,
                int ROW
        );

        /**
         * @paragraph Checks a given cell to see if it is empty or not.
         *
         * @param col - the col of the cell.
         * @param row - the row of the cell.
         *
         * @return true - the given cell is empty.
         * @return false - the given cell is not empty.
         */
        static
        bool
        isCellEmpty(
                int col,
                int row
        );

         //-----------------\\
        //--SETTING UP GRID--\\

        /**
             * @paragraph 1) Clears the grid.
             * @paragraph 2) Randomly fills it.
             * @paragraph 3) Randomly removes 43 numbers from the grid (38 clues left)
             * @paragraph
             * @paragraph Sets up the starting grid so that it's
             */
        static
        void
        setupEasyStart(

        );
        //Maybe move to another thing?

        static
        bool
        isValueNull(
                int VALUE
                );

        static
        bool
        hintCellValue(
                int COL,
                int ROW
                );

        /**
         * @paragraph Clears all values in cells placed by a user.
         */
        static
        void
        clearUserPlacedValues(

        );
};

#endif //SUDOKUGAME_GRID_H
