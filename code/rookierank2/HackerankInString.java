package code.rookierank2;

import java.util.Scanner;

/**
 * Created by nurud on 12/02/2017.
 */
public class HackerankInString {
    private static char[] hackerrank = {'h', 'a', 'c', 'k', 'e', 'r', 'r', 'a', 'n', 'k'};
    public static void main(String[] args){

        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        for(int i=0; i < t; i++){
            String s = sc.next();
            boolean[] sChar = new boolean[s.length()];
            if(isContain(s, 0, 0)){
                System.out.println("YES") ;
            }else{
                System.out.println("NO") ;
            }

        }
    }

    private static boolean isContain(String s, int indexChar, int indexHacerrank){
        if(indexHacerrank == 10){
            return true;
        }

        if(indexChar > s.length()-1){
            return false;
        }

        for(int i= indexChar; i < s.length(); i++){
            if(s.charAt(i) == hackerrank[indexHacerrank]){
                return isContain(s, i+1, indexHacerrank+1);
            }
        }
        return false;
    }
}
