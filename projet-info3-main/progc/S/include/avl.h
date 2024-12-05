#ifndef AVL_H
#define AVL_H

#include <stdio.h>

typedef struct Node {
    int id;
    float min;
    float max;
    float avg;
    float dif;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

Node *newNode(int id, float min, float avg, float max, float dif);
int height(Node *node);
int maxi(int a, int b);
Node *rightRotate(Node *y);
Node *leftRotate(Node *x);
int getBalance(Node *node);
Node *insert(Node *node, int id, float min, float avg, float max, float dif);
void infixe(Node *root, FILE *fichier, int *count);
void libererArbre(Node *arbre);

#endif

