package code.srin;

import java.util.*;

public class Town_hall {
	static int N,goldMine;
	
	static int goldMineX[] = new int[4];
	static int goldMineY[] = new int[4];
	static int map[][] = new int[20][20];
	static int mapWithDistance[][][] = new int[20][20][4];
	
	public static void main(String[] args){
		Scanner sc = new Scanner(System.in);
		
		N = sc.nextInt();
		goldMine = sc.nextInt();
		
		for(int a=0; a < goldMine; a++){
			goldMineX[a]= sc.nextInt()-1;
			goldMineY[a]= sc.nextInt()-1;
		}
		
		for(int y = 0; y < N; y++){
			for(int x =0; x < N; x++){
				map[x][y] = sc.nextInt();
					for(int a=0; a < goldMine; a++){
						mapWithDistance[x][y][a]=-1;
					}
			}
		}
		
		for(int a= 0; a< goldMine; a++){
			map[goldMineX[a]][goldMineY[a]]= 3;
		}
		

		int minDistance = N*N+1;
		for(int a=0; a < goldMine; a++){
			hitungJarak(a, goldMineX[a], goldMineY[a], 0);
		}
		
		for(int y = 0; y < N; y++){
			for(int x =0; x < N; x++){
				System.out.print(mapWithDistance[x][y][0]+ " ");
				}
			System.out.println();
		}
		
		System.out.println();
		
		for(int y = 0; y < N; y++){
			for(int x =0; x < N; x++){
				System.out.print(mapWithDistance[x][y][1]+ " ");
				}
			System.out.println();
		}
		
		System.out.println();
		
		for(int y = 0; y < N; y++){
			for(int x =0; x < N; x++){
				System.out.print(mapWithDistance[x][y][2]+ " ");
				}
			System.out.println();
		}
		
		
		
		for(int y=0; y < N; y++){
			for(int x =0; x < N; x++){
				if(map[x][y] == 0 || map[x][y] == 3){
					continue;
				}
				
				int maxDistance=0;
				
				for(int a=0; a < goldMine; a++){
					if(mapWithDistance[x][y][a] > maxDistance){
						maxDistance = mapWithDistance[x][y][a];
					}					
				}
				
				if(maxDistance < minDistance){
					minDistance = maxDistance;
					System.out.println(minDistance);
				}
			}
		}
		
		System.out.println();
		
		System.out.print(minDistance);
		sc.close();
	}
	
	static void hitungJarak(int mineIndex, int x, int y, int distance){
		if(x < 0 || y < 0 || x >=N || y >= N){
			return;
		}
		
		if(map[x][y] == 0){
			return;
		}
			
		if(mapWithDistance[x][y][mineIndex] == -1 || mapWithDistance[x][y][mineIndex] > distance){
				mapWithDistance[x][y][mineIndex] = distance;				
				hitungJarak(mineIndex, x+1, y, distance+1);
				hitungJarak(mineIndex, x-1, y, distance+1);
				hitungJarak(mineIndex, x, y+1, distance+1);
				hitungJarak(mineIndex, x, y-1, distance+1);				
		}			
		
	}

}
