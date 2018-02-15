/*
    Topologically sort a directed acyclic graph by DFS numbering (DAG) Using DFS and stack.
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


    Topological sorting can be performed efficiently using depth-first searching. 
    A directed graph is a DAG if and only if no back edges are encountered. Labeling the 
    vertices in the reverse order that they are marked processed finds a topological sort 
    of a DAG. We push each vertex on a stack as soon as we have evaluated all outgoing edges. 
    The top vertex on the stack always has no incoming edges from any vertex on the stack. 
    Repeatedly popping them off yields a topological ordering.


*/


#include<cstdio>
#include<iostream>

using namespace std;

#define MAXV        100     /* maximum number of vertices */

/*  DFS edge types          */
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

#define STACKSIZE       1000

typedef struct {
    int s[STACKSIZE+1];		/* body of queue */
    int top;                        /* position of top element */
    int count;                      /* number of stack elements */
} stack;

stack sorted;			/* topological ordering of vertices */

void init_stack(stack *s)
{
    s->top = -1;
    s->count = 0;
}


void push(stack *s, int x)
{
    if (s->count >= STACKSIZE)
        printf("Warning: stack overflow push x=%d\n",x);
    else {
        s->top = s->top + 1;
        s->s[ s->top ] = x;
        s->count = s->count + 1;
    }
}

int pop(stack *s)
{
    int x;
    
    if (s->count <= 0) printf("Warning: empty stack pop.\n");
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

void print_stack(stack *s)
{
    int i;				/* counter */
    
    for (i=(s->count-1); i>=0; i--)
        printf("%d ",s->s[i]);
    
    printf("\n");
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
    return TREE; // I am not sure about this ya
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
    push(&sorted,v);
    cout << "exit vertex " << v << " at time " << entry_time[v] << endl;
}

void process_edge(int x, int y)
{
    int classify;              /* edge class */
    
    classify = edge_classification(x,y);
    
    if (classify == BACK)
        printf("Warning: directed cycle found, not a DAG\n");
}


void dfs(graph *g, int v)
{
    edgenode *p;            /* temporary pointer */
    int y;              /* successor vertex */
    
    if (finished) return;       /* allow for search termination */
    
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

void topsort(graph *g)
{
    int i;				/* counter */
    
    init_stack(&sorted);
    
    for (i=1; i<=g->nvertices; i++)
        if (discovered[i] == FALSE)
            dfs(g,i);
    
    print_stack(&sorted);		/* report topological order */
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
    
    topsort(&g);
    
}