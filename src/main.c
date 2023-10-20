#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#define N 5

int main(int argc, char **argv) {
char *c;
int N = strtol(argv[1], &c, 10);
int **A = (int**)malloc(N * sizeof(int*));
int **B = (int**)malloc(N * sizeof(int*));
int **C = (int**)malloc(N * sizeof(int*));
for (int i = 0; i < N; i++)
{
    A[i] = (int*)malloc(N * sizeof(int));
    B[i] = (int*)malloc(N * sizeof(int));
    C[i] = (int*)malloc(N * sizeof(int));
}  
srand(time(NULL));
for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
    {
        A[i][j] = rand() % 1000;
        B[i][j] = rand() % 1000;
    }
for(int i = 0; i < N; i++)
    for(int j = 0; j < N; j++)
    {
        C[i][j] = 0;
        for(int k = 0; k < N; k++)
        C[i][j] += A[i][k] * B[k][j];
    }
printf("matrix A\n");
for (int i = 0; i < N; i++)
{
    for (int j = 0; j < N; j++)
        printf("%d ", A[i][j]);
    printf("\n");
}
printf("\nmatrix B\n");
for (int i = 0; i < N; i++)
{
    for (int j = 0; j < N; j++)
        printf("%d ", B[i][j]);
    printf("\n");
}
printf("\nthe result of multiplying\n");
for (int i = 0; i < N; i++)
{
    for (int j = 0; j < N; j++)
        printf("%3d ", C[i][j]);
    printf("\n");
}
for (int i = 0; i < N; i++)
{
    free(A[i]);
    free(B[i]);
    free(C[i]);
}
free(A);
free(B);
free(C);
 }
