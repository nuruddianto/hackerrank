//
//  priority_queue.cpp
//  Contekan
//
//  Created by Risman Adnan on 7/9/15.
//  Copyright (c) 2015 Risman Adnan. All rights reserved.
//

#include<iostream>
#include<limits>

using namespace std;

#define TRUE    1
#define FALSE   0

#define PQ_SIZE       1000

typedef int item_type;

typedef struct {
    item_type q[PQ_SIZE+1];     /* body of queue */
    int n;                      /* number of queue elements */
} priority_queue;



void pq_init(priority_queue *q){
    q->n = 0;
}


int pq_parent(int n){
    if (n == 1) return(-1);
    else return((int) n/2);     /* implicitly take floor(n/2) */
}

int pq_young_child(int n){
    return(2 * n);
}

void pq_swap(priority_queue *q, int i, int j){
    item_type temp;         /* placeholder */
    
    temp = q->q[i];
    q->q[i] = q->q[j];
    q->q[j] = temp;
}


void bubble_up(priority_queue *q, int p){
    if (pq_parent(p) == -1) return; /* at root of heap, no parent */
    
    if (q->q[pq_parent(p)] > q->q[p]) {
        pq_swap(q,p,pq_parent(p));
        bubble_up(q, pq_parent(p));
    }
}

void bubble_down(priority_queue *q, int p){
    int c;              /* child index */
    int i;              /* counter */
    int min_index;              /* index of lightest child */
    
    c = pq_young_child(p);
    min_index = p;
    
    for (i=0; i<=1; i++)
        if ((c+i) <= q->n) {
            if (q->q[min_index] > q->q[c+i]) min_index = c+i;
        }
    
    if (min_index != p) {
        pq_swap(q,p,min_index);
        bubble_down(q, min_index);
    }
}


void pq_insert(priority_queue *q, item_type x){
    if (q->n >= PQ_SIZE)
        cout << "Warning: priority queue overflow insert x= " << x << endl;
    else {
        q->n = (q->n) + 1;
        q->q[ q->n ] = x;
        bubble_up(q, q->n);
    }
}



item_type extract_min(priority_queue *q){
    int min = -1;           /* minimum value */
    if (q->n <= 0) cout << "Warning: empty priority queue." << endl;
    else {
        min = q->q[1];
        
        q->q[1] = q->q[ q->n ];
        q->n = q->n - 1; // reduce number of queue
        bubble_down(q,1);
    }
    return(min);
}


int empty_pq(priority_queue *q){
    if (q->n <= 0) return (TRUE);
    else return (FALSE);
}

void print_pq(priority_queue *q){
    for (int i=1; i<=q->n; i++)cout << int(q->q[i]) << " ";
    cout << endl;
}

void make_heap(priority_queue *q, item_type s[], int n){
    int i;                          /* counter */
    
    q->n = n;
    for (i=0; i<n; i++)
        q->q[i+1] = s[i];
    
    for (i=q->n; i>=1; i--)
        bubble_down(q,i);
}

void make_heap1(priority_queue *q, item_type s[], int n){
    int i;                          /* counter */
    pq_init(q);
    for (i=0; i<n; i++)
        pq_insert(q, s[i]);
}




int main(){
    // Please implement your codes here....
    priority_queue* pq = new priority_queue();
    pq_init(pq);

    item_type val = 10;
    pq_insert(pq, val);
    val = 20;
    pq_insert(pq, val);
    val = 13;
    pq_insert(pq, val);
    val = 2;
    pq_insert(pq, val);
    val = 52;
    pq_insert(pq, val);
    val = 5;
    pq_insert(pq, val);
    val = 40;
    pq_insert(pq, val);
    
    cout << "Size of PQ = " << pq->n << endl;
    print_pq(pq);
    cout << "First element" << pq->q[1] << "=----";
    cout << "Minimum of PQ =" << extract_min(pq) << endl;
    print_pq(pq);
    cout << "Minimum of PQ =" << extract_min(pq) << endl;
    print_pq(pq);
    
}






