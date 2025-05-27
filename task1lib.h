#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void citire_matrice(char **mat, int N, int M, FILE *citire);
void scriere_matrice(char **mat, int N, int M, FILE *scriere);
void vecini_vii(char **mat, int N, int M, int *nrVii, int j, int k);
void implementare_reguli(char **mat, int K, int N, int M, FILE *scriere);

