## Kanban Board Manager in C
Overview
A simple console program to manage a kanban-style board using linked lists. Each list holds multiple items. You can display, edit, load/save from files, and manage lists and items interactively.

## Features
Display all lists and items
Load board from a text file
Edit items and lists (add, rename, delete)
Save board to a file
Clean exit with memory cleanup

## Data Format
Lists end with :
Items listed below their list

## Example:
Nick:
3070 RTX
Tim:
Oculus Quest 2

## Usage
Compile with:
bash

gcc -o board_manager main.c./a3FULLCODE
Run the program and choose options from the menu to manage your board.

## Functions
createList(), createItem() — create nodes

loadBoard(), saveBoard() — file I/O

displayBoard() — show the board

editItemInList(), editBoard() — modify data

freeBoard() — clean memory
