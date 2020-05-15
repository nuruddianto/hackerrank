package code.srin;

import java.util.Scanner;

/**
 * Created by SRIN on 10/30/2017.
 */
public class ImaginaryTetris {

    private static final int BOARD_MAX_WIDTH = 10;
    private static final int BOARD_MAX_HEIGHT = 200;
    private static final int BLOCK_MAX_SIZE = 3;
    private static final int ROTATE_90 = 1;
    private static final int ROTATE_180 = 2;
    private static final int ROTATE_270 = 3;
    private static final int ROTATE_360 = 4;

    static int[][] mBoard;
    static int[][] mBlock;
    static int move;

    class Cordinat{
        int mRow;
        int mCol;

        public Cordinat(int row, int col){
            mRow = row;
            mCol = col;
        }
    }

    Cordinat potentialTopLeft;

    int mBlockWidth = 0;
    int mBoardWidth = 0;
    int mMaxHighestRow;

    public void init(int width) {
        mBlockWidth = 0;
        mBoardWidth = width;
        mBoard = new int[BOARD_MAX_HEIGHT][width];
        mBlock = new int[BLOCK_MAX_SIZE][BLOCK_MAX_SIZE];
        move = 0;
        mMaxHighestRow = BOARD_MAX_HEIGHT - 1;
    }

    public void newBlock(int block[][], int width, int height) {
        for(int r = 0; r < height; r++){
            for(int c = 0; c < width; c++){
                mBlock[r][c] = block[r][c];
            }
        }
        mBlockWidth = width;
    }

    public void rotate(int angle) {  // 1: ROTATE_90, 2: ROTATE_180, 3: ROTATE_270, 4: ROTATE_360
        if(angle != 4){
            for(int i = 0; i < angle; i++){
                mBlock = rotate90(mBlock);
            }
        }

        //if left column is empty,  move block
        mBlock = moveLeft(mBlock);
        System.out.println();
    }

    int[][] moveLeft(int[][] block){
        boolean isLeftColumnEmpty = true;
        for(int r=0; r < BLOCK_MAX_SIZE; r++){
            if(block[r][0] == 1){
                isLeftColumnEmpty = false;
            }
        }

        if(isLeftColumnEmpty){
            mBlockWidth--;
            int[][] movedBlock = new int[BLOCK_MAX_SIZE][BLOCK_MAX_SIZE];
            for(int r = 0; r < BLOCK_MAX_SIZE; r++){
                for(int c = 1; c < BLOCK_MAX_SIZE; c++){
                    movedBlock[r][c-1] = block[r][c];
                }
            }

            return moveLeft(movedBlock);
        }
        return block;
    }

    void move(int distance) {
        move += distance;
        if(move < 0){
            move = 0;
        }else if(move > mBoardWidth -1){
            move = mBoardWidth - 1;
        }
    }

    int land() {
        int answer = -1;
        //search potential top left
        searchPotentialTopLeft();

        //copy block to mBoard
        int startCol = move;
        int startRow = getHighestRow(startCol);

        //draw block to board using start col and start row
        if(mBlockWidth + move >= mBoardWidth){
            startCol = mBoardWidth - mBlockWidth;
        }else if(startCol < 0 ){
            startCol = 0;
        }

        drawBlockToBoard(startRow, startCol);

        //check clear line
        clearLine(startRow);

        //get highest row
        int lowestRow = getHighestCol(startRow);
        mMaxHighestRow -= lowestRow;

        testPrintBlock(mBlock);
        testPrintBoard(mBoard);

        mBlock = new int[BLOCK_MAX_SIZE][BLOCK_MAX_SIZE];
        move = 0;
        return lowestRow;
    }

    private void clearLine(int startRow) {
        int highestRow = startRow-3;
        int totalFill = 0;
        int clearingRow = 0;
        boolean isClearing = false;
        for(int row = startRow; row > highestRow; row--){
            for(int col = 0; col < mBoardWidth; col++){
                if(mBoard[row][col] == 1){
                    totalFill++;
                }
            }

            if(totalFill == mBoardWidth){
                //clear line
                for(int col = 0; col < mBoardWidth; col++){
                    if(mBoard[row][col] == 1){
                        mBoard[row][col] = 0;
                    }
                }
                isClearing = true;
                clearingRow = row;
                break;
            }
            totalFill = 0;
        }

        //drop after clear line
        if(isClearing){
            drop(clearingRow);
            mMaxHighestRow++;
            clearLine(startRow);
        }
    }

    void drop(int clearingRow){
        for(int row = clearingRow; row > clearingRow - 3; row--){
            for(int col = 0; col < mBoardWidth; col++){
                mBoard[row][col] = mBoard[row-1][col];
                mBoard[row-1][col] = 0;
            }
        }
    }

    void searchPotentialTopLeft(){
        for(int row = BLOCK_MAX_SIZE - 1; row >= 0; row--){
            for(int col = 0; col < BLOCK_MAX_SIZE; col++){
                if(mBlock[row][col] == 1){
                    potentialTopLeft = new Cordinat(row, col);
                    return;
                }
            }
        }
    }

    int getHighestRow(int startCol){
        int row = 0;
        for(row = BOARD_MAX_HEIGHT -1 ; row >= 0; row-- ){
            for(int col = startCol; col < startCol+3; col++){
                if(row == 195){
                    String s = "";
                }
                int colBlock = 0;
                int success = 0;
                int currentCol = col;
                while(colBlock < 3 && currentCol < mBoardWidth){
                    if(mBoard[row][currentCol] == 0 || (mBoard[row][currentCol] == 1 && mBlock[potentialTopLeft.mRow][colBlock] == 0)){
                        success++;
                    }
                    currentCol++;
                    colBlock++;
                }
                if(success >= mBlockWidth){
                    return row;
                }

            }
        }

        if(row == -1){
            String s = "";
        }

        return row;
    }

    int getHighestCol(int startRow){
        int rowSearch = startRow - 2;
        for(int row = rowSearch; row < startRow; row++){
            for(int col =0; col < mBoardWidth; col++){
                if(mBoard[row][col] == 1){
                    return BOARD_MAX_HEIGHT - row;
                }
            }
        }

        return 0;
    }

    void drawBlockToBoard(int startRow, int startCol){
        int rowBoard = startRow;
        int colBoard = startCol;
        for(int rowBlock = potentialTopLeft.mRow; rowBlock >=0; rowBlock--){
            for(int colBlock = 0; colBlock < BLOCK_MAX_SIZE; colBlock++){
                if(mBlock[rowBlock][colBlock] == 1){
                    mBoard[rowBoard][colBoard] = mBlock[rowBlock][colBlock];
                }
                colBoard++;
            }
            colBoard = startCol;
            rowBoard--;
        }
    }

    int[][] rotate90(int[][] block){
        int[][] rotatedBlock = new int[BLOCK_MAX_SIZE][BLOCK_MAX_SIZE];

        rotatedBlock[0][2] = block[0][0];
        rotatedBlock[1][2] = block[0][1];
        rotatedBlock[2][2] = block[0][2];
        rotatedBlock[0][1] = block[1][0];
        rotatedBlock[1][1] = block[1][1];
        rotatedBlock[2][1] = block[1][2];
        rotatedBlock[0][0] = block[2][0];
        rotatedBlock[1][0] = block[2][1];
        rotatedBlock[2][0] = block[2][2];

        return rotatedBlock;
    }

    void testPrintBlock(int[][] arr){

        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                System.out.print(arr[i][j]+" ");
            }
            System.out.println();
        }
        System.out.println();
    }

    void testPrintBoard(int[][] arr){

        for(int i = 180; i < BOARD_MAX_HEIGHT; i++){
            for(int j = 0; j < mBoardWidth; j++){
                System.out.print(arr[i][j]+" ");
            }
            System.out.println();
        }
        System.out.println();
    }
}

class Solution {
    private static final int BOARD_MAX_WIDTH = 10;
    private static final int BLOCK_MAX_SIZE = 3;
    private static final int CMD_ROTATE = 100;
    private static final int CMD_MOVE = 200;

    private static Scanner sc;
    private static ImaginaryTetris userSolution = new ImaginaryTetris();

    public static void main(String arg[]) throws Exception{
        //System.setIn(new java.io.FileInputStream("sample_input.txt"));
        sc = new Scanner(System.in);

        int testCnt;
        double totalScore = 0.0;
        int block[][] = new int[BLOCK_MAX_SIZE][BLOCK_MAX_SIZE];

        testCnt = sc.nextInt();
        for (int tc = 1; tc <= testCnt; ++tc)
        {
            int boardWidth = sc.nextInt();
            int blockCnt = sc.nextInt();
            int score = blockCnt;

            userSolution.init(boardWidth);

            for (int i = 0; i < blockCnt; ++i) {
                for (int h = 0; h < BLOCK_MAX_SIZE; ++h) {
                    for (int w = 0; w < BLOCK_MAX_SIZE; ++w) {
                        block[h][w] = 0;
                    }
                }

                int width = sc.nextInt();
                int height = sc.nextInt();

                for (int h = 0; h < height; ++h) {
                    for (int w = 0; w < width; ++w) {
                        block[h][w] = sc.nextInt();
                    }
                }

                userSolution.newBlock(block, width, height);

                int cmdCnt, cmd, option;
                cmdCnt = sc.nextInt();
                for (int j = 0; j < cmdCnt; ++j) {
                    cmd = sc.nextInt();
                    option = sc.nextInt();

                    switch (cmd) {
                        case CMD_ROTATE:
                            userSolution.rotate(option);
                            break;
                        case CMD_MOVE:
                            userSolution.move(option);
                            break;
                        default:
                            System.out.println("cmd error");
                            break;
                    }
                }

                int answer = sc.nextInt();
                int result = userSolution.land();
                if (answer != result) {
                    --score; // wrong answer
                }
            }

            System.out.println("#" + tc + " " + score);
            totalScore += (double)score / blockCnt * 100;
        }

        System.out.printf("Total Score : %.3f\n", totalScore / testCnt);

    }
}
/*
test 1
1
        5 2
        3 3
        1 1 1
        1 1 0
        1 0 0
        1
        100 3
        3
        3 2
        1 1 1
        1 0 1
        2
        100 1
        200 3
        2

        test 2
        1
        6 3
3 2
1 1 1
1 1 1
1
100 1
3
2 3
1 1
1 1
1 1
1
200 2
3
2 3
1 1
1 1
1 1
1
200 4
0

test 4
1
10 3
3 3
1 1 1
1 1 1
1 1 1
1
200 2
3
3 3
1 1 1
1 0 0
1 1 1
2
100 2
200 2
6
3 3
1 1 1
1 1 1
1 1 1
1
200 2
9


test 5
1
8 2
2 2
1 0
1 1
2
100 1
200 2
2
2 2
1 1
1 1
2
100 1
200 4
2

10 3
3 3
1 1 1
1 1 1
1 1 1
1
200 2
3
3 3
1 1 1
1 0 0
1 1 1
2
100 2
200 2
6
3 3
1 1 1
1 1 1
1 1 1
1
200 2
9

4 2
3 3
1 1 1
1 1 1
1 1 1
1
100 1
3
3 1
1 1 1
2
100 1
200 3
0
        */
