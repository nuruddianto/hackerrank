package code.srin;

import java.util.Scanner;

class AlienLanguageTrie {	
	private final static int MAX_PHONE_SIZE     = 32;
	private final static int MAX_WORD_SIZE      = 20000;
	
	private final static int WORD_LENGTH        = 6;
	
	private final static int CUTLINE            = 90;       // the value of cutline would not be changed in evaluation.
	                                                        // only execution time will be taken into account between test takers
	                                                        // who received the same score.
	
	private static int totalquery;
	private static int correctword;
	private static int M;									// phone size
	private static int N;									// word size
	
	private final static char phone[] = new char[MAX_PHONE_SIZE];
	private final static char word[][] = new char[MAX_WORD_SIZE][WORD_LENGTH];
	
	private static UserSolution usersolution = new UserSolution();
	
	private static int seed;
	
	static {
		for (int idx = 0; idx < MAX_WORD_SIZE; ++idx)
			word[idx] = new char[WORD_LENGTH];
	}
	
	private static int pseudo_rand() {
		seed = seed * 214013 + 2531011;
		return (seed >> 16) & 0x7fff;
	}
	
	private static void makephone() {
		int idx1, idx2;
		
		idx1 = 0;
		while(idx1 < M) {
			phone[idx1] = (char)(pseudo_rand() % 256);
			idx2 = 0;
			while(idx2 < idx1) {
				if (phone[idx1] == phone[idx2])
					break;
				++idx2;
			}
			if (idx1 == idx2) ++idx1;
		}
	}
	
	private static void makeword() {
		for (int idx1 = 0; idx1 < N; ++idx1)
			for (int idx2 = 0; idx2 < WORD_LENGTH; ++idx2)
				word[idx1][idx2] = phone[pseudo_rand() % M];
	}
	
	private static boolean issame(char in[], char out[]) {
		for (int idx = 0; idx < WORD_LENGTH; ++idx)
			if (in[idx] != out[idx])
				return false;
		return true;
	}

	private static void run(Scanner sc) {
		char in[] = new char[WORD_LENGTH];
		char out[] = new char[WORD_LENGTH];
		
		char t_phone[] = new char[MAX_PHONE_SIZE];
		char t_word[][] = new char[MAX_WORD_SIZE][WORD_LENGTH];

		M = sc.nextInt();
		N = sc.nextInt();
		totalquery = sc.nextInt();
		seed = sc.nextInt();
		
		makephone();
		
		for (int idx = 0; idx < M; ++idx)
			t_phone[idx] = phone[idx];

		usersolution.learnphone(M, t_phone);
		
		makeword();
		
		for (int idx1 = 0; idx1 < N; ++idx1) {
			t_word[idx1] = new char[WORD_LENGTH];
			for (int idx2 = 0; idx2 < WORD_LENGTH; ++idx2)
				t_word[idx1][idx2] = word[idx1][idx2];
		}
		
		usersolution.learnword(N, t_word);
		
		correctword = 0;
		for (int cnt = 0; cnt < totalquery; ++cnt) {
			int selected = pseudo_rand() % N;
			
			for (int idx1 = 0; idx1 < WORD_LENGTH; ++idx1) {
				in[idx1] = word[selected][idx1];
				boolean addnoise = pseudo_rand() % 2 == 1;
				if (addnoise)
					in[idx1] ^= 1 << (pseudo_rand() % 8); // add noise
			}
			
			usersolution.recognize(in, out);
			
			if (issame(word[selected], out))
				++correctword;
		}
		
	}
	
	public static void main(String[] args) throws Exception {
		int TC, totalscore;
	
		//System.setIn(new java.io.FileInputStream("sample_input.txt"));
		Scanner sc = new Scanner(System.in);
		TC = sc.nextInt();
		long startTime = System.currentTimeMillis();
        totalscore = 0;
		for (int testcase = 1; testcase <= TC; ++testcase) {
            run(sc);
            
            int correctwordratio = correctword * 100 / totalquery;
            int score = correctwordratio >= CUTLINE ? 100 : 0;
            totalscore += score;
            
            System.out.println("#" + testcase + " " + score);
		}
		long endTime = System.currentTimeMillis();
        System.out.println("total score = " + totalscore / TC);
        
        System.out.println(endTime - startTime);
		sc.close();
	}
	
	static class UserSolution {
		private final static int MAX_PHONE_SIZE     = 32;
		private final static int MAX_WORD_SIZE      = 20000;

		private final static int WORD_LENGTH        = 6;
		
		class TrieNode{
			int indexWord;
			TrieNode[] child = new TrieNode[257];
			boolean isEndOfWord;
		}
		
		TrieNode root;
		char[][] mWordMap;
		boolean[] mWordVisited;
		int wordIndex;
		
		
		void insert(char[] key, int indexWord){
			TrieNode tmp = root;
			int dec = 0;
			for(int i =0; i < WORD_LENGTH; i++){
				dec = (int) key[i];
				if(tmp.child[dec] == null ){
					tmp.child[dec] = new TrieNode();
					tmp.indexWord = indexWord;
				}
				tmp = tmp.child[dec];
			}
			tmp.isEndOfWord = true;
		}
		
		void search(TrieNode current, char[] word, int indexChar){
			if(current == null){
				return;
			}
			
			if(indexChar >= WORD_LENGTH - 1){
				wordIndex = current.indexWord;
				return;
			}
			
			int dec = (int) word[indexChar]; 
			
			if (current.child[dec] == null) {
				for(int i =0; i < 8; i++){
					int bitShift = bitShift(i, dec);
					
					if(current.child[bitShift] != null){
						search(current.child[bitShift], word, indexChar + 1);
					}
					
				}
			}
			search(current.child[dec], word, indexChar + 1);
		}
		
		boolean isWordValid(int i, int j){
			int xorVal = i ^ j;
			return xorVal == 0 || (xorVal & (xorVal - 1)) == 0;
		}
		
		
		int bitShift(int shift, int value){
			int shiftVal = 1 << shift;
			return value ^ shiftVal;
		}
		
		
		public void learnphone(int M, char phone[]) {
			mWordMap = null;
			wordIndex = -1;
			root = new TrieNode();
		}

		public void learnword(int N, char word[][]) {
			mWordMap = word;
			mWordVisited = new boolean[256];
			for(int i = 0; i < N; i++){
				insert(word[i], i);
			}
		}

		public void recognize(char in[], char out[]) {
			search(root, in, 0);
			for(int i =0; i < 6; i++){
				out[i] = mWordMap[wordIndex][i];
			}
		}
	}

}


