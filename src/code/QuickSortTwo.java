package code;

/**
 * Created by nurud on 17/12/2016.
 */

import java.util.*;

/*NOT FINISH YET*/
public class QuickSortTwo {
    private static int arr[] = new int[1000];

    public static void main (String[] args){
        Scanner sc = new Scanner(System.in);

        int N = sc.nextInt();

        for(int i=0; i < N; i++){
            arr[i]= sc.nextInt();
        }

        int tmp = arr[N/2];
        arr[N/2] = arr[0];
        arr[0] = tmp;

        doQuickSort(0, N-1, arr);

        int k=0;
        while(k < N/2 ){
            System.out.print(arr[k]+" ");
            k++;
        }
        System.out.println();
        int l = N-1;
        while(l > N/2 ){
            System.out.print(arr[l]+" ");
            l--;
        }
        System.out.println();
        for(int j =0; j < N ; j++){
            System.out.print(arr[j]+" ");
        }
    }

    public static void doQuickSort( int low, int high , int[] arr){
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
            doQuickSort(i, high, arr);
        }

        if(j > low){
            doQuickSort(low, j, arr);
        }
    }
}
