package code.srin;

import java.util.Scanner;

import sun.security.acl.WorldGroupImpl;

public class AlienLanguage {
	private final static int MAX_PHONE_SIZE     = 32;
	private final static int MAX_WORD_SIZE      = 20000;
	
	private final static int WORD_LENGTH        = 6;
	
	private final static int CUTLINE            = 90;       // the value of cutline would not be changed in evaluation.
	                                                        // only execution time will be taken into account between test takers
	                                                        // who received the same score.
	
	private static int totalquery;
	private static int correctword;
	private static int M;	
	// phone size
	private static int N;									// word size
	
	private final static char phone[] = new char[MAX_PHONE_SIZE];
	private final static char word[][] = new char[MAX_WORD_SIZE][WORD_LENGTH];
	
	private final static UserSolution usersolution = new UserSolution();
	
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
		static byte[] mPhone;
		static byte[][] mWordByte;
		static char[][] mWord;
		static int totalWord;
		static int totalPhone;
		static TrieNode root;
		
		static class TrieNode{
			TrieNode[] child = new TrieNode[256];
			boolean isEndOfWord;
		}
		
		static void insertTrie(char[] key){
			int index;
			int length = key.length;
			TrieNode tmp = root;
			
			for(int i = 0; i < length; i++){
				index = key[i] - '\0';
				if(tmp.child[index] == null){
					tmp.child[index] = new TrieNode();
				}
				tmp = tmp.child[index];
			}
			
			tmp.isEndOfWord = true;
		} 
		
		
		static boolean search(char[] k){
			int length = k.length;
			int index;
			TrieNode tmp = root;
			
			for(int i =0; i < length; i++){
				index = k[i] - '\0';
				if(tmp.child[index] == null){
					return false;
				}
				tmp = tmp.child[index];
			}
			
			return tmp.isEndOfWord;
		}
		
		public void learnphone(int M, char phone[]) {
			totalPhone = M;
			mPhone = new byte[phone.length];
			for(int i =0; i < phone.length; i++){
				mPhone[i] = (byte)phone[i];
			}
		}

		public void learnword(int N, char word[][]) {
			totalWord = N;
			mWord = word;
			mWordByte = new byte[N][WORD_LENGTH];
			for(int i = 0; i < N; i++){
				for(int j = 0; j < WORD_LENGTH; j++){
					mWordByte[i][j] = (byte)word[i][j];
				}
			}
		
		}

		public void recognize(char in[], char out[]) {
			byte[] inByte = new byte[in.length];
			for(int l = 0; l < 6; l++){
				inByte[l] = (byte)in[l];
			}
			int length = 0;
			int indexWord = -1;
			for(int i = 0; i < totalWord; i++){
				for(int j =0; j < WORD_LENGTH;j++){
					
					int xor = abs(inByte[j] ^ mWordByte[i][j]);
					if( isPowerOfTwo(xor) || xor == 0){
						length++;
					}else{
						j = 6;
						length = 0;
					}	
					
					if(length == 6){
						indexWord = i;
						break;
					}
					
				}
			}
			
			for(int k = 0; k < 6; k++){
				out[k] = mWord[indexWord][k]; 
			}
			
		}
		
		static boolean isPowerOfTwo(int x){
			return (x != 0) && ((x & (x-1)) == 0);
		}
		
		int abs(int x){
			return x > 0 ? x : x *-1;
		}
	}
	
}




