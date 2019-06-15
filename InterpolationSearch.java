package code;

/**
 * Created by SRIN on 1/16/2018.
 */
public class InterpolationSearch {
    static int arr[] = new int[]{1, 4, 5, 7, 10, 15, 18,23};

    static int interpolationSearch(int x){
        int lo = 0, hi = (arr.length -1);

        while(lo <= hi && x >= arr[lo] && x <= arr[hi] ){
            int pos = lo + ((x - arr[lo]) * (hi - lo))/(arr[hi] - arr[lo]);
            if(arr[pos] == x)
                return pos;
            if(arr[pos] < x){
                lo = pos + 1;
            }else{
                hi = pos - 1;
            }
        }
        return -1;
    }

    public static void main(String[] args)
    {
        int x = 18; // Element to be searched
        int index = interpolationSearch(x);

        // If element was found
        if (index != -1)
            System.out.println("Element found at index " + index);
        else
            System.out.println("Element not found.");
    }
}
