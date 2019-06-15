package code;

import java.util.Scanner;

/**
 * Created by SRIN on 4/20/2017.
 */
public class NonDivisibleSubset {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt();
        int k = sc.nextInt();
        int[] arr = new int[k + 1];

        if (k == 1) {
            System.out.print(1);
            return;
        }

        for (int i = 0; i < n; i++) {
            int val = sc.nextInt();
            int index = val % k;
            arr[index] += 1;
        }

        int sum = 0;

        for (int i = 1; i <= k / 2; i++) {
            if (i != k - i) {
                sum += max(arr[i], arr[k - i]);
            } else {
                sum += 1;
            }
        }

        if(arr[0] != 0){
            sum += 1;
        }
        System.out.print(sum);
    }

    private static int max(int a, int b) {
        return a > b ? a : b;
    }
}

/*

13 11
        582740017 954896345 590538156 298333230 859747706 155195851 331503493 799588305 164222042 563356693 80522822 432354938 652248359
        11

        10 4
1 2 3 4 5 6 7 8 9 10
5
        */
