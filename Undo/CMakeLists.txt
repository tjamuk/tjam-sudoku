set(HEADER_FILES
        Action.h
        PlaceAction.h
        ActionType.h
        CellEditAction.h
        ClearAction.h
        ActionHistory.h
        Cell.h
        )

set(SOURCE_FILES
        Action.cpp
        PlaceAction.cpp
        CellEditAction.cpp
        ClearAction.cpp
        ActionHistory.cpp
        Cell.cpp
        )

add_library(Undo STATIC ${SOURCE_FILES} ${HEADER_FILES})