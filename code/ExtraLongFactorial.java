package code;

import java.math.BigInteger;
import java.util.Scanner;

/**
 * Created by SRIN on 4/18/2017.
 */
public class ExtraLongFactorial {

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        System.out.println(f(BigInteger.valueOf(n)));
    }

    public static BigInteger f(BigInteger n){
        if(n.intValue() == 1){
            return BigInteger.valueOf(1);
        }

        BigInteger one = new BigInteger("1");

        return n.multiply(f( n.subtract(one)));
    }
}
