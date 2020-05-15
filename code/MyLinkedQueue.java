package code;

import java.util.NoSuchElementException;

public class MyLinkedQueue {
	
	private class Node{
		Node mNext;
		String mData;
		public Node(String data){
			mData = data;
		}
		
		public Node getNext(){
			return mNext;
		}
		
		public void setNext(Node next){
			mNext = next;
		}
	}
	
	private Node mHead = null;
	private Node mTail = null;
	
	public void enqueue(String data){
		Node newNode = new Node(data);
		if(isEmpty()){
			mHead = newNode;
		}else{
			mTail.setNext(newNode);
		}
		
		mTail = newNode;
	}
	
	public String dequeue(){
		if(isEmpty()){
			throw new NoSuchElementException();
		}
		String data = mHead.mData;
		if(mTail == mHead){
			mTail = null;
		}
		mHead = mHead.getNext();
		return data;
	}
	
	public boolean isEmpty(){
		return mHead == null;
	}
	
	public int size(){
		int count = 1;
		if(mHead == null){
			return count;
		}
		while(mHead.getNext() != null){
			count++;
			mHead = mHead.getNext();
		}
		return count;
	}

	public String peek(){
		if(mHead == null){
			throw  new NoSuchElementException();
		}

		return mHead.mData;
	}
	
}
