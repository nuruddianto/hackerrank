package code;

public class MyLinkedList {
	
	Node mHead;
	private static int mCount;
	
	public MyLinkedList(){
		
	}
	
	public static void main(String[] args){
		MyLinkedList linkedList = new MyLinkedList();
		linkedList.addLast("rudi", "98989", "8098", "mail@gmail.com", "awaw");
		linkedList.addLast("ozil", "98989", "8098", "mail@gmail.com", "awaw");
		linkedList.addLast("giroud", "98989", "8098", "mail@gmail.com", "awaw");
		linkedList.addAfter(1,"cazorla", "98989", "8098", "mail@gmail.com", "awaw");
		if(linkedList.remove(1)){
			System.out.println("sucsess remove index 1");
		}
		
		
		Node data = linkedList.mHead;
		

		while(data != null){
			System.out.println(data.mName+" "+data.mNumber+" "+data.mBirthday+" "+data.mEmail+" "+data.mMemo);
			data = data.getNext();
		}
	}
	
	public void addLast(String name, String number, String birthday, String email, String memo){
		if(mHead == null){
			mHead = new Node(name, number, birthday, email, memo);
			return;
		}
		
		Node tmpData = new Node(name, number, birthday, email, memo);
		Node currData = mHead;
		while(currData.getNext() != null){
			currData = currData.getNext();
		}
		
		currData.setNext(tmpData);
		mCount++;
	}
	
	public void addAfter(int index, String name, String number, String birthday, String email, String memo){
		if(mHead == null){
			return;
		}
		
		Node currData = mHead;
		for(int i=0; i < index; i++){
			currData = currData.getNext();
		}
		
		Node tmpData = new Node(currData.getNext(), name, number, birthday, email, memo);
		currData.setNext(tmpData);
		mCount++;
	}
	
	public boolean remove(int index){
		if(mHead == null || index>=getSize() || index < 0){
			return false;
		}
		Node currData = mHead;
		Node prevData = null;
		for(int i=0; i < index; i++){
			prevData = currData;
			currData = currData.getNext();
		}
		
		if(currData != null){
			prevData.setNext(currData.getNext());
			mCount--;
			return true;
		}
		return false;
	}
	
	public int getSize(){
		return mCount;
	}
	
	private class Node{
		public Node mNext;
		public String mName;
		public String mNumber;
		public String mBirthday;
		public String mEmail;
		public String mMemo;
		
		public Node(String name, String number, String birthday, String email, String memo){
			mName = name;
			mNumber = number;
			mBirthday = birthday;
			mEmail = email;
			mMemo = memo;
		}
		
		public Node(Node next, String name, String number, String birthday, String email, String memo){
			mNext = next;
			mName = name;
			mNumber = number;
			mBirthday = birthday;
			mEmail = email;
			mMemo = memo;
		}
		
		public void setNext(Node next){
			mNext = next;
		}
		
		public Node getNext(){
			return mNext;
		}
		
		public String getName(){
			return mName;
		}
	}
}
