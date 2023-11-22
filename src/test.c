#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// #define N 5

char Pmodel[1000];
int LNum = 1;
int fcF = 0;
double avgTimee = 0.0;
void PModel();
void csvFile(double time_spent);
void outEnd();
void avgTime();

int main(int argc, char **argv) {
  if (argc < 3) {
    printf("Check!\n");
    return 0;
  }
  PModel();
  csvFile(1);
  char *c;
  int rep = strtol(argv[2], &c, 10);
  int N = strtol(argv[1], &c, 10);
  for (int i = 0; i < rep; i++) {
    double time_spent = 0.0;

    fcF = 1;
    clock_t begin = clock();
    int **A = (int **)malloc(N * sizeof(int *));
    int **B = (int **)malloc(N * sizeof(int *));
    int **C = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
      A[i] = (int *)malloc(N * sizeof(int));
      B[i] = (int *)malloc(N * sizeof(int));
      C[i] = (int *)malloc(N * sizeof(int));
    }
    srand(time(NULL));
    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++) {
        A[i][j] = rand() % 100;
        B[i][j] = rand() % 100;
      }
    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++) {
        C[i][j] = 0;
        for (int k = 0; k < N; k++) C[i][j] += A[i][k] * B[k][j];
      } /*
     printf("matrix A\n");
     for (int i = 0; i < N; i++) {
       for (int j = 0; j < N; j++) printf("%d ", A[i][j]);
       printf("\n");
     }
     printf("\nmatrix B\n");
     for (int i = 0; i < N; i++) {
       for (int j = 0; j < N; j++) printf("%d ", B[i][j]);
       printf("\n");
     }
      printf("\nthe result of multiplying\n");
      for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) printf("%3d ", C[i][j]);
        printf("\n");
      }
      */
    for (int i = 0; i < N; i++) {
      free(A[i]);
      free(B[i]);
      free(C[i]);
    }
    free(A);
    free(B);
    free(C);
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%f\n", time_spent);
    avgTimee += time_spent;
    if (i == rep - 1) {
      fcF = 2;
    }
    csvFile(time_spent);
  }
}

void csvFile(double time_spent) {
  FILE *file;
  file = fopen("csvFile.csv", "a");
  if (file == NULL) {
    printf("Error!\n");
    exit(0);
  }
  if (!fcF) {
    fprintf(file,
            "PModel;Task;OpType;Opt;InsCount;Timer;Time;LNum;AvTime;AbsErr;"
            "RelErr;TaskPerf\n");
  }
  if (fcF == 2) {
    avgTime();
    fprintf(file, "%s;matrix;int;None;?InsCount?;clock;%f;%i;%f\n", Pmodel,
            time_spent, LNum, avgTimee);
  }
  if (fcF == 1) {
    outEnd();

    fprintf(file, "%s;matrix;int;None;?InsCount?;clock;%f;%i; ;\n", Pmodel,
            time_spent, LNum);
    LNum++;
  }
  pclose(file);
}

void avgTime() { avgTimee /= LNum; }

void outEnd() {
  for (int i = 0; i < strlen(Pmodel); i++) {
    if (Pmodel[i] == '\n') {
      Pmodel[i] = '\0';
      break;
    }
  }
}

void PModel() {
  FILE *uname;

  int lastchar;
  uname = popen(
      "lscpu | grep -E '^Имя модели|^Model name' | sed 's/Имя "
      "модели:*\\s*//;s/Model name:*\\s*//'",
      "r");
  lastchar = fread(Pmodel, 1, 1000, uname);
  Pmodel[lastchar] = '\0';
  printf("%s", Pmodel);
  pclose(uname);
}