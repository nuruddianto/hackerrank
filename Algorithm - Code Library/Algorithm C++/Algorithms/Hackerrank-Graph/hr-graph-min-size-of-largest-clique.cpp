/*
Problem Statement

A clique in a graph is set of nodes such that there is an edge between any two distinct nodes in the set. Finding the largest clique in a graph is a computationally tough problem. Currently no polynomial time algorithm is known for solving this. However, you wonder what is the minimum size of the largest clique in any graph with N nodes and M edges.

Input Format
The first line contains T the number of test cases. Each of the next T lines contain 2 integers : N, M

Output Format:
Output T lines, one for each test case, containing the desired answer for the corresponding test case.

Constraints
1 <= T <= 100000
2 <= N <= 10000
1 <= M <= N*(N-1)/2

Sample Input
3
3 2
4 6
5 7

Sample Output
2
4
3

Explanation
For the second test case, the only valid graph having 4 nodes and 6 edges is one where each pair of nodes is connected. So the size of the largest clique cannot be smaller than 4.
For the third test case, it is easy to verify that any graph with 5 nodes and 7 edges will surely have a clique of size 3 or more.

Hints Turan's theorem gives us an upper bound on the number of edges a graph can have if we wish that it should not have a clique of size x. Though the bound is not exact, it is easy to extend the statement of the theorem to get an exact bound in terms of n and x. Once this is done, we can binary search for the largest x such that f(n,x) <= m. See: Turan's Theorem

*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <queue>
#include <string>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <cstdlib>

using namespace std;

int sum(int n,int k) {
    int g1 = n%k ;
    int g2 = k - g1 ;
    int sz1 = n/k + 1 ;
    int sz2 = n/k ;
    int ret = g1*sz1*g2*sz2 + g1*(g1-1)*sz1*sz1/2 + g2*(g2-1)*sz2*sz2/2 ;
    return ret ;
}

int main() {
    int t;
    scanf("%d", &t);
    int n;
    long long m;
    while(t--) {
        scanf("%d%lld", &n, &m);
        int min_ = 1;
        int max_ = n;
        int mid_;
        while (min_ < max_) {
            mid_ = (min_ + max_) >> 1;
            if (sum(n, mid_) >= m /*- 1e-6*/) max_ = mid_;
            else min_ = mid_ + 1;
        }
        cout << min_ << endl;
    }
    return 0;
}