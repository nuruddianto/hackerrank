package code.rookierank2;

import java.util.Scanner;

/**
 * Created by nurud on 11/02/2017.
 */
public class MinimumDifferenceArray {
    private static int n;
    private static int minValue;
    private static int[] arr;

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        n = sc.nextInt();
        arr = new int[n];
        minValue = 1000000000;
        for(int i=0; i < n; i ++){
            arr[i] = sc.nextInt();
        }
        doQuickSort(0, arr.length-1);
        for(int i=0; i < arr.length-1; i++){
            int val = abs(arr[i],arr[i+1]);
            if(val < minValue){
                minValue = val;
            }
        }
        System.out.print(minValue);
    }

    private static int abs(int a, int b){
        int diff = a-b;
        return (diff > 0) ? diff : diff*-1;
    }

    private static int min(int a, int b){
        return (a <= b) ? a : b;
    }

    /*QuicSort*/

    public static void doQuickSort( int low, int high){
        if(low > high){
            return;
        }

        int i = low;
        int j = high;
        int mid = (i + j)/2;
        int pivot = arr[mid];

        while(i <= j){

            while(arr[i] < pivot){
                i++;
            }

            while(arr[j] > pivot){
                j--;
            }

            if(i <= j){
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
                i++;
                j--;
            }
        }
        //System.out.print(i+ " and "+j);
        if(i < high){
            doQuickSort(i, high);
        }

        if(j > low){
            doQuickSort(low, j);
        }
    }
}
