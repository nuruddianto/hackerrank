/*

    Compute shortest paths in weighted graphs using Dijkstra's algorithm
    This code using Weighted Graph. O(n2)

    Dijkstra’s algorithm is the method of choice for finding shortest paths in an edge- and/or 
    vertex-weighted graph. Given a particular start vertex s, it finds the shortest path from s 
    to every other vertex in the graph, including your desired destination t. Suppose the shortest 
    path from s to t in graph G passes through a particular intermediate vertex x. 
    Clearly, this path must contain the shortest path from s to x as its prefix, because if not, 
    we could shorten our s-to-t path by using the shorter s-to-x prefix. 

    Thus, we must compute the shortest path from s to x before we find the path from s to t.
    Dijkstra’s algorithm proceeds in a series of rounds, where each round establishes the shortest 
    path from s to some new vertex. This suggests a dynamic programming-like strategy. 

    This algorithm finds more than just the shortest path from s to t. It finds the shortest path 
    from s to all other vertices. This defines a shortest path spanning tree rooted in s. 
    For undirected graphs, this would be the breadth-first search tree, but in general it provides 
    the shortest path from s to all other vertices.

    Dijkstra works correctly only on graphs without negative-cost edges. Most applications do not 
    feature negative-weight edges, making this discus- sion academic. Floyd’s algorithm, works 
    correctly unless there are negative cost cycles, which grossly distort the shortest-path 
    structure. 

*/


#include<cstdio>
#include<iostream>

using namespace std;

#define MAXV        100     /* maximum number of vertices */
#define MAXDEGREE   50      /* maximum outdegree of a vertex */

#define TRUE        1
#define FALSE       0
#define MAXINT  100007


typedef struct edgenode {
    int y;              /* adjancency info */
    int weight;         /* edge weight, if any */
    edgenode *next;     /* next edge in list */
} edgenode;


typedef struct {
    edgenode *edges[MAXV+1];    /* adjacency info */
    int degree[MAXV+1];         /* outdegree of each vertex */
    int nvertices;              /* number of vertices in the graph */
    int nedges;                 /* number of edges in the graph */
    int directed;               /* is the graph directed? */
} graph;


int parent[MAXV+1];     /* discovery relation */


void initialize_graph(graph *g, bool directed)
{
    int i;              /* counter */
    
    g -> nvertices = 0;
    g -> nedges = 0;
    g -> directed = directed;
    
    for (i=1; i<=MAXV; i++) g->degree[i] = 0;
    for (i=1; i<=MAXV; i++) g->edges[i] = NULL;
}

void insert_edge(graph *g, int x, int y, bool directed, int w){
    edgenode *p;            /* temporary pointer */
    
    p = new edgenode();
    p->y = y;
    p->weight = w;
    
    p->next = g->edges[x];
    g->edges[x] = p;
    g->degree[x] ++;
    
    if (directed == FALSE)
        insert_edge(g,y,x,TRUE,w);
    else
        g->nedges ++;
    
}


void read_graph(graph *g, bool directed)
{
    int i;              /* counter */
    int m;              /* number of edges */
    int x,y,w;          /* placeholder for edge and weight */
    
    initialize_graph(g,directed);
    
    cin >> g->nvertices;
    cin >> m;
    
    for (i=1; i<=m; i++) {
        cin >> x >> y >> w;
        insert_edge(g,x,y,directed,w);
    }
}


void delete_edge(graph *g, int x, int y, bool directed)
{
    edgenode *p, *p_back;           /* temporary pointers */
    
    p = g->edges[x];
    p_back = NULL;
    
    while (p != NULL)
        if (p->y == y) {
            g->degree[x] --;
            if (p_back != NULL)
                p_back->next = p->next;
            else
                g->edges[x] = p->next;
            
            delete p;
            
            if (directed == FALSE)
                delete_edge(g,y,x,TRUE);
            else
                g->nedges --;
            return;
        }
        else
            p = p->next;
    
    cout << "Warning: deletion(" << x << "," << y << ") not found in graph" << endl;
}


void print_graph(graph *g)
{
    int i;                          /* counter */
    edgenode *p;                    /* temporary pointer */
    
    for (i=1; i<=g->nvertices; i++) {
        cout << i << ":";
        p = g->edges[i];
        while (p != NULL) {
            cout << " "<< p->y;
            p = p->next;
        }
        cout << endl;
    }
}


void find_path(int start, int end, int parents[])
{
    if ((start == end) || (end == -1)){
        cout << endl;
        cout << start;
    }else {
        find_path(start,parents[end],parents);
        cout << " " << end;
    }
}



void dijkstra(graph *g, int start)      /* WAS prim(g,start) */
{
    int i;                      /* counter */
    edgenode *p;                /* temporary pointer */
    bool intree[MAXV+1];        /* is the vertex in the tree yet? */
    int distance[MAXV+1];       /* distance vertex is from start */
    int v;              /* current vertex to process */
    int w;              /* candidate next vertex */
    int weight;         /* edge weight */
    int dist;           /* best current distance from start */
    
    for (i=1; i<=g->nvertices; i++) {
        intree[i] = FALSE;
        distance[i] = MAXINT;
        parent[i] = -1;
    }
    
    distance[start] = 0;
    v = start;
    
    while (intree[v] == FALSE) {
        intree[v] = TRUE;
        p = g->edges[v];
        while (p != NULL) {
            w = p->y;
            weight = p->weight;
            /* CHANGED */       if (distance[w] > (distance[v]+weight)) {
            /* CHANGED */           distance[w] = distance[v]+weight;
            /* CHANGED */           parent[w] = v;
            }
            p = p->next;
        }
        
        v = 1;
        dist = MAXINT;
        for (i=1; i<=g->nvertices; i++)
            if ((intree[i] == FALSE) && (dist > distance[i])) {
                dist = distance[i];
                v = i;
            }
    }
    for (i=1; i<=g->nvertices; i++) cout << i << " - " << distance[i] << endl;
}

int main()
{
    graph g;
    int i;
    read_graph(&g,FALSE);
    dijkstra(&g,1);
    
    for (i=1; i<=g.nvertices; i++)
        find_path(1,i,parent);
    cout << endl;
}

