//
//  datastructure-check-complete-binary-tree.cpp
//  SWTest
//
//  Created by Risman Adnan on 7/15/15.
//  Copyright (c) 2015 Risman Adnan. All rights reserved.
//

// A program to check if a given binary tree is complete or not

#include <cstdio>
#include <cstdlib>
#include <cstdbool>

#define MAX_Q_SIZE 500

/* A binary tree node has data, pointer to left child
 and a pointer to right child */
struct node
{
    int data;
    node* left;
    node* right;
};

/* frunction prototypes for functions needed for Queue data
 structure. A queue is needed for level order tarversal */
node** createQueue(int *, int *);
void enQueue(node **, int *, node *);
node *deQueue(node **, int *);
bool isQueueEmpty(int *front, int *rear);

/* Given a binary tree, return true if the tree is complete
 else false */
bool isCompleteBT(node* root)
{
    // Base Case: An empty tree is complete Binary Tree
    if (root == NULL)
        return true;
    
    // Create an empty queue
    int rear, front;
    node **queue = createQueue(&front, &rear);
    
    // Create a flag variable which will be set true
    // when a non full node is seen
    bool flag = false;
    
    // Do level order traversal using queue.
    enQueue(queue, &rear, root);
    while(!isQueueEmpty(&front, &rear))
    {
        node *temp_node = deQueue(queue, &front);
        
        /* Ceck if left child is present*/
        if(temp_node->left)
        {
            // If we have seen a non full node, and we see a node
            // with non-empty left child, then the given tree is not
            // a complete Binary Tree
            if (flag == true)
                return false;
            
            enQueue(queue, &rear, temp_node->left);  // Enqueue Left Child
        }
        else // If this a non-full node, set the flag as true
            flag = true;
        
        /* Ceck if right child is present*/
        if(temp_node->right)
        {
            // If we have seen a non full node, and we see a node
            // with non-empty left child, then the given tree is not
            // a complete Binary Tree
            if(flag == true)
                return false;
            
            enQueue(queue, &rear, temp_node->right);  // Enqueue Right Child
        }
        else // If this a non-full node, set the flag as true
            flag = true;
    }
    
    // If we reach here, then the tree is complete Bianry Tree
    return true;
}


/*UTILITY FUNCTIONS*/
node** createQueue(int *front, int *rear)
{
    node **queue =(node **)malloc(sizeof(struct node*)*MAX_Q_SIZE);
    
    *front = *rear = 0;
    return queue;
}

void enQueue(node **queue, int *rear, node *new_node)
{
    queue[*rear] = new_node;
    (*rear)++;
}

node *deQueue(node **queue, int *front)
{
    (*front)++;
    return queue[*front - 1];
}

bool isQueueEmpty(int *front, int *rear)
{
    return (*rear == *front);
}

/* Helper function that allocates a new node with the
 given data and NULL left and right pointers. */
node* newNode(int data)
{
    node* node = (struct node*)malloc(sizeof(node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    
    return(node);
}

/* Driver program to test above functions*/
int main()
{
    /* Let us construct the following Binary Tree which
     is not a complete Binary Tree
     1
     /   \
     2     3
     / \     \
     4   5     6
     */
    
    node *root  = newNode(1);
    root->left         = newNode(2);
    root->right        = newNode(3);
    root->left->left   = newNode(4);
    root->left->right  = newNode(5);
    root->right->right = newNode(6);
    
    if ( isCompleteBT(root) == true )
        printf ("Complete Binary Tree");
    else
        printf ("NOT Complete Binary Tree");
    
    return 0;
}