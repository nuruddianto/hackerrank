package code.srin;

import java.util.Scanner;

/**
 * Created by nurud on 04/02/2017.
 */
public class IceClimber {
    private static int map[][];
    private static boolean visited[][];
    private static int width;
    private static int height;

    private static int startX;
    private static int startY;
    private static int finishX;
    private static int finishY;

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        width = sc.nextInt();
        height = sc.nextInt();
        map = new int[width][height];
        visited = new boolean[width][height];
        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; i++) {
                map[i][j] = sc.nextInt();
                if (map[i][j] == 2) {
                    startX = i;
                    startY = j;
                } else if (map[i][j] == 3) {
                    finishX = i;
                    finishY = j;
                }
            }
        }

        findEasiestLevel(startX, startY, 1,1);
        if(minDownLevel > minUpLevel && minDownLevel != 10000 ){
            System.out.print(minDownLevel);
        }else {
            System.out.print(minUpLevel);
        }

    }

    private static int yNum[] = {-1, 1, 0, 0};
    private static int xNum[] = {0, 0, -1, 1};
    private static int minUpLevel = 10000;
    private static int minDownLevel = 10000;

    private static void findEasiestLevel(int x, int y, int uPlevel, int downLevel) {
        if (x == finishX && y == finishY) {
            if(uPlevel < minUpLevel && uPlevel != 1){
                minUpLevel = uPlevel;
            }else if(downLevel < minDownLevel && downLevel != 1){
                minDownLevel = downLevel;
            }else if(uPlevel == 1 & downLevel == 1){
                minUpLevel = 1;
                minDownLevel = 1;
            }
                return;
        }

        if(uPlevel > minUpLevel ||  downLevel > minDownLevel){
            return;
        }

        visited[x][y] = true;

        for(int i =0 ; i < 4; i++){
            if(isValid(x + xNum[i], y + yNum[i])){
                if(i == 0 && map[x + xNum[i]][y +yNum[i]] == 0){
                    findEasiestLevel(x + xNum[i], y + yNum[i], uPlevel+1, downLevel);
                }else if(i == 1 && map[x + xNum[i]][y +yNum[i]] == 0){
                    findEasiestLevel(x + xNum[i], y + yNum[i], uPlevel, downLevel+1);
                }else if ((i== 2 && map[x + xNum[i]][y +yNum[i]] == 0) || (i== 3 && map[x + xNum[i]][y +yNum[i]] == 0) ){
                    continue;
                }else{
                    findEasiestLevel(x + xNum[i], y + yNum[i], uPlevel, downLevel);
                }
            }
        }
        visited[x][y] = false;
    }

    private static boolean isValid(int x, int y) {
        if (x < width && x >= 0 && y < height && y >= 0 && !visited[x][y]) {
            return true;
        }
        return false;
    }
}
