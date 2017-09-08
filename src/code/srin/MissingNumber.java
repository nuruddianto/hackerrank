package code.srin;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

/**
 * Created by SRIN on 9/8/2017.
 */
public class MissingNumber {
    public static int[] input;
    public static int[] output;

    public static void main(String[] args){
        input = new int[]{1, 2, 3, 4, 5, 6, 7, 8, 9};
        output = new int[]{1, 3, 4, 5, 7};
        findMissing(0, output.length-1,0);
        for(int i = output[output.length-1] ; i < input [input.length -1] ; i++){
            System.out.print((i+1) +" ");
        }
    }

    private static void findMissing(int left, int right, int missingFound){
        if(left >= right ){
            return;
        }

        int l = left;
        int r = right;

        while (l <= r)
        {
            int mid = (l + r)/2;

            if (input[mid] < output[mid-missingFound])
            {
                r = mid-1;
            }
            else
            {
                l = mid+1;
            }
        }

        System.out.print(input[l]+" ");
        missingFound++;
        findMissing(l, right, missingFound);
    }

    void writeTestCaseFile(String fileName) throws IOException {
        BufferedWriter output = null;
        output = new BufferedWriter(new FileWriter(fileName));

        //make array
        int[] numbers = new int[800];
    }
}
