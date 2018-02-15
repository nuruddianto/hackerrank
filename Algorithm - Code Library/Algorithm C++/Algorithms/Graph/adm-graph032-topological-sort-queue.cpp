/*
    Topologically sort a directed acyclic graph (DAG) and Queue without DFS
    Author Risman Adnan

    Topological sorting is the most important operation on directed acyclic graphs (DAGs). 
    It orders the vertices on a line such that all directed edges go from left to right. 
    Such an ordering cannot exist if the graph contains a directed cycle, because there is 
    no way you can keep going right on a line and still return back to where you started from!

    Each DAG has at least one topological sort. The importance of topological sorting is that 
    it gives us an ordering to process each vertex before any of its successors. 
    Suppose the edges represented precedence constraints, such that edge (x, y) means job x 
    must be done before job y. Then, any topological sort defines a legal schedule. Indeed, 
    there can be many such orderings for a given DAG.
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


void compute_indegrees(graph *g, int in[])
{
    int i;				/* counter */
    edgenode *p;			/* temporary pointer */
    
    for (i=1; i<=g->nvertices; i++) in[i] = 0;
    
    for (i=1; i<=g->nvertices; i++) {
        p = g->edges[i];
        while (p != NULL) {
            in[ p->y ] ++;
            p = p->next;
        }
    }
}


void topsort(graph *g, int sorted[])
{
    int indegree[MAXV+1];		/* indegree of each vertex */
    queue zeroin;				/* vertices of indegree 0 */
    int x, y;					/* current and next vertex */
    int i, j;					/* counters */
    edgenode *p;				/* temporary pointer */
    
    compute_indegrees(g,indegree);
    init_queue(&zeroin);
    for (i=1; i<=g->nvertices; i++)
        if (indegree[i] == 0) enqueue(&zeroin,i);
    
    j=0;
    while (empty_queue(&zeroin) == FALSE) {
        j = j+1;
        x = dequeue(&zeroin);
        sorted[j] = x;
        p = g->edges[x];
        while (p != NULL) {
            y = p->y;
            indegree[y] --;
            if (indegree[y] == 0) enqueue(&zeroin,y);
            p = p->next;
        }
    }
    
    if (j != g->nvertices)
        printf("Not a DAG -- only %d vertices found\n",j);
}


int main()
{
    graph g;
    int out[MAXV+1];
    int i;
    
    read_graph(&g,TRUE);
    print_graph(&g);
    
    topsort(&g,out);
    
    for (i=1; i<=g.nvertices; i++)
        printf(" %d",out[i]);
    printf("\n");
    
}

