/*


    Compute all-pairs shortest paths in weighted graphs floyd algorithm
    Floyd is using adjacency matrix and runs with O(n3).
    
    Floyd’s algorithm is best employed on an adjacency matrix data structure, 
    which is no extravagance since we must store all n2 pairwise distances anyway.
    The Floyd-Warshall algorithm starts by numbering the vertices of the graph from 1 to n. 

    The output of Floyd’s algorithm, as it is written, does not enable one to reconstruct the actual 
    shortest path between any given pair of vertices. These paths can be recovered if we retain 
    a parent matrix P of our choice of the last intermediate vertex used for each vertex pair (x, y).
    Say this value is k. The shortest path from x to y is the concatenation of the shortest path 
    from x to k with the shortest path from k to y, which can be reconstructed recursively given 
    the matrix P . Note, however, that most all-pairs applications need only the resulting distance 
    matrix. These jobs are what Floyd’s algorithm was designed for.

*/

#include <cstdio>
#include <iostream>
using namespace std;


#define TRUE    1
#define FALSE   0
#define MAXV        100     /* maximum number of vertices */
#define MAXINT      100007

typedef struct{
    int v;              /* neighboring vertex */
    int weight;         /* edge weight */
    bool in;            /* is the edge "in" the solution? */
} edge;

typedef struct{
    int weight[MAXV+1][MAXV+1];     /* adjacency/weight info */
    int nvertices;                  /* number of vertices in the graph */
} adjacency_matrix;


void initialize_adjacency_matrix(adjacency_matrix *g){
    int i,j;            /* counters */
    
    g -> nvertices = 0;
    
    for (i=1; i<=MAXV; i++)
        for (j=1; j<=MAXV; j++)
            g->weight[i][j] = MAXINT;
}

void read_adjacency_matrix(adjacency_matrix *g, bool directed){
    int i;              /* counter */
    int m;              /* number of edges */
    int x,y,w;          /* placeholder for edge and weight */
    
    initialize_adjacency_matrix(g);
    cin >> g->nvertices;
    cin >> m;
    for (i=1; i<=m; i++) {
        cin >> x >> y >> w;
        g->weight[x][y] = w;
        if (directed==FALSE) g->weight[y][x] = w;
    }
}


void print_graph(adjacency_matrix *g){
    int i,j;            /* counters */
    
    for (i=1; i<=g->nvertices; i++) {
        cout << i << ": ";
        for (j=1; j<=g->nvertices; j++)
            if (g->weight[i][j] < MAXINT)
                cout << " " << j;
        cout << endl;
    }
}

void print_adjacency_matrix(adjacency_matrix *g){
    int i,j;                        /* counters */
    
    for (i=1; i<=g->nvertices; i++) {
        cout << i << ": ";
        for (j=1; j<=g->nvertices; j++)
            cout << " " << g->weight[i][j];
        cout << endl;
    }
}



void floyd(adjacency_matrix *g){
    int i,j;            /* dimension counters */
    int k;              /* intermediate vertex counter */
    int through_k;          /* distance through vertex k */
    
    for (k=1; k<=g->nvertices; k++)
        for (i=1; i<=g->nvertices; i++)
            for (j=1; j<=g->nvertices; j++) {
                through_k = g->weight[i][k]+g->weight[k][j];
                if (through_k < g->weight[i][j])
                    g->weight[i][j] = through_k;
            }
}


int main(){
    adjacency_matrix g;
    read_adjacency_matrix(&g,FALSE);
    print_graph(&g);
    floyd(&g);
    print_adjacency_matrix(&g);
    
}