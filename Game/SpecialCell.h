//
// Created by Tate Moore on 07/08/2023.
//

#ifndef SUDOKUGAME_SPECIALCELL_H
#define SUDOKUGAME_SPECIALCELL_H

class SpecialCell
{

    private:
        static const int NULL_INDEX = -1;
        int col;
        int row;
        bool is_null;

    public:

        /**
         * @paragraph Constructor for a SpecialCell object.
         */
        SpecialCell();

        /**
         * @paragraph Sets the object to point at a cell.
         *
         * @param COL - set to col, the column of the cell.
         * @param ROW  set to row, the row of the cell.
         */
        void
        setCell(
                int COL,
                int ROW
                );

        /**
         * @paragraph Returns data member row
         *
         * @return int - the row of the cell that the object is pointing to.
         */
        [[nodiscard]] int
        getCol(

                ) const;

        /**
         * @paragraph Returns data member row
         *
         * @return int - the row of the cell that the object is pointing to.
         */
        [[nodiscard]] int
        getRow(

                ) const;

        /**
         * @paragraph resets the object so that it points to no cell.
         */
        void
        reset(

                );

        /**
             * @paragraph Returns whether the object points to a cell or not.
             *
             * @return true - the special cell doesn't point to a cell.
             * @return false - the special cell points to a cell
             */
        [[nodiscard]] bool
        isNull(

                ) const;
};

#endif //SUDOKUGAME_SPECIALCELL_H
