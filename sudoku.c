#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
   int fila[9] = {0,0,0,0,0,0,0,0,0};
   int columna[9] = {0,0,0,0,0,0,0,0,0};
   int submatriz[3][3] = {0};

   for (int i = 0; i < 9; i++)
      {
         for (int j = 0; j < 9; j++)
            {
               if(n->sudo[i][j] != 0)
               {
                  fila[i] += n->sudo[i][j];
                  columna[j] += n->sudo[i][j];
                  submatriz[i/3][j/3] += n->sudo[i][j];
                  for (int k = 0; k < 9; k++)
                     {
                        if (n->sudo[i][j] == n->sudo[i][k])
                        {
                           return 0;
                        }
                     }
                  for (int l = 0; l < 9; l++)
                     {
                        if (n->sudo[i][j] == n->sudo[l][j])
                        {
                           return 0;
                        }
                     }
                  for (int c = 0; c < 3; c++)
                     {
                        for (int m = 0; m < 3; m++)
                           {
                              if (n->sudo[i][j] == n->sudo[c][m])
                              {
                                 return 0;
                              }
                           }
                     }
               }
            }
      }
   return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();
    int i, j, num = 1;
    for(i = 0; i < 9; i++)
       {
          for(j = 0; j < 9; j++)
             {
                if(n->sudo[i][j] == 0)
                {
                   while (num<=9)
                      {
                         Node* aux = copy(n);
                         aux->sudo[i][j] = num;
                         pushBack(list, aux);
                         num++;
                      }
                }
             }
       }
    return list;
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/