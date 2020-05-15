package code;

import java.util.Scanner;

/**
 * Created by SRIN on 4/26/2017.
 */
public class AbsolutePermutation {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int T = sc.nextInt();
        for (int i = 0; i < T; i++) {
            int n = sc.nextInt();
            int k = sc.nextInt();

            int arr[] = new int[n + 1];
            boolean isUsed[] = new boolean[n+1];
            boolean isValid = true;

            for (int l = 1; l <= n; l++) {
                int firstI = l + k;
                int secondI = l - k;

                int min = min(firstI, secondI);
                if(min <= n && min >= 1 && !isUsed[min] ){
                    arr[l] = min;
                    isUsed[min] = true;
                }else if (firstI <= n && firstI >= 1 && !isUsed[firstI]) {
                    arr[l] = firstI;
                    isUsed[firstI] = true;
                } else if (secondI <= n && secondI >= 1 && !isUsed[secondI]) {
                    arr[l] = secondI;
                    isUsed[secondI] = true;
                } else {
                    isValid = false;
                    break;
                }
            }

            if (!isValid) {
                System.out.print(-1);
            } else {
                for (int h = 1; h <= n; h++) {
                    System.out.print(arr[h] + " ");
                }
            }

//            for (int h = 1; h <= n; h++) {
//                System.out.print(arr[h] + " ");
//            }

            System.out.println();
        }
    }

    private static int min(int a, int b){
        return a < b ? a : b;
    }
}

/*
10
        94 70
        95 49
        92 14
        96 2
        98 7
        92 85
        90 15
        92 10
        94 0
        92 40
        */
