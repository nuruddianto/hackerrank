/*
 * Author: Gilang Kusuma Jati (gilang.k@samsung.com), SRIN.
 */
package graphalgorithm;

import datastructure.Stack;
import datastructure.UndirectedGraph;

public class FindPathUndirectedGraphDFS 
{
	private boolean[] visited;    
    private int[] parent;        
    private int sourceVertex;         

    // computes a path between source vertex and every other vertex in graph
    public FindPathUndirectedGraphDFS(UndirectedGraph graph, int sourceVertex) 
    {
        this.sourceVertex = sourceVertex;
        parent = new int[graph.getTotalVertices()];
        visited = new boolean[graph.getTotalVertices()];
        dfs(graph, sourceVertex);
    }

    // depth first search from vertex v
    private void dfs(UndirectedGraph graph, int v) 
    {
    	visited[v] = true;
        
        if (!graph.getAdjacency(v).isEmpty())
        {
	        Integer[] adj = graph.getAdjacency(v).toArray(Integer.class);
	        for(int w : adj)
	        {
	        	if (!visited[w]) 
	            {
	                parent[w] = v;
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

    // returns a path between the source vertex and vertex v, or return null  if no such path.
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
