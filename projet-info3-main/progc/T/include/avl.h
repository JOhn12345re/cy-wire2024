#ifndef AVL_H
#define AVL_H

#include <stdio.h>

typedef struct Node {
    int key;
    char* name;
    int countFirst;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

Node *newNode(int key, char nom[], int count);
int height(Node *node);
int max(int a, int b);
Node *rightRotate(Node *y);
Node *leftRotate(Node *x);
int getBalance(Node *node);
Node *insert(Node *node, int key, char nom[], int count);
Node *insertByName(Node *node, int key, char nom[], int count);
void infixe(Node *root, FILE *fichier);
void addPlusGrand(Node *abr, int *compteur, Node **alpha);
void libererArbre(Node *arbre);

#endif

