//
//  stack.cpp
//  Contekan
//
//  Created by Risman Adnan on 7/9/15.
//  Copyright (c) 2015 Risman Adnan. All rights reserved.
//

#include<iostream>

#define STACKSIZE 1000
#define TRUE    1
#define FALSE   0

typedef struct {
    int s[STACKSIZE+1];		/* body of queue */
    int top;                /* position of top element */
    int count;              /* number of stack elements */
} stack;


using namespace std;

void init_stack(stack *s)
{
    s->top = -1;
    s->count = 0;
}


void push(stack *s, int x)
{
    if (s->count >= STACKSIZE)
        cout << "Warning: stack overflow push x =" << x << endl;
    else {
        s->top = s->top + 1;
        s->s[ s->top ] = x;
        s->count = s->count + 1;
    }
}

int pop(stack *s)
{
    int x;
    
    if (s->count <= 0) cout << "Warning: empty stack pop.\n";
    else {
        x = s->s[ s->top ];
        s->top = s->top - 1;
        s->count = s->count - 1;
    }
    
    return(x);
}

int empty_stack(stack *s)
{
    if (s->count <= 0) return (TRUE);
    else return (FALSE);
}

void print_stack(stack *s)
{
    int i;				/* counter */
    for (i=(s->count-1); i>=0; i--) cout << s->s[i] << " ";
    cout << endl;
}

int main(){
    stack *s = new stack();
    init_stack(s);
    push(s, 10);
    push(s, 20);
    push(s, 30);
    push(s, 40);
    push(s, 50);
    print_stack(s);
    
    
}
