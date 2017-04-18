package code;

import java.util.Scanner;

/**
 * Created by SRIN on 4/18/2017.
 */
public class EmaSuperComputer {
    private static class PlusSign{
        PlusSign next;
        int row;
        int col;
        int width;

        public PlusSign(int row, int col, int width) {
            this.row = row;
            this.col = col;
            this.width = width;
        }
    }

    private static char map[][];
    private static int row;
    private static int col;
    private static PlusSign head;

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        row = sc.nextInt();
        col = sc.nextInt();

        map = new char[row+1][col+1];

        for(int j = 1; j <= row; j++){
            String  s = sc.next();
            for(int i = 0; i < col; i++){
                int k = i+1;
                map[j][k] = s.charAt(i);
            }
        }

        for(int j = 1; j <= row; j++){
            for(int i = 1; i <= col; i++){
                if(map[j][i] - 'G' == 0){
                    findPlusSign(j, i);
                }
            }
        }

        int max1 = 0;
        int max2 = 0;
        PlusSign tmp = head;
        while (tmp != null){
            int currWidth = tmp.width;
            if(max1 == 0){
                max1 = currWidth;
            }else if(max2 == 0){
                max2 = currWidth;
            }else if(currWidth > max1){
                max2 = max1;
                max1 = currWidth;
            }

            if(max1 < max2){
                int t = max1;
                max1 = max2;
                max2 = t;
            }
            tmp = tmp.next;
        }

        int result = (max1*4 +1) * (max2*4+1);

        System.out.println(result);
    }

    private static void findPlusSign(int row, int col){
        if(row == 2 && col == 5){
            String s = "";
        }

        //find left
        int width = -1;
        int tmpCol = col;
        while (isValid(row,tmpCol)){
            tmpCol--;
            width++;
        }

        if(width == 0){
            return;
        }

        //find right
        int i = -1;
        tmpCol = col;
        while (isValid(row, tmpCol) && i != width){
            i++;
            tmpCol++;
        }

        if(i == 0){
            return;
        }

        if( i < width ){
            width = i;
        }

        //find up
        int u = -1;
        int tmpRow = row;
        while (isValid(tmpRow, col) &&  u != width){
            tmpRow--;
            u++;
        }

        if(u == 0){
            return;
        }

        if( u < width ){
            width = u;
        }

        //find bottom
        int b=-1;
        tmpRow = row;
        while (isValid(tmpRow, col) &&  b != width){
            tmpRow++;
            b++;
        }

        if(b == 0){
            return;
        }

        if(b < width){
            width = b;
        }
        addPlusSign(row, col, width);

    }

    private static boolean isValid(int j, int i){
        return j >= 1 && j <=row && i>=1 && i <= col && map[j][i] == 'G';
    }

    private static void addPlusSign(int row, int col, int width){
        PlusSign newData = new PlusSign(row, col, width);
        if(head == null){
            head = newData;
            return;
        }

        PlusSign tmp = head;

        while (tmp.next != null ){
            tmp = tmp.next;
        }

        if(isOverlap(tmp, newData)){
            if(tmp.width < newData.width){
                tmp = newData;
            }
        }else{
            tmp.next = newData;
        }

    }

    private static PlusSign pop(){
        PlusSign tmp = head;
        if(tmp == null){
            return  null;
        }

        head = head.next;
        return tmp;
    }

    private static boolean isOverlap(PlusSign oldSign, PlusSign newSign){
        boolean isVisited[][] = new boolean[row+1][col+1];

        int oldRow = oldSign.row;
        int oldCol = oldSign.col;
        int oldWidth = oldSign.width;

        int newRow = newSign.row;
        int newCol = newSign.col;
        int newWidth = newSign.width;


        for(int i = 0 ; i <= oldWidth; i++){
            isVisited[oldRow+i][oldCol] = true;
            isVisited[oldRow-i][oldCol] = true;
            isVisited[oldRow][oldCol+i] = true;
            isVisited[oldRow][oldCol-i] = true;
        }

        for(int i = 0 ; i <= newWidth; i++){
            if(isVisited[newRow+i][newCol] || isVisited[newRow-i][newCol] || isVisited[newRow][newCol+i] || isVisited[newRow][newCol+i]){
                return true;
            }
        }

        return false;
    }

}

/*
5 6
        GGGGGG
        GBBBGB
        GGGGGG
        GGBBGB
        GGGGGG

        6 6
BGBBGB
GGGGGG
BGBBGB
GGGGGG
BGBBGB
BGBBGB

14 15
GBBBBBBGGGBGGBB
GBBBBBBGGGBGGBB
GBBBBBBGGGBGGBB
GBBBBBBGGGBGGBB
GGGGGGGGGGGGGGG
GGGGGGGGGGGGGGG
GBBBBBBGGGBGGBB
GBBBBBBGGGBGGBB
GGGGGGGGGGGGGGG
GBBBBBBGGGBGGBB
GBBBBBBGGGBGGBB
GGGGGGGGGGGGGGG
GGGGGGGGGGGGGGG
GBBBBBBGGGBGGBB
273
        */
