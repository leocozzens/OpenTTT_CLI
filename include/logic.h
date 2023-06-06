#ifndef LOGIC_H
#define LOGIC_H

// C Standard libraries
#include <time.h>
// Local headers
#include <structs.h>
#include <utils.h>

void game_type(Grid *board, _Bool *indicators, int *playerMode);
void player_move(Grid *board, _Bool indicators);
void check_winner(Grid *board, char *winnerVar, int patternLength);
void print_winner(char winner, char player, char opponent, ScoreTracker *scoreBoard, int playerMode);
void computer_move(Grid *board);

#endif