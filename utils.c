#include <stdio.h>
#include <string.h>

void swap_int(int *a, int *b) {
	int aux = *a;
	*a = *b;
	*b = aux;
}


void swap_char(char *a, char *b) {
	char aux = *a;
	*a = *b;
	*b = aux;
}

// dst needs to be of size >= l1+l2
int concat(char *src1, char *src2, char *dst) {
	int l1 = strlen(src1);
	int l2 = strlen(src2);

	strcpy(dst, src1);
	strcpy(&dst[l1], src2); // 0...l1-1 l1...l1+l2-1
	dst[l1+l2] = '\0';	

	return l1 + l2;
}

// Returns number of negative values in an int array for debugging
int count_negatives(int *a, int length) {
	int c = 0;
	for(int i = 0; i < length; i++) if(a[i]<0) c++;
	return c;
}

void print_int_array(int *array, int length) {
	for(int i = 0; i < length; i++) printf("%d\n", array[i]);
}


void print_char_array(char *array, int length) {
	for(int i = 0; i < length; i++) printf("%d\n", array[i]);
}
