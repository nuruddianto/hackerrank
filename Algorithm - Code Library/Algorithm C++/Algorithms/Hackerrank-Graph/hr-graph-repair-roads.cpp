/*
 Problem Statement
 
 The country of Byteland contains of N cities and N - 1 bidirectional roads between them such that there is a path between any two cities. The roads in Byteland were built long ago and now they are in need of repair. You have been hired to repair all the roads. You intend to do this by dispatching robots on some of the roads. Each robot will repair the road he is currently on and then move to one of the adjacent unrepaired roads. After repairing that, it will move to another adjacent unrepaired road, repair that and so on.
 
 Two roads are adjacent if they have the same city at one of their endpoints. For the process to be efficient, no two robots will can ever repair the same road, and no road can be visited twice. What is the least number of robots needed to accomplish the task?
 
 Input Format
 The first line contains the number of test cases T. T test cases follow. The first line of each testcase contains N, the number of cities in Byteland. The cities are numbered 0..N - 1. The following N - 1 lines contain the description of the roads. The ith line contains two integers ai and bi, meaning that there is a road connecting cities with numbers ai and bi.
 
 Output Format
 Output T lines, one corresponding to each test case containing the required answer for that test case.
 
 Constraints
 1 <= T <= 20
 1 <= N <= 10000
 0 <= ai,bi < N
 
 Sample Input
 
 3
 4
 0 1
 0 2
 0 3
 6
 0 1
 1 2
 2 3
 2 4
 4 5
 7
 0 1
 1 2
 2 3
 2 4
 4 5
 3 6
 Sample Output
 
 1
 1
 2
 Explanation
 For the first case, one robot is enough to repair all roads: (0,1) -> (0,2) -> (0,3)
 For the second case, one robot is again enough: (0,1) -> (1,2) -> (2,3) -> (2,4) -> (4,5)
 The the third case, there is no way to repair all the roads with one robot and at least two are needed.
*/

#include<iostream>
#include<vector>
#include<stdio.h>
#include<set>
#include<string.h>
#include<stdlib.h>
using namespace std ;
#define INF (int)1e9
#define MAXN 10002
vector<int> G[MAXN] ;
int n ;

int parent[MAXN] ;
void dfs(int k,int p)
{
    parent[k] = p ;
    for(int i = 0;i < G[k].size();i++)
        if(G[k][i] != p)
            dfs(G[k][i],k) ;
}

int u[MAXN],v[MAXN],f[MAXN],nleaf[MAXN] ;
int solve()
{
    memset(u,0,sizeof u) ;
    memset(v,0,sizeof v) ;
    memset(nleaf,0,sizeof nleaf) ;
    memset(parent,255,sizeof parent) ;
    dfs(0,-1) ;
    for(int i = 1;i < n;i++) nleaf[parent[i]]++ ;
    int nodes = n,ret = 0 ;
    for(int i = 1;i < n;i++) if(nleaf[i] == 0 && u[i] == 0)
    {
        nleaf[parent[i]]-- ;
        u[parent[i]] = 1 ;
        parent[i] = -1 ;
        nodes-- ;
    }
    if(nodes == 1) return 1 ;
    
    while(nodes > 1)
    {
        ret++ ;
        memset(f,255,sizeof f) ;
        char mark[MAXN] = {} ;
        for(int i = 1;i < n;i++) if(parent[i] != -1)
            if(nleaf[i] > 1)
                mark[i] = 1 ;
        int a = -1,b = -1,c = -1 ;
        for(int i = 1;i < n;i++) if(parent[i] != -1) if(nleaf[i] == 0)
        {
            int j = i ;
            while(j > 0 && !mark[j]) j = parent[j] ;
            if(f[j] == -1) f[j] = i ;
            else
            {
                a = f[j] ;
                b = i ;
                c = j ;
                break ;
            }
        }
        if(a == -1 || b == -1) break ;
        while(a != c) { int t = parent[a] ; parent[a] = -1 ; nleaf[t]-- ; nodes-- ; a = t ; }
        while(b != c) { int t = parent[b] ; parent[b] = -1 ; nleaf[t]-- ; nodes-- ; b = t ; }
        u[c] = 0 ;
        for(int i = 1;i < n;i++) if(parent[i] == c) v[i] = 1 ;
        v[c] = 1 ;
        if(nodes == 1) break ;
        
        if(c > 0 && nleaf[c] == 0) { int t = parent[c] ; parent[c] = -1 ; nleaf[t]-- ; nodes-- ; c = t ; }
        while(c > 0 && nleaf[c] == 0 && !u[c])
        {
            if(v[c]) { int t = parent[c] ; parent[c] = -1 ; nleaf[t]-- ; nodes-- ; c = t ; }
            else { int t = parent[c] ; parent[c] = -1 ; u[t] = 1 ; nleaf[t]-- ; nodes-- ; c = t ; }
        }
        if(nodes == 1 && c == 0 && u[c]) ret++ ;
    }
    return ret ;
}

int main()
{
    int runs ;
    scanf("%d",&runs) ;
    while(runs--)
    {
        scanf("%d",&n) ;
        for(int i = 0;i < MAXN;i++) G[i].clear() ;
        for(int i = 1;i < n;i++)
        {
            int a,b ;
            scanf("%d%d",&a,&b) ;
            G[a].push_back(b) ;
            G[b].push_back(a) ;
        }
        int ret = solve() ;
        printf("%d\n",ret) ;
    }
    return 0 ;
}