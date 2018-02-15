//
//  tree-basic-operations.cpp
//  SWTest
//
//  Created by Risman Adnan on 7/15/15.
//  Copyright (c) 2015 Risman Adnan. All rights reserved.
//

#include<cstdio>
#include<cstdlib>
#include<iostream>

using namespace std;

/* A binary tree node has data, pointer to left child
 and a pointer to right child */
typedef struct node
{
    int data;
    node* left;
    node* right;
}node;

/* Helper function that allocates a new node with the
 given data and NULL left and right pointers. */

node* newNode(int data)
{
    node* tmp = new node();
    tmp->data = data;
    tmp->left = NULL;
    tmp->right = NULL;
    
    return(tmp);
}

/* Computes the number of nodes in a tree. */
int size(node* node)
{
    if (node==NULL)
        return 0;
    else
        return(size(node->left) + 1 + size(node->right));
}

/* Function to get the count of leaf nodes in a binary tree*/
unsigned int getLeafCount(node* node)
{
    if(node == NULL)
        return 0;
    if(node->left == NULL && node->right==NULL)
        return 1;
    else
        return getLeafCount(node->left)+
        getLeafCount(node->right);
}


/* Returns the height of a binary tree */
int height(node* node);

/* Returns true if binary tree with root as root is height-balanced */
bool isBalanced(node *root)
{
    int lh; /* for height of left subtree */
    int rh; /* for height of right subtree */
    
    /* If tree is empty then return true */
    if(root == NULL)
        return 1;
    
    /* Get the height of left and right sub trees */
    lh = height(root->left);
    rh = height(root->right);
    
    if( abs(lh-rh) <= 1 &&
       isBalanced(root->left) &&
       isBalanced(root->right))
        return 1;
    
    /* If we reach here then tree is not height-balanced */
    return 0;
}

/* UTILITY FUNCTIONS TO TEST isBalanced() FUNCTION */

/* returns maximum of two integers */
int max(int a, int b)
{
    return (a >= b)? a: b;
}

/*  The function Compute the "height" of a tree. Height is the
 number of nodes along the longest path from the root node
 down to the farthest leaf node.*/
int height(node* node)
{
    /* base case tree is empty */
    if(node == NULL)
        return 0;
    
    /* If tree is not empty then height = 1 + max of left
     height and right heights */
    return 1 + max(height(node->left), height(node->right));
}

/* Given two trees, return true if they are
 structurally identical */
int identicalTrees(node* a, node* b)
{
    /*1. both empty */
    if (a==NULL && b==NULL)
        return 1;
    
    /* 2. both non-empty -> compare them */
    if (a!=NULL && b!=NULL)
    {
        return
        (
         a->data == b->data &&
         identicalTrees(a->left, b->left) &&
         identicalTrees(a->right, b->right)
         );
    }
    
    /* 3. one empty, one not -> false */
    return 0;
}

/*  This function traverses tree in post order to
 to delete each and every node of the tree */
void deleteTree(node* node)
{
    if (node == NULL) return;
    
    /* first delete both subtrees */
    deleteTree(node->left);
    deleteTree(node->right);
    
    /* then delete the node */
    cout << "\n Deleting node : " << node->data;
    delete node;
}

void mirror(node* node)
{
    if (node==NULL)
        return;
    else
    {
        struct node* temp;
        
        /* do the subtrees */
        mirror(node->left);
        mirror(node->right);
        
        /* swap the pointers in this node */
        temp        = node->left;
        node->left  = node->right;
        node->right = temp;
    }
}


/* Helper function to test mirror(). Given a binary
 search tree, print out its data elements in
 increasing sorted order.*/
void inOrder(node* node)
{
    if (node == NULL)
        return;
    
    inOrder(node->left);
    cout << node->data << " ";
    inOrder(node->right);
}

/* Compute the "maxDepth" of a tree -- the number of
 nodes along the longest path from the root node
 down to the farthest leaf node.*/
int maxDepth(node* node)
{
    if (node==NULL)
        return 0;
    else
    {
        /* compute the depth of each subtree */
        int lDepth = maxDepth(node->left);
        int rDepth = maxDepth(node->right);
        
        /* use the larger one */
        if (lDepth > rDepth)
            return(lDepth+1);
        else return(rDepth+1);
    }
}

/* Recursive helper function -- given a node, and an array containing
 the path from the root node up to but not including this node,
 print out all the root-leaf paths. */
void printPathsRecur(node* node, int path[], int pathLen)
{
    if (node==NULL) return;
    
    /* append this node to the path array */
    path[pathLen] = node->data;
    pathLen++;
    
    /* it's a leaf, so print the path that led to here */
    if (node->left==NULL && node->right==NULL)
    {
        //printArray(path, pathLen);
    }
    else
    {
        /* otherwise try both subtrees */
        printPathsRecur(node->left, path, pathLen);
        printPathsRecur(node->right, path, pathLen);
    }
}



/* Given a binary tree, print out all of its root-to-leaf
 paths, one per line. Uses a recursive helper to do the work.*/
void printPaths(node* node)
{
    int path[1000];
    printPathsRecur(node, path, 0);
}


/* Given a binary tree, print its nodes in reverse level order */
bool isIsomorphic(node* n1, node *n2)
{
    // Both roots are NULL, trees isomorphic by definition
    if (n1 == NULL && n2 == NULL)
        return true;
    
    // Exactly one of the n1 and n2 is NULL, trees not isomorphic
    if (n1 == NULL || n2 == NULL)
        return false;
    
    if (n1->data != n2->data)
        return false;
    
    // There are two possible cases for n1 and n2 to be isomorphic
    // Case 1: The subtrees rooted at these nodes have NOT been "Flipped".
    // Both of these subtrees have to be isomorphic, hence the &&
    // Case 2: The subtrees rooted at these nodes have been "Flipped"
    return
    (isIsomorphic(n1->left,n2->left) && isIsomorphic(n1->right,n2->right))||
    (isIsomorphic(n1->left,n2->right) && isIsomorphic(n1->right,n2->left));
}

/* Get width of a given level */
int getWidth(node* root, int level)
{
    if(root == NULL)
        return 0;
    if(level == 1)
        return 1;
    else if (level > 1){
        return getWidth(root->left, level-1) + getWidth(root->right, level-1);
    }else{
        return 0;
    }
}


/* Function to get the maximum width of a binary tree*/
int getMaxWidth(node* root)
{
    int maxWidth = 0;
    int width;
    int h = height(root);
    int i;
    
    /* Get width of each level and compare
     the width with maximum width so far */
    for(i=1; i<=h; i++)
    {
        width = getWidth(root, i);
        if(width > maxWidth)
            maxWidth = width;
    }
    
    return maxWidth;
}

void printKDistant(node *root , int k)
{
    if(root == NULL)
        return;
    if( k == 0 )
    {
        printf( "%d ", root->data );
        return ;
    }
    else
    {
        printKDistant( root->left, k-1 ) ;
        printKDistant( root->right, k-1 ) ;
    }
}

/* Helper function for getLevel().  It returns level of the data if data is
 present in tree, otherwise returns 0.*/
int getLevelUtil(node *node, int data, int level)
{
    if (node == NULL)
        return 0;
    
    if (node->data == data)
        return level;
    
    int downlevel = getLevelUtil(node->left, data, level+1);
    if (downlevel != 0)
        return downlevel;
    
    downlevel = getLevelUtil(node->right, data, level+1);
    return downlevel;
}

/* Returns level of given data value */
int getLevel(node *node, int data)
{
    return getLevelUtil(node,data,1);
}

/* If target is present in tree, then prints the ancestors
 and returns true, otherwise returns false. */
bool printAncestors(node *root, int target)
{
    /* base cases */
    if (root == NULL)
        return false;
    
    if (root->data == target)
        return true;
    
    /* If target is present in either left or right subtree of this node,
     then print this node */
    if ( printAncestors(root->left, target) ||
        printAncestors(root->right, target) )
    {
        cout << root->data << " ";
        return true;
    }
    
    /* Else return false */
    return false;
}

/* A utility function to get the sum of values in tree with root
 as root */
int sum(node *root)
{
    if(root == NULL)
        return 0;
    return sum(root->left) + root->data + sum(root->right);
}

/* returns 1 if sum property holds for the given
 node and both of its children */
int isSumTree(node* node)
{
    int ls, rs;
    
    /* If node is NULL or it's a leaf node then
     return true */
    if(node == NULL ||
       (node->left == NULL && node->right == NULL))
        return 1;
    
    /* Get sum of nodes in left and right subtrees */
    ls = sum(node->left);
    rs = sum(node->right);
    
    /* if the node and both of its children satisfy the
     property return 1 else 0*/
    if((node->data == ls + rs)&&
       isSumTree(node->left) &&
       isSumTree(node->right))
        return 1;
    
    return 0;
}

/* This function returns true if S is a subtree of T, otherwise false */
bool isSubtree(node *T, node *S)
{
    /* base cases */
    if (S == NULL)
        return true;
    
    if (T == NULL)
        return false;
    
    /* Check the tree with root as current node */
    //if (areIdentical(T, S))return true;
    
    /* If the tree with root as current node doesn't match then
     try left and right subtrees one by one */
    return isSubtree(T->left, S) ||
    isSubtree(T->right, S);
}

/* Driver program to test size function*/
int main()
{
    node *root = newNode(1);
    root->left        = newNode(2);
    root->right       = newNode(3);
    root->left->left  = newNode(4);
    root->left->right = newNode(5);
    cout << "Size of the tree is " << size(root);
    getchar();
    return 0;
}