/*


    Compute Minimum Spanning Trees (MST) of graphs via Kruskal's algorithm and Set Union
    Weighted graph and using setunion data structure. O(m log m). Good for sparse graph.
    Using qsort from stdlib ....
    Author : Risman Adnan

    A spanning tree of a graph G = (V,E) is a subset of edges from E forming a tree connecting 
    all vertices of V . For edge-weighted graphs, we are particularly interested in the 
    minimum spanning tree—the spanning tree whose sum of edge weights is as small as possible.

    A minimum spanning tree minimizes the total length over all possible spanning trees. 
    However, there can be more than one minimum spanning tree in a graph. 
    Indeed, all spanning trees of an unweighted (or equally weighted) graph G are 
    minimum spanning trees, since each contains exactly n − 1 equal-weight edges. 
    Such a spanning tree can be found using depth-first or breadth-first search. 

 
    
*/

#include <cstdio>
#include <cstdlib>
#include<iostream>


using namespace std;

#define SET_SIZE       1000
#define MAXV            100     /* maximum number of vertices */
#define TRUE            1
#define FALSE           0
#define MAXINT          100007


typedef struct {
    int p[SET_SIZE+1];          /* parent element */
    int size[SET_SIZE+1];       /* number of elements in subtree i */
    int n;                      /* number of elements in set */
} setunion;

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

typedef struct {
    int x, y;                       /* adjacency info */
    int weight;                     /* edge weight, if any */
} edge_pair;


/************************************************************/


void set_union_init(setunion *s, int n)
{
    int i;              /* counter */
    
    for (i=1; i<=n; i++) {
        s->p[i] = i;
        s->size[i] = 1;
    }
    
    s->n = n;
}

int find(setunion *s, int x)
{
    if (s->p[x] == x)
        return(x);
    else
        return( find(s,s->p[x]) );
}


bool same_component(setunion *s, int s1, int s2)
{
    return ( find(s,s1) == find(s,s2) );
}



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

int union_sets(setunion *s, int s1, int s2)
{
    int r1, r2;         /* roots of sets */
    r1 = find(s,s1);
    r2 = find(s,s2);
    cout << "s1= " << s1 << " r1= " << r1 << " s2 = " << s2 << " r2= " << r2 << endl;
    if (r1 == r2) return 0;     /* already in same set */
    if (s->size[r1] >= s->size[r2]) {
        s->size[r1] = s->size[r1] + s->size[r2];
        s->p[ r2 ] = r1;
    }
    else {
        s->size[r2] = s->size[r1] + s->size[r2];
        s->p[ r1 ] = r2;
    }
    
    return 0; // this may error
}


void print_set_union(setunion *s)
{
    for (int i=1; i<=s->n; i++)cout << i << " set= " << s->p[i] << " size= " << s->size[i] << endl;
    cout << endl;
}


void to_edge_array(graph *g, edge_pair e[])
{
    // convert graph content to edge_pair array
    int i,m;                /* counters */
    edgenode *p;            /* temporary pointer */
    
    m = 0;
    for (i=1; i<=g->nvertices; i++) {
        p = g->edges[i];
        while (p != NULL) {
            if (p->y > i) {
                e[m].x = i;
                e[m].y = p->y;
                e[m].weight = p->weight;
                m = m+1;
            }
            p = p->next;
        }
    }
}

typedef int (*compfn)(const void*, const void*);

int weight_compare(edge_pair *x, edge_pair *y)
{
    if (x->weight < y->weight) return(-1);
    if (x->weight > y->weight) return(1);
    return(0);
}

void kruskal(graph *g)
{
    int i;                      /* counter */
    setunion s;                 /* set union data structure */
    edge_pair e[MAXV+1];        /* array of edges data structure */
    set_union_init(&s, g->nvertices);
    cout << "initialized set union " << endl;
    to_edge_array(g, e);
    
    // sort the edge_pair array using qsort (you can replace with any sort here)
    qsort((void *) &e,g->nedges,sizeof(edge_pair), (compfn)weight_compare);
    
    for (i=0; i<(g->nedges); i++) {
        print_set_union(&s);
        if (!same_component(&s,e[i].x,e[i].y)) {
            cout << "edge (" << e[i].x << "," << e[i].y << ") of weight " << e[i].weight << " in MST";
            cout << endl;
            union_sets(&s,e[i].x,e[i].y);
        }
    }
}
int main()
{
    graph g;
    read_graph(&g,FALSE); // Can use insert_edge manually
    print_graph(&g);
    kruskal(&g);
    printf("Out of Kruskal\n");
    
}