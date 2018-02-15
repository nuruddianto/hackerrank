/*
    Program to identify a cycle in a graph, if one exists.
    Using DFS to find back edge.
    Author : Risman Adnan

    Back edges are the key to finding a cycle in an undirected graph. 
    If there is no back edge, all edges are tree edges, and no cycle exists in a tree. 
    But any back edge going from x to an ancestor y creates a cycle with the tree path 
    from y to x. Such a cycle is easy to find using DFS below. We use the finished flag 
    to terminate after finding the first cycle.

*/

#include<cstdio>
#include<iostream>

using namespace std;

#define MAXV        100     /* maximum number of vertices */

/*  DFS edge types      */

#define TREE        0       /* tree edge */
#define BACK        1       /* back edge */
#define CROSS       2       /* cross edge */
#define FORWARD     3       /* forward edge */

#define TRUE    1
#define FALSE   0

bool processed[MAXV+1];     /* which vertices have been processed */
bool discovered[MAXV+1];    /* which vertices have been found */
int parent[MAXV+1];         /* discovery relation */

int entry_time[MAXV+1];     /* time of vertex entry */
int exit_time[MAXV+1];      /* time of vertex exit */
int timeint;                   /* current event time */

bool finished = FALSE;      /* if true, cut off search immediately */


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



void initialize_graph(graph *g, bool directed)
{
    int i;              /* counter */
    
    g -> nvertices = 0;
    g -> nedges = 0;
    g -> directed = directed;
    
    for (i=1; i<=MAXV; i++) g->degree[i] = 0;
    for (i=1; i<=MAXV; i++) g->edges[i] = NULL;
}

void insert_edge(graph *g, int x, int y, bool directed)
{
    edgenode *p;            /* temporary pointer */
    
    p = new edgenode(); /* allocate storage for edgenode */
    
    p->weight = NULL;
    p->y = y;
    p->next = g->edges[x];
    
    g->edges[x] = p;        /* insert at head of list */
    
    g->degree[x] ++;
    
    if (directed == FALSE)
        insert_edge(g,y,x,TRUE);
    else
        g->nedges ++;
}

// Prototype to read graph from test cases
void read_graph(graph *g, bool directed)
{
    int i;              /* counter */
    int m;              /* number of edges */
    int x, y;           /* vertices in edge (x,y) */
    
    initialize_graph(g, directed);
    cin >> g->nvertices;
    cin >> m;
    
    for (i=1; i<=m; i++) {
        cin >> x >> y;
        insert_edge(g,x,y,directed);
    }
}



void delete_edge(graph *g, int x, int y, bool directed)
{
    edgenode *p, *p_back;       /* temporary pointers */
    
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
    int i;              /* counter */
    edgenode *p;            /* temporary pointer */
    
    for (i=0; i<g->nvertices; i++) {
        cout << i << ":";
        p = g->edges[i];
        while (p != NULL) {
            cout << " "<< p->y;
            p = p->next;
        }
        cout << endl;
    }
}



void initialize_search(graph *g)
{
    int i;                          /* counter */
    
    timeint = 0;
    
    for (i=0; i<=g->nvertices; i++) {
        processed[i] = discovered[i] = FALSE;
        parent[i] = -1;
    }
}

int edge_classification(int x, int y)
{
    if (parent[y] == x) return(TREE);
    if (discovered[y] && !processed[y]) return(BACK);
    if (processed[y] && (entry_time[y]>entry_time[x])) return(FORWARD);
    if (processed[y] && (entry_time[y]<entry_time[x])) return(CROSS);
    
    cout << "Warning: self loop (" << x << "," << y << ")" << endl;
    return TREE;
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



void process_vertex_early(int v){
}

void process_vertex_late(int v){
}

void process_edge(int x, int y){
    if (parent[x] != y) {   /* found back edge! */
        cout << "Cycle Found (" << x << "," << y << ")" << endl;
        find_path(y,x,parent);
        cout << endl;
        finished = TRUE;
    }
}


void dfs(graph *g, int v)
{
    edgenode *p;                /* temporary pointer */
    int y;                      /* successor vertex */
    
    if (finished) return;       /* allow for search termination */
    
    discovered[v] = TRUE;
    timeint = timeint + 1;
    entry_time[v] = timeint;
    
    /*printf("entered vertex %d at time %d\n",v, entry_time[v]);*/
    
    process_vertex_early(v);
    
    p = g->edges[v];
    while (p != NULL) {
        y = p->y;
        if (discovered[y] == FALSE) {
            parent[y] = v;
            process_edge(v,y);
            dfs(g,y);
        }
        else if ((!processed[y]) || (g->directed))
            process_edge(v,y);
        
        if (finished) return;
        
        p = p->next;
    }
    
    process_vertex_late(v);
    
    timeint = timeint + 1;
    exit_time[v] = timeint;
    /*printf("exit vertex %d at time %d\n",v, exit_time[v]);*/
    
    processed[v] = TRUE;
}



int main()
{
    graph g;
    initialize_graph(&g, TRUE);
    g.nvertices = 4;
    insert_edge(&g, 0, 1, TRUE);
    insert_edge(&g, 0, 2, TRUE);
    insert_edge(&g, 1, 2, TRUE);
    insert_edge(&g, 2, 0, TRUE);
    insert_edge(&g, 2, 3, TRUE);
    insert_edge(&g, 3, 3, TRUE);
    print_graph(&g);
    initialize_search(&g);
    dfs(&g,0);
}

