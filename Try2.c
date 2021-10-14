#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char symbol;
int f, start, elm, i, count, max, g, ribs, tops, check;
int *a, *b;


int main(void) {
  FILE* file_graph;
  FILE* result;
  count = 0;
  check = 0;
  ribs = 0;
  tops = 0;
  f = 0;
  g = 1;
  max = -1;
  i = 1;

  //Reading and choosing Max

  file_graph = fopen("graph.dot", "r");
  while ((symbol = getc(file_graph)) != EOF) {
    putc(symbol, stdin);
    if (symbol == '\n')
    count ++;
  }
  fclose(file_graph);
 // count --;
  printf("Result:\n");
 //    printf("Count = %d", count);

  count *= 2;
  count ++;



  file_graph = fopen("graph.dot", "r");

  a = (int*)malloc(count * sizeof(int));
  while ((symbol = getc(file_graph)) != EOF) {
    if ((symbol <= '9') && (symbol >= '0')){
      elm = elm * 10 + (int)(symbol - '0');
    }
    if (symbol == '-')
    f++;
    if (symbol == '\n')
    g++;
    if (f > 0)
    g = 0;
    if (f == 2)
    ribs++;
    if ((f == 2) || (symbol == '\n')) {
      if (g == 2) {
        a[i] = elm;
        a[i+1] = elm;
        i = i + 2;
        g = 1;
      } else {
      a[i] = elm;
      f = 0;
      i++;
      }
      elm = 0;
    }
    if (a[i-1] > max){
      max = a[i-1];
    } else if (a[i] > max){
      max = a[i];
    }
    if (count == i)
    break;
  }


//printf("max = %d \n", max);

int **matrix=(int**)calloc(max+2, sizeof(int*));
for(int i=0; i<=max; i++)
matrix[i]=(int*)calloc(max+2, sizeof(int));
for (int j = 1; j< i; j++){
  if ((j % 2) == 1){
  int x = a[j];
  int y = a[j+1];

//  printf("Cordinats to aim: x = %d, y = %d", x, y);
  
  matrix[x][y] += 1;
  }
}

//Processing Graph

  count --;
  i --;
  // j - строка
  // k - столбец

// Петля

if (check == 0) {
for (int j = 1; j<=max; j++){
  if (matrix[j][j] == 1){
  check = 1;
  break;
  }
}
}

// =

  if (check == 0){
    for (int j = 1; j<=max; j++)
    for (int k = 1; k<=j; k++){
      if (((matrix[j][k] == 1) && (matrix[k][j] == 1)) || (matrix[j][k] > 1) || ((matrix[k][j] > 1))) {
      check = 2;
      break;
     }
    }
  }

//Связанность

b = (int*)malloc(max * sizeof(int));
for (int j = 1; j<=i; j++){
  b[j] = 0;
}
for (int j = 1; j<=i; j++){
  b[a[j]] ++;
}
for (int j = 1; j<=i; j++){
  if (b[j]>0)
  tops ++;
}

//printf("ribs = %d, tops = %d", ribs, tops);


if (check == 0){
  if ((ribs) >= (tops - 1)){
  check = 0;
  } else{
    check = 3;
  }
}

//Цикл
  

if (check == 0){
  if ((tops - ribs) != 1){
    check = 4;
  }
}
fclose(file_graph);
result = fopen("result.txt", "w");
fprintf(result, "Result:\n");
if (check != 0){
fprintf(result,"This Graph is not a TREE\n");
printf("This Graph is not a TREE\n");
}
if (check == 0){
printf("This Graph is a TREE\n");
fprintf(result,"This Graph is a TREE\n");
}
fclose(result);
system("dot graph.dot -Tpng -o graph.png");

    free(a);
}

