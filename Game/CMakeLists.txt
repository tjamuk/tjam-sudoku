set(HEADER_FILES
        Grid.h
        SpecialCell.h
        Solver.h
        UserSetCells.h
        )

set(SOURCE_FILES
        Grid.cpp
        SpecialCell.cpp
        Solver.cpp
        UserSetCells.cpp
        )

add_library(Game STATIC ${SOURCE_FILES} ${HEADER_FILES})