#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct {
    char** cells; // Grid double pointer. This will be pointer the a set of pointers that each refer to a row of cells
    int height;
    int width;
    int freeSpaces;
    char player;
    char opponent;
    int patternLength;
} Grid;

typedef struct {
    int playerScore;
    int opponentScore;
} ScoreTracker;

#endif