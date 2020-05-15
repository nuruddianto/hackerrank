package code;

import java.util.Scanner;

/**
 * Created by SRIN on 5/16/2017.
 */
public class Equal {
    private static int v[] = {1, 2, 5};
    private static int arr[];
    private static int min;
    private static int mem[][];

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();

        for (int t = 0; t < T; t++) {
            int n = sc.nextInt();
            arr = new int[n];
            min = 10000000;
            mem = new int[4][100001];

            for (int i = 0; i < n; i++) {
                int val = sc.nextInt();
                arr[i] = val;
                if (min > val) {
                    min = val;
                }
            }

            long minStep = 1000000000;

            int i = 0;
            while (i <= 3 && min >= 0) {
                long totStep = 0;
                for (int j = 0; j < n; j++) {
                    long step = f(arr[j], i);
                    totStep += step;
                }

                if (totStep < minStep) {
                    minStep = totStep;
                }
                min--;
                i++;
            }
            System.out.println(minStep);
        }
    }

    private static int f(int val, int minValue) {
        if (val < min) {
            return 10000;
        }
        if (mem[minValue][val] == 0) {
            if (val == min) {
                return 0;
            }
            mem[minValue][val] = min(f(val - 5, minValue), min(f(val - 2, minValue), f(val - 1, minValue)))+1;
            return mem[minValue][val];
        }

        return mem[minValue][val];
    }

    private static int min(int a, int b) {
        return a < b ? a : b;
    }
}
