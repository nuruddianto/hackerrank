//
//  dp-matrix-multiplication.cpp
//  DynamicProgramming
//
//  Created by Risman Adnan on 7/15/15.
//  Copyright (c) 2015 Risman Adnan. All rights reserved.
//

/*
 Given a sequence of matrices, find the most efficient way to multiply these matrices together. The problem is not actually to perform the multiplications, but merely to decide in which order to perform the multiplications.
 
 We have many options to multiply a chain of matrices because matrix multiplication is associative. In other words, no matter how we parenthesize the product, the result will be the same. For example, if we had four matrices A, B, C, and D, we would have:
 
 (ABC)D = (AB)(CD) = A(BCD) = ....
 However, the order in which we parenthesize the product affects the number of simple arithmetic operations needed to compute the product, or the efficiency. For example, suppose A is a 10 × 30 matrix, B is a 30 × 5 matrix, and C is a 5 × 60 matrix. Then,
 
 (AB)C = (10×30×5) + (10×5×60) = 1500 + 3000 = 4500 operations
 A(BC) = (30×5×60) + (10×30×60) = 9000 + 18000 = 27000 operations.
 Clearly the first parenthesization requires less number of operations.
 
 Given an array p[] which represents the chain of matrices such that the ith matrix Ai is of dimension p[i-1] x p[i]. We need to write a function MatrixChainOrder() that should return the minimum number of multiplications needed to multiply the chain./
 
*/

// See the Cormen book for details of the following algorithm
#include<stdio.h>
#include<limits.h>

// Matrix Ai has dimension p[i-1] x p[i] for i = 1..n
int MatrixChainOrder(int p[], int n)
{
    
    /* For simplicity of the program, one extra row and one extra column are
     allocated in m[][].  0th row and 0th column of m[][] are not used */
    int m[n][n];
    
    int i, j, k, L, q;
    
    /* m[i,j] = Minimum number of scalar multiplications needed to compute
     the matrix A[i]A[i+1]...A[j] = A[i..j] where dimention of A[i] is
     p[i-1] x p[i] */
    
    // cost is zero when multiplying one matrix.
    for (i = 1; i < n; i++)
        m[i][i] = 0;
    
    // L is chain length.
    for (L=2; L<n; L++)
    {
        for (i=1; i<=n-L+1; i++)
        {
            j = i+L-1;
            m[i][j] = INT_MAX;
            for (k=i; k<=j-1; k++)
            {
                // q = cost/scalar multiplications
                q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                if (q < m[i][j])
                    m[i][j] = q;
            }
        }
    }
    
    return m[1][n-1];
}

int main()
{
    int arr[] = {1, 2, 3, 4};
    int size = sizeof(arr)/sizeof(arr[0]);
    
    printf("Minimum number of multiplications is %d ",
           MatrixChainOrder(arr, size));
    
    getchar();
    return 0;
}