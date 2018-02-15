/*
 Problem Statement
 
 It has been a prosperous year for King Charles and he is rapidly expanding his empire. In fact, he recently invaded his neighbouring country and set up a new kingdom! This kingdom has many cities connected by one-way roads. To ensure higher connectivity, two cities are sometimes directly connected by more than one road also.
 
 In the new kingdom, King Charles has made one of the cities his financial capital and another city his warfare capital. He wants a better connectivity between these two capitals. The connectivity of a pair of cities, A and B, is defined as the number of different paths from city A to city B. A path may use a road more than once if possible. Two paths are considered different if they do not use exactly the same sequence of roads.
 
 There are N cities numbered 1 to N in the new kingdom and M one-way roads. City 1 is the financial capital and city N is the warfare capital.
 
 What is the connectivity of the financial capital and the warfare capital, i.e., how many different paths are there from city 1 to city N?
 
 Input Format
 The first line contains two integers N and M.
 
 M lines follow, each containing two integers x and y, indicating there is a road from city x to city y (1<=x,y<=N).
 
 Output Format
 Print the number of different paths from city 1 to city N modulo 1,000,000,000(10^9). If there are infinitely many different paths, print "INFINITE PATHS"(quotes are for clarity).
 
 Constraints
 
 2<=N<=10,000(10^4)
 
 1<=M<=100,000(10^5)
 
 Two roads may connect the same cities, but they are still considered distinct for path connections.
 
 Sample Input #1
 5 5
 1 2
 2 4
 2 3
 3 4
 4 5
 
 Sample Output #1
 2
 
 Sample Input #2
 5 5
 1 2
 4 2
 2 3
 3 4
 4 5
 
 Sample Output #2
 INFINITE PATHS
 
 Suggest Edits
*/


#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int MODULO = 1000000000;
const int MAX_N = 10005;
const int MAX_M = 100005;

struct Edge {
    int v, next;
} edge[2 * MAX_M], edge2[2 * MAX_M];

int N, M;
int low[MAX_N], dfn[MAX_N], cnt[MAX_N], id[MAX_N], vis[MAX_N], Stack[MAX_N];
int dp[MAX_N], reach[MAX_N], reach2[MAX_N], topo[MAX_N];
int num, Head[MAX_N], num2, Head2[MAX_N];
int Size, Top, Index, topcnt;

void addEdge(int u, int v) {
    edge[num].v = v;
    edge[num].next = Head[u];
    Head[u] = num++;
}

void addEdge2(int u, int v) {
    edge2[num2].v = v;
    edge2[num2].next = Head2[u];
    Head2[u] = num2++;
}

void Tarjan(int u) {
    low[u] = dfn[u] = ++Index;
    Stack[++Top] = u;
    vis[u] = 1;
    
    for (int i = Head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].v;
        
        if (!dfn[v]) {
            Tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (vis[v])
            low[u] = min(low[u], dfn[v]);
    }
    
    if (low[u] == dfn[u]) {
        Size++;
        
        for (; Stack[Top + 1] != u; --Top) {
            vis[Stack[Top]] = 0;
            id[Stack[Top]] = Size;
        }
    }
}

void dfs(int u) {
    reach[u] = 1;
    
    for (int i = Head[u]; i != -1; i = edge[i].next)
        if (!reach[edge[i].v])
            dfs(edge[i].v);
}

void dfs2(int u) {
    reach2[u] = 1;
    
    for (int i = Head2[u]; i != -1; i = edge2[i].next)
        if (!reach2[edge2[i].v])
            dfs2(edge2[i].v);
}

void topdfs(int u) {
    vis[u] = true;
    
    for (int i = Head[u]; i != -1; i = edge[i].next)
        if (!vis[edge[i].v]) dfs(edge[i].v);
    
    topo[topcnt++] = u;
}

int main() {
    num = num2 = Top = Size = Index = 0;
    memset(Head, -1, sizeof(Head));
    memset(Head2, -1, sizeof(Head2));
    
    cin >> N >> M;
    
    for (; M--; ) {
        int u, v;
        cin >> u >> v;
        addEdge(u, v);
        addEdge2(v, u);
    }
    
    for (int i = 1; i <= N; i++)
        if (!dfn[i]) Tarjan(i);
    
    for (int i = 1; i <= N; i++)
        cnt[id[i]]++;
    
    dfs(1);
    dfs2(N);
    
    if (!reach[N]) {
        cout << 0 << endl;
        return 0;
    }
    
    for (int i = 1; i <= N; i++)
        if (reach[i] && reach2[i] && cnt[id[i]] > 1) {
            cout << "INFINITE PATHS" << endl;
            return 0;
        }
    
    num2 = 0;
    memset(Head2, -1, sizeof(Head2));
    
    for (int i = 1; i <= N; i++)
        for (int j = Head[i]; j != -1; j = edge[j].next)
            if (id[i] != id[edge[j].v])
                addEdge2(id[i], id[edge[j].v]);
    
    memset(vis, 0, sizeof(vis));
    topcnt = 0;
    
    for (int i = 1; i <= Size; i++)
        if (!vis[i]) topdfs(i);
    
    reverse(topo, topo + Size);
    
    memset(dp, 0, sizeof(dp));
    dp[id[1]] = 1;
    
    for (int u = 0; u < topcnt; u++) {
        int idx = topo[u];
        if (dp[idx]) {
            for (int i = Head2[idx]; i != -1; i = edge2[i].next) {
                dp[edge2[i].v] += dp[idx];
                dp[edge2[i].v] %= MODULO;
            }
        }
    }
    
    cout << dp[id[N]] << endl;
    
    return 0;
}