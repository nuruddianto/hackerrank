import java.util.Scanner;

class Solution {	
	private static Scanner sc;

	private final static int MAX_N = 5000;
	private final static int MAX_M = 5;	
	private final static int MAX_R = 500;
	
	public static class INFO
	{
		public char first[];
		public char second[];
		public char third[];
		public char fourth[];
		public char fifth[];
		INFO() {
			first  = new char[11];
			second = new char[11];
			third  = new char[11];
			fourth = new char[11];
			fifth  = new char[11];
		}
		public String toString() {
			// TODO Auto-generated method stub
			StringBuilder sb = new StringBuilder();
			sb.append(first).append('\t');
			sb.append(second).append('\t');
			sb.append(third).append('\t');
			sb.append(fourth).append('\t');
			sb.append(fifth).append('\t');
			return sb.toString();
		}
	}
	
	private static int N;
	private static int K;
	private static int Weight;

	private static int R[] = new int[MAX_M];
	private static int Compound[][] = new int[MAX_N * 2][MAX_M];
	private static char Str[][][] = new char[MAX_M][MAX_R][11];
	
	private static INFO Info = new INFO();
	
	private static UserSolution usersolution = new UserSolution();
	
	static {
		for (int i = 0; i < MAX_N * 2; ++i)
			Compound[i] = new int[MAX_M];
		
		for (int i = 0; i < MAX_M; ++i)
			for (int k = 0; k < MAX_R; ++k)
				Str[i][k] = new char[11];
	}
	
	public static int calc_correlation(char str1[], char str2[])
	{
		int sum = 0;
		if (mstrcmp(str1, str2) == 0) return 100;
		else {
			for (int i = 0; i < 10; ++i) {
				if (str1[i] == 0 || str2[i] == 0) break;
				if (str1[i] > str2[i])
					sum += ((26 - (str1[i] - str2[i])) * Weight);
				else
					sum += ((26 - (str2[i] - str1[i])) * Weight);
			}
		}
		sum /= 100;
		if (sum > 99) sum = 99;
		return sum;
	}
	
	private static int seed;
	private static int pseudo_rand()
	{
		seed = seed * 214013 + 2531011;
		return (seed >> 16) & 0x7fff;
	}
	
	private static void mstrcpy(char dst[], char src[])
	{
		int c = 0;
		while ((dst[c] = src[c]) != 0) ++c;
	}
	
	private static int mstrcmp(char str1[], char str2[])
	{
		int c = 0;
		while (str1[c] != 0 && str1[c] == str2[c]) ++c;
		return str1[c] - str2[c];
	}
	
	private static void make_compound()
	{
		for (int i = 0; i < MAX_M; ++i) {
			for (int k = 0; k < R[i]; ++k) {
				int length = pseudo_rand() % 6 + 5;
				for (int m = 0; m < length; ++m) {
					Str[i][k][m] = (char)('a' + pseudo_rand() % 26);
				}
				Str[i][k][length] = 0;
			}
		}

		for (int i = 0; i < (N + K); ++i) {
			for (int k = 0; k < MAX_M; ++k) {
				Compound[i][k] = pseudo_rand() % R[k];
			}
		}
	}

	private static int run()
	{
		nanoInit	=-System.nanoTime() *1e-6;

		int score = 100;

		N = sc.nextInt();
		K = sc.nextInt();
		seed = sc.nextInt();
		Weight = sc.nextInt();
		
		for (int i = 0; i < 5; ++i)
			R[i] = sc.nextInt();

		make_compound();

		usersolution.init();

		for (int i = 0; i < N; ++i) {
			mstrcpy(Info.first, Str[0][Compound[i][0]]);
			mstrcpy(Info.second, Str[1][Compound[i][1]]);
			mstrcpy(Info.third, Str[2][Compound[i][2]]);
			mstrcpy(Info.fourth, Str[3][Compound[i][3]]);
			mstrcpy(Info.fifth, Str[4][Compound[i][4]]);
			usersolution.addDB(Info);
		}
		nanoAction	=-System.nanoTime() *1e-6;

		for (int i = N; i < (N + K); ++i) {
			int answer = sc.nextInt();

			mstrcpy(Info.first, Str[0][Compound[i][0]]);
			mstrcpy(Info.second, Str[1][Compound[i][1]]);
			mstrcpy(Info.third, Str[2][Compound[i][2]]);
			mstrcpy(Info.fourth, Str[3][Compound[i][3]]);
			mstrcpy(Info.fifth, Str[4][Compound[i][4]]);

			int result = usersolution.newCompound(Info);
			if (result != answer)
				score = 0;
		}
		nanoInit	+=-nanoAction;
		nanoAction	+=System.nanoTime() *1e-6;
		
		return score;
	}
	static double nanoInit = 0; 		// DEBUGGER
	static double nanoAction = 0;		// DEBUGGER

	public static void main(String[] args) throws Exception {
//		try{
//			FileInputStream fis = new FileInputStream("C:\\Users\\SRIN\\Desktop\\temp\\UtilityClasses\\src\\MyOptLinkedListHashMapWithDuplicateKey.java");
//			int content;
//			while((content = fis.read()) != -1){
//				System.out.print((char)content);
//			}
//			fis.close();
//		}catch(Exception ex){ex.printStackTrace();}
	
		System.setIn(new java.io.FileInputStream("sample_input.txt"));
		sc = new Scanner(System.in);

		int TC = sc.nextInt();
		long start = System.currentTimeMillis();
		for (int testcase = 1; testcase <= TC; ++testcase) {
            System.out.println("#" + testcase + " " + run()
            		+ "\t" + nanoAction
            		+ "\t" + -nanoInit
            		);
		}
		System.out.println(System.currentTimeMillis() - start);
		
		sc.close();
	}
}