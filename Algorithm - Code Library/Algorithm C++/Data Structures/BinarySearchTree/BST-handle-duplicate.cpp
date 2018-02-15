//
//  BST-handle-duplicate.cpp
//  SWTest
//
//  Created by Risman Adnan on 7/15/15.
//  Copyright (c) 2015 Risman Adnan. All rights reserved.
//

// C program to implement basic operations (search, insert and delete)
// on a BST that handles duplicates by storing count with every node

#include<cstdio>
#include<cstdlib>
#include<iostream>

using namespace std;


typedef struct node
{
    int key;
    int count;
    node *left, *right;
}node;

// A utility function to create a new BST node
node *newNode(int item)
{
    node *temp =  new node();
    temp->key = item;
    temp->left = temp->right = NULL;
    temp->count = 1;
    return temp;
}

// A utility function to do inorder traversal of BST
void inorder(node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        cout << root->key << "(" << root->count <<")";
        inorder(root->right);
    }
}

/* A utility function to insert a new node with given key in BST */
node* insert(node* node, int key)
{
    /* If the tree is empty, return a new node */
    if (node == NULL) return newNode(key);
    
    // If key already exists in BST, icnrement count and return
    if (key == node->key)
    {
        (node->count)++;
        return node;
    }
    
    /* Otherwise, recur down the tree */
    if (key < node->key)
        node->left  = insert(node->left, key);
    else
        node->right = insert(node->right, key);
    
    /* return the (unchanged) node pointer */
    return node;
}

/* Given a non-empty binary search tree, return the node with
 minimum key value found in that tree. Note that the entire
 tree does not need to be searched. */
node *minValueNode(node* n)
{
    node* current = n;
    
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
    
    return current;
}

/* Given a binary search tree and a key, this function
 deletes a given key and returns root of modified tree */
node* deleteNode(node* root, int key)
{
    // base case
    if (root == NULL) return root;
    
    // If the key to be deleted is smaller than the
    // root's key, then it lies in left subtree
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    
    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    
    // if key is same as root's key
    else
    {
        // If key is present more than once, simply decrement
        // count and return
        if (root->count > 1)
        {
            (root->count)--;
            return root;
        }
        
        // ElSE, delete the node
        
        // node with only one child or no child
        if (root->left == NULL)
        {
            node *temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL)
        {
            node *temp = root->left;
            delete root;
            return temp;
        }
        
        // node with two children: Get the inorder successor (smallest
        // in the right subtree)
        node* temp = minValueNode(root->right);
        
        // Copy the inorder successor's content to this node
        root->key = temp->key;
        
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

// Driver Program to test above functions
int main()
{
    /* Let us create following BST
     12(3)
     /        \
     10(2)      20(1)
     /   \
     9(1)  11(1)   */
    node *root = NULL;
    root = insert(root, 12);
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 9);
    root = insert(root, 11);
    root = insert(root, 10);
    root = insert(root, 12);
    root = insert(root, 12);
    
    cout << "Inorder traversal of the given tree \n";
    inorder(root);
    
    cout << "\nDelete 20\n";
    root = deleteNode(root, 20);
    cout << "Inorder traversal of the modified tree \n";
    inorder(root);
    
    cout << "\nDelete 12\n";
    root = deleteNode(root, 12);
    cout << "Inorder traversal of the modified tree \n";
    inorder(root);
    
    cout << "\nDelete 9\n";
    root = deleteNode(root, 9);
    cout << "Inorder traversal of the modified tree \n";
    inorder(root);
    
    return 0;
}