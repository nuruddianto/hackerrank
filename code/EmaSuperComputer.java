package code;

import java.util.Scanner;

/**
 * Created by SRIN on 4/18/2017.
 */
public class EmaSuperComputer {
    private static class PlusSign {
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
    private static PlusSign plusOne;
    private static PlusSign plusTwo;
    private static int maxValue;

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        row = sc.nextInt();
        col = sc.nextInt();

        map = new char[row + 1][col + 1];

        for (int j = 1; j <= row; j++) {
            String s = sc.next();
            for (int i = 0; i < col; i++) {
                int k = i + 1;
                map[j][k] = s.charAt(i);
            }
        }

        int maxWidth = row > col ? col / 2 : row / 2;

        for (int l = maxWidth; l > 0; l--) {
            for (int j = 1; j <= row; j++) {
                for (int i = 1; i <= col; i++) {
                    if (map[j][i] - 'G' == 0) {
                        findPlusSign(j, i, l);
                    }
                }
            }
        }

        PlusSign tmp = head;
        if(tmp == null){
            System.out.println(1);
        }else{
            while(tmp != null){
                int currMax = finMax(tmp);
                if(currMax > maxValue){
                    maxValue = currMax;
                }
                tmp = tmp.next;
            }

            System.out.println(maxValue);
        }


    }

    private static void findPlusSign(int row, int col, int width) {
        if (row == 2 && col == 5) {
            String s = "";
        }

        if (!isValid(row + width, col ) || !isValid(row - width, col ) || !isValid(row , col - width) || !isValid(row , col + width) ) {
            return;
        }

        //find left
        int outerLeft = width;
        while (isValid(row, col - outerLeft) && outerLeft != 0) {
            outerLeft--;
        }

        if (outerLeft > 0) {
            return;
        }

        //find right
        int outerRight = width;
        while (isValid(row, col + outerRight) && outerRight != 0) {
            outerRight--;
        }

        if (outerRight > 0) {
            return;
        }

        //find up
        int outerUp = width;
        while (isValid(row - outerUp, col) && outerUp != 0) {
            outerUp--;
        }

        if (outerUp > 0) {
            return;
        }


        //find bottom
        int outerBottom = width;
        while (isValid(row + outerBottom, col) && outerBottom != 0) {
            outerBottom--;
        }

        if (outerBottom > 0) {
            return;
        }


        addPlusSign(row, col, width);
    }

    private static int finMax(PlusSign head){

        PlusSign tmp = head;
        plusOne = null;
        plusTwo = null;
        while (tmp != null) {
            if (plusOne == null) {
                plusOne = tmp;
            } else if (plusTwo == null && !isOverlap(plusOne, tmp)) {
                plusTwo = tmp;
            }

            tmp = tmp.next;
        }

        if(plusTwo == null){
            plusTwo = new PlusSign(0,0, 0);
        }

        return (plusOne.width * 4 + 1) * (plusTwo.width * 4 + 1);
    }

    private static boolean isValid(int j, int i) {
        return j >= 1 && j <= row && i >= 1 && i <= col && map[j][i] == 'G';
    }

    private static void addPlusSign(int row, int col, int width) {
        PlusSign newData = new PlusSign(row, col, width);
        if (head == null) {
            head = newData;
            return;
        }

        PlusSign tmp = head;
        PlusSign prev = null;
        while (tmp.next != null) {
            tmp = tmp.next;
        }
        tmp.next = newData;
    }

    private static PlusSign pop() {
        PlusSign tmp = head;
        if (tmp == null) {
            return null;
        }

        head = head.next;
        return tmp;
    }

    private static boolean isOverlap(PlusSign oldSign, PlusSign newSign) {
        boolean isVisited[][] = new boolean[row + 1][col + 1];

        int oldRow = oldSign.row;
        int oldCol = oldSign.col;
        int oldWidth = oldSign.width;

        int newRow = newSign.row;
        int newCol = newSign.col;
        int newWidth = newSign.width;


        for (int i = 0; i <= oldWidth; i++) {
            isVisited[oldRow + i][oldCol] = true;
            isVisited[oldRow - i][oldCol] = true;
            isVisited[oldRow][oldCol + i] = true;
            isVisited[oldRow][oldCol - i] = true;
        }

        for (int i = 0; i <= newWidth; i++) {
            if (isVisited[newRow + i][newCol] || isVisited[newRow - i][newCol] || isVisited[newRow][newCol + i] || isVisited[newRow][newCol - i]) {
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
