package code;

import java.util.Scanner;

/**
 * Created by SRIN on 4/25/2017.
 */
public class ModifiedKapekraNumber {
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        long start = sc.nextInt();
        long end = sc.nextInt();
        boolean isContainKapreka = false;
        for(long i = start; i <= end; i++ ){
            if(isKapreka(i)){
                isContainKapreka = true;
                System.out.print(i + " ");
            }
        }

        if(!isContainKapreka){
            System.out.print("INVALID RANGE");
        }
    }

    private static boolean isKapreka(long i){
        long square = i *i;
        int length = String.valueOf(square).length()+1;

        long divise = 1;
        for(int l=1; l <= length/2; l++){
            divise *= 10;
        }

        long firstDigit = square /divise;
        long secondDigit = square - (firstDigit*divise);

        if(firstDigit + secondDigit == i){
            return true;
        }
        return false;
    }
}
