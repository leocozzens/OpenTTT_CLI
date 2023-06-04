// C Standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// Local headers
// #include <structs.h> Utils no longer needs grid struct

#define FGETS_BUFFER_SIZE 4096

int num_max(int num1, int num2) {
    return (num1 > num2) ? num1 : num2;
}

char **dynamic_grid(int rows, int columns) {
    char **grid = NULL;
    grid = malloc(rows * (sizeof(char*))); // Allocate memory to the size of rows * char pointers

    if(grid == NULL) { // Error handling: Failed to allocate memory for grid.cells so return an empty grid
        grid = NULL;

        return grid;
    }

    for(int i = 0; i < rows; i++) {
        grid[i] = (char*) malloc(columns * (sizeof(char))); // Allocate each index of grid to a new set of columns * char size
    }
    return grid;
}

_Bool parse_int(char *string, int *integer, int max) { // Counts max integer decimal count and uses it to set max string size
    int i = 0; // Iterator variable
    while (isspace(string[i])) i++; // Iterates past all successive spaces at start of string

    if (strlen(string) == i) return 0; // If after iterating through spaces there is no remaining text, return false

    char integerBuffer[max + 1]; // Buffer to hold integer, set to size of max digits + 1 for null terminator
    int integerChars = 0; // Iterator for integer buffer

    if(string[i] == '-') { // Checks if the first element is '-' to denote a negative number
        integerBuffer[0] = '-';
        integerChars++;
        i++;

        if(!isdigit(string[i])) return 0; // If the character after '-' is not a digit, return false
    }
    while(i < strlen(string) && !isspace(string[i])) {
        if(!isdigit(string[i])) return 0; //If the character after any spaces and the '-' sign isn't a space, return false

        if(integerChars < max) {
            integerBuffer[integerChars] = string[i]; // If integerChars isn't filled passed our max add the current index of string to it
            integerChars++;
            i++;
        }
        else break;
    }
    integerBuffer[integerChars] = '\0'; // Add null terminator to string to format it properly

    //while(isspace(string[i])) i++; Skip through spaces at the end of string (unnecessary in this func)
    *integer = atoi(integerBuffer); // Convert integer string to int data type
    return 1;
}

int digit_num(int digits) {
    int count = 0;
    do {
        digits /= 10;
        count++;
    }while(digits != 0);

    return count;
}

_Bool grid_free(char **target, int rows) { // Free's memory of 2D array on heap, also checks for error and will return true if any of the pointers memory addresses are undefined
    if(target == NULL) return 1;
    for(int i = 0; i < rows; i++) {
        if(target[i] != NULL) free(target[i]); // Loop through each index of the target array and free the row at each index denoted by its first block of memory
        else return 1;
    }
    free(target); // Now free the pointer to the first set pointer heap array
    return 0;
}

void validate_input(int *input, int min, int max, char *data, char dataType) {
    char buffer[FGETS_BUFFER_SIZE];
    _Bool parsed = 1;
    char firstChar = 64;
    int i = 0;

    if(dataType == 'c') {
        min += firstChar;
        max += firstChar;
    }

    do {
        if(dataType == 'd') printf("Enter %s #(%d-%d): ", data, min, max);
        else printf("Enter %s #(%c-%c): ", data, min, max);

        fgets(buffer, FGETS_BUFFER_SIZE, stdin);
        if(dataType == 'd') parsed = parse_int(buffer, input, digit_num(max) + 1); // Any number 1 digit above the max will confirm as an integer but notify the user it wasn't in the expected range
        else if(dataType == 'c') {
            while(isspace(buffer[i])) i++;
            *input = (int) toupper(buffer[i]);
        }
        if(!parsed && dataType == 'd') printf("\nPlease enter a number.\n");
        else if((*input > max || *input < min) && dataType == 'd') printf("\nYou did not enter an integer between %d and %d\n", min, max);
        else if((*input > max || *input < min) && dataType == 'c' && !isspace(buffer[i + 1])) printf("\nYou did not enter an character between %c and %c\n", min, max);
    }while(!parsed || (*input > max || *input < min));
}