/*
 * Author: Gilang Kusuma Jati (gilang.k@samsung.com), SRIN.
 */
package graphalgorithm;

import datastructure.DirectedGraph;
import datastructure.Stack;

public class FindShortestCycleDirectedGraph 
{
	private Stack<Integer> cycle;    // directed cycle (or null if no such cycle)
    private int length;

    public FindShortestCycleDirectedGraph(DirectedGraph graph) 
    {
        DirectedGraph R = graph.reverse();
        length = graph.getTotalVertices() + 1;
        for (int v = 0; v < graph.getTotalVertices(); v++) 
        {
            FindPathDirectedGraphBFS bfs = new FindPathDirectedGraphBFS(R, v);
            
            if (!graph.getAdjacency(v).isEmpty())
            {
            	Integer[] adj = graph.getAdjacency(v).toArray(Integer.class);
	            for (int w : adj) 
	            {
	                if (bfs.hasPathTo(w) && (bfs.getDistanceTo(w) + 1) < length) 
	                {
	                    length = bfs.getDistanceTo(w) + 1;
	                    cycle = new Stack<Integer>();
	                    
	                    Stack<Integer> path = bfs.getPathTo(w);
	                    if (!path.isEmpty())
	                    {
	                    	Integer[] arr = path.toArray(Integer.class);
	                    	for (int x : arr)
	                    		cycle.push(x);
	                    }
	                    
	                    cycle.push(v);
	                }
	            }
            }
            
        }
    }

    // return true if graph has cycle
    public boolean hasCycle()
    { 
    	return cycle != null;   
    }
    
    // return the cycle if graph has cycle, return null otherwise
    public Stack<Integer> getCycle() 
    {
    	return cycle;
    }
    
    public int length()              
    {
    	return length;
    }
}
