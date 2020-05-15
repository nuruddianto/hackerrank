package code;

import java.util.Scanner;

public class XorSequence {

  	public static void main(String[] args){
		Scanner in = new Scanner(System.in);
        int Q = in.nextInt();
        for(int a0 = 0; a0 < Q; a0++){
            long L = in.nextLong();
            long R = in.nextLong();
            
            long ans = xorAtN(L-1)^xorAtN(R);
            
            System.out.println(ans);
        }
	}
	
	public static long xorAtN(long n){
		long val = n % 8;
		
        if(val == 0 || val == 1){
			return n;
		}
        
		if(val == 2 || val == 3){
			return 2;
		}
		
		if(val == 4 || val == 5){
			return n+2;
		}
		
		return 0;
	}
}
