package code;

import javax.swing.plaf.synth.SynthTextAreaUI;
import java.util.Scanner;

/**
 * Created by SRIN on 4/10/2017.
 */
public class ChessBoardGame {
    private static boolean[][] isVisited;
    private static int[][] move;
    private static int[][] map;
    private static int[] xNum = {-2, -2, 1, -1};
    private static int[] yNum = {1, -1, -2, -2};
    private static int globalMax = 0;
    private static int minMoveToLose = 100000;

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        map = new int[16][16];

        for(int i =1; i < 16; i++){
            for(int j=1; j < 16; j++){
                if(map[i][j] == 0){
                    signPlayerMove(i,j);
                }
            }
        }

        for (int i = 1; i < 16; i++) {
            for (int j = 1; j < 16; j++) {
                System.out.print(map[j][i] + " ");
            }
            System.out.println();
        }


        for (int t = 0; t < T; t++) {
            int coins = sc.nextInt();
            String winner = "";
            for (int c = 0; c < coins; c++) {

                int x = sc.nextInt();
                int y = sc.nextInt();

                if(winner == ""){
                    winner = map[x][y] == 1 ? "First" : "Second";
                }else if(winner == "First" && map[x][y] == 1){
                    winner = "Second";
                }else if(winner == "First" && map[x][y] == 2){
                    winner = "First";
                }else if(winner == "Second" && map[x][y] == 1){
                    winner = "First";
                }else{
                    winner = "Second";
                }
            }

            System.out.println(winner);
            //System.out.println("globalMax :" + globalMax);
        }


//        for(int i =1; i < 16; i++){
//            for(int j=1; j < 16; j++){
//                System.out.print(map[j][i] +" ");
//            }
//            System.out.println();
//        }

//        for (int t = 0; t < T; t++) {
//            globalMax = 0;
//            int coins = sc.nextInt();
//            for (int c = 0; c < coins; c++) {
//                isVisited = new boolean[16][16];
//                move = new int[16][16];
//
//                int x = sc.nextInt();
//                int y = sc.nextInt();
//
//                signBoard(x, y, 1);
//                globalMax += minMoveToLose;
//                System.out.println("minimum move to lose :" + minMoveToLose);
//                minMoveToLose = 10000;
//
//
//                for (int row = 1; row < 16; row++) {
//                    for (int col = 1; col < 16; col++) {
//                        System.out.print(move[row][col] + " ");
//                    }
//                    System.out.println();
//                }
//                System.out.println();
//            }
//
//            System.out.println(whosMove(globalMax));
//            //System.out.println("globalMax :" + globalMax);
//        }
    }

    public static void signBoard(int x, int y, int counter) {
        if (!isValid(x, y) || counter > minMoveToLose) {
            return;
        }

        if (move[y][x] == -1) {
            if (counter < minMoveToLose) {
                minMoveToLose = counter;
            }

        } else {
            move[y][x] = counter;
        }

        isVisited[y][x] = true;

        if (!isValid(x - 2, y + 1) && !isValid(x - 2, y - 1) && !isValid(x + 1, y - 2) && !isValid(x - 1, y - 2)) {
            move[y][x] = -1;
            if (minMoveToLose > counter) {
                minMoveToLose = counter;
            }
        } else {
            for (int i = 0; i < 4; i++) {
                signBoard(x + xNum[i], y + yNum[i], counter + 1);
            }
        }

        isVisited[y][x] = false;
    }

    public static boolean isValid(int x, int y) {
        return x >= 1 && x <= 15 && y >= 1 && y <= 15 && !isVisited[x][y];
    }

    private static boolean isInsideBoard(int x, int y) {
        return x >= 1 && x <= 15 && y >= 1 && y <= 15;
    }

    private static String whosMove(int counter) {
        return counter % 2 == 0 ? "Second" : "First";
    }

    private static void signPlayerMove(int x, int y) {

        if ((isInsideBoard(x - 2, y + 1) && map[x - 2][y + 1] == 2)
                || (isInsideBoard(x - 2, y - 1) && map[x - 2][y - 1] == 2)
                || (isInsideBoard(x + 1, y - 2) && map[x + 1][y - 2] == 2)
                || (isInsideBoard(x - 1, y - 2) && map[x - 1][y - 2] == 2)) {
            map[x][y] = 1;
            return;
        }

        if (isInsideBoard(x - 2, y + 1) && map[x - 2][y + 1] == 0) {
            signPlayerMove(x - 2, y + 1);
            if (map[x - 2][y + 1] == 2) {
                map[x][y] = 1;
                return;
            }
        }
        if (isInsideBoard(x - 2, y - 1) && map[x - 2][y - 1] == 0) {
            signPlayerMove(x - 2, y - 1);
            if(map[x - 2][y - 1] == 2){
                map[x][y] = 1;
                return;
            }
        }

        if (isInsideBoard(x + 1, y - 2) && map[x + 1][y - 2] == 0) {
            signPlayerMove(x + 1, y - 2);
            if(map[x + 1][y - 2] == 2){
                map[x][y] = 1;
                return;
            }
        }

        if (isInsideBoard(x - 1, y - 2) && map[x - 1][y - 2] == 0) {
            signPlayerMove(x - 1, y - 2);
            if(map[x - 1][y - 2] == 2){
                map[x][y] = 1;
                return;
            }
        }

        map[x][y] = 2;
    }
}

/*
2
        3
        5 4
        5 8
        8 2
        6
        7 1
        7 2
        7 3
        7 4
        7 4
        7 4

1
4
1 1
1 3
1 4
1 1

Second

1
1
3 1

1
        3
        5 4
        5 8
        8 2


        1
25
5 6
3 6
2 7
7 5
7 8
2 7
3 4
1 3
3 5
6 5
7 6
5 5
6 6
1 5
1 6
6 5
3 1
2 4
7 8
8 5
7 1
3 1
4 4
4 6
8 1
First

https://www.topcoder.com/community/data-science/data-science-tutorials/algorithm-games/
        */
