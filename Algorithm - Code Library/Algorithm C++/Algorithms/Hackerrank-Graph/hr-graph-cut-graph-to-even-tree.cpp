/*
Problem Statement

You are given a tree (a simple connected graph with no cycles). You have to remove as many edges from the tree as possible to obtain a forest with the condition that : Each connected component of the forest should contain an even number of vertices.

To accomplish this, you will remove some edges from the tree. Find out the number of removed edges.

Input Format
The first line of input contains two integers N and M. N is the number of vertices and M is the number of edges.
The next M lines contain two integers ui and vi which specifies an edge of the tree. (1-based index)

Output Format
Print the answer, a single integer.

Constraints
2 <= N <= 100.

Note: The tree in the input will be such that it can always be decomposed into components containing even number of nodes.

Sample Input

10 9
2 1
3 1
4 3
5 2
6 1
7 2
8 6
9 8
10 8
Sample Output

2
*/


#include <iostream>
#include <cstdio>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

int dp[200][200];
vector<int> a[200];

int n, m;
int tmp[2][200];
void solve(int fa, int x) {
    int cnt = 0;
    for (int i = 0; i < a[x].size(); i ++) {
        if (a[x][i] != fa) {
            solve(x, a[x][i]);
            cnt ++;
        }
    }
    if (cnt == 0) {
        dp[x][1] = 0;
        return;
    }
    
    for (int i = 0; i <= n; i ++) tmp[0][i] = -1;
    tmp[0][1] = 0;
    int flag = 0;
    for (int i = 0; i < a[x].size(); i ++) {
        if (a[x][i] != fa) {
            for (int j = 0; j <= n; j ++) tmp[1 - flag][j] = -1;
            for (int j = n; j >= 0; j --) {
                if (tmp[flag][j] != -1) {
                    for (int k = 0; k <= n; k ++) {
                        if (dp[a[x][i]][k] != -1) {
                            tmp[1 - flag][j + k] = max(tmp[1 - flag][j + k], tmp[flag][j] + dp[a[x][i]][k]);
                            if (k % 2 == 0) {
                                tmp[1 - flag][j] = max(tmp[1 - flag][j], 1 + dp[a[x][i]][k] + tmp[flag][j]);
                            }
                        }
                    }
                }
            }
            flag = 1 - flag;
        }
    }
    for (int i = 0; i <= n; i ++) dp[x][i] = tmp[flag][i];
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i ++) {
        a[i].clear();
        for (int j = 0; j <= n; j ++) dp[i][j] = -1;
    }
    int x, y;
    while (m --) {
        cin >> x >> y;
        a[x].push_back(y);
        a[y].push_back(x);
    }
    int ans = 0;
    solve(-1, 1);
    for (int i = 2; i <= n; i += 2) {
        ans = max(ans, dp[1][i]);
    }
    
    cout << ans << endl;
    return 0;
}