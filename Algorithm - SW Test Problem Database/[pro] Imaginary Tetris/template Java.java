import java.util.Scanner;

class Solution {
   private static final int BOARD_MAX_WIDTH = 10;
   private static final int BLOCK_MAX_SIZE = 3;
   private static final int CMD_ROTATE = 100;
   private static final int CMD_MOVE = 200;

   private static Scanner sc;
   private static UserSolution userSolution = new UserSolution();

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



class UserSolution {
   private static final int BOARD_MAX_WIDTH = 10;
   private static final int BOARD_MAX_HEIGHT = 200;
   private static final int BLOCK_MAX_SIZE = 3;
   private static final int ROTATE_90 = 1;
   private static final int ROTATE_180 = 2;
   private static final int ROTATE_270 = 3;
   private static final int ROTATE_360 = 4;

   public void init(int width) {

   }

   public void newBlock(int block[][], int width, int height) {

   }

   public void rotate(int angle) {  // 1: ROTATE_90, 2: ROTATE_180, 3: ROTATE_270, 4: ROTATE_360

   }

   void move(int distance) {

   }

   int land() {
      int answer = -1;

      return answer;
   }
}
