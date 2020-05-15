package code;

import java.util.Scanner;

/**
 * Created by SRIN on 3/13/2018.
 */
public class GridChallenge {
    int[][] map;
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        GridChallenge g = new GridChallenge();
        for(int t = 0; t < T; t++){
            int row = sc.nextInt();
            g.map = new int[row][row];
            boolean isValid = true;
            for(int l =0 ; l < row; l++){
                String s = sc.next();
                for(int c = 0; c < s.length(); c++) {
                    g.map[l][c] = (int)s.charAt(c);
                }
                g.doQuickSort(0, s.length() - 1, g.map[l]);
                if(l > 0){
                    for(int y=0; y < row; y++){
                        if(g.map[l][y] < g.map[l-1][y]){
                            isValid = false;
                            break;
                        }
                    }

                }
            }
            //g.printMap(g.map);

            System.out.println( isValid ? "YES" : "NO");
            
        }
    }

    private void doQuickSort(int low, int high, int arr[]){
        if(low > high){
            return;
        }

        int mid = (low + high)/2;
        int pivot = arr[mid];

        int l = low;
        int h = high;

        while(l <= h){
            while(arr[l] <  pivot){
                l++;
            }

            while(arr[h] > pivot){
                h--;
            }

            //swap
            if(l <= h){
                int tmp = arr[l];
                arr[l] = arr[h];
                arr[h] = tmp;
                l++;
                h--;
            }
        }

        if(l < high){
            doQuickSort(l, high, arr);
        }

        if(h > low){
            doQuickSort(low, h, arr);
        }

    }

    private void printMap(int m[][]){
        for(int i=0; i < m.length; i++){
            for(int j=0; j < m.length; j++){
                System.out.print((char)m[i][j]+" ");
            }
            System.out.println();
        }
        System.out.println();
    }
}
