//  A generic weighted graph data type with DFS functionalities
//
//  Author : Risman Adnan


#include<cstdio>
#include<iostream>

using namespace std;

#define MAXV        100     /* maximum number of vertices */
#define MAXDEGREE   50      /* maximum outdegree of a vertex */

/*  DFS edge types          */
#define TREE        0       /* tree edge */
#define BACK        1       /* back edge */
#define CROSS       2       /* cross edge */
#define FORWARD     3       /* forward edge */

#define TRUE    1
#define FALSE   0

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


bool processed[MAXV+1];     /* which vertices have been processed */
bool discovered[MAXV+1];        /* which vertices have been found */
int parent[MAXV+1];     /* discovery relation */

int entry_time[MAXV+1];         /* time of vertex entry */
int exit_time[MAXV+1];          /* time of vertex exit */
int timeint;                       /* current event time */

bool finished = FALSE;  /* if true, cut off search immediately */


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


int edge_classification(int x, int y)
{
    if (parent[y] == x) return(TREE);
    if (discovered[y] && !processed[y]) return(BACK);
    if (processed[y] && (entry_time[y]>entry_time[x])) return(FORWARD);
    if (processed[y] && (entry_time[y]<entry_time[x])) return(CROSS);
    
    cout << "Warning: self loop (" << x << "," << y << ")" << endl;
    return TREE; // I am not sure about this ya
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

void process_vertex_early(int v)
{
    timeint = timeint + 1;
    entry_time[v] = timeint;
    cout << "entered vertex " << v << " at time " << entry_time[v] << endl;
}

void process_vertex_late(int v)
{
    timeint = timeint + 1;
    exit_time[v] = timeint;
    cout << "exit vertex " << v << " at time " << entry_time[v] << endl;
}

void process_edge(int x, int y)
{
    int classify;       /* edge class */
    
    classify = edge_classification(x,y);
    
    if (classify == BACK) cout << "back edge (" << x << "," << y << ")" << endl;
    else if (classify == TREE) cout << "tree edge (" << x << "," << y << ")" << endl;
    else if (classify == FORWARD) cout << "forward edge (" << x << "," << y << ")" << endl;
    else if (classify == CROSS) cout << "cross edge (" << x << "," << y << ")" << endl;
    else cout << "edge (" << x << "," << y << ") not in valid class" << classify << endl;
}



void dfs(graph *g, int v)
{
    edgenode *p;                    /* temporary pointer */
    int y;                          /* successor vertex */
    
    if (finished) return;           /* allow for search termination */
    
    discovered[v] = TRUE;
    timeint = timeint + 1;
    entry_time[v] = timeint;
    cout << "entered vertex " << v << " at time " << entry_time[v] << endl;
    
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
    cout << "exit vertex " << v << " at time " << entry_time[v] << endl;
    
    processed[v] = TRUE;
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


void connected_components(graph *g)
{
    int c;              /* component number */
    int i;              /* counter */
    
    initialize_search(g);
    
    c = 0;
    for (i=1; i<=g->nvertices; i++)
        if (discovered[i] == FALSE) {
            c = c+1;
            cout << "Component " << c << ":";
            dfs(g,i);
            cout << endl;
        }
}

int main(){
    
    return 0;
}