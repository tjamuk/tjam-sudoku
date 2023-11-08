#include <iostream>
#include "Screens/GameScreen.h"
#include "gtkmm/Application.h"
#include "ActionHistory.h"
#include "Grid.h"
#include "Solver.h"

int main(int argc, char *argv[])
{
    Grid();
    auto conflict_cell_ptr = new SpecialCell();
    auto selected_cell_ptr = new SpecialCell();
    auto s = new Solver(conflict_cell_ptr);

    Grid::setupEasyStart();

    auto ah = new ActionHistory();

    auto app = Gtk::Application::create("org.gtkmm.example");

    //Shows the window and returns when it is closed.
    return app->make_window_and_run<GameScreen>(
            argc,
            argv,
            conflict_cell_ptr,
            selected_cell_ptr
            );
}