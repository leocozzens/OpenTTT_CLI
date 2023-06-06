#ifndef BOARD_H
#define BOARD_H

// C Standard libraries
#include <stdio.h>
// Local headers
#include <structs.h>

#define clear() printf("\e[1;1H\e[2J")

void reset_board(Grid *board);
void print_board(Grid *board, _Bool indicators);
void print_turn(char playerMode, char player);
void check_free_space(Grid *board);

#endif