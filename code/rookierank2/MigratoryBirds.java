package code.rookierank2;

import java.util.Scanner;

/**
 * Created by nurud on 11/02/2017.
 */
public class MigratoryBirds {
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int birds[] = new int[5+1];
        for(int i=0; i < n; i++){
            int bird = sc.nextInt();
            birds[bird] +=1;
        }
        int mostFreq =0;
        int mostBird =0;
        for(int j=1; j <=  5; j++){
            if(birds[j]>mostFreq){
                mostFreq = birds[j];
                mostBird =j;
            }
        }
        System.out.print(mostBird);
    }
}
