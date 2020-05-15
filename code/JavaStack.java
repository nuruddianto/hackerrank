package code;
import java.util.NoSuchElementException;
import java.util.Scanner;

/**
 * Created by SRIN on 1/26/2017.
 */
public class JavaStack {
    private class Node{
        Node mNext;
        char mData;

        public Node(char data){
            mData = data;
        }

        private Node getNext(){
            return mNext;
        }

        private void setNext(Node next){
            mNext = next;
        }

        private char getData(){
            return mData;
        }
    }

    static char open[] = {'{', '[', '('};
    static char close[] = {'}', ']', ')'};

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        while (sc.hasNext()){
            String s = sc.next();
            JavaStack q = new JavaStack();
            System.out.println(q.isBalance(s, q));
        }
    }

    private  String isBalance(String s, JavaStack q){
        char chars[] = s.toCharArray();

        if(chars.length %2 != 0){
            return "false";
        }

        for (char c : chars){
            q.enqueue(c);
        }

        if(check(q)){
            return "true";
        }else{
            return "false";
        }
    }

    private boolean check( JavaStack q){
        if(q.isEmpty()){
            return true;
        }
        char firstChar = q.get(0);
        if(q.get(0) == close[0] || q.get(0) == close[1] || q.get(0) == close[2]){
            return false;
        }

        for(int i = 0; i < q.size()-1; i++){
            if((q.get(i) == open[0] && q.get(i+1) == close[0]) ||(q.get(i) == open[1] && q.get(i+1) == close[1]) || (q.get(i) == open[2] && q.get(i+1) == close[2])){
                q.remove(i);
                q.remove(i);
                return check(q);
            }
        }
        return false;
    }

    private Node mHead = null;
    private Node mTail = null;

    private void enqueue(char data){
        Node node = new Node(data);
        if(isEmpty()){
            mHead = node;
        }else{
            mTail.setNext(node);
        }
        mTail = node;
    }

    private char get(int index){
        Node currData = mHead;
        if(index == 0){
            return currData.getData();
        }
        for(int i=0; i< index; i++){
            currData = currData.getNext();
        }

        return currData.getData();
    }
    private void remove(int index){
        Node currData = mHead;
        Node prevData = null;

        if(index == 0){
            mHead = mHead.getNext();
            return;
        }
        for(int i =0; i < index; i++){
            prevData = currData;
            currData = currData.getNext();
        }

        prevData.setNext(currData.getNext());
    }

    private char dequeue(){
        if(isEmpty()){
            throw new NoSuchElementException();
        }

        char data= mHead.getData();
        if(mHead == mTail){
            mTail = null;
        }
        mHead = mHead.getNext();
        return data;
    }

    private boolean isEmpty(){
        return mHead == null;
    }

    private int size(){
        int counter = 1;
        if(!isEmpty()){
            Node currData = mHead;
            while(currData.getNext() != null){
                counter++;
                currData = currData.getNext();
            }
        }
        return counter;
    }
}
