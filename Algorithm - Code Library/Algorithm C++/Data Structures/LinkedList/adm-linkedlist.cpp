// Simple linked list program with generic type defined by item_type.
//  linkedlist.cpp
//  Created by Risman Adnan on 7/9/15.
//  Copyright (c) 2015 Risman Adnan. All rights reserved.

#include<iostream>

#define TRUE    1
#define FALSE   0

using namespace std;

typedef int item_type;

typedef struct list {
    item_type item;			/* data item */
    struct list *next;		/* point to successor */
} list;

list *init_list(){
    return(nullptr);
}

bool empty_list(list *l){
    if (l == nullptr) return (TRUE);
    else return (FALSE);
}

list *search_list(list *l, item_type x){
    if (l == nullptr) return(nullptr);
    
    if (l->item == x)
        return(l);
    else
        return( search_list(l->next, x) );
}


list *predecessor_list(list *l, item_type x){
    if ((l == nullptr) || (l->next == nullptr)) {
        cout << "Error: predecessor sought on null list." << endl;
        return(nullptr);
    }
    
    if ((l->next)->item == x)
        return(l);
    else
        return( predecessor_list(l->next, x) );
}


void insert_list(list **l, item_type x){
    list *p;			/* temporary pointer */
    p = new list();
    p->item = x;
    p->next = *l;
    *l = p;
}

void print_list(list *l){
    while (l != nullptr) {
        cout << l->item << " ";
        l = l->next;
    }
    cout << endl;
}


void delete_list(list **l, item_type x){
    list *p;			/* item pointer */
    list *pred;			/* predecessor pointer */
    
    p = search_list(*l,x);
    if (p != nullptr) {
        pred = predecessor_list(*l,x);
        if (pred == NULL)	/* splice out out list */
            *l = p->next;
        else
            pred->next = p->next;
        
        delete p;
    }
}

int main(){
    item_type d;	/* input item */
    list *l;		/* list under construction */
    list *tmp;		/* returned list from search */
    d = 10;
    tmp = nullptr;
    l = init_list();
    for(int i = 0;i<10;i++){
        insert_list(&l, i*d);
    }
    print_list(l);
    search_list(l, 30);
    delete_list(&l,20);
    print_list(l);
}



