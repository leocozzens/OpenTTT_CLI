#ifndef LOGIC_H
#define LOGIC_H

// C Standard libraries
#include <time.h>
// Local headers
#include <structs.h>
#include <utils.h>

void game_type(Grid *board, _Bool *indicators);
void player_move(Grid *board, _Bool indicators);
void check_winner(Grid *board, char *winnerVar, int patternLength);
void print_winner(char winner, char player, char opponent, ScoreTracker *scoreBoard);
void computer_move(Grid *board);

#endif