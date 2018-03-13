package code;

public class MyTrie {
	
	static class TrieNode{
		int ALPHABET_SIZE = 26;
		
		TrieNode[] child = new TrieNode[26];
		boolean isEndOfWord;
	}
	
	public static void main(String[] args){
		String keys[] = { "the", "a", "there", "answer", "any", "by", "bye",
				"their" };

		String output[] = { "Not present in trie", "Present in trie" };

		root = new TrieNode();

		int i;
		for (i = 0; i < keys.length; i++)
			insert(keys[i]);

		// Search for different keys
		if (search("the") == true)
			System.out.println("the --- " + output[1]);
		else
			System.out.println("the --- " + output[0]);

		if (search("these") == true)
			System.out.println("these --- " + output[1]);
		else
			System.out.println("these --- " + output[0]);

		if (search("their") == true)
			System.out.println("their --- " + output[1]);
		else
			System.out.println("their --- " + output[0]);

		if (search("thaw") == true)
			System.out.println("thaw --- " + output[1]);
		else
			System.out.println("thaw --- " + output[0]);
	}
	
	static TrieNode root;
	
	static void insert(String key){
		int index;
		int length = key.length();
		int level;
		
		TrieNode data = root;
		for(level = 0; level < length; level++){
			index = key.charAt(level) - 'a';
			if(data.child[index] == null){
				data.child[index] = new TrieNode();
			}
			
			data = data.child[index];
		}
		
		data.isEndOfWord = true;
	}
	
	static boolean search(String key){
		int length = key.length();
		int index;
		TrieNode tmp = root;
		for(int i=0; i < length; i++){
			index = key.charAt(i) - 'a';
			if(tmp.child[index] == null){
				return false;
			}
			tmp = tmp.child[index];
		}
		
		return tmp != null && tmp.isEndOfWord;
	}
}
