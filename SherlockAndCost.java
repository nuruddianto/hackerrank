package code;

import java.util.Scanner;

/**
 * Created by SRIN on 2/9/2017.
 */
public class SherlockAndCost {
    private static int[] data;
    private static int N;

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        while(T != 0){
            N = sc.nextInt();
            data = new int[N];
            for(int i=0; i < N; i++ ){
                data[i] = sc.nextInt();
            }

            System.out.println(findMax());
            T--;
        }
    }


    private static int findMax(){
        int total_from_low[] = new int[N];
        int total_from_high[] = new int[N];
        for(int i=1; i < N; i++){
            int high_to_low = abs(1, data[i-1]);
            int low_to_high = abs(data[i], 1);

            total_from_low[i] = max(total_from_low[i-1] , total_from_high[i-1]+low_to_high);
            total_from_high[i] = max(total_from_high[i-1] , total_from_low[i-1]+high_to_low);
        }
        return max(total_from_low[N-1], total_from_high[N-1]);
    }

    private static int abs(int a, int b){
        int abs = a-b;
        return abs > 0 ? abs : abs*-1;
    }

    private static int max(int a, int b){
        return (a >= b) ? a : b;
    }
}

/*
1
11
79 6 40 68 68 16 40 63 93 49 91
642

1
10
55 68 31 80 57 18 34 28 76 55
508
*/
