/*
 Problem Statement
 
 In the magical kingdom of Kasukabe, people strive to possess only one skillset. Higher the number of skillset present among the people, the more content people will be.
 
 There are N types of skill set present and initially there exists Ci people possessing ith skill set, where i∈[1,N].
 
 There are T wizards in the kingdom and they have the ability to transform the skill set of a person into another skill set. Each of the these wizards has two list of skill sets associated with them, A and B. He can only transform the skill set of person whose initial skill set lies in list A and that final skill set will be an element of list B. That is, if A=[2,3,6] and B=[1,2] then following transformation can be done by that trainer.
 
 2→12→23→13→26→16→2
 Once a transformation is done, both skill is removed from the respective lists. In the above example, if he perform 3→1 transformation on a person, list A will be updated to [2,6] and list B will be [2]. This updated list will be used for next transformation and so on.

 Few points to note are:
 
 A wizard can perform 0 or more transformation as long as they satisfies the above criteria.
 A person can go through multiple transformation of skill set.
 Same class transformation is also possible. That is a person' skill set can be transformed into his current skill set. Eg. 2→2 in the above example.
 Your goal is to design a series of transformation which results into maximum number of skill set with non-zero acquaintance.
 
 Input Format
 The first line contains two numbers, N T, where N represent the number of skill set and T represent the number of wizards.
 Next line contains N space separated integers, C1 C2 … CN, where Ci represents the number of people with ith skill. Then follows 2×T lines, where each pair of line represent the configuration of each wizard.
 First line of the pair will start with the length of list A and followed by list A in the same line. Similarly second line of the pair starts with the length of list B and then the list B.
 
 Output Format
 The output must consist of one number, the maximum number of distinct skill set that can the people of country learn, after making optimal transformation steps.
 
 Constraints
 1≤N≤200
 0≤T≤30
 0≤Ci≤10
 0≤|A|≤50
 1≤Ai≤N
 Ai≠Aj,1≤i<j≤|A|
 0≤|B|≤50
 1≤Bi≤N
 Bi≠Bj,1≤i<j≤|B|
 Sample Input
 
 3 1
 3 0 0
 1 1
 2 2 3
 Sample Output
 
 2
 Explanation
 There are 3 types of skill set present and only 1 wizard. Initially all three people know 1st skill set, while no one knows 2nd and 3rd skill set.
 First, and only, wizard' initial list are: A=[1] and B=[2,3]. So he can perform any of the 1→2 or 1→3 transformation. Suppose he go for 1→2 transformation on any of person with 1st skill set, then list A will be updated to an empty list [] and and list B will be [3]. Now he can't perform another transformation as list A is empty. So there will be two people with 1st skill set, and 1 people with 2nd skill set. So there are two skill sets available in the kingdom.
 

*/

#include <iostream>
#include <vector>
#include<map>

using namespace std;

// Self Template Code BGEIN

#define sz(x) ((int)((x).size()))
#define out(x) printf(#x" %d\n", x)
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define repf(i,a,b) for (int i = (a); i <= (b); ++i)
#define repd(i,a,b) for (int i = (a); i >= (b); --i)
#define repcase int t, Case = 1; for (scanf ("%d", &t); t; --t)
#define repeach(i,x) for (__typeof((x).begin()) i = (x).begin(); i != (x).end(); ++i)

typedef long long int64;
typedef pair<int, int> pii;

int sgn(double x) { return (x > 1e-8) - (x < -1e-8); }
int count_bit(int x) { return x == 0? 0 : count_bit(x >> 1) + (x & 1); }

template<class T> inline void ckmin(T &a, const T b) { if (b < a) a = b; }
template<class T> inline void ckmax(T &a, const T b) { if (b > a) a = b; }

// Self Template Code END

struct graph {
    static const int maxn = 50 * 30 * 2 + 200 * 30 + 10;
    static const int inf = (-1u) >> 1;
    
    struct Adj {
        int v, c, b;
        Adj(int _v, int _c, int _b): v(_v), c(_c), b(_b) {}
        Adj() {};
    };
    int i, n, S, T, h[maxn], cnt[maxn];
    vector <Adj> adj[maxn];
    void clear() {
        for (i = 0; i < n; ++i)
            adj[i].clear();
        n = 0;
    }
    void insert(int u, int v, int c, int d = 0) {
        // printf ("insert %d %d %d\n", u, v, c);
        n = max(n, max(u, v) + 1);
        adj[u].push_back(Adj(v, c, adj[v].size()));
        adj[v].push_back(Adj(u, c * d, adj[u].size() - 1));
    }
    int maxflow(int _S, int _T) {
        S = _S, T = _T;
        fill(h, h + n, 0);
        fill(cnt, cnt + n, 0);
        int flow = 0;
        while (h[S] < n)
            flow += dfs(S, inf);
        return flow;
    }
    int dfs(int u, int flow) {
        if (u == T)
            return flow;
        int minh = n - 1, ct = 0;
        for (vector<Adj>::iterator it = adj[u].begin(); flow && it != adj[u].end(); ++it) {
            if (it -> c) {
                if (h[it -> v] + 1 == h[u]) {
                    int k = dfs(it -> v, min(it -> c, flow));
                    if (k) {
                        it -> c -= k;
                        adj[it -> v][it -> b].c += k;
                        flow -= k;
                        ct += k;
                    }
                    if (h[S] >= n)
                        return ct;
                }
                minh = min(minh, h[it -> v]);
            }
        }
        if (ct)
            return ct;
        if (--cnt[h[u]] == 0)
            h[S] = n;
        h[u] = minh + 1;
        ++cnt[h[u]];
        return 0;
    }
};

struct wizard {
    int NA, NB;
    vector<int> A, B;
    
    void input() {
        scanf ("%d", &NA);
        A.clear();
        rep (i, NA) {
            int bar;
            scanf ("%d", &bar);
            A.push_back(--bar);
        }
        scanf ("%d", &NB);
        B.clear();
        rep (i, NB) {
            int bar;
            scanf ("%d", &bar);
            B.push_back(--bar);
        }
    }
};

const int MAXN = 200 + 2;
const int MAXW = 50 + 2;

wizard wizards[MAXW];
graph g;
int num[MAXN];
int n, w;

int get_level_id(int x, int y) {
    return y * n + x + 2;
}

int solve() {
    // build graph
    
    // 0 : clear
    g.clear();
    int S = 0, T = 1;
    
    // 1 : build level
    rep (i, n) {
        rep (j, w) {
            g.insert (get_level_id(i, j), get_level_id(i, j + 1), graph::inf);
        }
    }
    rep (i, n) {
        if (num[i]) g.insert (S, get_level_id(i, 0), num[i]);
        g.insert (get_level_id(i, w), T, 1);
    }
    
    // 2 : build transform edge
    int vertex_cnt = get_level_id(n - 1, w) + 1;
    map<int, int> in_vertex_id, out_vertex_id;
    rep (i, w) {
        rep (j, wizards[i].NA) {
            g.insert (get_level_id(wizards[i].A[j], i), vertex_cnt, 1);
            in_vertex_id[wizards[i].A[j]] = vertex_cnt++;
        }
        rep (j, wizards[i].NB) {
            g.insert (vertex_cnt, get_level_id(wizards[i].B[j], i + 1), 1);
            out_vertex_id[wizards[i].B[j]] = vertex_cnt++;
        }
        rep (j, wizards[i].NA) {
            rep (k, wizards[i].NB) {
                g.insert (in_vertex_id[wizards[i].A[j]], out_vertex_id[wizards[i].B[k]], 1);
            }
        }
    }
    
    return g.maxflow(S, T);
}

int main() {
    while (scanf ("%d%d", &n, &w) != EOF) {
        rep (i, n) {
            scanf ("%d", &num[i]);
        }
        rep (i, w) {
            wizards[i].input();
        }
        
        printf ("%d\n", solve());
    }
    return 0;
}
