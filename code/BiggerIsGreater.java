package code;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Scanner;

/**
 * Created by SRIN on 5/8/2017.
 */
public class BiggerIsGreater {

    /***
     * 1. Find longest non increasing suffix 
     * 2. Get pivot and switch with rigmost successor 
     * 3. Reverse the suffix
     **/
    // Complete the biggerIsGreater function below.
    static String biggerIsGreater(String w) {
        int right = w.length() - 1;
        char[] c = w.toCharArray();

        for (int r = right; r >= 1; r--) {
            if (c[r] > c[r - 1]) {
                int pivot = c[r - 1];
                for (int i = right; i > r - 1; i--) {
                    if (c[i] > pivot) {

                        // switch
                        char tmp = c[i];
                        c[i] = c[r - 1];
                        c[r - 1] = tmp;

                        // reverse
                        int a = r;
                        int b = c.length - 1;

                        while (a < b) {
                            tmp = c[a];
                            c[a] = c[b];
                            c[b] = tmp;
                            a++;
                            b--;
                        }
                        return new String(c);
                    }
                }
            }
        }
        return "no answer";
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();

        for(int i = 0; i < n; i++) {
            String s = sc.next();
            System.out.println(biggerIsGreater(s));
        }
        sc.close();
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
