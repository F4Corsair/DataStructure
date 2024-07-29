#include <stdio.h>
#include <stdlib.h>
#include "avlTree.h"

// use double pointer to set NULL value if needed
void avlInsert(TreeNode **parent, int key, int *unbalanced) {
    if(!*parent) {
        // make node
        *unbalanced = TRUE;
        *parent = malloc(sizeof(TreeNode));
        (*parent)->lChild = (*parent)->rChild = NULL;
        (*parent)->bf = 0;
        (*parent)->key = key;
    }
    else if(key < (*parent)->key) {
        avlInsert(&(*parent)->lChild, key, unbalanced);
        if(*unbalanced) {
            // left branch has grown higher
            switch ((*parent)->bf)
            {
            case -1:
                (*parent)->bf = 0;
                *unbalanced = FALSE;
                break;
            case 0:
                (*parent)->bf = 1;
                break;
            case 1:
                leftRotation(parent, unbalanced);
            }
        }
    } else if(key > (*parent)->key) {
        avlInsert(&(*parent)->rChild, key, unbalanced);
        if(*unbalanced) {
            // right branch has grown higher
            switch ((*parent)->bf)
            {
            case 1:
                (*parent)->bf = 0;
                *unbalanced = FALSE;
                break;
            case 0:
                (*parent)->bf = -1;
                break;
            case -1:
                rightRotation(parent, unbalanced);
            }
        }
    } else {
        *unbalanced = FALSE;
        printf("The Key is already in used");
    }
}

void leftRotation(TreeNode **parent, int *unbalanced) {
    TreeNode *grandChild, *child;
    child = (*parent)->lChild;

    if(child->bf == 1) {
        // LL rotation
        (*parent)->lChild = child->rChild;
        child->rChild = *parent;
        (*parent)->bf = 0;
        (*parent) = child;
    } else {
        // LR rotation
        grandChild = child->rChild;
        child->rChild = grandChild->lChild;
        grandChild->lChild = child;
        (*parent)->lChild = grandChild->rChild;
        grandChild->rChild = *parent;
        
        switch (grandChild->bf) // after append, what child does grandchild has?
        {
        case 1: // lChild of grandChild moves to child->rChild
            (*parent)->bf = -1;
            child->bf = 0;
            break;
        case 0: // both child gonna balance all
            (*parent)->bf = child->bf = 0;
            break;
        case -1: // rChild of grandChild moves to parent->lChild
            (*parent)->bf = 0;
            child->bf = 1;
        }
        *parent = grandChild;
    }
    (*parent)->bf = 0;
    *unbalanced = FALSE;
}

void rightRotation(TreeNode **parent, int *unbalanced) {
    TreeNode *grandChild, *child;
    child = (*parent)->rChild;

    if(child->bf == -1) {
        // RR rotation
        (*parent)->rChild = child->lChild;
        child->lChild = *parent;
        (*parent)->bf = 0;
        (*parent) = child;
    } else {
        // RL rotation
        grandChild = child->lChild;
        child->lChild = grandChild->rChild;
        (*parent)->rChild = grandChild->lChild;
        grandChild->lChild = *parent;

        switch (grandChild->bf) // after append, what child does grandchild has?
        {
        case -1: // rChild of grandChild moves to child->lChild
            (*parent)->bf = 1;
            child->bf = 0;
            break;
        case 0:
            (*parent)->bf = child->bf = 0;
            break;
        case 1: // lChild of grandChild moves to parent->rChild
            (*parent)->bf = 0;
            child->bf = -1;
        }
    }
    (*parent)->bf = 0;
    *unbalanced = FALSE;
}