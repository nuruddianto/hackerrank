package code;

import java.util.*;

public class BreadthFirstShortestPath {
	
	static Map<Integer, LinkedList<Integer>> adjList;
	
	public BreadthFirstShortestPath(int nodes){
		adjList = new HashMap<Integer, LinkedList<Integer>>();
		for(int i=0; i <= nodes;i++){
			adjList.put(i, new LinkedList<Integer>());
		}
	}
	
	public static void addAdjency(int node1, int node2){
		adjList.get(node1).add(node2);
	}
	
	public static LinkedList<Integer> getAdjencyNodes(int node){
		return adjList.get(node);
	}
	
	public static void printList(){
		int i =0;
		for(Map.Entry<Integer, LinkedList<Integer>> map : adjList.entrySet()){
			//int key = map.getKey();
			System.out.print("adjacencyList[" + i + "] -> ");
			LinkedList<Integer> list = map.getValue();
			for(int listVal : list){
				System.out.print("("+listVal+")");
			}
			++i;
			System.out.println();
		}
	}
	
	public static void main(String[] args){
				
		Scanner sc = new Scanner(System.in);
		int T = sc.nextInt();
		
		for(int i=0; i < T; i++){
			int totalNode = sc.nextInt();
			int totalEdge = sc.nextInt();
			//System.out.println(totalEdge);
			BreadthFirstShortestPath bfs = new BreadthFirstShortestPath(totalNode);
			for(int a=0; a< totalEdge; a++ ){
				
				int node1 = sc.nextInt()-1;
				int node2 = sc.nextInt()-1;
				
				addAdjency(node1, node2);
				addAdjency(node2, node1);
			}		
			
			int start = sc.nextInt()-1;
			//System.out.println("start= "+ start);
			
			for(int b=0; b < totalNode; b++){
				if(b!= start){
					System.out.print(doBfs(start, b, totalNode)+" ");
					//doBfs(start, b, totalNode);
				}			
			}
			
			//printList();
			
			System.out.println();
		}
		
		sc.close();
	}
	
	public static int doBfs(int start, int targetNode, int totalNodes ){
		Queue<Integer> queueFirst = new LinkedList<>();
		Queue<Integer> queueSecond =  new LinkedList<>();
		
		queueFirst.offer(targetNode);
				
		boolean[] visitedNodes = new boolean[totalNodes];
		int weight=6;
		int level =0;
		
		while(!queueFirst.isEmpty() || !queueSecond.isEmpty()){
			while(!queueFirst.isEmpty()){
				
				int tmpNode = queueFirst.poll();
				//System.out.print(tmpNode+" ");
				
				if(visitedNodes[tmpNode]){
					continue;
				}
				
				if(tmpNode == start){
					return level*weight;
				}
				
				visitedNodes[tmpNode] = true;
				queueSecond.addAll(getAdjencyNodes(tmpNode));
				
			}
			level++;
			
			while(!queueSecond.isEmpty()){
				int tmpNode = queueSecond.poll();
				//System.out.print(tmpNode+" ");
				
				if(visitedNodes[tmpNode]){
					continue;
				}
				
				if(tmpNode == start){
					return level*weight;
				}
				
				visitedNodes[tmpNode] = true;
				queueFirst.addAll(getAdjencyNodes(tmpNode));
			}
			level++;
			
		}
		
		
		return -1;

		
	}
}