/*
    Compute the connected components of a graph.
    Implement BFS to compute connected component.

    We say that a graph is connected if there is a path between any two vertices.
    A connected component of an undirected graph is a maximal set of vertices such that 
    there is a path between every pair of vertices. Connected components can be found 
    using breadth-first search, since the vertex order does not matter. 

    Observe how we increment a counter c denoting the current component number with each 
    call to bfs. We could have explicitly bound each vertex to its component number 
    (instead of printing the vertices in each component) by changing the action of process vertex.

*/

#include<cstdio>
#include<iostream>

using namespace std;

#define MAXV        100     /* maximum number of vertices */

#define QUEUESIZE       1000
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


typedef int item_type; // Type of the item node / vertice

typedef struct {
    item_type q[QUEUESIZE+1];       /* body of queue */
    int first;                      /* position of first element */
    int last;                       /* position of last element */
    int count;                      /* number of queue elements */
} queue;


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

// Print the graph for visualization
void print_graph(graph *g)
{
    int i;                  /* counter */
    edgenode *p;            /* temporary pointer */
    
    for (i=0; i<g->nvertices; i++) {
        cout << "Adjacency List of Vertex : " << i << endl;
        cout << "Head ";
        p = g->edges[i];
        while (p != NULL) {
            cout << "->"<< p->y;
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

void init_queue(queue *q)
{
    q->first = 0;
    q->last = QUEUESIZE-1;
    q->count = 0;
}

void enqueue(queue *q, item_type x)
{
    if (q->count >= QUEUESIZE)
        cout << "Warning: queue overflow enqueue x= " << x << endl;
    else {
        q->last = (q->last+1) % QUEUESIZE;
        q->q[ q->last ] = x;
        q->count = q->count + 1;
    }
}

item_type dequeue(queue *q)
{
    item_type x;
    
    if (q->count <= 0) cout <<"Warning: empty queue dequeue.\n";
    else {
        x = q->q[ q->first ];
        q->first = (q->first+1) % QUEUESIZE;
        q->count = q->count - 1;
    }
    
    return(x);
}

item_type headq(queue *q)
{
    return( q->q[ q->first ] );
}

int empty_queue(queue *q)
{
    if (q->count <= 0) return (TRUE);
    else return (FALSE);
}

void process_vertex_early(int v){
    cout <<"processed vertex early " << v << endl;
}

void process_vertex_late(int v){
}


void process_edge(int x, int y){
    cout <<"processed edge (" << x << "," << y << ")" << endl;
}


void process_vertex(int v){
    cout <<"processed vertex  " << v << endl;
}




void bfs(graph *g, int start)
{
    queue q;            /* queue of vertices to visit */
    int v;              /* current vertex */
    int y;              /* successor vertex */
    edgenode *p;        /* temporary pointer */
    
    init_queue(&q);
    enqueue(&q,start);
    discovered[start] = TRUE;
    
    while (empty_queue(&q) == FALSE) {
        v = dequeue(&q);
        process_vertex_early(v);
        processed[v] = TRUE;
        p = g->edges[v];
        while (p != NULL) {
            y = p->y;
            if ((processed[y] == FALSE) || g->directed)
                process_edge(v,y);
            if (discovered[y] == FALSE) {
                enqueue(&q,y);
                discovered[y] = TRUE;
                parent[y] = v;
            }
            p = p->next;
        }
        process_vertex_late(v);
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
            bfs(g,i);
            cout << endl;
        }
}


int main()
{
    graph g;
    initialize_graph(&g, FALSE);
    g.nvertices = 4;
    insert_edge(&g, 0, 1, FALSE);
    insert_edge(&g, 0, 2, FALSE);
    insert_edge(&g, 1, 2, FALSE);
    insert_edge(&g, 2, 0, FALSE);
    insert_edge(&g, 2, 3, FALSE);
    insert_edge(&g, 3, 3, FALSE);
    print_graph(&g);
    connected_components(&g);
}




