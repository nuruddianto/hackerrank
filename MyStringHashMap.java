package code;

public class MyStringHashMap {
	Node[] table;
	int mTableSize;
	
	class Node{
		String data;
		Node next;	
	}
	
	
	void init(int tableSize){
		mTableSize = tableSize;
		table = new Node[mTableSize];
	}
	
	int hashFunction( char[] str)
	{	
		int hash = 7;
		for (int i = 0; i < str.length; i++) {
			hash = hash*31 + str[i];
		}
		
		return hash % mTableSize;
	}
	
	void put(char[] str){
		int hashVal = hashFunction(str);
		Node newData = new Node();
		newData.data = new String(str);
		
		Node tmp = table[hashVal]; 
		if(tmp == null){
			table[hashVal] = newData;
		} else {
			newData.next = tmp;
			table[hashVal] = newData;
		}
	}
	
	Node get(char[] str){
		int hashVal = hashFunction(str);
		Node tmp = table[hashVal];
		while(tmp != null){
			if(equals(tmp.data.toCharArray(), str)){
				return tmp;
			}
			tmp = tmp.next;
		}
		return null;
	}
	
	boolean equals(char[] str1, char[] str2){
		if(str1.length != str2.length){
			return false;
		}
		
		for(int i=0; i < str1.length; i++){
			if(str1[i] != str2[i]){
				return false;
			}
		}
		
		return true;
	}
	
	public static void main(String[] args){
		MyStringHashMap h = new MyStringHashMap();
		h.init(10);
		h.put("as".toCharArray());
		h.put("ab".toCharArray());
		h.put("as".toCharArray());
		h.put("c".toCharArray());
		
		System.out.println(h.get("as".toCharArray()).data);
	}
}

