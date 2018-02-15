//
//  tree.cpp
//  Contekan
//
//  Created by Risman Adnan on 7/9/15.
//  Copyright (c) 2015 Risman Adnan. All rights reserved.
//

#include<iostream>

using namespace std;

#define TRUE    1
#define FALSE   0

typedef int item_type;

typedef struct tree {
    item_type item;     /* data item */
    tree *parent;       /* pointer to parent */
    tree *left;         /* pointer to left child */
    tree *right;        /* pointer to right child */
} tree;

tree *parent;               /* last node visited */

tree *init_tree(){
    return(nullptr);
}

bool empty_tree(tree *t){
    if (t == nullptr) return (TRUE);
    else return (FALSE);
}

tree *search_tree(tree *l, item_type x){
    if (l == nullptr) return(nullptr);
    
    if (l->item == x) return(l);
    
    if (x < l->item)
        return( search_tree(l->left, x) );
    else
        return( search_tree(l->right, x) );
}

void traverse_tree(tree *l){
    if (l != nullptr) {
        traverse_tree(l->left);
        //process_item(l->item);
        traverse_tree(l->right);
    }
}

void insert_tree(tree **l, item_type x, tree *parent){
    tree *p;            /* temporary pointer */
    
    if (*l == nullptr) {
        p = new tree();
        p->item = x;
        p->left = p->right = nullptr;
        p->parent = parent;
        *l = p;
        return;
    }
    
    if (x < (*l)->item)
        insert_tree(&((*l)->left), x, *l);
    else
        insert_tree(&((*l)->right), x, *l);
}


void print_tree(tree *l){
    if (l != nullptr) {
        cout << l->left;
        cout << l->item;
        print_tree(l->right);
    }
    
}

tree *successor_descendant(tree *t){
    tree *succ;         /* successor pointer */
    
    if (t->right == nullptr) return(nullptr);
    succ = t->right;
    while (succ->left != nullptr)
        succ = succ->left;
    return(succ);
}

tree *find_minimum(tree *t){
    tree *min;                     /* pointer to minimum */
    
    if (t == nullptr) return(nullptr);
    
    min = t;
    while (min->left != nullptr)
        min = min->left;
    return(min);
}


tree *predecessor_descendant(tree *t){
    tree *pred;                     /* predecessor pointer */
    
    if (t->left == nullptr) return(nullptr);
    
    pred = t->left;
    while (pred->right != nullptr)
        pred = pred->right;
    return(pred);
}


tree *delete_tree(tree *t, item_type x){
    tree *d;                /* node with key to delete */
    tree *p;                /* node to be physically deleted */
    item_type new_key;      /* key to overwrite deleted key */
    tree *child;            /* d's only child, if any */
    
    d = search_tree(t,x);
    
    if (d == nullptr) {
        cout << "Warning: key to be deleted %d is not in tree." << x << endl;
        return(t);
    }
    
    if (d->parent == nullptr) { /* if d is the root */
        if ((d->left == nullptr) && (d->right == nullptr)) {
            delete d;
            return nullptr; /* root-only tree */
        }
        
        if (d->left != nullptr)     /* find node to physically delete */
            p = predecessor_descendant(d);
        else
            p = successor_descendant(d);
    } else {
        if ((d->left == nullptr) || (d->right == nullptr)) {
            /* d has <=1 child, so try to find non-null child */
            if (d->left != nullptr)
                child = d->left;
            else
                child = d->right;
            
            if ((d->parent)->left == d) {   /* fill null pointer */
                d->parent->left = child;
            }
            else {
                d->parent->right = child;
            }
            if (child != nullptr) child->parent = d->parent;
            
            delete d;
            return(t);
        }
        else {
            p = successor_descendant(d);    /* p has 2 children */
        }
    }
    
    new_key = p->item;      /* deal with simpler case of deletion */
    delete_tree(t, p->item);
    d->item = new_key;
    return (t);
}


/* if ((t->left == nullptr) && (t->right == nullptr)) */
/*                 troot = nullptr; */
/*         else */
/*                 troot = t;       /\* identify root of returned tree *\/ */


/*  if (d->left != nullptr) {       /\* copy rightmost left descendant over d *\/ */
/*      p = d->left; */
/*      while (p->right != nullptr)  */
/*          p = p->right; */
/*      d->item = p->item; */
/*      (p->parent)->right = p->left; */
/*  } */
/*  else if (d->right != nullptr) { /\* copy leftmost right descendant over d *\/ */
/*      p = d->right; */
/*      while (p->left != nullptr) */
/*          p = p->left; */
/*      d->item = p->item; */
/*      (p->parent)->left = p->right; */
/*  } */
/*  else {              /\* leaf deletion *\/ */
/*      if (d->parent != nullptr) { */
/*          if ((d->parent)->left == d) */
/*              (d->parent)->left == nullptr; */
/*          else */
/*              (d->parent)->right == nullptr; */
/*      } */
/*      p = d; */
/*  } */

/*  delete p; */
/*  return(troot); */

int main()
{
    item_type d;            /* input item */
    tree *l;        /* tree under construction */
    tree *tmp;      /* returned tree from search */
    l = init_tree();
}






