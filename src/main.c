// Local headers
#include <utils.h>
#include <board.h>
#include <logic.h>

int main() {
    char contGame; // This var will determine if the game loop continues
    char askSwap; // This will accept the prompt response of whether the user wants to swap
    _Bool turnSwap = 0;
    _Bool indicators = 1;
    ScoreTracker scoreBoard = {0, 0};
    do {
        char winner = ' ';
        int height = 3;
        int width = 3;
        int patternLength = 3;
        _Bool playerTurn = !turnSwap; // Will track the current player's turn

        Grid board; // Initialize grid struct to hold board elements
        board = dynamic_grid(height, width); // Dynamic grid will create a 2D array to store board positions
        board.player = 'X'; // TODO: Character customization prompts for players
        board.opponent = 'O';
        board.freeSpaces = board.height * board.width;

        reset_board(&board);
        //printf("Would you like to play versus A.I., Local Multiplayer, or Online Multiplayer");
        //printf("Would you like to play Tic Tac Toe, or Connect 4?");
        //printf("Would you like to play standard or custom?")
        //printf("Chose board size: 5x5 (Type 5), 7x7 (Type 7), or Custom (type C)");

        // Game loop
        while (winner == ' ' && board.freeSpaces != 0) {
            if (playerTurn) {
                print_board(&board, indicators);
                player_move(&board);
                playerTurn = 0;
            }
            else {
                computer_move(&board);
                playerTurn = 1;
            }
            check_winner(&board, &winner, patternLength);
            check_free_space(&board);   
        }

        print_board(&board, indicators);
        print_winner(winner, board.player, board.opponent, &scoreBoard);
        
        if(grid_free(board.cells, board.height)) printf("\n ERROR: Not able to free memory for grid\n");

        printf("The score is %d to %d\nWould you like to play again? (Y OR N): ", scoreBoard.playerScore, scoreBoard.opponentScore);
        scanf("%c", &contGame);
        getchar(); // Clear newline from the input stream (scanf will leave it in)

        if(tolower(contGame) == 'y') {
            printf("Would you like to swap turn order? (Y OR N): ");
            scanf("%c", &askSwap);
            getchar(); // Clear newline from the input stream (scanf will leave it in)
            if(tolower(askSwap) == 'y') turnSwap = !turnSwap;
        }
    } while(tolower(contGame) == 'y');
    return 0;
}