//
//  BST-k-th-smallest-element.cpp
//  SWTest
//
//  Created by Risman Adnan on 7/15/15.
//  Copyright (c) 2015 Risman Adnan. All rights reserved.
//

/*
 Method 1: Using Inorder Traversal.
 
 Inorder traversal of BST retrieves elements of tree in the sorted order. The inorder traversal uses stack to store to be explored nodes of tree (threaded tree avoids stack and recursion for traversal, see this post). The idea is to keep track of popped elements which participate in the order statics. Hypothetical algorithm is provided below,
 
 Time complexity: O(n) where n is total nodes in tree..
 
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

#define ARRAY_SIZE(arr) sizeof(arr)/sizeof(arr[0])

/* just add elements to test */
/* NOTE: A sorted array results in skewed tree */
int ele[] = { 20, 8, 22, 4, 12, 10, 14 };

/* same alias */
typedef struct node_t node_t;

/* Binary tree node */
typedef struct node_t
{
    int data;
    
    node_t* left;
    node_t* right;
}node_t;


/* initial element always NULL, uses as sentinal */
typedef struct stack_tt
{
    node_t*  base[ARRAY_SIZE(ele) + 1];
    int      stackIndex;
}stack_tt;

/* pop operation of stack */
node_t *pop(stack_tt *st)
{
    node_t *ret = NULL;
    
    if( st && st->stackIndex > 0 )
    {
        ret = st->base[st->stackIndex];
        st->stackIndex--;
    }
    
    return ret;
}

/* push operation of stack */
void push(stack_tt *st, node_t *node)
{
    if( st )
    {
        st->stackIndex++;
        st->base[st->stackIndex] = node;
    }
}

/* Iterative insertion
 Recursion is least preferred unless we gain something
 */
node_t *insert_node(node_t *root, node_t* node)
{
    /* A crawling pointer */
    node_t *pTraverse = root;
    node_t *currentParent = root;
    
    // Traverse till appropriate node
    while(pTraverse)
    {
        currentParent = pTraverse;
        
        if( node->data < pTraverse->data )
        {
            /* left subtree */
            pTraverse = pTraverse->left;
        }
        else
        {
            /* right subtree */
            pTraverse = pTraverse->right;
        }
    }
    
    /* If the tree is empty, make it as root node */
    if( !root )
    {
        root = node;
    }
    else if( node->data < currentParent->data )
    {
        /* Insert on left side */
        currentParent->left = node;
    }
    else
    {
        /* Insert on right side */
        currentParent->right = node;
    }
    
    return root;
}

/* Elements are in an array. The function builds binary tree */
node_t* binary_search_tree(node_t *root, int keys[], int const size)
{
    int iterator;
    node_t *new_node = NULL;
    
    for(iterator = 0; iterator < size; iterator++)
    {
        new_node = (node_t *)malloc( sizeof(node_t) );
        
        /* initialize */
        new_node->data   = keys[iterator];
        new_node->left   = NULL;
        new_node->right  = NULL;
        
        /* insert into BST */
        root = insert_node(root, new_node);
    }
    
    return root;
}

node_t *k_smallest_element_inorder(stack_tt *stack, node_t *root, int k)
{
    stack_tt *st = stack;
    node_t *pCrawl = root;
    
    /* move to left extremen (minimum) */
    while( pCrawl )
    {
        push(st, pCrawl);
        pCrawl = pCrawl->left;
    }
    
    /* pop off stack and process each node */
    while( pCrawl == pop(st) )
    {
        /* each pop operation emits one element
         in the order
         */
        if( !--k )
        {
            /* loop testing */
            st->stackIndex = 0;
            break;
        }
        
        /* there is right subtree */
        if( pCrawl->right )
        {
            /* push the left subtree of right subtree */
            pCrawl = pCrawl->right;
            while( pCrawl )
            {
                push(st, pCrawl);
                pCrawl = pCrawl->left;
            }
            
            /* pop off stack and repeat */
        }
    }
    
    /* node having k-th element or NULL node */
    return pCrawl;
}

/* Driver program to test above functions */
int main(void)
{
    node_t* root = NULL;
    stack_tt stack = { {0}, 0 };
    node_t *kNode = NULL;
    
    int k = 2;
    
    /* Creating the tree given in the above diagram */
    root = binary_search_tree(root, ele, ARRAY_SIZE(ele));
    
    kNode = k_smallest_element_inorder(&stack, root, k);
    
    if( kNode )
    {
        cout << "\n kth smallest element for k = " << k << " is " << kNode->data;
    }
    else
    {
        cout << "There is no such element";
    }
    
    getchar();
    return 0;
}

