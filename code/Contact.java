package code;

import java.util.Scanner;

public class Contact {
	class Trie{
		Trie[] child = new Trie[26];
		int count;
	}
	
	Trie root;
	public static void main(String[] args){
		Scanner sc = new Scanner(System.in);
		int T = sc.nextInt();
		Contact c = new Contact();
		for(int i=0; i < T; i++){
			String command = sc.next();
			if(command.equalsIgnoreCase("add")){
				c.insert(sc.next().toCharArray());
			} else {
				System.out.println(c.getCount(sc.next().toCharArray()));
			}
		}
	}
	
	void insert(char[] s){
		if(root == null){
			root = new Trie();
		}
		
		Trie head = root;
		for(int i=0; i < s.length; i++){
			int index = (int)s[i] - (int)'a';
			if(head.child[index] == null){
				head.child[index] = new Trie();
			}
			head.child[index].count += 1;
			head = head.child[index];
		}
	}
	
	int getCount(char[] s){
		Trie head = root;
		for(int i=0; i < s.length; i++){
			int index = (int)s[i]-'a';
			if(head.child[index] == null){
				return 0;
			}
			head = head.child[index];
		}
		return head.count;
	}
	
	//hash function
	
}
