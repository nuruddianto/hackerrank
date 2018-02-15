//
//  tree-post-order-traversal.cpp
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
} node;

/* Helper function that allocates a new node with the
 given data and NULL left and right pointers. */
node* newNode(int data)
{
    node* n = new node();
    n->data = data;
    n->left = NULL;
    n->right = NULL;
    return(n);
}

/* Given a binary tree, print its nodes according to the
 "bottom-up" postorder traversal. */
void printPostorder(node* node)
{
    if (node == NULL)
        return;
    
    // first recur on left subtree
    printPostorder(node->left);
    
    // then recur on right subtree
    printPostorder(node->right);
    
    // now deal with the node
    cout << node->data << " ";
}

/* Given a binary tree, print its nodes in inorder*/
void printInorder(node* node)
{
    if (node == NULL)
        return;
    
    /* first recur on left child */
    printInorder(node->left);
    
    /* then print the data of node */
    cout << node->data << " ";
    
    /* now recur on right child */
    printInorder(node->right);
}

/* Given a binary tree, print its nodes in preorder*/
void printPreorder(node* node)
{
    if (node == NULL)
        return;
    
    /* first print data of node */
    cout << node->data << " ";
   
    /* then recur on left sutree */
    printPreorder(node->left);
    
    /* now recur on right subtree */
    printPreorder(node->right);
}

/* Driver program to test above functions*/
int main()
{
    node *root  = newNode(1);
    root->left          = newNode(2);
    root->right         = newNode(3);
    root->left->left    = newNode(4);
    root->left->right   = newNode(5);
    
    cout <<  "\n Preorder traversal of binary tree is \n";
    printPreorder(root);
    
    cout << "\n Inorder traversal of binary tree is \n";
    printInorder(root);
    
    cout << "\n Postorder traversal of binary tree is \n";
    printPostorder(root);
    
    getchar();
    return 0;
}