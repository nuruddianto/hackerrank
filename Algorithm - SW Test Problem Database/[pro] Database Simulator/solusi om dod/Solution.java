// note : this is not a full, working solution! we just want to show how to handle the char[] datapackage hackerrank.road2pro.databasesimulator;

import java.io.FileInputStream;
import java.util.Scanner;

/**
 * @author SRIN
 * https://www.hackerrank.com/contests/road2pro/challenges/test-api-problems
 */
public class Solution {
	
	private static final int CMD_INIT = 0;
	private static final int CMD_ADD = 1;
	private static final int CMD_DELETE = 2;
	private static final int CMD_CHANGE = 3;
	private static final int CMD_SEARCH = 4;

	static Scanner sc;

	static int[] dummy = new int[100];
	static int Score, ScoreIdx;
	static char[] name, number, birthday, email, memo;

	static char[][] lastname = { "kim".toCharArray(), "lee".toCharArray(),
			"park".toCharArray(), "choi".toCharArray(), "jung".toCharArray(),
			"kang".toCharArray(), "cho".toCharArray(), "oh".toCharArray(),
			"jang".toCharArray(), "lim".toCharArray() };
	static int[] lastname_length = { 3, 3, 4, 4, 4, 4, 3, 2, 4, 3 };

	public static class RESULT {
		public int count;
		public char[] str = new char[20];
		
		@Override
		public String toString() {
			return new String(str);
		}
	};

	static int mSeed;

	static int mrand(int num) {
		mSeed = mSeed * 1103515245 + 37209;
		if (mSeed < 0)
			mSeed *= -1;
		return ((mSeed >> 8) % num);
	}

	static void make_field(int seed) {
		int name_length, email_length, memo_length;
		int idx, num;
		name = new char[20];
		number = new char[20];
		birthday = new char[20]; 
		email = new char[20];
		memo = new char[20];
		mSeed = (int) seed;

		name_length = 6 + mrand(10);
		email_length = 10 + mrand(10);
		memo_length = 5 + mrand(10);

		num = mrand(10);
		for (idx = 0; idx < lastname_length[num]; idx++)
			name[idx] = lastname[num][idx];
		for (; idx < name_length; idx++)
			name[idx] = (char) ('a' + mrand(26));
		name[idx] = 0;

		for (idx = 0; idx < memo_length; idx++)
			memo[idx] = (char) ('a' + mrand(26));
		memo[idx] = 0;

		for (idx = 0; idx < email_length - 6; idx++)
			email[idx] = (char) ('a' + mrand(26));
		email[idx++] = '@';
		email[idx++] = (char) ('a' + mrand(26));
		email[idx++] = '.';
		email[idx++] = 'c';
		email[idx++] = 'o';
		email[idx++] = 'm';
		email[idx] = 0;

		idx = 0;
		number[idx++] = '0';
		number[idx++] = '1';
		number[idx++] = '0';
		for (; idx < 11; idx++)
			number[idx] = (char) ('0' + mrand(10));
		number[idx] = 0;

		idx = 0;
		birthday[idx++] = '1';
		birthday[idx++] = '9';
		num = mrand(100);
		birthday[idx++] = (char) ('0' + num / 10);
		birthday[idx++] = (char) ('0' + num % 10);
		num = 1 + mrand(12);
		birthday[idx++] = (char) ('0' + num / 10);
		birthday[idx++] = (char) ('0' + num % 10);
		num = 1 + mrand(30);
		birthday[idx++] = (char) ('0' + num / 10);
		birthday[idx++] = (char) ('0' + num % 10);
		birthday[idx] = 0;
	}

	static void cmd_init() {
		ScoreIdx = sc.nextInt();

		InitDB();
	}

	static void cmd_add() {
		int seed;
		seed = sc.nextInt();

		make_field(seed);

		Add(name, number, birthday, email, memo);
	}

	static void cmd_delete() {
		int field, check, result;
		char[] str = new char[20];
		field = sc.nextInt();
		str = sc.next().toCharArray();
		check = sc.nextInt();

		result = Delete(field, str);
		if (result != check) {
			Score -= ScoreIdx;
			System.out.println("-------------------------------------------------");
			System.out.println(">> delete field: "+field+", str: "+new String(str)+", result: "+result+", check: "+check);
			System.out.println(">> delete score minus "+ScoreIdx+", score: "+Score);
		}
	}

	static void cmd_change() {
		int field, changefield, check, result;
		char[] str = new char[20], changestr = new char[20];
		field = sc.nextInt();
		str = sc.next().toCharArray();
		changefield = sc.nextInt();
		changestr = sc.next().toCharArray();
		check = sc.nextInt();

		result = Change(field, str, changefield, changestr);
		if (result != check) {
			Score -= ScoreIdx;
			System.out.println("-------------------------------------------------");
			System.out.println(">> change field: "+field+", str: "+new String(str)+
					", changefield: "+changefield+", changestr: "+new String(changestr)+
					", result: "+result+", check: "+check);
			System.out.println(">> change score minus "+ScoreIdx+", score: "+Score);
		}
	}

	static void cmd_search() {
		int field, returnfield, check;
		char[] str = new char[20], checkstr = new char[20];
		field = sc.nextInt();
		str = sc.next().toCharArray();
		returnfield = sc.nextInt();
		checkstr = sc.next().toCharArray();
		check = sc.nextInt();

		RESULT result = Search(field, str, returnfield);
		if (result.count != check || 
				(result.count == 1 && 
					(new String(checkstr).compareTo(result.toString()) != 0))) {
			Score -= ScoreIdx;
			System.out.println("-------------------------------------------------");
			System.out.println(">> search field: "+field+", str: "+new String(str)+
					", returnfield: "+returnfield+", checkstr: "+new String(checkstr)+
					", result count: "+result.count+", str: "+new String(result.str)+", check: "+check);
			System.out.println(">> search score minus "+ScoreIdx+", score: "+Score);
		}
	}

	static void run() {
		int N;
		N = sc.nextInt();
		for (int i = 0; i < N; i++) {
			int cmd;
			cmd = sc.nextInt();
			switch (cmd) {
			case CMD_INIT:
				cmd_init();
				break;
			case CMD_ADD:
				cmd_add();
				break;
			case CMD_DELETE:
				cmd_delete();
				break;
			case CMD_CHANGE:
				cmd_change();
				break;
			case CMD_SEARCH:
				cmd_search();
				break;
			default:
				break;
			}
		}
	}

	static void init() {
		Score = 1000;
		ScoreIdx = 1;
	}
	
	public static void main(String[] args) throws Exception {
		System.setIn(new FileInputStream("res/hackerrank/testapi/sample_input.txt"));
		sc = new Scanner(System.in);
		
		int T;
		T = sc.nextInt();

		int TotalScore = 0;
		for (int tc = 1; tc <= T; tc++) {
			init();

			run();

			if (Score < 0)
				Score = 0;

			TotalScore += Score;
			System.out.format("#%d %d%n", tc, Score);
		}
		System.out.format("TotalScore = %d%n", TotalScore);
	}

	// -------------------------------------------------------------------------------------------
	// Write your code here :
	// --------------------------------------------------------------------
	// -------------------------------------------------------------------------------------------
	static Record[] records;
	static int idx;
	static BST[] BSTs;
	
	private static void InitDB() {
		records = new Record[50*1000];
		idx = 0;
		BSTs = new BST[5];
		for (int i = 0; i < BSTs.length; i++) {
			BSTs[i] = new BST();
		}
		return;
	}

	private static void Add(char[] name2, char[] number2, char[] birthday2, char[] email2, char[] memo2) {
		String name = new String(name2).trim();
		String number = new String(number2).trim();
		String birthday = new String(birthday2).trim();
		String email = new String(email2).trim();
		String memo = new String(memo2).trim();
		
		records[idx] = new Record(name, number, birthday, email, memo);
		//System.out.println("add["+idx+"]: "+records[idx].values[0]+"\t | "+records[idx].values[1]+"\t | "+records[idx].values[2]+"\t | "+records[idx].values[3]+"\t | "+records[idx].values[4]);
		
		BSTs[0].insert(name, idx);
		BSTs[1].insert(number, idx);
		BSTs[2].insert(birthday, idx);
		BSTs[3].insert(email, idx);
		BSTs[4].insert(memo, idx);
		
		idx++;
	}
	
	private static int Delete(int field, char[] str) {
		//System.out.println("---------------------------------------------------------------");
		//System.out.println(">> delete field: "+field+", string: "+new String(str));
		String key = new String(str);
		Node node = BSTs[field].root;
		int count = 0;
		int idx = 0;
		
		while ((node = BSTs[field].search(node, key)) != null) {
			idx = node.idx;
			BSTs[field].delete(key, idx);
			for (int j = 0; j < 5; j++) {
				if (field != j) {
					BSTs[j].delete(records[idx].values[j], idx);
				}
			}
			count++;
			node = node.left;
		}
		//System.out.println(">> result count: "+count);
		return count;
	}

	private static int Change(int field, char[] str, int changefield, char[] changestr) {
		//System.out.println("---------------------------------------------------------------");
		//System.out.println(">> change field: "+field+", string: "+new String(str)+", changefield: "+changefield+", changestr: "+new String(changestr));
		String key = new String(str);
		String changeValue = new String(changestr);
		String lastValue;
		Node node = BSTs[field].root;
		int idx = 0;
		int count = 0;
		
		while ((node = BSTs[field].search(node, key)) != null) {
			idx = node.idx;
			lastValue = records[idx].values[changefield];
			records[idx].values[changefield] = changeValue;
			
			BSTs[changefield].delete(lastValue, idx);
			BSTs[changefield].insert(changeValue, idx);
			
			count++;
			node = node.left;
		}
		//System.out.println(">> result count: "+count);
		return count;
	}

	private static RESULT Search(int field, char[] str, int returnfield) {
		//System.out.println("---------------------------------------------------------------");
		//System.out.println(">> search field: "+field+", str: "+new String(str)+", returnfield: "+returnfield);
		RESULT result = new RESULT();
		result.count = 0;
		result.str = "null".toCharArray();
		
		String key = new String(str);
		Node node = BSTs[field].root;
		int idx = 0;
		
		while ((node = BSTs[field].search(node, key)) != null) {
			result.count++;
			if (result.count == 1) idx = node.idx;
			node = node.left;
		}
		
		if (result.count == 1) {
			result.str = records[idx].values[returnfield].toCharArray();
		}
		//System.out.println(">> result idx: "+idx+", count: "+result.count+", str: "+new String(result.str));
		return result;
	}
	
	static class Record {
		String[] values;

		public Record(String name, 
				String number, 
				String birtday, 
				String email,
				String memo) {
			values = new String[5];
			values[0] = name;
			values[1] = number;
			values[2] = birtday;
			values[3] = email;
			values[4] = memo;
		}
	}
	
	static class BST {
		Node root;
		
		public BST() {
			root = null;
		}
		
		public void insert(String key, int idx) {
			root = insert(root, key, idx);
		}
		
		public Node insert(Node node, String key, int idx) {
			if (node == null) {
				node = new Node(key, idx);
				return node;
			}
			
			if (StringComparator.compare(key, node.key) < 0 ||
					StringComparator.compare(key, node.key) == 0) {
				node.left = insert(node.left, key, idx);
			}
			else if (StringComparator.compare(key, node.key) > 0) {
				node.right = insert(node.right, key, idx);
			}
			
			return node;
		}
		
		public Node search(String key) {
			return search(root, key);
		}
		
		public Node search(Node node, String key) {
			if (node == null || StringComparator.compare(key, node.key) == 0) {
				return node;
			}
			
			if (StringComparator.compare(key, node.key) < 0) {
				return search(node.left, key);
			}
			
			return search(node.right, key);
		}
		
		public void delete(String key, int idx) {
			root = delete(root, key, idx);
		}
		
		public Node delete(Node node, String key, int idx) {
			if (node == null) {
				return node;
			}
			
			if (StringComparator.compare(key, node.key) < 0) {
				node.left = delete(node.left, key, idx);
			}
			else if (StringComparator.compare(key, node.key) > 0) {
				node.right = delete(node.right, key, idx);
			}
			else {//key == node.key
				if (idx == node.idx) {
					//node with only child or no child
					if (node.left == null) {
						return node.right;
					}
					else if (node.right == null) {
						return node.left;
					}
					
					//node with two children
					Node temp = node;
					node = minNode(temp.right);
					node.right = deleteMinNode(temp.right);
					node.left = temp.left;
					/*
					node.key = minKey(node.right);
					node.right = delete(node.right, node.key);
					*/
				}
				else {
					node.left = delete(node.left, key, idx);
				}
			}
			
			return node;
		}
		
		public String minKey(Node node) {
			if (node.left == null) {
				return node.key;
			}
			
			return minKey(node.left);
		}
		
		public Node minNode(Node node) {
			if (node.left == null) {
				return node;
			}
			
			return minNode(node.left);
		}
		
		public Node deleteMinNode(Node node) {
			if (node.left == null) {
				return node.right;
			}
			
			node.left = deleteMinNode(node.left);
			return node;
		}
		
		public void print() {
			System.out.print("print --> ");
			print(root);
			System.out.println();
		}
		
		private void print(Node node) {
			if (node != null) {
				print(node.left);
				System.out.print(node.key+" ");
				print(node.right);
			}
		}
		
		static class StringComparator {
			public static int compare(String str1, String str2) {
				int comparison = 0;
				int c1, c2;

				for (int i = 0; i < str1.length() && i < str2.length(); i++) {
					c1 = str1.toLowerCase().charAt(i);
					c2 = str2.toLowerCase().charAt(i);
					comparison = c1 - c2;

					if (comparison != 0) {
						return comparison;
					}
				}

				if (str1.length() > str2.length()) {
					return 1;
				} else if (str1.length() < str2.length()) {
					return -1;
				} else {
					return comparison;
				}
			}
		}
	}
	
	static class Node {
		String key;
		int idx;
		Node left, right;
		
		public Node(String key, int idx) {
			this.key = key;
			this.idx = idx;
			left = right = null;
		}
	}
}
