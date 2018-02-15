/*
 Problem Statement
 
 There are N points in a plane. The ith point has coordinates (xi, yi). Perform the following queries, and always include the boundry points (i and j) in the operation:
 
 1) Reflect all points between points i and j along the X axis. This query is represented as "X i j"
 2) Reflect all points between points i and j along the Y axis. This query is represented as "Y i j"
 3) Count how many points between points i and j lie in each of the 4 quadrants. This query is represented as "C i j"
 
 Input Format
 The first line contains N, the number of points. N lines follow.
 
 The ith line contains xi and yi separated by a space.
 
 The next line contains Q, the number of queries. The next Q lines contain one query each, in one of the above forms.
 
 All indices are 1 indexed.
 
 Output Format
 Display one line for each query of the type "C i j". The corresponding line contains 4 integers; the number of points having indices in the range [i..j] in the 1st,2nd,3rd and 4th quadrants respectively.
 
 Constraints
 1 <= N <= 100000
 1 <= Q <= 1000000
 You may assume that no point lies on the X or the Y axis. All (xi,yi) will fit in a 32-bit signed integer
 In all queries, 1 <=i <=j <=N
 
 Sample Input
 
 4
 1 1
 -1 1
 -1 -1
 1 -1
 5
 C 1 4
 X 2 4
 C 3 4
 Y 1 2
 C 1 3
 Sample Output
 
 1 1 1 1
 1 1 0 0
 0 2 0 1
 Explanation
 When a query says "X i j", it means: take all the points between indices i and j (both i and j inclusive) and reflect those points along the X axis. The i and j here have nothing to do with the co-ordinates of the points. They are the indices.  i refers to point i and j refers to point j
 
 'C 1 4' asks you to 'Consider the set of points having index in {1,2,3,4}. Amongst those points, how many of them lie in the 1st,2nd,3rd and 4th quadrants respectively?'
 
 The answer to this is clearly 1 1 1 1.
 
 Next, we reflect the points between indices '2 4' along the X axis. So the new coordinates are :
 
 1 1
 -1 -1
 -1 1
 1 1
 Now 'C 3 4' is 'Consider the set of points having index in {3,4}. Amongst those points, how many of them lie in the 1st,2nd,3rd and 4th quadrants respectively?' Point 3 lies in quadrant 2 and point 4 lies in quadrant 1.
 
 So the answer is 1 1 0 0
*/
#include <iostream>
#include <algorithm>

using namespace std;

#define N 111111

struct Tp {
    int l, r, add;
    int cnt[4];
} T[3*N];

void Init(int v, int l, int r) {
    T[v].l = l, T[v].r = r;
    T[v].cnt[0] = r - l  + 1;
    
    if (l < r) {
        Init(v + v, l, (r + l) >> 1);
        Init(v + v + 1, (r + l + 2) >> 1, r);
    }
}

void Xor(int v, int r, int x) {
    if (T[v].r <= r) {
        T[v].add ^= x;
        return;
    }
    
    if (T[v].l > r) return;
    
    Xor(v + v, r, x);
    Xor(v + v + 1, r, x);
    
    T[v].cnt[0] = T[v + v].cnt[T[v + v].add] + T[v + v + 1].cnt[T[v + v + 1].add];
    T[v].cnt[1] = T[v + v].cnt[T[v + v].add ^ 1] + T[v + v + 1].cnt[T[v + v + 1].add ^ 1];
    T[v].cnt[2] = T[v + v].cnt[T[v + v].add ^ 2] + T[v + v + 1].cnt[T[v + v + 1].add ^ 2];
    T[v].cnt[3] = T[v + v].cnt[T[v + v].add ^ 3] + T[v + v + 1].cnt[T[v + v + 1].add ^ 3];
}

void Cnt(int v, int r, int* ca, int add = 0) {
    if (T[v].r <= r) {
        add ^= T[v].add;
        ca[add] += T[v].cnt[0];
        ca[add ^ 1] += T[v].cnt[1];
        ca[add ^ 2] += T[v].cnt[2];
        ca[add ^ 3] += T[v].cnt[3];
        return;
    }
    
    if (T[v].l > r) return;
    
    Cnt(v + v, r, ca, add ^ T[v].add);
    Cnt(v + v + 1, r, ca, add ^ T[v].add);
}

int x[N], y[N];

int main() {
    int n, last;
    cin >> n;
    
    for (int i = 1; i <= n; ++i)
        cin >> x[i] >> y[i];
    
    Init(1, 1, n);
    
    last = 0;
    
    for (int i = n; i > 0; --i) {
        Xor(1, i, last ^ (((x[i] < 0) << 1) + (y[i] < 0)));
        last = (((x[i] < 0) << 1) + (y[i] < 0));
    }
    
    int q, l, r, cnt1[4], cnt2[4];
    char ch;
    
    cin >> q;
    
    for (int i = 0; i < q; ++i) {
        cin >> ch >> l >> r;
        
        if (ch == 'Y') {
            Xor(1, r, 2);
            if (l > 1) Xor(1, l - 1, 2);
        } else if (ch == 'X') {
            Xor(1, r, 1);
            if (l > 1) Xor(1, l - 1, 1);
        } else if (ch == 'C') {
            cnt1[0] = cnt1[1] = cnt1[2] = cnt1[3] = 0;
            cnt2[0] = cnt2[1] = cnt2[2] = cnt2[3] = 0;
            Cnt(1, r, cnt1);
            if (l > 1) Cnt(1, l - 1, cnt2);
            
            cout << cnt1[0] - cnt2[0] << " " << cnt1[2] - cnt2[2] << " " << cnt1[3] - cnt2[3] << " " << cnt1[1] - cnt2[1] << endl;
        }
    }
    
    return 0;
}