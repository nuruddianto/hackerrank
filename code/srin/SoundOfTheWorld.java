package code.srin;

import java.util.Scanner;

/**
 * Created by SRIN on 10/19/2017.
 */
public class SoundOfTheWorld {


    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int testCases = sc.nextInt();
        int i = 0;
        for( i = 0;i < testCases; i++){
            String s = sc.next();
            int totalHypens = sc.nextInt();

            int[] hypen = new int[100];
            for(int j = 0; j < totalHypens; j++){
                int location = sc.nextInt();
                hypen[location]++;
            }
            
        	String ans = "";
            int indexChar = 0;
            for(int l = 0; l < s.length(); l++){
                for(int b = 0; b < hypen[l]; b++ ){
                    ans = ans + "-";
                }
                
              	ans =ans+s.charAt(l);
            }
            System.out.print("#"+i+" ");
            System.out.println(ans);

            System.out.println(ans);
        }
        System.out.println(i);
    }

}

/*
2
wow
3
2 3 2
hoi
3
0 0 0
*/
