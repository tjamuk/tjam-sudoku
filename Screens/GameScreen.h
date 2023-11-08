//
// Created by Tate Moore on 06/07/2023.
//

#ifndef SUDOKUGAME_GAMESCREEN_H
#define SUDOKUGAME_GAMESCREEN_H

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/grid.h>
#include <gtkmm/button.h>
#include "../Undo/ClearAction.h"
#include "SpecialCell.h"

class GameScreen : public Gtk::Window
{
public:
    GameScreen(SpecialCell * ccp, SpecialCell * scp);
    ~GameScreen() override;

protected:

    //Signal handlers:
    /**
     *
     */
    void
    onButtonClear(

            );

    /**
     * @paragraph Called when a toggle button that has not been placed by a computer is clicked.
     * @paragraph
     * @paragraph Figures out what to do when a toggle button is clicked.
     * @paragraph
     * @paragraph If there is a conflict ongoing, shows nothing.
     * @paragraph Else (no conflict), decide
     * @param COL - the column of the selected cell.
     * @param ROW - the row of the selected cell.
     */
    void
    onCellSelected(
            int COL,
            int ROW
            );

    /**
     * @paragraph Deselects the last selected cell (if any) visually.
     * @paragraph If only deselect, calls Game member functions to clear the value of selected cell.
     *
     * @param COL - the column of the new selected cell.
     * @param ROW - the column of the new selected cell.
     * @return true - not deselect only.
     * @return false - it's a deselect only (when new selected cell = last selected cell)
     */
    bool
    deselectCell(
            int COL,
            int ROW
            );

    /**
     * @paragraph Selects the last selected cell (if any) visually and calls Game member functions to change the value of selected cell.
     *
     * @param COL - the column of the new selected cell.
     * @param ROW - the column of the new selected cell.
     */
    void
    selectCell(
            int COL,
            int ROW
            );

    /**
     *
     * @param key_val - the key that is pressed.
     * @param key_code - unused but necessary I think.
     * @param state - the state of the keyboard e.g. if shift is being pressed.
     * @return necessary from where it is called.
     *
     * @note Research.
     */
    bool
    onKeyPressed(
            guint key_val,
            guint key_code,
            Gdk::ModifierType state
            );

    /**
     * @paragraph Calls functions that adds this action to ActionHistory, changes the label of the given cell to the new value, clears previous rulebreak highlighting if any, highlights any rulebreaks.
     *
     * @param COL - col of the cell where the number is entered.
     * @param ROW - col of the cell where the number is entered.
     * @param VALUE - the number is entered.
     * @return
     */
    bool
    onNumberEntered(
            int COL,
            int ROW,
            int VALUE
            );

    /**
     * @paragraph de/_ highlights a given cell to not/show that it's a possible conflict zone.
     *
     * @param COL - col of the cell.
     * @param ROW - row of the cell
     * @param IS_HIGHLIGHTING - if true, is highlighting it to be a possible conflict. Else false, unhighlighting it to a regular cell.
     */
    void
    changeCellPossibleConflictHighlight(
            int COL,
            int ROW,
            bool IS_HIGHLIGHTING
            );

    /**
     * @paragraph Highlights the possible conflict zone to the selected cell.
     * @paragraph This function calls highlightBoxPossibleConflicts(..)
     * @paragraph And does the row and column.
     *
     * @param COL - the selected cell's col.
     * @param ROW - the selected cell's row.
     * @param IS_HIGHLIGHTING - if true, is highlighting it to be a possible conflict. Else false, unhighlighting it to a regular cell.
     */
    void
    highlightPossibleConflicts(
            int COL,
            int ROW,
            bool IS_HIGHLIGHTING
            );

    /**
     * @paragraph Highlights the box part of the possible conflict zone to the selected cell.
     *
     * @param COL - the selected cell's col.
     * @param ROW - the selected cell's row.
     * @param IS_HIGHLIGHTING - if true, is highlighting it to be a possible conflict. Else false, unhighlighting it to a regular cell.
     */
    void
    highlightBoxPossibleConflicts(
            int COL,
            int ROW,
            bool IS_HIGHLIGHTING
            );

    /**
     * @paragraph Game.h function to remove the value of a given cell.
     * @paragraph Visually removes it.
     *
     * @param COL - the column of the cell
     * @param ROW - the column of the cell
     */
    void
    onErase(
            int COL,
            int ROW
    );

    /**
     * @paragraph Through a given col and row it can find a toggle button in the visual grid.
     * @paragraph It then sets the active property of the toggle button to a given bool.
     *
     * @param COL - the col of the toggle button in the grid.
     * @param ROW - the row of the toggle button in the grid.
     * @param IS_ACTIVE - whether the toggle button is active or not.
     */
    void
    setCellActive(
            int COL,
            int ROW,
            bool IS_ACTIVE
            );

    /**
     * @paragraph Through a given col and row it can find a toggle button in the visual grid.
     * @paragraph It then sets the name property of the toggle button to a given string.
     * @paragraph Its name designates its appearance.
     *
     * @param COL - the col of the toggle button in the grid.
     * @param ROW - the row of the toggle button in the grid.
     * @param NAME - the new name of the togglebutton.
     *
     * @see stylesheet.css
     */
    void
    setCellName(
            int COL,
            int ROW,
            const std::string & NAME
            );

    /**
     * @paragraph Through a given col and row it can find a toggle button in the visual grid.
     * @paragraph It then sets the label property of the toggle button to a given string.
     *
     * @param COL - the col of the toggle button in the grid.
     * @param ROW - the row of the toggle button in the grid.
     * @param LABEL - the string that the text label of the toggle button will be set to.
     */
    void
    setCellLabel(
            int COL,
            int ROW,
            const std::string& LABEL
    );

    /**
     * @paragraph there was a previous conflict, it will clear the visual highlights of the conflict.
     */
    void
    clearPrevConflictDisplay(

            );

    /**
     * @paragraph Decides what GameScreen.h to call based on the type of the most recent action in ActionHistory.
     */
    void
    undoHandler(

            );

    /**
     * @paragraph Calls an ActionHistory function to Undo a cell edit action (one that changes a single cell's value)
     * @paragraph And calls functions to remove this visually.
     * @param LAST_ACTION - a pointer to the most recent action in ActionHistory
     */
    void
    undoCellEditAction(
            CellEditAction * LAST_ACTION
            );

    /**
     * @todo
     * @param LAST_ACTION - a pointer to the most recent action in ActionHistory
     */
    void
    undoClearAction(
            ClearAction * LAST_ACTION
            );

    /**
     * @paragraph This function to see if the undo breaks any rules, if so changes the visuals to match this.
     *
     * @param COL - the column of the cell that the undo affects.
     * @param ROW - the row of the cell hat the undo affects.
     * @param VALUE - the value of the cell hat the undo affects.
     */
    void
    checkUndoForRuleBreak(
            int COL,
            int ROW,
            int VALUE
            );

    /**
     * @todo think of what to rename
     *
     * @paragraph When an undo occurs, decides what to do post undo based on if before it there was a conflict.
     * @paragraph Basically checks for rulebreaks and adjusts the board display for undo and any possible rulebreaks.
     *
     * @param COL - the column of the cell that the undo affects.
     * @param ROW - the row of the cell hat the undo affects.
     * @param VALUE - the value of the cell hat the undo affects.
     */
    void
    postUndo(
            int COL,
            int ROW,
            int VALUE
            );

    /**
     * @paragraph Decides what to name a toggle button if its corresponding Game.h cell is a computer placed num or not.
     * @paragraph Computer placed nums visually have a different colour to user placed ones
     *
     * @param COL - the col of the toggle button in the grid.
     * @param ROW - the row of the toggle button in the grid.
     * @param PREFIX_NAME - an incomplete string, this function will complete it by adding onto it. It will then call setCellName(..) to set the given toggle button to the complete string.
     */
    void
    decideCellName(
            int COL,
            int ROW,
            const std::string & PREFIX_NAME
            );

    /**
     * @paragraph If there is a rule-break, highlights the cell with the placed number red and the cell with the conflicting number a lighter red.
     *
     * @param PLACED_COL - the col of the cell that has a placed num.
     * @param PLACED_ROW - the row of the cell that has a placed num.
     * @param KNOW_IF_RULE_BREAK - if true, you already know if there is a rule-break or not, no need to call Game.h isNumRuleBreak(..) to check. Else, you need to.
     * @return true - there is a rule-break
     * @return false - there is not a rule-break.
     */
    bool
    showRuleBreak(
            int PLACED_COL,
            int PLACED_ROW,
            bool KNOW_IF_RULE_BREAK
            );

    void
    onButtonHint(
            );

    //Child widgets:
    Gtk::Box * m_VBox;
    Gtk::Grid m_Grid;
    Gtk::Button * m_ButtonClear;
    Gtk::Button * m_ButtonHint;

    //Vars
    SpecialCell * conflict_cell_ptr;
    SpecialCell * selected_cell_ptr;
};

#endif //SUDOKUGAME_GAMESCREEN_H
