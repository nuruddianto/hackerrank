package code;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Scanner;

/**
 * Created by SRIN on 5/8/2017.
 */
public class BiggerIsGreater {

    private static char[] c;

    public static void main(String[] args) throws IOException {
        BufferedReader sc = new BufferedReader(new InputStreamReader(System.in));
        int T = Integer.parseInt(sc.readLine());
//        String line = "";
//        Scanner sc = new Scanner(System.in);
//        long T = sc.nextInt();
        for(long t=0; t < T; t++){
            String s = sc.readLine();
            c = null;
            c = s.toCharArray();
            int firstChar = findFirstChar(s.toCharArray());
            if(firstChar == -1){
                System.out.println("no answer");
            }else{
                int secondChar = findSecondChar(firstChar, s.toCharArray());
                if(secondChar == -1){
                    System.out.println("no answer");
                }else{
                    swap(firstChar, secondChar, c);
                    doQuickSort(firstChar+1, c.length-1, c);
                    //System.out.print(firstChar+" "+secondChar);
                    System.out.println(c);
                }
            }

        }
    }

    private static int findFirstChar(char[] c){
        int length = c.length;
        if(length == 1){
            return -1;
        }
        for(int i = length - 2; i >= 0; i--){
            if(c[i] < c[i+1]){
                return i;
            }
        }

        return -1;
    }

    private static int findSecondChar(int start, char[] c){
        int length = c.length;
        if(length == 1){
            return -1;
        }
        char min = 'z';
        int index = -1;
        for(int i = start+1 ; i < length; i++){
            if(c[start] < c[i] && c[i] < min){
                min = c[i];
                index = i;
            }
        }
        return index;
    }

    private static void swap(int a, int b, char[] s){
        char tmp = s[a];
        s[a] = s[b];
        s[b] = tmp;
    }

    private static void doQuickSort(int l, int r, char[] s){
        if( l >= r ){
            return;
        }

        int mid = (l + r)/2;

        int left = l;
        int right = r;

        while(left <= right){

            while(s[left] < s[mid]){
                left++;
            }

            while(s[right] > s[mid]){
                right--;
            }

            if(left <= right){
                char tmp = s[left];
                s[left] = s[right];
                s[right] = tmp;
                left++;
                right--;
            }
        }

        if(left < r){
            doQuickSort(left, r, s);
        }

        if(right > l){
            doQuickSort(l, right, s);
        }
    }

    private static void printChar(char[] c){
        for(int i=0; i < c.length; i++){
            System.out.print(c[i]);
        }
        System.out.println();
    }

}

        /*
        input
        1
        ocsmerkgidvddsazqxjbqlrrxcotrnfvtnlutlfcafdlwiismslaytqdbvlmcpapfbmzxmftrkkqvkpflxpezzapllerxyzlcf

        output
        ocsmerkgidvddsazqxjbqlrrxcotrnfvtnlutlfcafdlwiismslaytqdbvlmcpapfbmzxmftrkkqvkpflxpezzapllerxyzlfc


        input
        4
        zyxwqpnnmlljihhgfffeeeddca
        tccjaoahruyblpejzgkfnpmqoajnvqnvqmcdwpioxkrllofvixidannpvzxtpnzdtyxfkcloanztgkvgsngqxahnzmtrh
        nxczkgxcazmwlutxjwmflhqhfgnqf
        ehxxdsuhoowxpbxiwxjrhe

        output
        no answer
        tccjaoahruyblpejzgkfnpmqoajnvqnvqmcdwpioxkrllofvixidannpvzxtpnzdtyxfkcloanztgkvgsngqxahnzrhmt
        nxczkgxcazmwlutxjwmflhqhfgqfn
        ehxxdsuhoowxpbxiwxrehj
        */
