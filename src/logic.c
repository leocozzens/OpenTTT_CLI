// C Standard libraries
#include <time.h>
// Local headers
#include <structs.h>
#include <utils.h>

void game_type(Grid *board, _Bool *indicators, int *playerMode) {
    char gameType;
    char askIndicators;

    printf("\nWould you like to play versus A.I. (A), Local Multiplayer (B), or Online Multiplayer (C)?\n");
    validate_input(playerMode, 1, 3, "game type", 'c');
    if((char) *playerMode == 'A') printf("\nSingle Player mode selected.\n\n");
    else if((char) *playerMode == 'B') printf("\nLocal Multiplayer mode selected.\n\n");
    else {
        printf("\nFunctionality not yet implemented.\n\n");
        *playerMode = (int) 'A';
    }

    //printf("Would you like to play Tic Tac Toe, or Connect 4?");

    printf("Would you like to play standard or custom? (S or C): "); // Defaults to S
    scanf("%c", &gameType);
    getchar(); // Clear the input stream of the newline char

    if(tolower(gameType) == 'c') {
        printf("\nChose board size: \n");

        validate_input(&board->height, 3, 30, "board height", 'd');
        validate_input(&board->width, 3, 30, "board width", 'd');
        validate_input(&board->patternLength, 3, num_max(board->height, board->width), "pattern length", 'd');

        printf("Would you like row and column indicators? (Y or N): ");
        scanf("%c", &askIndicators);
        getchar(); // Clear newline from the input stream
        if(tolower(askIndicators) == 'y') *indicators = 1;
    }
}

void player_move(Grid *board, _Bool indicators) { // Function allows player to place their next move by entering the desired square's coordinates (row, column)
    int rows;
    int columns;
    char dataType;
    if(indicators) dataType = 'c';
    else dataType = 'd';
    do {
        validate_input(&rows, 1, board->height, "row", 'd'); // Runs validate utility to correctly handle and receive user prompt then process into integer
        validate_input(&columns, 1, board->width, "column", dataType);

        rows--; // Iterate both rows and columns down to be valid array indices
        if(dataType == 'd') columns--;
        else columns -= 65;

        //printf("Player move\n"); Purely for debugging
        if(board->cells[rows][columns] != ' ') {
            printf("\nInvalid move!\n");
        }
        else {
            //printf("Player move sent\n"); Also for debugging
            board->cells[rows][columns] = board->player;
            break;
        }
    } while (board->cells[rows][columns] != ' ');
}

void check_winner(Grid *board, char *winnerVar, int patternLength) { // Checks for a successive pattern of specified length and returns the character other than ' ' which it was found with
    _Bool winnerFound = 0;
    // Checking rows
    for(int i = 0; i < board->height; i++) {
        for(int j = 0; j < board->width - (patternLength - 1); j++) {
            _Bool match = 1;
            for(int k = 1; k < patternLength; k++) {
                if ((board->cells[i][j] == ' ') || (board->cells[i][j] != board->cells[i][j + k])) {
                    match = 0;
                    break;
                }
            }
            if(match) {
                //printf("Winner identified with rows: %c\n", board->cells[i][j]); Debugging prompt
                *winnerVar = board->cells[i][j];
                winnerFound = 1;
                break;
            }   
        }
        if(winnerFound) break;
    }
    //printf("Rows Checked\n"); Debugging prompt
    // Checking columns
    for(int i = 0; i < board->width; i++) {
        for(int j = 0; j < board->height - (patternLength - 1); j++) {
            _Bool match = 1;
            for(int k = 1; k < patternLength; k++) {
                if((board->cells[j][i] == ' ') || (board->cells[j][i] != board->cells[j + k][i])) {
                    match = 0;
                    break;
                }
            }
            if(match) {
                //printf("Winner identified with columns: %c\n", board->cells[j][i]); Debugging prompt
                *winnerVar = board->cells[j][i];
                winnerFound = 1;
                break;
            }
        }
        if(winnerFound) break;
    }
    //printf("Columns Checked\n"); Debugging prompt
    // Checking diagonals
    for(int i = 0; i < board->height - (patternLength - 1); i++) {
        for(int j = 0; j < board->width; j++) {
            _Bool main = 1;
            _Bool anti = 1;
            for(int k = 1; k < patternLength; k++) {
                if(board->cells[i][j] == ' ') {
                    main = 0;
                    anti = 0;
                    break;
                }
                if(j < (board->width - (patternLength - 1))) {
                    if(board->cells[i][j] != board->cells[i + k][j + k]) {
                        main = 0;
                    }
                }
                else main = 0;
                if(j > patternLength - 2) {
                    if(board->cells[i][j] != board->cells[i + k][j - k]) {
                        anti = 0;
                    }
                }
                else anti = 0;
            }
            if(main || anti) {
                //printf("Winner identified with diagonals: %c\n", board->cells[i][j]); Debugging prompt
                //printf("Main:%d \nAnti:%d \n", main, anti); Debugging prompt
                *winnerVar = board->cells[i][j];
                winnerFound = 1;
                break;
            }
        }
        if(winnerFound)break;
    }

    //printf("Diagonals Checked\n"); Debugging prompt
    if(!winnerFound) {
        *winnerVar = ' ';
    }
}

void print_winner(char winner, char player, char opponent, ScoreTracker *scoreBoard, int playerMode) { // Checks the winnervar to see if it matches either player
    if(winner == player) {
        if((char) playerMode == 'A') printf("You win!\n\n");
        else printf("Player %c wins!\n\n", player);
        scoreBoard->playerScore++; // Iterates the corresponding score
    }
    else if(winner == opponent) {
        if((char) playerMode == 'A') printf("You lose!\n\n");
        else printf("Player %c wins!\n\n", opponent);
        scoreBoard->opponentScore++;
    }
    else {  // Persistent "Cat's game" means this statement is recieving an incorrect input
        printf("Cat's game!\n\n");
        scoreBoard->playerScore++; // In the event of a tie, both players get a point
        scoreBoard->opponentScore++;
    }
}

void computer_move(Grid *board) { // Defines and places computer's move
    srand(time(0)); // Creates seed for random values
    int rows;
    int columns;

// TODO: Add a more complex AI
    if(board->freeSpaces > 0) { // Additional error safegaurd
        do {
            rows = rand() % board->height; // Modulos operator returns the remainder of a division, this then allows us to set a maximum value for rand()
            columns = rand() % board->width;
        } while(board->cells[rows][columns] != ' ');
        //printf("Computer move\n"); Debugging prompt
        board->cells[rows][columns] = board->opponent; // Set the computer move to the random decision prior
    }
}