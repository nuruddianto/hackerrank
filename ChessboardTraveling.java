package code;

import java.util.Scanner;

public class ChessboardTraveling {
	static int width = 8;
	static int height = 8;
	
	static int[] dRow = {1, 0};
	static int[] dCol = {0, 1};
	
	static int finishRow;
	static int finishCol;
	static int totalWay;
	
	static boolean[][] mVisited;
	public static int ChessboardTraveling(String str) { 
		mVisited = new boolean[height][width];
		totalWay = 0;
		int startCol = str.charAt(2) - '0';
		int startRow = str.charAt(4) - '0';
		finishCol = str.charAt(7) - '0';
		finishRow = str.charAt(9) - '0';
	    // code goes here   
	    /* Note: In Java the return type of a function and the 
	       parameter types being passed are defined, so this return 
	       call must match the return type of the function.
	       You are free to modify the return type. */
		doTraverse(startRow, startCol);
	    return totalWay;
	    
	  } 
	
	static void doTraverse(int row, int col){
		if(row < 0 || row >= height || col <0 || col >= width || mVisited[row][col]){
			return;
		}
		
		if(row == finishRow && col == finishCol){
			totalWay++;
			return;
		}
		
		mVisited[row][col] = true;
		
		for(int i=0; i < 2; i++){
			doTraverse(row + dRow[i], col + dCol[i]);
		}
		
		mVisited[row][col] = false;
	}
	  
	  public static void main (String[] args) {  
	    // keep this function call here     
	    Scanner s = new Scanner(System.in);
	    
	    System.out.print(ChessboardTraveling(s.nextLine())); 
	  }   
}
