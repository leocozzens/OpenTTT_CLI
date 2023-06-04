#ifndef UTILS_H
#define UTILS_H

// C standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// Local headers
#include <structs.h>

#define FGETS_BUFFER_SIZE 4096

int num_max(int num1, int num2);
char **dynamic_grid(int rows, int columns);
_Bool parse_int(char *string, int *integer, int max);
int digit_num(int digits);
_Bool grid_free(char **target, int rows);
void validate_input(int *input, int min, int max, char *data, char dataType);

#endif