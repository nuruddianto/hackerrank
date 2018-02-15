/*
 Problem Statement
 
 Machines have again attacked the kingdom of Zions!  The kingdom of Zions has N cities and N-1 bidirectional roads. There is a unique path between any pair of cities.
 
 Morpheus has found out that K Machines are planning to destroy the whole kingdom. These Machines are initially living in K different cities of the kingdom and they can launch an attack at anytime. Morpheus has asked Neo to destroy some of the roads in the kingdom to disrupt all connection among the Machines. After destroying the necessary roads there should be no path between any two Machines.
 
 Since the attack may happen at any moment, Neo has to do this task as fast as possible. Each road in the kingdom takes a certain amount of time to destroy and only one road can be destroyed at a time.
 
 You need to write a program that tells Neo the minimum amount of time he will require to destroy the necessary roads.
 
 Input Format
 The First line of the input contains two, space-separated integers, N and K. Cities are numbered 0 to N-1.
 
 N-1 lines follow, each containing three space-separated integers, x y z, which means there is a bidirectional road connecting city x and city y, and to destroy this road it takes z units of time.
 
 K lines follow, each containing an integer. The ith integer is the id of the city in which the ith Machine is currently located.
 
 Output Format
 Print in a single line the minimum time required to disrupt the connection among Machines.
 
 Constraints
 
 2 <= N <= 100,000
 
 2 <= K <= N
 
 1 <= time to destroy a road <= 1000,000
 
 Sample Input
 
 5 3
 2 1 8
 1 0 5
 2 4 5
 1 3 4
 2
 4
 0
 Sample Output
 
 10
 Explanation
 Neo can destroy the road connecting city 2 and city 4 of weight 5 , and the road connecting city 0 and city 1 of weight 5. As only one road can be destroyed at a time, the total minimum time taken is 10 units of time. After destroying these roads none of the Machines can reach another Machine via any path.
*/

#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

#define PB push_back
#define MP make_pair

typedef long long LL;
const int MAXN = 100005;
const LL inf = 1LL << 55;
int N, K;
bool bad[MAXN];
LL dp[MAXN][2];
vector<pair<int, int> > adj[MAXN];

void dfs(int u, int fa) {
    dp[u][1] = 0;
    dp[u][0] = bad[u] ? inf : 0;
    
    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i].first, w = adj[u][i].second;
        
        if (v != fa) {
            dfs(v, u);
            dp[u][1] += min(dp[v][0], dp[v][1] + w);
            dp[u][1] = min(dp[u][1], dp[u][0] + dp[v][1]);
            
            if (!bad[u])
                dp[u][0] += min(dp[v][0], dp[v][1] + w);
        }
    }
}

int main() {
    cin >> N >> K;
    
    for (int i = 1; i < N; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].PB(MP(b, c)); adj[b].PB(MP(a, c));
    }
    
    memset(bad, false, sizeof(bad));
    
    for (int i = 0; i < K; i++) {
        int x;
        cin >> x;
        bad[x] = true;
    }
    
    dfs(0, -1);
    LL ret = min(dp[0][0], dp[0][1]);
    
    cout << ret << endl;
    
    return 0;
}