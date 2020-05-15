package code;

import java.util.Scanner;

/**
 * Created by SRIN on 3/19/2018.
 */
public class QueenAttack2 {
    int N;
    int k;
    int[] kRow;
    int[] kCol;

    public static void main(String[] args) {
        QueenAttack2 q = new QueenAttack2();
        Scanner sc = new Scanner(System.in);
        q.N = sc.nextInt();
        q.k = sc.nextInt();

        int rQ = sc.nextInt();
        int cQ = sc.nextInt();

        //k terdekat dati timur, tenggara, selatan, barat daya, barat, barat laut, utara, timur laut
        int[] dRow = {-1, -1, -1, -1, -1, -1, -1, -1};
        int[] dCol = {-1, -1, -1, -1, -1, -1, -1, -1};

        for (int j = 1; j <= q.k; j++) {
            int rK = sc.nextInt();
            int cK = sc.nextInt();

            //timur
            if(rK == rQ && cK > cQ){
                if(dCol[0] == -1 || abs(dCol[0], cQ) > abs(cK ,cQ)){
                    dRow[0] = rK;
                    dCol[0] = cK;
                }
            }

            //tenggara
            if( abs(rK , rQ) == abs(cK , cQ) && rK < rQ && cK > cQ){
                if(dCol[1] == -1 ||  abs(dCol[1], cQ) > abs (cK ,cQ) ){
                    dRow[1] = rK;
                    dCol[1] = cK;
                }
            }

            //selatan
            if(cK == cQ && rK < rQ){
                if(dCol[2] == -1 || abs(dRow[2] ,rQ) > abs(rK, rQ) ){
                    dRow[2] = rK;
                    dCol[2] = cK;
                }
            }

            //barat daya
            if(abs(rK, rQ) == abs(cK, cQ) && rK < rQ && cK < cQ){
                if(dCol[3] == -1 || abs(dCol[3], cQ) > abs(cK, cQ)){
                    dRow[3] = rK;
                    dCol[3] = cK;
                }
            }

            //barat
            if(rK == rQ && cK < cQ){
                if(dCol[4] == -1 || abs(dCol[4], cQ) > abs(cK, cQ)){
                    dRow[4] = rK;
                    dCol[4] = cK;
                }
            }

            //barat laut
            if(abs(rK, rQ) == abs(cK, cQ) && cK < cQ && rK > rQ){
                if(dCol[5] == -1 || abs(dCol[5], cQ) > abs(cK, cQ)){
                    dRow[5] = rK;
                    dCol[5] = cK;
                }
            }

            //utara
            if(cK == cQ && rK > rQ){
                if(dCol[6] == -1 || abs(dRow[6], rQ) > abs(rK, rQ)){
                    dRow[6] = rK;
                    dCol[6] = cK;
                }
            }

            //timur laut
            if(abs(rK, rQ) == abs(cK, cQ) && rK > rQ && cK > cQ){
                if(dCol[7] == -1 || abs(dCol[7], cQ) > abs(cK, cQ)){
                    dRow[7] = rK;
                    dCol[7] = cK;
                }
            }
        }

        int sum = 0;
        //timur
        sum += dCol[0] == -1 ? abs(q.N, cQ) : abs(dCol[0], cQ)-1;
        //tenggara
        sum += dCol[1] == -1 ? min(abs(1,rQ), abs(q.N,cQ)) : abs(cQ, dCol[1])-1;
        //selatan
        sum += dCol[2] == -1 ? abs(1 ,rQ) : abs(dRow[2], rQ)-1;
        //barat daya
        sum += dCol[3] == -1 ? min(abs(1,rQ), abs(1,cQ)) : abs(cQ, dCol[3])-1;
        //barat
        sum += dCol[4] == -1 ? abs(1, cQ) : abs(dCol[4], cQ)-1;
        //barat laut
        sum += dCol[5] == -1 ? min(abs(q.N,rQ), abs(1,cQ)) : abs(cQ, dCol[5])-1;
        //utara
        sum += dCol[6] == -1 ? abs(q.N, rQ) : abs(dRow[6], rQ)-1;
        //timur laut
        sum += dCol[7] == -1 ? min(abs(q.N,rQ), abs(q.N,cQ)) : abs(cQ, dCol[7])-1;

        System.out.println(sum);

    }

    static int abs(int a, int b){
        return (a - b) > 0 ? (a-b) : -1 * (a - b);
    }

    static int min(int a, int b){
        return a < b ? a : b;
    }
}

/*
5 1
        4 3
        3 4
        */
