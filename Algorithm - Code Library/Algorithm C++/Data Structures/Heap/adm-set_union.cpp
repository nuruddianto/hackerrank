//
//  Set Union - Heap / Priority Queue.cpp
//  Implementation of a heap / priority queue abstract data type.
//  Contekan
//
//  Created by Risman Adnan on 7/9/15.
//  Copyright (c) 2015 Risman Adnan. All rights reserved.
//

#include<iostream>

using namespace std;

#define TRUE    1
#define FALSE   0

#define SET_SIZE       1000

typedef struct union_set{
    int p[SET_SIZE+1]; 		/* parent element */
    int size[SET_SIZE+1];   /* number of elements in subtree i */
    int n;                  /* number of elements in set */
} union_set;


void set_union_init(union_set *s, int n){
    int i;				/* counter */
    for (i=1; i<=n; i++) {
        s->p[i] = i;
        s->size[i] = 1;
    }
    s->n = n;
}

int find(union_set *s, int x){
    if (s->p[x] == x)
        return(x);
    else
        return( find(s,s->p[x]) );
}

void union_sets(union_set *s, int s1, int s2){
    int r1, r2;			/* roots of sets */
    
    r1 = find(s,s1);
    r2 = find(s,s2);
    cout << s1 << r1 << s2 << r2 << endl;
    
    if (r1 == r2) return;		/* already in same set */
    
    if (s->size[r1] >= s->size[r2]) {
        s->size[r1] = s->size[r1] + s->size[r2];
        s->p[ r2 ] = r1;
    }
    else {
        s->size[r2] = s->size[r1] + s->size[r2];
        s->p[ r1 ] = r2;
    }
}


bool same_component(union_set *s, int s1, int s2){
    return ( find(s,s1) == find(s,s2) );
}


void print_set_union(union_set *s){
    int i;                          /* counter */
    for (i=1; i<=s->n; i++)
        cout << i << s->p[i] << s->size[i];
    cout << endl;
}

int main(){
    
}


