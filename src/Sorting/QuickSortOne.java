package Sorting;

import java.util.Scanner;

/**
 * Created by nurud on 03/12/2016.
 */

/*FINISH*/
public class QuickSortOne {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        int arr[] = new int[N];

        for (int i = 0; i < N; i++) {
            arr[i] = sc.nextInt();
        }

        int length = arr.length - 1;
        int pivot = arr[0];
        int tmp = 0;
        int pIndex = length;

        for (int i = length; i >= 0; i--) {
            if (arr[i] >= pivot) {
                tmp = arr[i];
                arr[i] = arr[pIndex];
                arr[pIndex] = tmp;
                pIndex--;
            }
        }

        for (int b = 0; b < N; b++) {
            System.out.print(arr[b] + " ");
        }
    }

}
