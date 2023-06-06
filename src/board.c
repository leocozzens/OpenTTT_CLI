// C standard libraries
#include <stdio.h>
// Local headers
#include <structs.h>

#define clear() printf("\e[1;1H\e[2J") // Portable clear screen

void reset_board(Grid *board) { // Iterates once each for rows and columns and sets each index to space
    for(int i = 0; i < board->height; i++) {
        for(int j = 0; j < board->width; j++) {
            board->cells[i][j] = ' ';
        }
    }
}

void print_board(Grid *board, _Bool indicators) { // Formats the indices of the board into a readable output based on chosen board size
    clear();
    printf("\n");
    int yIterations = 0;
    char columnIdent = 'A';
    if(indicators) yIterations++;
    for(int i = 0; i < board->height + yIterations; i++){
        for(int j = 0; j < board->width; j++) {
            if(j > 0) printf(" |");
            if(i < board->height) printf(" %c", board->cells[i][j]);
            else printf(" %c", columnIdent + j);
            if(indicators && ((j == (board->width - 1)) && i < board->height)) printf(" | %d", i + 1);
        }
        printf("\n");
        for(int j = 0; j < board->width; j++) {
            if((i != (board->height - 1) && !indicators) || (i != board->height && indicators)) {
                if(j != (board->width - 1)) printf("---|");
                else if(i != (board->height - 1) && indicators) printf("---|--");
                else printf("---");
            }
        }
        if(i < board->height) printf("\n");
    }
}

void print_turn(char playerMode, char player) {
    if((char) playerMode != 'A') printf("\n\nPlayer Turn: %c\n", player);
}

void check_free_space(Grid *board) { 
    board->freeSpaces = board->height * board->width; // Establishes the maximum alloted number of free spaces based on chosen board size
    for(int i = 0; i < board->height; i++) {
        for(int j = 0; j < board->width; j++) {
            if(board->cells[i][j] != ' ') { // Every time a cell within the board is not empty, iterate freesSpaces down
                board->freeSpaces--;
            }
        }
    }
    //printf("\nFree spaces: %d\n", board->freeSpaces); This is strictly for error checking
}