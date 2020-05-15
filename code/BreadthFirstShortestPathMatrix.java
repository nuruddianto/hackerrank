package code;

import java.util.*;

public class BreadthFirstShortestPathMatrix {
	static int totalNodes, totalEdges, S;
	
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int T = sc.nextInt();
		
		for(int i =0; i < T; i++){
			totalNodes = sc.nextInt();
			totalEdges = sc.nextInt();
			int map[][] = new int[totalNodes][totalNodes];
			
			for(int a=0; a < totalEdges; a++){
				int node1 = sc.nextInt()-1;
				int node2 = sc.nextInt()-1;
				map[node1][node2] = 1;
				map[node2][node1] = 1;
			}
			
			S = sc.nextInt()-1;
			
			for(int b=0; b < totalNodes; b++){
				if(b != S){
					System.out.print(searchTargetNode(S, b, map)+ " ");
				}
			}
			
			System.out.println();
		}		
		
		sc.close();
	}
	
	public static int searchTargetNode(int start, int index, int[][] map){
		Queue<Integer> queueFirst = new LinkedList<>();
		Queue<Integer> queueSecond = new LinkedList<>();
		boolean visited[] = new boolean[totalNodes];
		queueFirst.offer(index);
		int level = 0;
		
		while(!queueFirst.isEmpty() || !queueSecond.isEmpty()){
			while(!queueFirst.isEmpty()){
				int tmpNode = queueFirst.poll();
				
				if(visited[tmpNode]){
					continue;
				}
				
				if(tmpNode == start){
					return level*6;
				}
				
				visited[tmpNode] = true;
				
				for(int a=0; a < totalNodes; a++){
					if(map[tmpNode][a]==1){
						queueSecond.add(a);
					}
				}	
				
				
			}
			level++;
			
			while(!queueSecond.isEmpty()){
				int tmpNode = queueSecond.poll();
				
				if(visited[tmpNode]){
					continue;
				}
				
				if(tmpNode == start){
					return level*6;
				}
				
				visited[tmpNode] = true;
				
				for(int a=0; a < totalNodes; a++){
					if(map[tmpNode][a]==1){
						queueFirst.add(a);
					}
				}	
				
				
			}
			level++;
		}
		
		
		
		return -1 ;
	}

}
