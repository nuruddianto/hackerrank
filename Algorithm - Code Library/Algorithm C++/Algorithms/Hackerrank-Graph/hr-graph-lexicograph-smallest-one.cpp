/*
 Problem Statement
 
 Johnny, like every mathematician, has his favorite sequence of distinct natural numbers. Let’s call this sequence M. Johnny was very bored, so he wrote down N copies of the sequence M in his big notebook. One day, when Johnny was out, his little sister Mary erased some numbers(possibly zero) from every copy of M and then threw the notebook out onto the street. You just found it. Can you reconstruct the sequence?
 
 In the input there are N sequences of natural numbers representing the N copies of the sequence M after Mary’s prank. In each of them all numbers are distinct. Your task is to construct the shortest sequence S that might have been the original M. If there are many such sequences, return the lexicographically smallest one. It is guaranteed that such a sequence exists.
 
 Note
 Sequence A[1…n] is lexicographically less than sequence B[1…n] if and only if there exists 1≤i≤n such that for all 1≤j<i,A[j]=B[j]  and  A[i]<B[i].
 
 Input Format
 
 In the first line, there is one number N denoting the number of copies of M.
 This is followed by K
 and in next line a sequence of length K representing one of sequences after Mary's prank. All numbers are separated by a single space.
 
 Constraints
 1≤N≤103
 2≤K≤103
 All values in one sequence are distinct numbers in range
 
 Output Format
 
 In one line, write the space-separated sequence S - the shortest sequence that might have been the original M. If there are many such sequences, return the lexicographically smallest one.
 
 Sample Input
 
 2
 2
 1 3
 3
 2 3 4
 Sample Output
 
 1 2 3 4
 Explanation
 
 You have 2 copies of the sequence with some missing numbers: [1,3] and [2,3,4]. There are two candidates for the original sequence M:[1,2,3,4] and [2,1,3,4], where the first one is lexicographically least.
*/

#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
#include<queue>
#include<functional>
using namespace std;

vector<int> gr[1000001];
int indeg[1000001];
priority_queue<int, vector<int>, greater<int>> pq;

int main()
{
    int n;
    scanf("%d", &n);
    int maxval = -1;
    for (int i = 0; i < n; i++)
    {
        int len;
        scanf("%d", &len);
        int prev;
        for (int j = 0; j < len; j++)
        {
            int tmp;
            scanf("%d", &tmp);
            if (tmp > maxval) maxval = tmp;
            if (j != 0) gr[prev].push_back(tmp), indeg[tmp]++;
            prev = tmp;
        }
    }
    for (int i = 1; i <= maxval; i++)
    {
        if (indeg[i] == 0 && !gr[i].empty())
            pq.push(i);
    }
    while (!pq.empty())
    {
        int next = pq.top();
        printf("%d ", next);
        pq.pop();
        int sz = (int)gr[next].size();
        for (int i = 0; i < sz; i++)
        {
            int node = gr[next][i];
            indeg[node]--;
            if (indeg[node] == 0)
                pq.push(node);
        }
    }
    printf("\n");
    return 0;
}
