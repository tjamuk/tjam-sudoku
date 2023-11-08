cmake_minimum_required(VERSION 3.25)

project(SudokuGame)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)
include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

set(SOURCE_FILES main.cpp)
add_executable(SudokuGame ${SOURCE_FILES})

include_directories(Game)
add_subdirectory(Game)

include_directories(Undo)
add_subdirectory(Undo)

add_subdirectory(Tests)

include_directories(Screens)
add_subdirectory(Screens)

target_link_libraries(SudokuGame Game)
target_link_libraries(SudokuGame Undo)
target_link_libraries(SudokuGame Screens)
target_link_libraries(SudokuGame ${GTKMM_LIBRARIES})