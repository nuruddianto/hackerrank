/*
Count all possible walks from a source to a destination with exactly k edges
Given a directed graph and two vertices ‘u’ and ‘v’ in it, count all possible walks from ‘u’ to ‘v’ with exactly k edges on the walk.

The graph is given as adjacency matrix representation where value of graph[i][j] as 1 indicates that there is an edge from vertex i to vertex j and a value 0 indicates no edge from i to j.

*/

// C++ program to count walks from u to v with exactly k edges
#include <iostream>
using namespace std;
 
// Number of vertices in the graph
#define V 4
 
// A naive recursive function to count walks from u to v with k edges
int countwalks(int graph[][V], int u, int v, int k)
{
   // Base cases
   if (k == 0 && u == v)      return 1;
   if (k == 1 && graph[u][v]) return 1;
   if (k <= 0)                return 0;
 
   // Initialize result
   int count = 0;
 
   // Go to all adjacents of u and recur
   for (int i = 0; i < V; i++)
       if (graph[u][i])  // Check if is adjacent of u
           count += countwalks(graph, i, v, k-1);
 
   return count;
}
 
// driver program to test above function
int main()
{
    /* Let us create the graph shown in above diagram*/
     int graph[V][V] = { {0, 1, 1, 1},
                        {0, 0, 0, 1},
                        {0, 0, 0, 1},
                        {0, 0, 0, 0}
                      };
    int u = 0, v = 3, k = 2;
    cout << countwalks(graph, u, v, k);
    return 0;
}
