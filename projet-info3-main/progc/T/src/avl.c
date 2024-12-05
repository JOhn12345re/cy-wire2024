#include "../include/avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Implémentation des fonctions déclarées dans avl.h



Node *newNode(int key,char nom[],int count) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->name = malloc(strlen(nom) + 1); // Alloue la mémoire pour le nom
    if (node->name == NULL) {
        free(node);
        exit(1);
    }
    strcpy(node->name, nom); // Copie le nom dans la mémoire allouée
    node->countFirst = count;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // Nouveau nœud est ajouté à une hauteur de 1
    return node;
}

// Fonction pour obtenir la hauteur d'un nœud
int height(Node *node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Fonction pour obtenir le maximum entre deux entiers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Fonction pour faire une rotation à droite
Node *rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    // Effectuer la rotation
    x->right = y;
    y->left = T2;

    // Mettre à jour les hauteurs
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Retourner le nouveau nœud racine
    return x;
}

// Fonction pour faire une rotation à gauche
Node *leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    // Effectuer la rotation
    y->left = x;
    x->right = T2;

    // Mettre à jour les hauteurs
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Retourner le nouveau nœud racine
    return y;
}

// Obtenir le facteur d'équilibre d'un nœud
int getBalance(Node *node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Insérer un nouveau nœud dans l'arbre AVL
Node *insert(Node *node, int key, char nom[], int count) {
    // Étape 1: Insertion standard de l'élément BST
    if (node == NULL){
        return newNode(key, nom, count);
    }

    // Comparaison des clés
    if (key < node->key || (key == node->key && strcmp(nom, node->name) < 0)) {
        node->left = insert(node->left, key, nom, count);
    } else if (key > node->key || (key == node->key && strcmp(nom, node->name) > 0)) {
        node->right = insert(node->right, key, nom, count);
    } else {
        // Les clés et les noms sont les mêmes, il est possible de choisir un côté pour insérer
        node->right = insert(node->right, key, nom, count); // Insérer à droite arbitrairement
    }

    // Étape 2: Mettre à jour la hauteur du nœud actuel
    node->height = 1 + max(height(node->left), height(node->right));

    // Étape 3: Obtenir le facteur d'équilibre de ce nœud pour vérifier l'équilibre
    int balance = getBalance(node);

    // Les rotations pour équilibrer l'arbre selon les cas

    // Cas gauche-gauche
    if (balance > 1 && (key < node->left->key || (key == node->left->key && strcmp(nom, node->left->name) < 0))) {
        return rightRotate(node);
    }

    // Cas droite-droite
    if (balance < -1 && (key > node->right->key || (key == node->right->key && strcmp(nom, node->right->name) > 0))) {
        return leftRotate(node);
    }

    // Cas gauche-droite
    if (balance > 1 && (key > node->left->key || (key == node->left->key && strcmp(nom, node->left->name) > 0))) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Cas droite-gauche
    if (balance < -1 && (key < node->right->key || (key == node->right->key && strcmp(nom, node->right->name) < 0))) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Si l'arbre est équilibré, retourner le nœud actuel
    return node;
}

Node *insertByName(Node *node, int key, char nom[], int count) {
    // Étape 1: Insertion standard de l'élément par ordre alphabétique du nom
    if (node == NULL){
        return newNode(key, nom, count);
    }

    // Comparaison des noms
    if (strcmp(nom, node->name) < 0) {
        node->left = insertByName(node->left, key, nom, count);
    } else if (strcmp(nom, node->name) > 0) {
        node->right = insertByName(node->right, key, nom, count);
    } else {
        // Les noms sont les mêmes, on peut choisir un côté pour insérer (par exemple, à droite)
        node->right = insertByName(node->right, key, nom, count); // Insérer à droite arbitrairement
    }

    // Étape 2: Mettre à jour la hauteur du nœud actuel
    node->height = 1 + max(height(node->left), height(node->right));

    // Étape 3: Obtenir le facteur d'équilibre de ce nœud pour vérifier l'équilibre
    int balance = getBalance(node);

    // Les rotations pour équilibrer l'arbre selon les cas...

    // Cas gauche-gauche
    if (balance > 1 && strcmp(nom, node->left->name) < 0) {
        return rightRotate(node);
    }

    // Cas droite-droite
    if (balance < -1 && strcmp(nom, node->right->name) > 0) {
        return leftRotate(node);
    }

    // Cas gauche-droite
    if (balance > 1 && strcmp(nom, node->left->name) > 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Cas droite-gauche
    if (balance < -1 && strcmp(nom, node->right->name) < 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Si l'arbre est équilibré, retourner le nœud actuel
    return node;
}



// Fonction pour afficher l'arbre en ordre infixe
void infixe(Node *root,FILE*fichier) {
    if (root != NULL) {
        infixe(root->left,fichier);
        fprintf(fichier,"%s;%d;%d\n",root->name, root->key,root->countFirst);
        infixe(root->right,fichier);
    }
}


void addPlusGrand(Node* abr, int *compteur, Node **alpha) {
    if (abr == NULL || *compteur >= 10) {
        return;
    }

    // Parcours l'arbre du côté droit (valeurs les plus grandes en premier)
    addPlusGrand(abr->right, compteur, alpha);

    // Insérer dans le nouvel arbre si le compteur est inférieur à 10
    if (*compteur < 10) {
        *alpha = insertByName(*alpha, abr->key, abr->name, abr->countFirst);
        (*compteur)++;
    }

    // Parcours le côté gauche si le nombre d'éléments ajoutés est inférieur à 10
    if (*compteur < 10) {
        addPlusGrand(abr->left, compteur, alpha);
    }
}




void libererArbre(Node *arbre) {
    if (arbre == NULL) {
        return;
    }
    free(arbre->name);
    free(arbre);
}
