package code.srin;

import java.util.Scanner;

/**
 * Created by SRIN on 4/13/2017.
 */
public class BombermanGame {

    private static int[] di = {-1, 1, 0, 0};
    private static int[] dj = {0, 0, -1, 1};

    private static char[][] map_1;
    private static char[][] map_3;
    private static char[][] map_5;
    private static char[][] map_7;

    private static int row;
    private static int col;

    public static void main(String[] args) {
        map_1 = new char[201][201];
        map_3 = new char[201][201];
        map_5 = new char[201][201];
        map_7 = new char[201][201];

        Scanner sc = new Scanner(System.in);
        row = sc.nextInt();
        col = sc.nextInt();
        int n = sc.nextInt();

        //state 1
        for (int i = 1; i <= row; i++) {
            String s = sc.next();
            for (int j = 0; j < s.length(); j++) {
                map_1[i][j + 1] = s.charAt(j);
            }
        }

        //state 2
        doExplosion(map_1, map_3);


        //state 3
        doExplosion(map_3, map_5);

        if (isMapSame(map_1, map_5)) {
            map_7 = map_3;
        } else {
            //state 4
            doExplosion(map_5, map_7);
        }

       // System.out.print(503486865 % 7);

//        printMap(map_1);
//        printMap(map_3);
//        printMap(map_5);

        if (n % 2 == 0) {
            printZeroMap();
        } else {
            if(n < 5){
                printResult(n);
            }else{
                printResults(n);
            }

        }
        //
    }

    private static boolean isValid(int i, int j) {
        return i >= 1 && i <= row && j >= 1 && j <= col;
    }

    private static void printResult(int n) {
        if (n == 1) {
            printMap(map_1);
        } else if (n == 3) {
            printMap(map_3);
        } else if (n == 5) {
            printMap(map_5);
        } else if (n == 7) {
            printMap(map_7);
        } else {
            printResult(n % 4);
        }
    }

    private static void printResults(int n) {
        if(n % 4 == 1){
            printMap(map_5);
        }else if(n % 4 == 3){
            printMap(map_3);
        }
    }

    private static boolean isMapSame(char[][] map1, char[][] map2) {
        for (int i = 1; i <= row; i++) {
            for (int j = 1; j <= col; j++) {
                if (map1[i][j] - map2[i][j] != 0) {
                    return false;
                }
            }
        }
        return true;
    }

    private static void printMap(char[][] map) {
        for (int i = 1; i <= row; i++) {
            for (int j = 1; j <= col; j++) {
                System.out.print(map[i][j]);
            }
            System.out.println();
        }
        System.out.println();
    }

    private static void printZeroMap() {
        for (int i = 1; i <= row; i++) {
            for (int j = 1; j <= col; j++) {
                System.out.print('O');
            }
            System.out.println();
        }
    }

    private static void doExplosion(char[][] prevMap, char[][] nextMap) {
        for (int i = 1; i <= row; i++) {
            for (int j = 1; j <= col; j++) {
                if (nextMap[i][j] != 0) {
                    continue;
                }
                if (prevMap[i][j] == '.' && nextMap[i][j] == 0) {
                    nextMap[i][j] = 'O';
                } else {
                    nextMap[i][j] = '.';
                    for (int k = 0; k < di.length; k++) {


                        if (isValid(i + di[k], j + dj[k])) {
                            if (prevMap[i + di[k]][j + dj[k]] == 'O') {
                                continue;
                            }
                            nextMap[i + di[k]][j + dj[k]] = '.';
                        }
                    }
                }
            }
        }
    }
}

/*

3 3 7
...
OO.
.O.


3 3 7
...
.0.
...
*/
