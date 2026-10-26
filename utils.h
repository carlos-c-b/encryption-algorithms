#ifndef UTILS_H
#define UTILS_H

void swap_int(int *a, int *b);
void swap_char(char *a, char *b);

// Returns the size of the concatenated string
// dst needs to be of size >= strlen(src1) + strlen(src2)
int concat(char *src1, char *src2, char *dst);

int count_negatives(int *a, int length);

void print_int_array(int *array, int length);
void print_char_array(char *array, int length);

#endif
