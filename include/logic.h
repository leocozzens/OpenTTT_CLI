#ifndef LOGIC_H
#define LOGIC_H

// C Standard libraries
#include <time.h>
// Local headers
#include <structs.h>
#include <utils.h>

typedef struct {
    int playerScore;
    int opponentScore;
} ScoreTracker;

void player_move(Grid *board);
void check_winner(Grid *board, char *winnerVar, int patternLength);
void print_winner(char winner, char player, char opponent, ScoreTracker *scoreBoard);
void computer_move(Grid *board);

#endif