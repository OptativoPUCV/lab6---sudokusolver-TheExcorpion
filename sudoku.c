#include "list.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int sudo[9][9];
} Node;

Node *createNode() {
  Node *n = (Node *)malloc(sizeof(Node));
  return n;
}

Node *copy(Node *n) {
  Node *new = (Node *)malloc(sizeof(Node));
  *new = *n;
  return new;
}

Node *read_file(char *file_name) {
  Node *n = createNode();
  FILE *file = fopen(file_name, "r");
  int i, j;
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++) {
      if (!fscanf(file, "%d", &n->sudo[i][j]))
        printf("failed to read data!");
    }
  }

  fclose(file);
  return n;
}

void print_node(Node *n) {
  int i, j;
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++)
      printf("%d ", n->sudo[i][j]);
    printf("\n");
  }
  printf("\n");
}

int is_valid(Node *n) {
  // Check each row
  for (int i = 0; i < 9; i++) {
    int seen[10] = {0}; // Array to keep track of numbers seen in this row
    for (int j = 0; j < 9; j++) {
      int num = n->sudo[i][j];
      if (num != 0 && seen[num]) {
        return 0; // If the number is repeated in this row, the Sudoku is invalid
      }
      seen[num] = 1;
    }
  }

  // Check each column
  for (int j = 0; j < 9; j++) {
    int seen[10] = {0}; // Array to keep track of numbers seen in this column
    for (int i = 0; i < 9; i++) {
      int num = n->sudo[i][j];
      if (num != 0 && seen[num]) {
        return 0; // If the number is repeated in this column, the Sudoku is invalid
      }
      seen[num] = 1;
    }
  }

  // Check each 3x3 subgrid
  for (int i = 0; i < 9; i += 3) {
    for (int j = 0; j < 9; j += 3) {
      int seen[10] = {0}; // Array to keep track of numbers seen in this subgrid
      for (int di = 0; di < 3; di++) {
        for (int dj = 0; dj < 3; dj++) {
          int num = n->sudo[i + di][j + dj];
          if (num != 0 && seen[num]) {
            return 0; // If the number is repeated in this subgrid, the Sudoku is invalid
          }
          seen[num] = 1;
        }
      }
    }
  }

  return 1; // If all checks pass, the Sudoku is valid
}

List *get_adj_nodes(Node *n) {
  List *adj_nodes = createList();
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (n->sudo[i][j] == 0) {
        for (int num = 1; num <= 9; num++) {
          Node *new_node = copy(n);
          new_node->sudo[i][j] = num;
          if (is_valid(new_node)) { // Call is_valid and check its return value
            pushBack(adj_nodes, new_node);
          } else {
            free(new_node); // Free memory if the node is not valid
          }
        }
        return adj_nodes; // Return the list of adjacent nodes immediately after adding nodes
      }
    }
  }
  return adj_nodes;
}


Node *DFS(Node *initial, int *cont) { return NULL; }

/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/