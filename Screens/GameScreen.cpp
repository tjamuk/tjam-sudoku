//
// Created by Tate Moore on 06/07/2023.
//

#include "GameScreen.h"
#include <iostream>
#include <gtkmm/togglebutton.h>
#include <gtkmm/eventcontrollerkey.h>
#include <gtkmm/cssprovider.h>
#include "../Undo/ActionHistory.h"
#include "UserSetCells.h"
#include "Grid.h"
#include "Solver.h"

GameScreen::GameScreen(SpecialCell * ccp, SpecialCell * scp)
//        : m_VBox(Gtk::Orientation::VERTICAL, 10),
//          m_ButtonClear("Clear", true)
{
//    m_VBox.set_orientation(Gtk::Orientation::VERTICAL);
//    m_VBox.set_spacing(10);

    m_VBox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 5);

    m_ButtonClear = Gtk::make_managed<Gtk::Button>("Clear", true);
    m_ButtonHint = Gtk::make_managed<Gtk::Button>("Hint", true);

    conflict_cell_ptr = ccp;
    selected_cell_ptr = scp;

    //Window
    set_title("Gtk::ScrolledWindow example");
    set_size_request(500, 500);

    //Vbox in Window
    set_child(*m_VBox);
    m_VBox->set_margin(10);
    //

    m_VBox->append(m_Grid);

    /* this simply creates a 9x9grid of toggle buttons
     * to demonstrate the scrolled window. */
    for (int col = 0; col < 9; col++)
    {
        for (int row = 0; row < 9; row++)
        {

            auto pButton = Gtk::make_managed<Gtk::ToggleButton>();
            pButton -> set_size_request(60,60);

            //The starting grid has been generated
            //Where if a cell has a value, it's a computer set cell (as a result of starting grid generation)
            //If no value, it will be a user set cell.

//            if (Game::isCellComputerPlaced(col,row))
            if (UserSetCells::isCellUserSet(col, row))
            {

                //If there is no number in the corresponding Game.h grid's cell.
                //So don't label it as anything.
                //But show it as a user cell.
                //Bind it as clickable.

                pButton -> set_name("toggle_button_reg_user");

                pButton->signal_clicked().connect(
                        sigc::bind(
                                sigc::mem_fun(*this, &GameScreen::onCellSelected),
                                col,
                                row
                        )
                );
            }
            else
            {

                //If there is a number in the corresponding Game.h grid's cell, set this visual cell to display that number, and it as a computer placed one.

                pButton -> set_label(std::to_string(Grid::getCellValue(col, row)));
                pButton -> set_name("toggle_button_reg_computer");
            }

            m_Grid.attach(*pButton, col, row);
        }
    }
    m_Grid.set_name("grid");

    /* Add a "close" button to the bottom of the dialog */
    m_VBox->append(*m_ButtonClear);
    m_ButtonClear->set_halign(Gtk::Align::END);
    m_ButtonClear->signal_clicked().connect(
            sigc::mem_fun(*this, &GameScreen::onButtonClear));

    m_VBox -> append (*m_ButtonHint);
    m_ButtonHint -> set_halign(Gtk::Align::END);
    m_ButtonHint -> signal_clicked().connect(
            sigc::mem_fun(*this, &GameScreen::onButtonHint));

    //Listens for key presses, upon key press, function onKeyPressed handles.
    auto controller = Gtk::EventControllerKey::create();
    controller->signal_key_pressed().connect(
            sigc::mem_fun(*this, &GameScreen::onKeyPressed), false);
//            sigc::ptr_fun(&GameScreen::onKeyPressed), false);
    add_controller(controller);

    //Styles the window using CSS.
    auto css = Gtk::CssProvider::create();
    css->load_from_path("../stylesheet.css");
    Gtk::StyleContext::add_provider_for_display(
            Gdk::Display::get_default(), css,
            GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}

//------------------------------------------------------------------
//==================================================================
//------------------------------------------------------------------

void
GameScreen::onCellSelected(
        const int COL,
        const int ROW
        )
{
    //If there is no current conflict, do if clicking on the currently selecting cell, it's only a de-select. Else on any other cell, need to select that cell.
    //Else (no conflict), do nothing

//    if (not Game::isConflictOngoing())
    if (conflict_cell_ptr -> isNull() && UserSetCells::isCellUserSet(COL,ROW))
    {
        if (deselectCell(COL, ROW))
        {
            selectCell(COL,ROW);
        }
    }
    else
    {
        setCellActive(COL, ROW, false); //Basically any toggle button will become checked upon clicked, so need to deactivate it.
    }
}

//------------------------------------------------------------------
//==================================================================
//------------------------------------------------------------------

bool
GameScreen::deselectCell(
        const int COL,
        const int ROW
        )
{
    //If there is no previously selected cell, there is no need to deselect any cell.
//    if (not Game::isAnyCellSelected())
    if (selected_cell_ptr -> isNull())
    {
        return true;
    }

//    const int * PREV_SELECTED_CELL = Game::getSelectedCell();
    const int SELECTED_CELL_COL =  selected_cell_ptr -> getCol();
    const int SELECTED_CELL_ROW = selected_cell_ptr -> getRow();

    //Stop highlighting the cells that were possible conflicts for the previously selected cell.
    highlightPossibleConflicts(
            SELECTED_CELL_COL,
            SELECTED_CELL_ROW,
            false
            );

    //Set the previously selected cell to be non-active.
    setCellActive(
                SELECTED_CELL_COL,
                SELECTED_CELL_ROW,
            false
            );

    //If the previously selected cell is the cell that's been clicked then set the selected cell to none (it's a de-select only)
//    if (*PREV_SELECTED_CELL == COL && *(PREV_SELECTED_CELL+1) == ROW)
    if (SELECTED_CELL_COL == COL && SELECTED_CELL_ROW == ROW)
    {
//        Game::resetSelectedCell();
        selected_cell_ptr -> reset();
        return false;
    }
    else
    {
        return true;
    }
}

//------------------------------------------------------------------
//==================================================================
//------------------------------------------------------------------

void
GameScreen::selectCell(
        const int COL,
        const int ROW
        )
{

    setCellActive(COL, ROW, true);
//    Game::setSelectedCell(COL,ROW);
    selected_cell_ptr -> setCell(COL, ROW);

    highlightPossibleConflicts(COL, ROW, true);
}

//------------------------------------------------------------------
//==================================================================
//------------------------------------------------------------------

bool
GameScreen::onKeyPressed(
        guint key_val,
        guint key_code,
        Gdk::ModifierType state
        )
{
//    if (Game::isAnyCellSelected())
    if (not selected_cell_ptr -> isNull())
    {
//        const int * PREV_SELECTED_CELL = Game::getSelectedCell();

        switch(key_val)
        {
            case GDK_KEY_1:
                onNumberEntered(selected_cell_ptr -> getCol(), selected_cell_ptr -> getRow(), 1);
                break;
            case GDK_KEY_2:
                onNumberEntered(selected_cell_ptr -> getCol(), selected_cell_ptr -> getRow(), 2);
                break;
            case GDK_KEY_3:
                onNumberEntered(selected_cell_ptr -> getCol(), selected_cell_ptr -> getRow(), 3);
                break;
            case GDK_KEY_4:
                onNumberEntered(selected_cell_ptr -> getCol(), selected_cell_ptr -> getRow(), 4);
                break;
            case GDK_KEY_5:
                onNumberEntered(selected_cell_ptr -> getCol(), selected_cell_ptr -> getRow(), 5);
                break;
            case GDK_KEY_6:
                onNumberEntered(selected_cell_ptr -> getCol(), selected_cell_ptr -> getRow(), 6);
                break;
            case GDK_KEY_7:
                onNumberEntered(selected_cell_ptr -> getCol(), selected_cell_ptr -> getRow(), 7);
                break;
            case GDK_KEY_8:
                onNumberEntered(selected_cell_ptr -> getCol(), selected_cell_ptr -> getRow(), 8);
                break;
            case GDK_KEY_9:
                onNumberEntered(selected_cell_ptr -> getCol(), selected_cell_ptr -> getRow(), 9);
                break;
            case GDK_KEY_BackSpace:
                onErase(selected_cell_ptr->getCol(), selected_cell_ptr->getRow());
                break;
            case GDK_KEY_z:
                if (state == Gdk::ModifierType::CONTROL_MASK)
                {
                    undoHandler();
                }
            default:
                return false;
        }
    }
    return true;
}

//------------------------------------------------------------------
//==================================================================
//------------------------------------------------------------------

bool
GameScreen::onNumberEntered (
        const int COL,
        const int ROW,
        int VALUE
        )
{
    ActionHistory::addCellEditAction(
            COL,
            ROW,
            Grid::getCellValue(COL,ROW)
            );

    setCellLabel(COL,ROW,std::to_string(VALUE)); //Set the cell label to the new entered number or value.

    clearPrevConflictDisplay(); //If there was a previous conflict, remove its highlighting.

    Grid::setCellValue(COL,ROW,VALUE); //Update the Game.h corresponding cell to the new value.

    return showRuleBreak(COL, ROW, false); //Highlight the rulebreak (if any)
}

//------------------------------------------------------------------
//==================================================================
//------------------------------------------------------------------

GameScreen::~GameScreen(

        )
= default;

//------------------------------------------------------------------
//==================================================================
//------------------------------------------------------------------

void
GameScreen::onButtonClear(

        )
{
    int row; int col;

    ActionHistory::addClearAction();

    for (col = 0; col < 9; col++)
    {
        for (row = 0; row < 9; row++)
        {
//            if (not Game::isCellComputerPlaced(col, row) and not Game::isCellEmpty(col,row))
//            if (selected_cell_ptr -> isNull() and not Grid::isCellEmpty(col, row))
            if (UserSetCells::isCellUserSet(col, row) and not Grid::isCellEmpty(col, row))
            {
                std::cout<<col<<", "<<row<<std::endl;
                setCellLabel(col, row, "");
                ActionHistory::addOntoClearAction(col, row, Grid::getCellValue(col,row));
            }
        }
    }

    if (ActionHistory::isLastClearActionEmpty())
    {
        ActionHistory::removeLastAction();
    }
    else
    {
//        Game::clearUserPlacedValues();
        Grid::clearUserPlacedValues();

        clearPrevConflictDisplay();
    }
}

//------------------------------------------------------------------
//==================================================================
//------------------------------------------------------------------

void
GameScreen::changeCellPossibleConflictHighlight(
        const int COL,
        const int ROW,
        const bool IS_HIGHLIGHTING
        )
{
    if (IS_HIGHLIGHTING)
    {
        decideCellName(COL, ROW, "toggle_button_possible_conflict");
    }
    else
    {
        decideCellName(COL, ROW, "toggle_button_reg");
    }
}

//------------------------------------------------------------------
//==================================================================
//------------------------------------------------------------------

void
GameScreen::highlightPossibleConflicts(
        const int COL,
        const int ROW,
        const bool IS_HIGHLIGHTING
        )
{
    int index = -1;

    //--DE/-HIGHLIGHTING COLUMN--\\

    //de/-highlighting cells left of number
    while (++index < COL) {
        changeCellPossibleConflictHighlight(index, ROW, IS_HIGHLIGHTING);
    }

    //de/-highlighting cells right of number
    while (++index < 9) {
        changeCellPossibleConflictHighlight(index, ROW, IS_HIGHLIGHTING);
    }

    //--DE/-HIGHLIGHTING ROW--\\

    index = -1;

    //de/-highlighting cells above number
    while (++index < ROW) {
        changeCellPossibleConflictHighlight(COL, index, IS_HIGHLIGHTING);
    }

    //de/-highlighting cells below number
    while (++index < 9) {
        changeCellPossibleConflictHighlight(COL, index, IS_HIGHLIGHTING);
    }

    //de/-highlighting cells in box.
    highlightBoxPossibleConflicts(COL, ROW, IS_HIGHLIGHTING);
}

//------------------------------------------------------------------
//==================================================================
//------------------------------------------------------------------

void
GameScreen::highlightBoxPossibleConflicts(
        const int COL,
        const int ROW,
        const bool IS_HIGHLIGHTING
        )
{
    const int BOX_START_COL = (COL / 3) * 3;
    const int BOX_END_COL = BOX_START_COL + 2;

    const int BOX_START_ROW = (ROW / 3) * 3;
    const int BOX_END_ROW = BOX_START_ROW + 2;

    int row; int col;

    //Checks every cell in the square (incl. new number's cell)
    for (col = BOX_START_COL; col <= BOX_END_COL; col++)
    {
        for (row = BOX_START_ROW; row <= BOX_END_ROW; row++)
        {
            if (col != COL && row != ROW)
            {
                changeCellPossibleConflictHighlight(col, row, IS_HIGHLIGHTING);
            }
        }
    }
}

//------------------------------------------------------------------
//==================================================================
//------------------------------------------------------------------

void
GameScreen::onErase(
        int COL,
        int ROW
        )
{
    //If the given cell is NOT empty...
//    if (Game::getCellValue(COL,ROW) != Game::NULL_CELL_VALUE)
    if (not Grid::isCellEmpty(COL, ROW))
    {
        ActionHistory::addCellEditAction(
                COL,
                ROW,
                Grid::getCellValue(COL,ROW)
        );

        //Set its text label to nothing (shows as no number nor anything)
        setCellLabel(
                COL,
                ROW,
                ""
        );

        // Colour it as a regular user cell.
        setCellName(
                COL,
                ROW,
                "toggle_button_reg_user"
        );

        //When you enter two nums into a cell, undo once then erase, cell becomes inactive.
        setCellActive(COL, ROW, true);

//        if (not conflict_cell_ptr -> isNull())
//        {
//            clearPrevConflictDisplay(); //Clear previous conflicting highlighting.
//
//            conflict_cell_ptr -> reset();
//        }
        clearPrevConflictDisplay();

        Grid::removeCellValue(COL, ROW); //Clear cell value on the corresponding cell on the Game.h grid.
    }
}

//------------------------------------------------------------------
//==================================================================
//------------------------------------------------------------------

void
GameScreen::setCellActive(
        const int COL,
        const int ROW,
        const bool IS_ACTIVE
)
{
    (
            (Gtk::ToggleButton *)
            m_Grid.get_child_at(COL, ROW )
    ) -> set_active(IS_ACTIVE);
}

//------------------------------------------------------------------
//==================================================================
//------------------------------------------------------------------

void
GameScreen::setCellName(
        const int COL,
        const int ROW,
        const std::string& NAME
)
{
    (
            (Gtk::ToggleButton *)
            m_Grid.get_child_at(COL, ROW )
    ) -> set_name(NAME);
}

//------------------------------------------------------------------
//==================================================================
//------------------------------------------------------------------

void
GameScreen::setCellLabel (
        const int COL,
        const int ROW,
        const std::string& LABEL
)
{
    (
            (Gtk::ToggleButton *)
            m_Grid.get_child_at(COL, ROW )
    ) -> set_label(LABEL);
}

void
GameScreen::clearPrevConflictDisplay(

)
{

//    const int * RULEBREAK_POS = Game::getConflictCell();

//    if (RULEBREAK_POS)
    if (not conflict_cell_ptr -> isNull())
    {
        std::cout<<"There is a previous conflict, so clearing\n";

        decideCellName(
//                * RULEBREAK_POS,
//                *(RULEBREAK_POS + 1),
                conflict_cell_ptr -> getCol(),
                conflict_cell_ptr -> getRow(),
                "toggle_button_possible_conflict"
        );

        setCellName(
//                * Game::getSelectedCell(),
//                * (Game::getSelectedCell() + 1 ),
                selected_cell_ptr -> getCol(),
                selected_cell_ptr -> getRow(),
                "toggle_button_reg_user"
                );

        conflict_cell_ptr -> reset();
    }
}

//------------------------------------------------------------------
//==================================================================
//------------------------------------------------------------------

void
GameScreen::undoHandler(

        )
{
    std::cout<<"entering undoHandler()\n";

    if (not ActionHistory::isEmpty()) //If there are any actions to undo.
    {
        std::cout<<"There are actions to undo\n";

        const Action * const LAST_ACTION = ActionHistory::getLastAction();

        if (LAST_ACTION -> getActionType() == CELL_EDIT)
        {
            std::cout<<"is a cell edit action\n";

            undoCellEditAction(
                    (CellEditAction * ) LAST_ACTION
                    );
        }
        else
        {
            std::cout<<"is a clear action\n";

            undoClearAction(
                    (ClearAction * ) LAST_ACTION
            );
        }
    }
    else
    {
        std::cout<<"No actions to undo\n";
    }
    std::cout<<"leaving undoHandler()\n";
}

//------------------------------------------------------------------
//==================================================================
//------------------------------------------------------------------

void
GameScreen::undoCellEditAction(
        CellEditAction * LAST_ACTION
        )
{

    const int COL = LAST_ACTION -> getCol();
    const int ROW = LAST_ACTION -> getRow();

    std::cout<<"Entering undoCellEditAction where col: " << COL << " ; row: " << ROW << "\n";

    if (UserSetCells::isCellUserSet(COL, ROW))
    {
        std::cout<<"Cell is user set\n";

        const int NEW_VALUE = LAST_ACTION -> getValue();
        std::string new_label; //the new label of the cell

        std::cout<<"It is a cell edit action with:\n";
        std::cout<<"     - col: " << COL << std::endl;
        std::cout<<"     - row: " << ROW << std::endl;
        std::cout<<"     - val: " << NEW_VALUE << std::endl;

//    if (NEW_VALUE != Game::NULL_CELL_VALUE) //If the cell had a previous actual value (and not the number indicating null)...
        if (not Grid::isValueNull(NEW_VALUE)) //If the cell had a previous actual value (and not the number indicating null)...
        {
            std::cout<<"It is adding a value :\n";
            new_label = std::to_string(NEW_VALUE);
        }
        else
        {
            std::cout<<"It is removing a value:\n";
        }

        setCellLabel(
                COL,
                ROW,
                new_label
        );

        ActionHistory::undoLastAction();

        //Basically checks for rulebreaks and adjusts the board display for undo and any possible rulebreaks.
        postUndo(COL, ROW, NEW_VALUE);
    }
    else
    {
        std::cout<<"Cell is now a hint value\n";
        ActionHistory::removeLastAction();
        undoHandler();
    }
}

///Visual side not done.
//todo
void GameScreen::undoClearAction(
        ClearAction * LAST_ACTION
        )
{
    std::cout<<"Enterring undoClearAction\n";

    const std::forward_list<CellEditAction> * CLEARED_NUMS = LAST_ACTION -> getClearedNums();

    LAST_ACTION -> undo();

    bool rulebreak_found = false;
    bool is_any_user_set_cell_affected = false;

    for (const CellEditAction & remove_action : * CLEARED_NUMS)
    {
        std::cout<<"Remove action with:\n";
        std::cout<<"     - col: " << remove_action.getCol() << std::endl;
        std::cout<<"     - row: " << remove_action.getRow() << std::endl;
        std::cout<<"     - val: " << remove_action.getValue() << std::endl;

        //remove_action.undo();
//        undoCellEditAction(&remove_action);
        if (UserSetCells::isCellUserSet(remove_action.getCol(), remove_action.getRow()))
        {
            std::cout<<"Cell is user set\n";

            is_any_user_set_cell_affected = true;

            setCellLabel(
                    remove_action.getCol(),
                    remove_action.getRow(),
                    std::to_string( remove_action.getValue() )
            );

            if (not rulebreak_found)
            {
                rulebreak_found = showRuleBreak(
                        remove_action.getCol(),
                        remove_action.getRow(),
                        false
                );
            }
        }
        else
        {
            std::cout<<"Cell value is now a hint\n";
        }
    }

    ActionHistory::removeLastAction();

    if (not is_any_user_set_cell_affected)
    {
        std::cout<<"No user set was affected.\n";

        undoHandler();
    }
}

void
GameScreen::checkUndoForRuleBreak(
        const int COL,
        const int ROW,
        const int VALUE
        )
{

    //if the old value was nothing, then it won't have caused a rulebreak (so no need to check for one)
//    if (VALUE != Game::NULL_CELL_VALUE)
    if (not Grid::isValueNull(VALUE))
    {
        std::cout<<"The new value is not nothing.\n";

        //If the undo broke a rule...
        if (Solver::isNumRuleBreak(COL,ROW))
        {
            std::cout<<"The new value broke a rule\n";

            //Basically if the undo cell != selected cell and causes an error, make the selected cell the undo cell.
            if (
                    not (
//                            *Game::getSelectedCell() == COL
//                            &&
//                            * ( Game::getSelectedCell() + 1 ) == ROW

                            selected_cell_ptr -> getCol() == COL
                            &&
                            selected_cell_ptr -> getRow() == ROW
                    ))
            {
                deselectCell(COL,ROW);
                selectCell(COL,ROW);
            }
            showRuleBreak(COL, ROW, true);
        }
        //showRuleBreak(COL, ROW, true);
    }
    else
    {
//        Game::resetConflictCell();
        std::cout<<"There is no value now so reset conflict_cell_ptr\n";

        conflict_cell_ptr -> reset();
    }
}

void
GameScreen::decideCellName(
        const int COL,
        const int ROW,
        const std::string &PREFIX_NAME
        )
{
//    if (Game::isCellComputerPlaced(COL, ROW))
    if (UserSetCells::isCellUserSet(COL, ROW))
    {
        //setCellName(COL, ROW, PREFIX_NAME + "_computer");
        setCellName(COL, ROW, PREFIX_NAME + "_user");
    }
    else {
        //setCellName(COL, ROW, PREFIX_NAME + "_user");
        setCellName(COL, ROW, PREFIX_NAME + "_computer");
    }
}

bool
GameScreen::showRuleBreak(int PLACED_COL, int PLACED_ROW, bool KNOW_IF_RULE_BREAK)
{
//    const int * RULEBREAK_POS;
//
//    //If you already have tested for a rulebreak...
//    if (KNOW_IF_RULE_BREAK) {
//        RULEBREAK_POS = Game::getConflictCell(); //Get the conflict cell (assigned when testing for a rule-break)
//    }
//    else
//    {
////        RULEBREAK_POS = Game::isNumRuleBreak(PLACED_COL, PLACED_ROW);
//        //Else test for one...
//        Solver::isNumRuleBreak(PLACED_COL, PLACED_ROW);
//    }

    //If you haven't tested for a rule-break...
    if (not KNOW_IF_RULE_BREAK)
    {
        Solver::isNumRuleBreak(PLACED_COL, PLACED_ROW);
    }

    //If the new number is a rule-break...
    if (not conflict_cell_ptr -> isNull())
    {
        std::cout<<"Highlighting rulebreak.\n";

        //Highlight the *selected* cell to darker red.
        setCellName(
                PLACED_COL,
                PLACED_ROW,
                "toggle_button_rulebreak_placed"
        );

        //Highlight the *conflicting* cell to lighter red.
        setCellName(
//                * RULEBREAK_POS,
//                *(RULEBREAK_POS + 1),
                conflict_cell_ptr -> getCol(),
                conflict_cell_ptr -> getRow(),
                "toggle_button_rulebreak_conflicting"
        );

        return true;
    }
    else
    {
        return false;
    }
}

void
GameScreen::postUndo(
        const int COL,
        const int ROW,
        const int VALUE
        )
{
    std::cout<<"Entering postUndo(" << COL << "," << ROW << "," << VALUE << ") \n";

    //Basically if there was a conflict before the undo, clear it.
    //When you make a conflict, you can't do anything to any other cells until you there is no conflict in that cell.
    //So if there is an undo on a conflict either the cell becomes:
    //  -Another conflict (so need to change red highlighting to match new conflict)
    //  -No conflict (so red highlighting is removed.)

    //Either way the current red highlighting is removed.

//    if (Game::isConflictOngoing())
//    {
//        clearPrevConflictDisplay();
//    }
//    if (not conflict_cell_ptr -> isNull())
//    {
//        std::cout<<"There is a previous conflict so clear it.";
//
//        clearPrevConflictDisplay();
//    }

    clearPrevConflictDisplay();

    //Check new value for rulebreak, if so highlight it so.
    checkUndoForRuleBreak(COL, ROW, VALUE);
}

void
GameScreen::onButtonHint(
        )
{
    if (not selected_cell_ptr -> isNull())
    {
        const int SELECTED_COL = selected_cell_ptr -> getCol();
        const int SELECTED_ROW = selected_cell_ptr -> getRow();

        if (Grid::hintCellValue(SELECTED_COL, SELECTED_ROW))
        {
            setCellLabel(
                    SELECTED_COL,
                    SELECTED_ROW,
                    std::to_string(Grid::getCellValue(SELECTED_COL, SELECTED_ROW))
                    );

            setCellName(
                    SELECTED_COL,
                    SELECTED_ROW,
                    "toggle_button_reg_computer"
                    );

            deselectCell(SELECTED_COL, SELECTED_ROW);

            selected_cell_ptr -> reset();

            clearPrevConflictDisplay();
        }
    }
}




