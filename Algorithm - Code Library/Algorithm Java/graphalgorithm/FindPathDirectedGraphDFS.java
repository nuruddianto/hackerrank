/*
 * Author: Gilang Kusuma Jati (gilang.k@samsung.com), SRIN.
 */
package graphalgorithm;

import datastructure.DirectedGraph;
import datastructure.Stack;

public class FindPathDirectedGraphDFS 
{
	private boolean[] visited;  // visited[v] = true if v is reachable from s
    private int[] parent;      // parent[v] = last edge on path from s to v
    private final int sourceVertex;       // source vertex

    // computes a directed path from s to every other vertex in directed graph.
    public FindPathDirectedGraphDFS(DirectedGraph graph, int sourceVertex) 
    {
        visited = new boolean[graph.getTotalVertices()];
        parent = new int[graph.getTotalVertices()];
        this.sourceVertex = sourceVertex;
        dfs(graph, sourceVertex);
    }

    private void dfs(DirectedGraph graph, int vertex) 
    { 
        visited[vertex] = true;
        
        if (!graph.getAdjacency(vertex).isEmpty())
        {
        	Integer[] adj = graph.getAdjacency(vertex).toArray(Integer.class);
	        for (int w : adj) 
	        {
	            if (!visited[w]) 
	            {
	                parent[w] = vertex;
	                dfs(graph, w);
	            }
	        }
        }
    }

    // return true there if there is a path between the source vertex and vertex v
    public boolean hasPathTo(int v) 
    {
        return visited[v];
    }

    
    // returns a shortest path between the source vertex and vertex v, or null if no such path.
    public Stack<Integer> getPathTo(int v) 
    {
        if (!hasPathTo(v)) 
        	return null;
        
        Stack<Integer> path = new Stack<Integer>();
        for (int x = v; x != sourceVertex; x = parent[x])
            path.push(x);
        path.push(sourceVertex);
        
        return path;
    }
}
