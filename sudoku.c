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
    int i, j, k, l;
    int row_check[10] = {0};
    int col_check[10] = {0};
    int submatrix_check[10] = {0};

    // Check for repeating numbers in rows and columns
    for(i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            // Check rows
            if(row_check[n->sudo[i][j]] == 1){
                return 0;
            } else {
                row_check[n->sudo[i][j]] = 1;
            }

            // Check columns
            if(col_check[n->sudo[j][i]] == 1){
                return 0;
            } else {
                col_check[n->sudo[j][i]] = 1;
            }
        }
        memset(row_check, 0, sizeof(row_check)); // Reset row check array
        memset(col_check, 0, sizeof(col_check)); // Reset column check array
    }

    // Check for repeating numbers in submatrices
    for(k = 0; k < 9; k++){
        int start_row = 3 * (k / 3);
        int start_col = 3 * (k % 3);

        for(l = 0; l < 9; l++){
            int row = start_row + (l / 3);
            int col = start_col + (l % 3);

            if(submatrix_check[n->sudo[row][col]] == 1){
                return 0;
            } else {
                submatrix_check[n->sudo[row][col]] = 1;
            }
        }
        memset(submatrix_check, 0, sizeof(submatrix_check)); // Reset submatrix check array
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