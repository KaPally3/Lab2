#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// #define N 5

char Pmodel[1000];
char Pmodel_new[1000] = "\0";
int LNum = 1;
int fcF = 0;
double avgTimee = 0.0;
double avgTimee_o = 0.0;
double absErr = 0.0;
double relErr = 0.0;
double taskPef = 0.0;

void intMatrix(int rep, int N);
void PModel();
void csvFile(double time_spent);
void outEnd();
void avgTime();
void absError(double time_spent);
void RelError(double time_spent);
void TaskPerf();

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

  intMatrix(rep, N);
}

void intMatrix(int rep, int N) {
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
      }
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
    // if (i == rep - 1) {
    //   fcF = 2;
    // }
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
  // if (fcF == 2) {
  //   absError(time_spent);
  //   avgTime();
  //   fprintf(file, "%s;matrix;int;None;?InsCount?;clock;%f;%i;%f;%f\n",
  //   Pmodel,
  //           time_spent, LNum, avgTimee, absErr);
  // }
  if (fcF) {
    outEnd();
    avgTime();
    absError(time_spent);
    RelError(time_spent);
    TaskPerf();
    fprintf(file, "%s;matrix;int;None;1;clock;%f;%i;%f;%f;%f;%f\n", Pmodel,
            time_spent, LNum, avgTimee_o, absErr, relErr, taskPef);
    LNum++;
  }
  fclose(file);
}

void avgTime() { avgTimee_o = avgTimee / LNum; }

void absError(double time_spent) {
  absErr = fabs((avgTimee / LNum) - time_spent);
}

void RelError(double time_spent) { relErr = absErr * 100 / time_spent; }

void TaskPerf() { taskPef = 1 / avgTimee_o; }

void outEnd() {
  for (long unsigned int i = 0; i < strlen(Pmodel); i++) {
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