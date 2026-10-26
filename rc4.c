#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

/*
 * Implementation of Alleged RC4
 * State of RC4
 *
 * k = Secret Key of size <= 256B.
 * K = Byte array of 256B consisting of a 256B repeated concatenations of k.
 * S = Byte array of 256B, with all its elements unique
 * i,j = Two counters
 * R = Byte array of 256B to be XOR-ed with the message
 * P = Message in plain text  to be chipered and deciphered
 * C = Ciphered message. In particular, C_i = P_i XOR R_i. C_i is the i-th byte of the array, i.e., the i-th character
 *
 *
 * 33 - 126 are actual characters in ASCII
 *
 * ---------------------
 *
 * The algorithm has two phases
 *
 * Phase 1: RC4's state is initialised, i.e., S is set so that it can be used to generate the array R
 * Phase 2: We obtain R_i using S, i, and j, and we XOR it with P_i to get C_i
 *
 * ----------------------
 *
 * Decryption
 * The algorithm is determinist given the same key, so the receiver will have to generate the same array
 * R to XOR character by character the ciphered message C to obtain P.
 *
 *
 *
 *
 * Based on VPNs Illustrated by Jon C Stander (Chapter 3)
 */

#define FIRST_CHAR 33
#define LAST_CHAR 126
#define ALPH_LENGTH (LAST_CHAR - FIRST_CHAR + 1)

char *repeat(const char *k) {
	char *K = malloc(ALPH_LENGTH + 1);
	int k_length = strlen(k);

	for(int i = 0; i < ALPH_LENGTH; i++) K[i] = k[i % k_length];
	K[ALPH_LENGTH] = '\0';

	return K;
}

char *rc4(const char *P, const char *k) {
	// Phase 1
	int m = 0;	
	char S[ALPH_LENGTH];
	char *K = repeat(k);

	for(int n = 0; n < ALPH_LENGTH; n++) S[n] = n + FIRST_CHAR;



	for(int n = 0; n < ALPH_LENGTH; n++) {
		m = ( m + (int)S[n] +  (int)K[n] ) % ALPH_LENGTH; // 0 <= m <= ALPH_LENGTH-1
		swap_char(&S[n], &S[m]);
	}

	
	// Phase 2
	int i = -1;
	int j = 0;
	int x;
	int length = strlen(P);
	char *C = malloc(length+1);
	C[length] = '\0';

	for(int n = 0; n < length; n++) {
		i = (i + 1) % ALPH_LENGTH;
		j = (j + S[j]) % ALPH_LENGTH;
		x = (S[i] + S[j]) % ALPH_LENGTH;
		swap_char(&S[i], &S[j]);
		C[i] = P[i] ^ S[x];	// S[x] = R_i
	}


	return C;

}

int main() {

	char *P = "hola, buenos dias";
	char *k = "contrasena secreta";

	char *C = rc4(P, k); // C = Ciphered text
	char *D = rc4(C, k); // D = Deciphered text

	printf("%s\n", C);
	printf("%s\n", D);



	return 0;
}
