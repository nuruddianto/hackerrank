package code;

import java.io.FileOutputStream;
import java.io.PrintStream;
import java.util.Scanner;

/**
 * Created by SRIN on 3/19/2018.
 */
public class ClimbingTheLeaderboard {
    int[] scores;
    int lengthScores;
    int n;

    int[] climbingLeaderboard(int[] scores, int[] alice) {
        // Complete this function
        int left = 0;
        int right = lengthScores-1;

        int rank[] = new int[alice.length];
        for(int i=0; i < rank.length; i++){
            if(alice[i] == scores[right]){
                rank[i] = lengthScores;
            } else if(alice[i] < scores[right]){
                rank[i] = lengthScores+1;
            } else if(alice[i] >= scores[left]){
                rank[i] = 1;
            } else {
                rank[i] = doBinary(left, right, alice[i]);
            }
        }
        return rank;
    }

    int doBinary(int left, int right, int currVal){
        int mid = (left + right) /2;
        int midVal = scores[mid];

        if(currVal == midVal){
            //System.out.println("val : "+currVal +", rank: "+mid+1);
            return mid + 1;
        }

        if((currVal > midVal && currVal < scores[mid-1]) ){
            //System.out.println("val : "+currVal +", rank: "+mid);
            return mid + 1;
        }

        if((currVal < midVal && currVal > scores[mid+1])){
            //System.out.println("val : "+currVal +", rank: "+mid+2);
            return mid + 2;
        }

        if(currVal < midVal){
            return doBinary(mid, right, currVal);
        } else {
            return doBinary(left, mid, currVal);
        }
    }


    public static void main(String[] args) {
        ClimbingTheLeaderboard c = new ClimbingTheLeaderboard();
        Scanner in = new Scanner(System.in);
        c.n = in.nextInt();

        c.scores = new int[c.n];

        c.lengthScores = 0;
        int prev = 0;

        for(int scores_i = 0; scores_i < c.n; scores_i++){
            int tmp = in.nextInt();
            if(prev != tmp){
                prev = tmp;
                c.scores[c.lengthScores] = tmp;
                c.lengthScores++;

            }

        }

        int m = in.nextInt();
        int[] alice = new int[m];
        for(int alice_i = 0; alice_i < m; alice_i++){
            alice[alice_i] = in.nextInt();
        }
        int[] result = c.climbingLeaderboard(c.scores, alice);
        for (int i = 0; i < result.length; i++) {
            System.out.print(result[i] + (i != result.length - 1 ? "\n" : ""));
        }
        System.out.println("");


        in.close();
    }
}
/*

7
        100 100 50 40 40 20 10
        4
        5 25 50 120
        */
