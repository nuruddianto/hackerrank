package code;

import java.util.HashSet;
import java.util.NoSuchElementException;
import java.util.Scanner;
import java.util.Set;

/**
 * Created by SRIN on 1/26/2017.
 */
public class JavaDequeue {
    private class Node {
        Node mNext;
        int mData;

        private Node(int data) {
            mData = data;
        }

        private Node getNext() {
            return mNext;
        }

        private void setNext(Node next) {
            mNext = next;
        }

        private int getData() {
            return mData;
        }
    }

    Node mHead;
    Node mTail;
    private static int size = 0;
    private static int[] arr;
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        JavaDequeue q1 = new JavaDequeue();

       int N = sc.nextInt();
       int com = sc.nextInt();

       for(int i =0; i < N; i++){
           int in = sc.nextInt();
           q1.enqueue(in);
       }
       int max = 0;

       while(!q1.isEmpty()){
           if (max == com) {
               break;
           }
           Set<Integer> set = new HashSet<>();
           arr = new int[com];
           Node currData = q1.mHead;

           for(int j=0; j < com; j++){
               set.add(currData.getData());
               // arr[j] = currData.getData();
                currData = currData.getNext();
           }

           //doQuickSort(0, arr.length-1);
           int currUniqueValue = set.size();
           if(max < currUniqueValue){
               max = currUniqueValue;
           }

           if(q1.size() == com){
               break;
           }
           q1.dequeue();
       }
       System.out.print(max);
    }

    private void enqueue(int data) {
        Node node = new Node(data);
        if (isEmpty()) {
            mHead = node;
        } else {
            mTail.setNext(node);
        }
        mTail = node;
        size++;
    }

    private int dequeue() {
        if (isEmpty()) {
            throw new NoSuchElementException();
        }

        Node currData = mHead;
        int data = currData.getData();
        if (mHead == mTail) {
            mTail = null;
        }
        mHead = mHead.getNext();
        size--;
        return data;
    }

    private boolean isEmpty() {
        return mHead == null;
    }

    private int size(){
        return size;
    }

    /*Quick Sort*/

    private static void doQuickSort(int low, int high){
        if(high <= low){
            return;
        }
        int j = doPartition(low, high);
        doQuickSort(low, j-1);
        doQuickSort(j+1, high);
    }

    private static int doPartition(int left, int right){
        int low = left+1;
        int pivot  = arr[left];
        int rightIndex = right;
        for(int i = right; i >= low; i--){
            if(arr[i] >= pivot){
                int tmp = arr[i];
                arr[i]= arr[rightIndex];
                arr[rightIndex] = tmp;
                rightIndex--;
            }
        }

        int tmp = arr[left];
        arr[left] = arr[rightIndex];
        arr[rightIndex] = tmp;

        return rightIndex;
    }

    /*Find distict value*/
    private static int totalUniqueValue(){
        int total =1;
        for(int i=0; i< arr.length-1; i++){
            if(arr[i] != arr[i+1]){
                total++;
            }
        }
        return total;
    }
}
