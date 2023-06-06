// Local headers
#include <utils.h>
#include <board.h>
#include <logic.h>

int main() {
    char contGame; // This var will determine if the game loop continues

    _Bool turnSwap = 0;
    ScoreTracker scoreBoard = {0, 0}; // Initialize scoreboard to track player scores
    Grid board; // Initialize grid struct to hold board elements
    board.height = 3;
    board.width = 3;
    board.patternLength = 3;

    _Bool indicators = 0;
    int playerMode;

    game_type(&board, &indicators, &playerMode);
    do {
        char winner = ' ';
        _Bool playerTurn = !turnSwap; // Will track the current player's turn

        board.cells = dynamic_grid(board.height, board.width); // Dynamic grid will create a 2D array to store board positions
        board.player = 'X'; // TODO: Character customization prompts for players
        board.opponent = 'O';
        board.freeSpaces = board.height * board.width;

        reset_board(&board);

        // Game loop
        while (winner == ' ' && board.freeSpaces != 0) {
            if (playerTurn) {
                print_board(&board, indicators);
                print_turn(playerMode, board.player);
                player_move(&board, indicators);
                playerTurn = 0;
            }
            else if((char) playerMode == 'A') {
                computer_move(&board);
                playerTurn = 1;
            }
            else {
                char temp = board.player;
                board.player = board.opponent;

                print_board(&board, indicators);
                print_turn(playerMode, board.player);
                player_move(&board, indicators);

                board.player = temp;
                playerTurn = 1;
            }
            check_winner(&board, &winner, board.patternLength);
            check_free_space(&board);   
        }

        print_board(&board, indicators);
        print_winner(winner, board.player, board.opponent, &scoreBoard, playerMode);
        
        if(grid_free(board.cells, board.height)) printf("\n ERROR: Not able to free memory for grid\n");

        printf("The score is %d to %d\nWould you like to play again? (Y OR N): ", scoreBoard.playerScore, scoreBoard.opponentScore);
        scanf("%c", &contGame);
        getchar(); // Clear newline from the input stream (scanf will leave it in)

        if(tolower(contGame) == 'y') { 
            char askSwap; // This will accept the prompt response of whether the user wants to swap
            printf("Would you like to swap turn order? (Y OR N): ");
            scanf("%c", &askSwap);
            getchar(); // Clear newline from the input stream (scanf will leave it in)
            if(tolower(askSwap) == 'y') turnSwap = !turnSwap;
        }
    } while(tolower(contGame) == 'y');
    return 0;
}