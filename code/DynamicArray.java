package code;

import java.util.Scanner;

/**
 * Created by SRIN on 11/9/2017.
 */
public class DynamicArray {
    static int initialSize;
    static int totalN;
    static int seq[][];

    public static void main(String[] args){
        //create index sequence and its value
        int index[];
        initialSize = 100;

        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        totalN = n;
        seq = new int[n][initialSize];
        index = new int[n];

        int q = sc.nextInt();
        int lastAnswer = 0;
        for(int i =0; i < q; i++){
            int type = sc.nextInt();
            int x = sc.nextInt();
            int y = sc.nextInt();
            int indexSeq = 0;
            switch (type){
                case 1:
                    indexSeq = (x^lastAnswer)%n;
                    int startIndex = index[indexSeq];

                    if(startIndex >= initialSize){
                        seq = copyArray(seq);
                    }
                    seq[indexSeq][startIndex] = y;
                    index[indexSeq]++;
                    break;
                case 2:
                    indexSeq = (x^lastAnswer)%n;
                    int findIndex = y % index[indexSeq];
                    if(findIndex >= initialSize){
                        seq = copyArray(seq);
                    }
                    lastAnswer = seq[indexSeq][findIndex];
                    System.out.println(lastAnswer);
                    break;
            }
        }
    }

    static int[][] copyArray(int[][] old){
        int[][] newArray = new int[totalN][initialSize + 10];
        for(int seq = 0; seq < totalN; seq++){
            for(int index = 0; index < initialSize; index++){
                if(old[seq][index] == 0){
                    break;
                }
                newArray[seq][index] = old[seq][index];
            }
        }
        initialSize += 10;
        return newArray;
    }

}
