/*
    Program to identify strongly connected components in a graph
    Author : Risman Adnan

    We are often concerned with strongly connected components—that is, partitioning a graph 
    into chunks such that directed paths exist between all pairs of vertices within a given chunk. 
    A directed graph is strongly connected if there is a directed path between any two vertices. 

    It is straightforward to use graph traversal to test whether a graph G = (V, E) is strongly 
    connected in linear time. First, do a traversal from some arbitrary vertex v. Every vertex in 
    the graph had better be reachable from v (and hence discovered on BFS or DFS starting from v),
    otherwise G cannot possibly be strongly connected. Now construct a graph G′ = (V,E′) with 
    the same vertex and edge set as G but with all edges reversed.
    
    By doing a DFS from v in G′, we find all vertices with paths to v in G. The graph is strongly 
    connected iff all vertices in G can (1) reach v and (2) are reachable from v.

    Graphs that are not strongly connected can be partitioned into strongly connected components.
    The set of such components and the weakly-connecting edges that link them together can be 
    determined using DFS. The algorithm is based on the observation that it is easy to find a 
    directed cycle using a depth-first search, since any back edge plus the down path in the 
    DFS tree gives such a cycle. All vertices in this cycle must be in the same strongly connected 
    component. Thus, we can shrink (contract) the vertices on this cycle down to a single vertex 
    representing the component, and then repeat. This process terminates when no directed cycle 
    remains, and each vertex represents a different strongly connected component.

*/


#include<cstdio>
#include<iostream>

using namespace std;

#define MAXV            100     /* maximum number of vertices */
#define STACKSIZE       1000

typedef struct {
    int s[STACKSIZE+1];             /* body of queue */
    int top;                        /* position of top element */
    int count;                      /* number of stack elements */
} stack;


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


int low[MAXV+1];            /* oldest vertex surely in component of v */
int scc[MAXV+1];            /* strong component number for each vertex */


stack active;               /* active vertices of unassigned component */
int components_found;       /* number of strong components identified */


void init_stack(stack *s)
{
    s->top = -1;
    s->count = 0;
}


void push(stack *s, int x)
{
    if (s->count >= STACKSIZE)
        cout << "Warning: stack overflow push x = " << x << endl;
    else {
        s->top = s->top + 1;
        s->s[ s->top ] = x;
        s->count = s->count + 1;
    }
}

int pop(stack *s)
{
    int x;
    
    if (s->count <= 0) cout << "Warning: empty stack pop.\n";
    else {
        x = s->s[ s->top ];
        s->top = s->top - 1;
        s->count = s->count - 1;
    }
    
    return(x);
}

int empty_stack(stack *s)
{
    if (s->count <= 0) return (TRUE);
    else return (FALSE);
}


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


void print_graph(graph *g)
{
    int i;              /* counter */
    edgenode *p;            /* temporary pointer */
    
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


void initialize_search(graph *g)
{
    int i;                          /* counter */
    
    timeint = 0;
    
    for (i=0; i<=g->nvertices; i++) {
        processed[i] = discovered[i] = FALSE;
        parent[i] = -1;
    }
}


void pop_component(int v)
{
    int t;                  /* vertex placeholder */
    
    components_found = components_found + 1;
    cout << v << " is in component " << components_found << endl;
    scc[ v ] = components_found;
    while ((t = pop(&active)) != v) {
        scc[ t ] = components_found;
        cout << t << " is in component " << components_found << " with " << v << endl;
    }
}


int edge_classification(int x, int y)
{
    if (parent[y] == x) return(TREE);
    if (discovered[y] && !processed[y]) return(BACK);
    if (processed[y] && (entry_time[y]>entry_time[x])) return(FORWARD);
    if (processed[y] && (entry_time[y]<entry_time[x])) return(CROSS);
    
    cout << "Warning: self loop (" << x << "," << y << ")" << endl;
    return TREE; // Be carefull to this logic.
}

void process_vertex_early(int v)
{
    cout << "entered vertex " << v << " at time " << entry_time[v] << endl;
    push(&active,v);
}

void process_vertex_late(int v)
{
    cout << "exit vertex " << v << " at time " << exit_time[v] << endl;
    
    if (low[v] == v) {      /* edge (parent[v],v) cuts off scc */
        cout << "strong component started backtracking from " << v << endl;
        pop_component(v);
    }
    
    if (entry_time[low[v]] < entry_time[low[parent[v]]])
        low[parent[v]] = low[v];
}

void process_edge(int x, int y)
{
    int classify;       /* edge class */
    
    classify = edge_classification(x,y);
    //cout << "(" << x << "," << y << ") class " << classify << endl;
    
    if (classify == BACK) {
        if (entry_time[y] < entry_time[ low[x] ] )
            low[x] = y;
    }
    
    if (classify == CROSS) {
        if (scc[y] == -1)   /* component not yet assigned */
            if (entry_time[y] < entry_time[ low[x] ] )
                low[x] = y;
    }
}




void dfs(graph *g, int v)
{
    edgenode *p;            /* temporary pointer */
    int y;              /* successor vertex */
    
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

void strong_components(graph *g)
{
    int i;              /* counter */
    
    for (i=1; i<=(g->nvertices); i++) {
        low[i] = i;
        scc[i] = -1;
    }
    
    components_found = 0;
    
    init_stack(&active);
    initialize_search(g);
    
    for (i=1; i<=(g->nvertices); i++)
        if (discovered[i] == FALSE) {
            dfs(g,i);
            /*pop_component(i); // Optional to display*/
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
    strong_components(&g);
    cout << components_found << " Strong Component Found !" << endl;
}
