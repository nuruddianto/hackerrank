/*
 Problem Statement
 
 There are N problems numbered 1..N which you need to complete. You've arranged the problems in increasing difficulty order, and the ith problem has estimated difficulty level i. You have also assigned a rating vi to each problem. Problems with similar vi values are similar in nature. On each day, you will choose a subset of the problems and solve them. You've decided that each subsequent problem solved on the day should be tougher than the previous problem you solved on that day. Also, to make it less boring, consecutive problems you solve should differ in their vi rating by at least K. What is the least number of days in which you can solve all problems?
 
 Input Format
 
 The first line contains the number of test cases T. T test cases follow. Each case contains an integer N and K on the first line, followed by integers v1,...,vn on the second line.
 
 Output Format
 
 Output T lines, one for each test case, containing the minimum number of days in which all problems can be solved.
 
 Constraints
 
 1 <= T <= 100
 1 <= N <= 300
 1 <= vi <= 1000
 1 <= K <= 1000
 
 Sample Input
 
 2
 3 2
 5 4 7
 5 1
 5 3 4 5 6
 
 Sample Output
 
 2
 1
 
 Explanation
 
 For the first example, you can solve the problems with rating 5 and 7 on the first day and the problem with rating 4 on the next day. Note that the problems with rating 5 and 4 cannot be completed consecutively because the ratings should differ by at least K (which is 2). Also, the problems cannot be completed in order 5,7,4 in one day because the problems solved on a day should be in increasing difficulty level.
 
 For the second example, all problems can be solved on the same day.
 
 Suggest Edits
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
#define maxn 310
vector<int>a[maxn];
bool visit[maxn];
int match[maxn];
int n;
bool find(int x) {
    for (int i = 0; i < a[x].size(); i ++) {
        if (!visit[a[x][i]]) {
            visit[a[x][i]] = true;
            if (match[a[x][i]] == -1 || find(match[a[x][i]])) {
                match[a[x][i]] = x;
                return true;
            }
        }
    }
    return false;
}

int main() {
    // freopen("data.txt", "r", stdin);
    int t;
    cin >> t;
    int k;
    int d[maxn];
    while (t --) {
        cin >> n >> k;
        for (int i = 0; i < n; i ++) {
            a[i].clear();
            cin >> d[i];
            match[i] = -1;
        }
        for (int i = 0; i < n; i ++) {
            for (int j = i + 1; j < n; j ++) {
                if (abs(d[i] - d[j])  >= k) {
                    a[i].push_back(j);
                }
            }
        }
        
        int res = 0;
        for (int i = 0; i < n; i ++) {
            memset(visit, false, sizeof(bool) * maxn);
            res += find(i);
        }
        cout << n - res << endl;
    }
    return 0;
}