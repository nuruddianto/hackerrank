package code;

import javax.swing.plaf.synth.SynthTextAreaUI;
import java.util.Scanner;

/**
 * Created by SRIN on 4/10/2017.
 */
public class ChessBoardGame {
    private static int dRow[] = {-2, -2, 1, -1};
    private static int dCol[] = {1, -1, -2, -2};
    private static int[][] map;

    public static void main(String[] args){
        map = new int[16][16];
        map[1][2] = 2;
        map[2][1] = 2;
        map[2][2] = 2;

        for(int row = 1; row <=15; row++){
            for(int col =1; col <= 15; col++){
                if(map[row][col] == 0){
                    signBoard(row,col);
                }
            }
        }

        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        for(int t =0; t < T; t++){
            int whosWin = map[sc.nextInt()][sc.nextInt()];
            String s = whosWin == 2 ? "Second" : "First";
            System.out.println(s);
        }

        //printMap(map);
    }

    private static void signBoard(int row, int col){
        if(row == 15 && col == 15){
            String s="";
        }

        for(int i=0; i < 4; i++){
            if(isValid(row +dRow[i], col+dCol[i])){
                if(map[row +dRow[i]][col+dCol[i]] == 0){
                    signBoard(row +dRow[i], col+dCol[i]);
                    if(map[row +dRow[i]][col+dCol[i]] == 2){
                        map[row][col] = 1;
                        return;
                    }

                }
                if(map[row +dRow[i]][col+dCol[i]] == 2){
                    map[row][col] = 1;
                    return;
                }

            }
        }

//        for(int i=0; i < 4; i++){
//            if(isValid(row +dRow[i], col+dCol[i])){
//
//            }
//        }

        map[row][col] = 2;
    }

    private static boolean isValid(int row, int col){
        return row >= 1 && row <=15 && col >=1 && col <=15;
    }

    private static void printMap(int[][] map){
        for(int col = 1; col <=15; col++){
            for(int row =1; row <= 15; row++){
                System.out.print(map[col][row]+" ");
            }
            System.out.println();
        }
    }
}

/*
row 8
col 1*/
