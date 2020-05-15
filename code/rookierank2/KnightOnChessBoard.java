package code.rookierank2;

import java.util.Scanner;

/**
 * Created by nurud on 12/02/2017.
 */
public class KnightOnChessBoard {
    private static int memo[][];
    private static boolean visited[][];
    private static int minMove;
    private static int n;


    private static class Point {
        int x;
        int y;

        public Point(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        n = sc.nextInt();
        Point finish = new Point(n - 1, n - 1);
        Point start = new Point(0, 0);
        memo = new int[n][n];
        memo[1][1] = n-1;
        memo[n-1][n-1] = 1;
        for(int i = 1; i < n; i++){
            for(int j = 1; j < n; j++){
                int yNum[];
                int xNum[];
                if(i==j){
                    yNum = new int[]{-1*j, -1*j, j, j};
                    xNum = new int[]{-1*i, i, -1*i, i};
                }else{
                    yNum = new int[]{-1*i, -1*j, -1*i, -1*j, j, i, i, j};
                    xNum = new int[]{-1*j, -1*i, j, i, -1*i, -1*j, j, i};
                }

                minMove = n*n;
                visited = new boolean[n][n];
                if(memo[i][j] == 0 && memo[i][j] == 0){
                    explore(start, finish, 0, yNum, xNum);
                }else{
                    if(memo[i][j] == 0 ){
                        minMove = memo[j][i];
                    }else{
                        minMove = memo[i][j];
                    }
                }

                memo[j][i] = minMove;
                if (minMove == n*n) {
                    System.out.print(-1+" ");
                } else {
                    System.out.print(minMove+" ");
                }
            }
            System.out.println();
        }



    }

    private static void explore(Point start, Point finish, int move, int[] yNum, int[] xNum) {
        if (start.x == finish.x && start.y == finish.y) {
            if (move < minMove) {
                minMove = move;
                return;
            }
        }

        if (move > minMove) {
            return;
        }

        visited[start.x][start.y] = true;
        for (int i = 0; i < xNum.length; i++) {
            if (isValid(start.x + xNum[i], start.y + yNum[i])) {
                Point newStart = new Point(start.x + xNum[i], start.y + yNum[i]);
                explore(newStart, finish, move + 1, yNum, xNum);
            }
        }

        visited[start.x][start.y] = false;
    }

    private static boolean isValid(int x, int y) {
        if (x < n && y < n && x >= 0 && y >= 0 && !visited[x][y]) {
            return true;
        }
        return false;
    }
}
