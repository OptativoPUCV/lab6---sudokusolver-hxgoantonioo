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

int is_valid(Node* n) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (n->sudo[i][j] != 0) {
                // Verificar fila
                for (int k = 0; k < 9; k++) {
                    if (k != j && n->sudo[i][j] == n->sudo[i][k]) {
                        return 0;
                    }
                }
                // Verificar columna
                for (int l = 0; l < 9; l++) {
                    if (l != i && n->sudo[i][j] == n->sudo[l][j]) {
                        return 0;
                    }
                }
                // Verificar submatriz 3x3
                int x = (i / 3) * 3;
                int y = (j / 3) * 3;
                for (int m = 0; m < 3; m++) {
                    for (int s = 0; s < 3; s++) {
                        if ((x + m != i || y + s != j) && n->sudo[x + m][y + s] == n->sudo[i][j]) {
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
                         if (is_valid(aux))
                         {
                            pushBack(list, aux);
                         }
                         num++;
                      }
                }
             }
       }
    return list;
}


int is_final(Node* n){
    int i, j;
    for (i = 0; i < 9; i++)
        {
            for (j = 0; j < 9; j++)
                {
                    if (n->sudo[i][j] == 0)
                        return 0;
                }
        }
    return 1;
}

Node* DFS(Node* initial, int* cont){
    *cont = 0;
    Node** stack = (Node**) malloc(sizeof(Node*));
    int top = 0;

    stack[top] = initial;
    top++;

    while (top > 0) {
        Node* current = stack[top - 1];
        top--;
        (*cont)++;

        if (is_final(current)) {
            free(stack);
            return current;
        }

        List* adj = get_adj_nodes(current);
        Node* aux = first(adj);
        while (aux != NULL) {
            stack = (Node**) realloc(stack, (top + 1) * sizeof(Node*));
            stack[top] = aux;
            top++;
            aux = next(adj);
        }
        clean(adj);
    }

    free(stack);
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