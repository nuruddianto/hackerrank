//
//  Binary Search Tree Implementation with Common Operations
//
//  Created by Risman Adnan on 7/15/15.
//  Copyright (c) 2015 Risman Adnan. All rights reserved.
//

#include<cstdio>
#include<cstdlib>
#include<iostream>

using namespace std;

typedef struct node
{
    int key;
    struct node *left, *right;
}node;

// A utility function to create a new BST node
node *newNode(int item)
{
    node *temp =  new node();
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

// A utility function to do inorder traversal of BST
void inorder(struct node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        cout << root->key << " " ;
        inorder(root->right);
    }
}

/* A utility function to insert a new node with given key in BST */
node* insert(node* node, int key)
{
    /* If the tree is empty, return a new node */
    if (node == NULL) return newNode(key);
    
    /* Otherwise, recur down the tree */
    if (key < node->key)
        node->left  = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    
    /* return the (unchanged) node pointer */
    return node;
}

/* Given a non-empty binary search tree, return the node with minimum
 key value found in that tree. Note that the entire tree does not
 need to be searched. */
node *minValueNode(node* n)
{
    node* current = n;
    
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
    
    return current;
}

/* Given a binary search tree and a key, this function deletes the key
 and returns the new root */
node* deleteNode(node* root, int key)
{
    // base case
    if (root == NULL) return root;
    
    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    
    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    
    // if key is same as root's key, then This is the node
    // to be deleted
    else
    {
        // node with only one child or no child
        if (root->left == NULL)
        {
            struct node *temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL)
        {
            struct node *temp = root->left;
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


/* Given a non-empty binary search tree,
 return the minimum data value found in that
 tree. Note that the entire tree does not need
 to be searched. */
int minValue(struct node* n) {
    node* current = n;
    
    /* loop down to find the leftmost leaf */
    while (current->left != NULL) {
        current = current->left;
    }
    return(current->key);
}

// This function finds predecessor and successor of key in BST.
// It sets pre and suc as predecessor and successor respectively
void findPreSuc(node* root, node*& pre, node*& suc, int key)
{
    // Base case
    if (root == NULL)  return ;
    
    // If key is present at root
    if (root->key == key)
    {
        // the maximum value in left subtree is predecessor
        if (root->left != NULL)
        {
            node* tmp = root->left;
            while (tmp->right)
                tmp = tmp->right;
            pre = tmp ;
        }
        
        // the minimum value in right subtree is successor
        if (root->right != NULL)
        {
            node* tmp = root->right ;
            while (tmp->left)
                tmp = tmp->left ;
            suc = tmp ;
        }
        return ;
    }
    
    // If key is smaller than root's key, go to left subtree
    if (root->key > key)
    {
        suc = root ;
        findPreSuc(root->left, pre, suc, key) ;
    }
    else // go to right subtree
    {
        pre = root ;
        findPreSuc(root->right, pre, suc, key) ;
    }
}



int isBSTUtil(node* node, int min, int max);

/* Returns true if the given tree is a binary search tree
 (efficient version). */
int isBST(node* node)
{
    return(isBSTUtil(node, INT_MIN, INT_MAX));
}

/* Returns true if the given tree is a BST and its
 values are >= min and <= max. */
int isBSTUtil(node* node, int min, int max)
{
    
    /* an empty tree is BST */
    if (node==NULL)
        return 1;
    
    /* false if this node violates the min/max constraint */
    if (node->key < min || node->key > max)
        return 0;
    
    /* otherwise check the subtrees recursively,
     tightening the min or max constraint */
    return
    isBSTUtil(node->left, min, node->key-1) &&  // Allow only distinct values
    isBSTUtil(node->right, node->key+1, max);  // Allow only distinct values
}



// Lowest Common Ancestor in BST
/* Function to find LCA of n1 and n2. The function assumes that both
 n1 and n2 are present in BST */
node *lca(node* root, int n1, int n2)
{
    if (root == NULL) return NULL;
    
    // If both n1 and n2 are smaller than root, then LCA lies in left
    if (root->key > n1 && root->key > n2)
        return lca(root->left, n1, n2);
    
    // If both n1 and n2 are greater than root, then LCA lies in right
    if (root->key < n1 && root->key < n2)
        return lca(root->right, n1, n2);
    
    return root;
}


/* The functions prints all the keys which in the given range [k1..k2].
 The function assumes than k1 < k2 */
void Print(node *root, int k1, int k2)
{
    /* base case */
    if ( NULL == root )
        return;
    
    /* Since the desired o/p is sorted, recurse for left subtree first
     If root->data is greater than k1, then only we can get o/p keys
     in left subtree */
    if ( k1 < root->key )
        Print(root->left, k1, k2);
    
    /* if root's data lies in range, then prints root's data */
    if ( k1 <= root->key && k2 >= root->key )
        cout << root->key << " ";
    /* If root->data is smaller than k2, then only we can get o/p keys
     in right subtree */
    if ( k2 > root->key)
        Print(root->right, k1, k2);
}


/* A function that constructs Balanced Binary Search Tree from a sorted array */
node* sortedArrayToBST(int arr[], int start, int end)
{
    /* Base Case */
    if (start > end)
        return NULL;
    
    /* Get the middle element and make it root */
    int mid = (start + end)/2;
    struct node *root = newNode(arr[mid]);
    
    /* Recursively construct the left subtree and make it
     left child of root */
    root->left =  sortedArrayToBST(arr, start, mid-1);
    
    /* Recursively construct the right subtree and make it
     right child of root */
    root->right = sortedArrayToBST(arr, mid+1, end);
    
    return root;
}


/* largestBSTUtil() updates *max_size_ref for the size of the largest BST
 subtree.   Also, if the tree rooted with node is non-empty and a BST,
 then returns size of the tree. Otherwise returns 0.*/
int largestBSTUtil(node* node, int *min_ref, int *max_ref, int *max_size_ref, bool *is_bst_ref)
{
    
    /* Base Case */
    if (node == NULL)
    {
        *is_bst_ref = 1; // An empty tree is BST
        return 0;    // Size of the BST is 0
    }
    
    int min = INT_MAX;
    
    /* A flag variable for left subtree property
     i.e., max(root->left) < root->data */
    bool left_flag = false;
    
    /* A flag variable for right subtree property
     i.e., min(root->right) > root->data */
    bool right_flag = false;
    
    int ls, rs; // To store sizes of left and right subtrees
    
    /* Following tasks are done by recursive call for left subtree
     a) Get the maximum value in left subtree (Stored in *max_ref)
     b) Check whether Left Subtree is BST or not (Stored in *is_bst_ref)
     c) Get the size of maximum size BST in left subtree (updates *max_size) */
    *max_ref = INT_MIN;
    ls = largestBSTUtil(node->left, min_ref, max_ref, max_size_ref, is_bst_ref);
    if (*is_bst_ref == 1 && node->key > *max_ref)
        left_flag = true;
    
    /* Before updating *min_ref, store the min value in left subtree. So that we
     have the correct minimum value for this subtree */
    min = *min_ref;
    
    /* The following recursive call does similar (similar to left subtree)
     task for right subtree */
    *min_ref =  INT_MAX;
    rs = largestBSTUtil(node->right, min_ref, max_ref, max_size_ref, is_bst_ref);
    if (*is_bst_ref == 1 && node->key < *min_ref)
        right_flag = true;
    
    // Update min and max values for the parent recursive calls
    if (min < *min_ref)
        *min_ref = min;
    if (node->key < *min_ref) // For leaf nodes
        *min_ref = node->key;
    if (node->key > *max_ref)
        *max_ref = node->key;
    
    /* If both left and right subtrees are BST. And left and right
     subtree properties hold for this node, then this tree is BST.
     So return the size of this tree */
    if(left_flag && right_flag)
    {
        if (ls + rs + 1 > *max_size_ref)
            *max_size_ref = ls + rs + 1;
        return ls + rs + 1;
    }
    else
    {
        //Since this subtree is not BST, set is_bst flag for parent calls
        *is_bst_ref = 0;
        return 0;
    }
}



/* Returns size of the largest BST subtree in a Binary Tree
 (efficient version). */
int largestBST(node* node)
{
    // Set the initial values for calling largestBSTUtil()
    int min = INT_MAX;  // For minimum value in right subtree
    int max = INT_MIN;  // For maximum value in left subtree
    
    int max_size = 0;  // For size of the largest BST
    bool is_bst = 0;
    
    largestBSTUtil(node, &min, &max, &max_size, &is_bst);
    
    return max_size;
}
// Recursive function to add all greater values in every node
void modifyBSTUtil(struct node *root, int *sum)
{
    // Base Case
    if (root == NULL)  return;
    
    // Recur for right subtree
    modifyBSTUtil(root->right, sum);
    
    // Now *sum has sum of nodes in right subtree, add
    // root->data to sum and update root->data
    *sum = *sum + root->key;
    root->key = *sum;
    
    // Recur for left subtree
    modifyBSTUtil(root->left, sum);
}

// A wrapper over modifyBSTUtil()
void modifyBST(node *root)
{
    int sum = 0;
    modifyBSTUtil(root, &sum);
}



// Resmoves all nodes having value outside the given range and returns the root
// of modified tree
node* removeOutsideRange(node *root, int min, int max)
{
    // Base Case
    if (root == NULL)
        return NULL;
    
    // First fix the left and right subtrees of root
    root->left =  removeOutsideRange(root->left, min, max);
    root->right =  removeOutsideRange(root->right, min, max);
    
    // Now fix the root.  There are 2 possible cases for toot
    // 1.a) Root's key is smaller than min value (root is not in range)
    if (root->key < min)
    {
        node *rChild = root->right;
        delete root;
        return rChild;
    }
    // 1.b) Root's key is greater than max value (root is not in range)
    if (root->key > max)
    {
        node *lChild = root->left;
        delete root;
        return lChild;
    }
    // 2. Root is in range
    return root;
}


// A function to convert given BST to Doubly Linked List. left pointer is used
// as previous pointer and right pointer is used as next pointer. The function
// sets *head to point to first and *tail to point to last node of converted DLL
void convertBSTtoDLL(node* root, node** head, node** tail)
{
    // Base case
    if (root == NULL)
        return;
    
    // First convert the left subtree
    if (root->left)
        convertBSTtoDLL(root->left, head, tail);
    
    // Then change left of current root as last node of left subtree
    root->left = *tail;
    
    // If tail is not NULL, then set right of tail as root, else current
    // node is head
    if (*tail)
        (*tail)->right = root;
    else
        *head = root;
    
    // Update tail
    *tail = root;
    
    // Finally, convert right subtree
    if (root->right)
        convertBSTtoDLL(root->right, head, tail);
}

// This function returns true if there is pair in DLL with sum equal
// to given sum. The algorithm is similar to hasArrayTwoCandidates()
// in method 1 of http://tinyurl.com/dy6palr
bool isPresentInDLL(node* head, node* tail, int sum)
{
    while (head != tail)
    {
        int curr = head->key + tail->key;
        if (curr == sum)
            return true;
        else if (curr > sum)
            tail = tail->left;
        else
            head = head->right;
    }
    return false;
}

// The main function that returns true if there is a 0 sum triplet in
// BST otherwise returns false
bool isTripletPresent(node *root)
{
    // Check if the given  BST is empty
    if (root == NULL)
        return false;
    
    // Convert given BST to doubly linked list.  head and tail store the
    // pointers to first and last nodes in DLLL
    node* head = NULL;
    node* tail = NULL;
    convertBSTtoDLL(root, &head, &tail);
    
    // Now iterate through every node and find if there is a pair with sum
    // equal to -1 * heaf->key where head is current node
    while ((head->right != tail) && (head->key < 0))
    {
        // If there is a pair with sum equal to  -1*head->key, then return
        // true else move forward
        if (isPresentInDLL(head->right, tail, -1*head->key))
            return true;
        else
            head = head->right;
    }
    
    // If we reach here, then there was no 0 sum triplet
    return false;
}


// A utility function to swap two integers
void swap( int* a, int* b )
{
    int t = *a;
    *a = *b;
    *b = t;
}


// This function does inorder traversal to find out the two swapped nodes.
// It sets three pointers, first, middle and last.  If the swapped nodes are
// adjacent to each other, then first and middle contain the resultant nodes
// Else, first and last contain the resultant nodes
void correctBSTUtil(node* root, node** first,node** middle, node** last,node** prev){
    if( root )
    {
        // Recur for the left subtree
        correctBSTUtil( root->left, first, middle, last, prev );
        
        // If this node is smaller than the previous node, it's violating
        // the BST rule.
        if (*prev && root->key < (*prev)->key)
        {
            // If this is first violation, mark these two nodes as
            // 'first' and 'middle'
            if ( !*first )
            {
                *first = *prev;
                *middle = root;
            }
            
            // If this is second violation, mark this node as last
            else
                *last = root;
        }
        
        // Mark this node as previous
        *prev = root;
        
        // Recur for the right subtree
        correctBSTUtil( root->right, first, middle, last, prev );
    }
}

// A function to fix a given BST where two nodes are swapped.  This
// function uses correctBSTUtil() to find out two nodes and swaps the
// nodes to fix the BST
void correctBST(node* root)
{
    // Initialize pointers needed for correctBSTUtil()
    struct node *first, *middle, *last, *prev;
    first = middle = last = prev = NULL;
    
    // Set the poiters to find out two nodes
    correctBSTUtil( root, &first, &middle, &last, &prev );
    
    // Fix (or correct) the tree
    if( first && last )
        swap( &(first->key), &(last->key) );
    else if( first && middle ) // Adjacent nodes swapped
        swap( &(first->key), &(middle->key) );
    
    // else nodes have not been swapped, passed tree is really BST.
}


// A recursive function to construct Full from pre[]. preIndex is used
// to keep track of index in pre[].
node* constructTreeUtil (int pre[], int* preIndex, int low, int high, int size){
    // Base case
    if (*preIndex >= size || low > high)
        return NULL;
    
    // The first node in preorder traversal is root. So take the node at
    // preIndex from pre[] and make it root, and increment preIndex
    struct node* root = newNode ( pre[*preIndex] );
    *preIndex = *preIndex + 1;
    
    // If the current subarry has only one element, no need to recur
    if (low == high)
        return root;
    
    // Search for the first element greater than root
    int i;
    for ( i = low; i <= high; ++i )
        if ( pre[ i ] > root->key )
            break;
    
    // Use the index of element found in postorder to divide postorder array in
    // two parts. Left subtree and right subtree
    root->left = constructTreeUtil ( pre, preIndex, *preIndex, i - 1, size );
    root->right = constructTreeUtil ( pre, preIndex, i, high, size );
    
    return root;
}

// The main function to construct BST from given preorder traversal.
// This function mainly uses constructTreeUtil()
node *constructTree (int pre[], int size)
{
    int preIndex = 0;
    return constructTreeUtil (pre, &preIndex, 0, size - 1, size);
}

// A utility function to print inorder traversal of a Binary Tree
void printInorder (node* node)
{
    if (node == NULL)
        return;
    printInorder(node->left);
    cout << node->key << " ";
    printInorder(node->right);
}


// Function to find ceil of a given input in BST. If input is more
// than the max key in BST, return -1
int Ceil(node *root, int input)
{
    // Base case
    if( root == NULL )
        return -1;
    
    // We found equal key
    if( root->key == input )
        return root->key;
    
    // If root's key is smaller, ceil must be in right subtree
    if( root->key < input )
        return Ceil(root->right, input);
    
    // Else, either left subtree or root has the ceil value
    int ceil = Ceil(root->left, input);
    return (ceil >= input) ? ceil : root->key;
}

// Driver Program to test above functions
int main()
{
    /* Let us create following BST
     50
     /     \
     30      70
     /  \    /  \
     20   40  60   80 */
    struct node *root = NULL;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);
    
    // print inoder traversal of the BST
    inorder(root);
    
    return 0;
}