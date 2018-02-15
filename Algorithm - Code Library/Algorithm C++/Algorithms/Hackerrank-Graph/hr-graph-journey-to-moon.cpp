/*
 Problem Statement
 
 The member states of the UN are planning to send 2 people to the Moon. But there is a problem. In line with their principles of global unity, they want to pair astronauts of 2 different countries.
 
 There are N trained astronauts numbered from 0 to N-1. But those in charge of the mission did not receive information about the citizenship of each astronaut. The only information they have is that some particular pairs of astronauts belong to the same country.
 
 Your task is to compute in how many ways they can pick a pair of astronauts belonging to different countries. Assume that you are provided enough pairs to let you identify the groups of astronauts even though you might not know their country directly. For instance, if 1,2,3 are astronauts from the same country; it is sufficient to mention that (1,2) and (2,3) are pairs of astronauts from the same country without providing information about a third pair (1,3).
 
 Input Format
 The first line contains two integers, N and I, separated by a single space. I lines follow. Each line contains 2 integers separated by a single space A and B such that
 
 0 ≤ A, B ≤ N-1
 
 and A and B are astronauts from the same country.
 
 Output Format
 An integer that denotes the number of permissible ways to choose a pair of astronauts.
 
 Constraints
 1<=N<=105
 1<=I<=104
 
 Sample Input
 
 4 2
 0 1
 2 3
 Sample Output
 
 4
 Explanation
 Persons numbered 0 and 1 belong to same country, and those numbered 2 and 3 belong to same country. So the UN can choose one person out of 0 & 1 and another person out of 2 & 3. So number of ways of choosing a pair of astronauts is 4.
 
*/

#include <map>
#include <set>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <bitset>
#include <vector>
#include <cstdio>
#include <string>
#include <cassert>
#include <climits>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
#define FOREACH(e,x) for(__typeof(x.begin()) e=x.begin();e!=x.end();++e)
typedef long long LL;

const int maxn = 100000 + 5;
struct DisJointSet{
    int rank[maxn], parent[maxn];
    
    void init(int n) {
        for (int i = 0; i < n; i++) {
            rank[i] = 1;
            parent[i] = i;
        }
    }
    
    int Find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = Find(parent[x]);
    }
    
    void Union(int x, int y) {
        x = Find(x);
        y = Find(y);
        
        if (x == y) return;
        
        parent[x] = y;
        rank[y] += rank[x];
    }
    
    int count(int n) {
        int ret = 0;
        for (int i = 0; i < n; i++)
            ret += Find(i) == i;
        return ret;
    }
}djs;
int n, m;

int main() {
    scanf("%d%d", &n, &m);
    djs.init(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        djs.Union(a, b);
    }
    LL ret = 0;
    for (int i = 0; i < n; i++) {
        if (djs.Find(i) != i) continue;
        ret += (LL)djs.rank[i] * (n - djs.rank[i]);
    }
    cout << ret / 2 << endl;
    return 0;
}