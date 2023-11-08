//
// Created by Tate Moore on 07/08/2023.
//

#ifndef SUDOKUGAME_USERSETCELLS_H
#define SUDOKUGAME_USERSETCELLS_H

class UserSetCells
{
    private:
        inline static bool user_set_cells[9][9];

    public:

        UserSetCells();

        /**
         * @paragraph Returns whether a given cell is set by a computer or user.
         *
         * @param COL - the column of the cell to be checked.
         * @param ROW - the column of the cell to be checked
         *
         * @return true - the given cell has had its value assigned by the USER.
         * @return false - the given cell has  had its value assigned by a COMPUTER.
         */
        static bool isCellUserSet(int COL, int ROW);

        /**
         * @paragraph Sets a given cell to be marked as computer placed.
         *
         * @param COL - the column of the cell
         * @param ROW - the column of the cell
         */
        static void setCellComputerPlaced(int COL, int ROW);

        static
        void
        reset(

                );


};

#endif //SUDOKUGAME_USERSETCELLS_H
