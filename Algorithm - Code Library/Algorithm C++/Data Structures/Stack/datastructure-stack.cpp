//
//  datastructure-stack.cpp
//  SWTest
//
//  Created by Risman Adnan on 7/15/15.
//  Copyright (c) 2015 Risman Adnan. All rights reserved.
//

// C program for array implementation of stack

#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cstring>

// A structure to represent a stack
struct Stack
{
    int top;
    unsigned capacity;
    int* array;
};

// function to create a stack of given capacity. It initializes size of
// stack as 0
Stack* createStack(unsigned capacity)
{
    Stack* stack = new Stack();
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = new int();
    return stack;
}

// Stack is full when top is equal to the last index
int isFull(Stack* stack)
{   return stack->top == stack->capacity - 1; }

// Stack is empty when top is equal to -1
int isEmpty(Stack* stack)
{   return stack->top == -1;  }

// Function to add an item to stack.  It increases top by 1
void push(Stack* stack, int item)
{
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
    printf("%d pushed to stack\n", item);
}

// Function to remove an item from stack.  It decreases top by 1
int pop(Stack* stack)
{
    if (isEmpty(stack))
        return INT_MIN;
    return stack->array[stack->top--];
}

// Function to get top item from stack
int peek(Stack* stack)
{
    if (isEmpty(stack))
        return INT_MIN;
    return stack->array[stack->top];
}


// The main function that converts given infix expression
// to postfix expression.
int infixToPostfix(char* exp)
{
    int i, k;
    
    // Create a stack of capacity equal to expression size
    Stack* stack = createStack(int(strlen(exp)));
    if(!stack) // See if stack was created successfully
        return -1 ;
    
    for (i = 0, k = -1; exp[i]; ++i)
    {
        // If the scanned character is an operand, add it to output.
        if (isOperand(exp[i]))
            exp[++k] = exp[i];
        
        // If the scanned character is an ‘(‘, push it to the stack.
        else if (exp[i] == '(')
            push(stack, exp[i]);
        
        //  If the scanned character is an ‘)’, pop and output from the stack
        // until an ‘(‘ is encountered.
        else if (exp[i] == ')')
        {
            while (!isEmpty(stack) && peek(stack) != '(')
                exp[++k] = pop(stack);
            if (!isEmpty(stack) && peek(stack) != '(')
                return -1; // invalid expression
            else
                pop(stack);
        }
        else // an operator is encountered
        {
            while (!isEmpty(stack) && Prec(exp[i]) <= Prec(peek(stack)))
                exp[++k] = pop(stack);
            push(stack, exp[i]);
        }
        
    }
    
    // pop all the operators from the stack
    while (!isEmpty(stack))
        exp[++k] = pop(stack );
    
    exp[++k] = '\0';
    printf( "%s\n", exp );
}


// A stack based function to reverese a string
void reverse(char str[])
{
    // Create a stack of capacity equal to length of string
    int n = int(strlen(str));
    Stack* stack = createStack(n);
    
    // Push all characters of string to stack
    int i;
    for (i = 0; i < n; i++)
        push(stack, str[i]);
    
    // Pop all characters of string and put them back to str
    for (i = 0; i < n; i++)
        str[i] = pop(stack);
}


// The main function that returns value of a given postfix expression
int evaluatePostfix(char* exp)
{
    // Create a stack of capacity equal to expression size
    Stack* stack = createStack(int(strlen(exp)));
    int i;
    
    // See if stack was created successfully
    if (!stack) return -1;
    
    // Scan all characters one by one
    for (i = 0; exp[i]; ++i)
    {
        // If the scanned character is an operand or number,
        // push it to the stack.
        if (isdigit(exp[i]))
            push(stack, exp[i] - '0');
        
        //  If the scanned character is an operator, pop two
        // elements from stack apply the operator
        else
        {
            int val1 = pop(stack);
            int val2 = pop(stack);
            switch (exp[i])
            {
                case '+': push(stack, val2 + val1); break;
                case '-': push(stack, val2 - val1); break;
                case '*': push(stack, val2 * val1); break;
                case '/': push(stack, val2/val1);   break;
            }
        }
    }
    return pop(stack);
}

// Driver program to test above functions
int main()
{
    struct Stack* stack = createStack(100);
    
    push(stack, 10);
    push(stack, 20);
    push(stack, 30);
    
    printf("%d popped from stack\n", pop(stack));
    
    printf("Top item is %d\n", peek(stack));
    
    return 0;
}