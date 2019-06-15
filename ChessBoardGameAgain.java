package code;

import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

/**
 * Created by SRIN on 4/17/2017.
 */
public class ChessBoardGameAgain {
    private static int dx[] = {-2, -2, 1, -1};
    private static int dy[] = {1, -1, -2, -2};
    private static int map[][];
    private static boolean isVisited[][];

    public static void main(String[] args) {
        map = new int[16][16];
        isVisited = new boolean[16][16];
        calculateGrundyNumber();
       // printMap(map);
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        for (int t = 0; t < T; t++) {
            int coins = sc.nextInt();
            int rowCoin[] = new int[coins];
            int colCoin[] = new int[coins];
            for(int i=0; i < coins; i++){
                rowCoin[i] = sc.nextInt();
                colCoin[i] = sc.nextInt();
            }
            int whosWin = map[rowCoin[0]][colCoin[0]];
            for(int i=1; i < coins; i++){
                whosWin ^= map[rowCoin[i]][colCoin[i]];
            }

            if(whosWin == 0){
                System.out.println("Second");
            }else{
                System.out.println("First");
            }
        }
    }

    private static void calculateGrundyNumber() {
        for (int i = 1; i <= 15; i++) {
            for (int j = 1; j <= 15; j++) {
                map[i][j] = nimber(i, j);
                isVisited[i][j] = true;
            }
        }
    }

    private static int nimber(int row, int col) {
        if(!isVisited[row][col]){
            Set s = new HashSet();

            for (int i = 0; i < 4; i++) {
                if (isValid(row + dx[i], col + dy[i])) {
                    s.add(nimber(row + dx[i], col + dy[i]));
                }
            }

            int ret = 0;
            while (s.contains(ret)) {
                ret++;
            }
            map[row][col] = ret;
            return map[row][col];
        }else{
            return map[row][col];
        }

    }

    private static boolean isValid(int row, int col) {
        return row >= 1 && row <= 15 && col >= 1 && col <= 15;
    }

    private static void printMap(int[][] map) {
        for (int i = 1; i <= 15; i++) {
            for (int j = 1; j <= 15; j++) {
                System.out.print(map[i][j] + " ");
            }
            System.out.println();
        }
    }
}
