/*

    Program to define graph data structure using C/C++ without STL
    Author : Risman Adnan

    The program is using adjacency list, suitable for un-weighted graph. 
*/

#include<cstdio>
#include<iostream>

using namespace std;

#define MAXV    100     /* maximum number of vertices */
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


// Initialize the graph - set number of vertice and edge to zero. Adjacent list to null
void initialize_graph(graph *g, bool directed)
{
    int i;              /* counter */
    
    g -> nvertices = 0;
    g -> nedges = 0;
    g -> directed = directed;
    
    for (i=1; i<=MAXV; i++) g->degree[i] = 0;
    for (i=1; i<=MAXV; i++) g->edges[i] = NULL;
}

// Insert the edge (x, y) pair.
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
        insert_edge(g,y,x,TRUE); /* If not directed, insert reverse edge*/
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

// Function to delete edge in graph
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

int main(){
    graph g;
    initialize_graph(&g, FALSE);
    g.nvertices = 5;
    insert_edge(&g, 0, 1, FALSE);
    insert_edge(&g, 0, 4, FALSE);
    insert_edge(&g, 1, 2, FALSE);
    insert_edge(&g, 1, 3, FALSE);
    insert_edge(&g, 1, 4, FALSE);
    insert_edge(&g, 2, 3, FALSE);
    insert_edge(&g, 3, 4, FALSE);
    print_graph(&g);
    delete_edge(&g, 0,1,FALSE);
    cout << "NEW GRAPH " << endl;
    print_graph(&g);
}

