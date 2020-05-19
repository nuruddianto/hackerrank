package code;

import java.util.*;

class FindTheRunningMedian {
    public static void main(final String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();

        int[] a = new int[n];
        for(int i=0; i< n; i++) {
            a[i] = sc.nextInt();
        }
        
        System.out.println(Arrays.toString(runningMedian(a)));
        sc.close();
    }

    static double[] runningMedian(int[] a) {
        Queue<Integer> maxHeap = new PriorityQueue<Integer>(10, Collections.reverseOrder());
        Queue<Integer> minHeap = new PriorityQueue<>();

        double[] result = new double[a.length];

        maxHeap.add(a[0]);
        result[0] = new Double(a[0]);
        for (int i = 1; i < a.length; i++) {
            if (a[i] < maxHeap.peek()) {
                maxHeap.add(a[i]);
            } else {
                minHeap.add(a[i]);
            }

            // balancing
            if (maxHeap.size() - minHeap.size() > 1) {
                minHeap.add(maxHeap.remove());
            } else if (minHeap.size() - maxHeap.size() > 1) {
                maxHeap.add(minHeap.remove());
            }

            double leftMed = new Double(maxHeap.peek());
            double rightMed = new Double(minHeap.peek());

            if (maxHeap.size() == minHeap.size()) {
                result[i] = (leftMed + rightMed) / 2;
                System.out.println(result[i]);
            } else if (maxHeap.size() > minHeap.size()) {
                result[i] = leftMed;
            } else {
                result[i] = rightMed;
            }
        }
        return result;
    }
}

