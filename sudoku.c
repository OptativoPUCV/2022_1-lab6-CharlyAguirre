#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct
{  
int sudo[9][9];
}Node;

Node* createNode()
{
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n)
{
  Node* new=(Node*) malloc(sizeof(Node));
  *new = *n;
  return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++)
  {
    for(j=0;j<9;j++)
    {
      if(!fscanf (file, "%d", &n->sudo[i][j]))
      printf("failed to read data!");
    }
  }

  fclose (file);
  return n;
}

void print_node(Node* n)
{
  int i,j;
  for(i=0;i<9;i++)
  {
    for(j=0;j<9;j++)
      printf("%d ", n->sudo[i][j]);
    printf("\n");
  }
  printf("\n");
}

int is_valid(Node* n)
{
  for(int i = 0 ; i < 9 ; i++)
  {
    int filaValid[10] = {0};
    for(int j = 1 ; j < 10 ; j++)
    {
      for(int k = 0 ; k < 9 ; k++)
      {
        if(j == n->sudo[i][k])
        {
          filaValid[j]++;
          if(filaValid[j] > 1) return 0;
        }
      }
    }
  }

  for(int i = 0 ; i < 9 ; i++)
  {
    int columValid[10] = {0};
    for(int j = 1 ; j < 10 ; j++)
    {
      for(int k = 0 ; k < 9 ; k++)
      {
        if(j == n->sudo[k][i])
        {
          columValid[j]++;
          if(columValid[j] > 1) return 0;
        }
      }
    }
  }

  for(int c = 0 ; c < 9 ; c++)
  {
    int matriValid[10] = {0};
    for(int m = 1 ; m < 10 ; m++)
    {
      for(int p = 0 ; p < 9 ; p++)
      {
        int i=3*(c/3) + (p/3) ;
        int j=3*(c%3) + (p%3) ;

        if(m == n->sudo[i][j])
        {
          matriValid[m]++;
          if(matriValid[m] > 1) return 0;
        }
      }
    }
  }
  return 1;
}


List* get_adj_nodes(Node* n)
{
  List* list = createList();

  int i,j,k, flag;
  flag = 0;

  for(i = 0 ; i < 9 ; i++)
  {
    for(j = 0 ; j < 9 ; j++)
    {
      if(n->sudo[i][j] == 0)
      {
        flag = 1;
        break;
      }
    }
    if(flag == 1) break;
  }

  if(flag == 0) return list;

  for(k = 1 ; k < 10 ; k++)
  {
    Node* adjNode = copy(n);
    adjNode->sudo[i][j] = k;
        
    if(is_valid(adjNode))
    {
      pushBack(list, adjNode);
    } 
  }
  
  return list;
}


int is_final(Node* n)
{
  for(int i = 0; i < 9 ; i++)
  {
    for(int j = 0 ; j < 9 ; j++)
    {
      if(n->sudo[i][j] == 0) return 0;
    }
  }
  
  return 1;
}

Node* DFS(Node* initial, int* cont)
{
  Stack *S = createStack();

  push(S,initial);

  while(get_size(S) != 0)
  {
    Node * auxNode = top(S);
    pop(S);

    if(is_final(auxNode) == 1) return auxNode;
    
    List *listAdjNode = get_adj_nodes(auxNode);

    Node *auxNode2 = first(listAdjNode);

    while(auxNode2 != NULL)
    {
      push(S,auxNode2);
      auxNode2 = next(listAdjNode);
    }
    free(auxNode);
    (*cont)++;
  }
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