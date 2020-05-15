package code;

import java.util.*;

public class LinkedListed {
	Node mHead;
	public LinkedListed(){
		
	}
	
	public static void main(String[] args){
		Scanner sc = new Scanner(System.in);
		LinkedListed list  = new LinkedListed();
		
		int N = sc.nextInt();
		for(int i =0; i < N; i++){
			int num = sc.nextInt();
			list.add(num);
		}
		
		int totalOp = sc.nextInt();
		for(int j =0; j < totalOp; j++){
			String operation = sc.next();
			if(operation.equals("Insert")){
				int index = sc.nextInt();
				int data = sc.nextInt();
				list.addAt(index, data);
			}else{
				int indexs = sc.nextInt();
				list.remove(indexs);
			}
		}
		
		Node head = list.mHead;
		
		while(head != null){
			System.out.print(head.mData+" ");
			head = head.getNext();
		}
		
		sc.close();
	}
	
	public void add(int data){
		if(mHead == null){
			mHead = new Node(data);
			return;
		}
		
		Node tmpData = new Node(data);
		Node currData = mHead;
		
		while(currData.getNext() != null){
			currData = currData.getNext();
		}
		
		currData.setNext(tmpData);
	}
	
	public void addAt(int index, int data){
		if(mHead == null){
			return;
		}
		
		Node currData = mHead;
		Node prevData = null;
		
		if(index == 0){
			mHead = new Node(data);
			mHead.setNext(currData);
			return;
		}
		
		for(int i=0; i < index; i++){
			prevData= currData;
			currData = currData.getNext();
		}
		Node tmpData = new Node(data, currData);
		prevData.setNext(tmpData);
	}
	
	public void remove(int index){
		
		if(mHead == null){
			return;
		}
		
		Node currData = mHead;
		Node prevData = null;
		
		if(index == 0){
			mHead = mHead.getNext();
			return;
		}
		
		for(int i = 0; i < index; i++){
			prevData = currData;
			currData = currData.getNext();
		}
		
		prevData.setNext(currData.getNext());
	}
	
	private class Node{
		Node mNext;
		int mData;
		
		public Node(int data){
			mData= data;
		}
		
		public Node(int data, Node next){
			mData= data;
			mNext = next;
		}
		
		public Node getNext(){
			return mNext;
		}
		
		public void setNext(Node next){
			mNext = next;
		}
	}
}
