//#include <iostream>
//
//using namespace std;
//
//const int MAX_REG = 32;
//const int HAF_REG = MAX_REG / 2;
//const int MAX_CMD = 4096;
//const int MAX_STR = MAX_CMD * 2 + 1;
//const int MAX_MOV = MAX_CMD * 500;
//
//extern void run(const char* str);
//
//	// static int dummy1[...];
//
//static int R[MAX_REG];  // Register : R0 ~ R31
//static struct
//{
//	int c;  // cmd
//	int i;  // Ri
//	int j;  // Rj or Num
//	int k;  // Rk
//}   M[MAX_CMD];  // Memory
//static int I = 0;  // Instruction Pointer
//
//	// static int dummy2[...];
//
//static int testcase;
//static char str[MAX_STR];
//static int ans;
//
//	// static int dummy3[...];
//
//static struct
//{
//	int c;  // count of cmd
//	bool r;  // valid or invalid
//	bool s;  // start command exist
//	bool e;  // end command exist
//}   rst;
//
//	// static int dummy4[...];
//
//bool save(int cmd, int line)
//{
//	if (!rst.r)
//		return false;
//	++rst.c;
//	if (line < 0 || MAX_CMD <= line)
//		return (rst.r = false);
//	if (line == 0)
//	{
//		if (cmd != (1 << 31))
//			return (rst.r = false);
//		M[0].c = 0;
//		return (rst.s = true);
//	}
//	if (0 < line  && cmd == (1 << 31))
//		return (rst.r = false);
//	M[line].c = cmd >> 23;
//	if (M[line].c == 128 || M[line].c == 64 || M[line].c == 32)  // (LOAD, Ri, Num) or (ADD, Ri, Num) or (SUB, Ri, Num)
//	{
//		M[line].i = cmd >> 18 & 31;
//		M[line].j = cmd & 262143;
//	}
//	else if (M[line].c == 16 || M[line].c == 8)  // (ADD Ri, Rj) or (SUB Ri, Rj)
//	{
//		if (0 < (cmd & 8191))
//			return (rst.r = false);
//		M[line].i = cmd >> 18 & 31;
//		M[line].j = cmd >> 13 & 31;
//	}
//	else if (M[line].c == 4)  // JMP Rk
//	{
//		if (0 < (cmd  & 8380671))
//			return (rst.r = false);
//		M[line].k = cmd >> 8 & 31;
//	}
//	else if (M[line].c == 2)  // CJMP Ri, Rj, Rk
//	{
//		if (0 < (cmd & 255))
//			return (rst.r = false);
//		M[line].i = cmd >> 18 & 31;
//		M[line].j = cmd >> 13 & 31;
//		M[line].k = cmd >> 8 & 31;
//	}
//	else if (M[line].c == 1)  // END Ri
//	{
//		if (0 < (cmd & 262143))
//			return (rst.r = false);
//		M[line].i = cmd >> 18 & 31;
//		rst.e = true;
//	}
//	else
//	{
//		return (rst.r = false);
//	}
//	return true;
//}
//
//static bool execute(void)
//{
//	if (!rst.r || !rst.s || !rst.e)
//		return false;
//	int mov = 0;
//	while (++mov < MAX_MOV && ++I < MAX_CMD)
//	{
//		if (I < 1)
//			break;
//		switch (M[I].c)
//		{
//		case 1:  // END Ri
//			if (ans == R[M[I].i])
//				return true;
//			return false;
//		case 2:  // CJMP Ri, Rj, Rk
//			if (R[M[I].i] == R[M[I].j])
//			{
//				I = R[M[I].k] - 1;
//				if (I < 0 || MAX_CMD - 1 <= I)
//					return false;
//			}
//			break;
//		case 4:  // JMP Rk
//			I = R[M[I].k] - 1;
//			if (I < 0 || MAX_CMD - 1 <= I)
//				return false;
//			break;
//		case 8:  // SUB Ri, Rj
//			R[M[I].i] -= R[M[I].j];
//			break;
//		case 16:  // ADD Ri, Rj
//			R[M[I].i] += R[M[I].j];
//			break;
//		case 32:  // SUB Ri, Num
//			R[M[I].i] -= M[I].j;
//			break;
//		case 64:  // ADD Ri, Num
//			R[M[I].i] += M[I].j;
//			break;
//		case 128:  // LOAD Ri, Num
//			R[M[I].i] = M[I].j;
//			break;
//		}
//	}
//	return false;
//}
//
//static void init(void)
//{
//	for (int r = 0; r < HAF_REG; ++r)
//		R[HAF_REG + r] = 0;  // Register : R[16] ~ R[31] = 0
//	for (int c = 0; c < MAX_CMD; ++c)
//		M[c].c = M[c].i = M[c].j = M[c].k = 0;  // Memory
//	I = 0;  // instruction pointer initialize
//
//	rst.c = 0;
//	rst.r = true;
//	rst.s = false;
//	rst.e = false;
//}
//
//int main(void)
//{
//	// freopen("sample_input.txt", "r", stdin);
//
//	cout << "---- user output ----" << endl;
//	
//	int total = 0;  // total count
//	cin >> testcase;
//	for (int t = 1; t <= testcase; ++t)
//	{
//		// input
//		for (int r = 0; r < HAF_REG; ++r)
//			cin >> R[r];
//		cin >> str >> ans;
//
//		// initialize
//		init();
//		
//		// implement run() function
//		run(str);
//
//		// execute
//		if (!execute())
//			rst.c = 1000000;
//		total += rst.c;
//
//		// print result
//		cout << "#" << t << " " << rst.c << endl;
//	}
//
//	// print total count
//	cout << "total : " << total << endl;
//
//	return 0;
//}
//
//// -- user code
//
//#define MAX_CMD 4096
//#define MAX_STR (MAX_CMD * 2 + 1)
//
//extern bool save(int cmd, int line);
//
//void run(const char* str)
//{
//    // TO DO
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//// -- java
//
//import java.util.Scanner;
//
//interface Constants {
//	public static final int MAX_REG = 32;
//	public static final int HAF_REG = MAX_REG / 2;
//	public static final int MAX_CMD = 4096;
//	public static final int MAX_STR = MAX_CMD * 2;
//	public static final int MAX_MOV = MAX_CMD * 500;
//}
//
//class Core {
//	class Memory {
//		public int c;  // cmd
//		public int i;  // Ri
//		public int j;  // Rj or Num
//		public int k;  // Rk
//		
//		Memory() {
//			c = i = j = k = 0;
//		}
//	}
//
//	private int[] R;  // Register
//	private Memory[] M;  // Memory
//	private int I;  // Instruction Pointer
//	
//	class Result {
//		public int c;  // count of command
//		public boolean r;  // valid or invalid
//		public boolean s;  // start command exist
//		public boolean e;  // end command exist
//		
//		Result() {
//			c = 0;
//			r = true;
//			s = false;
//			e = false;
//		}
//	}
//	
//	private Result rst;
//	
//	Core(int[] reg) {
//		R = new int[Constants.MAX_REG];
//		for (int r = 0; r < Constants.HAF_REG; ++r) {
//			R[r] = reg[r];
//			R[Constants.HAF_REG + r] = 0;
//		}
//		M = new Memory[Constants.MAX_CMD];
//		for (int c = 0; c < Constants.MAX_CMD; ++c)
//			M[c] = new Memory();
//		I = 0;
//		rst = new Result();
//	}
//
//	public boolean save(int cmd, int line) {
//		if (!rst.r)
//			return false;
//		++rst.c;
//		if (line < 0 || Constants.MAX_CMD <= line)
//			return (rst.r = false);
//		if (line == 0) {
//			if (cmd != -2147483648)
//				return (rst.r = false);
//			M[0].c = 0;
//			return (rst.s = true);
//		}
//		if (0 < line  && cmd == -2147483648)
//			return (rst.r = false);
//		M[line].c = cmd >> 23;
//		if (M[line].c == 128 || M[line].c == 64 || M[line].c == 32) {  // (LOAD, Ri, Num) or (ADD, Ri, Num) or (SUB, Ri, Num)
//			M[line].i = cmd >> 18 & 31;
//			M[line].j = cmd & 262143;
//		} else if (M[line].c == 16 || M[line].c == 8) {  // (ADD Ri, Rj) or (SUB Ri, Rj)
//			if (0 < (cmd & 8191))
//				return (rst.r = false);
//			M[line].i = cmd >> 18 & 31;
//			M[line].j = cmd >> 13 & 31;
//		} else if (M[line].c == 4) {  // JMP Rk
//			if (0 < (cmd  & 8380671))
//				return (rst.r = false);
//			M[line].k = cmd >> 8 & 31;
//		} else if (M[line].c == 2) {  // CJMP Ri, Rj, Rk
//			if (0 < (cmd & 255))
//				return (rst.r = false);
//			M[line].i = cmd >> 18 & 31;
//			M[line].j = cmd >> 13 & 31;
//			M[line].k = cmd >> 8 & 31;
//		} else if (M[line].c == 1) {  // END Ri
//			if (0 < (cmd & 262143))
//				return (rst.r = false);
//			M[line].i = cmd >> 18 & 31;
//			rst.e = true;
//		} else {
//			return (rst.r = false);
//		}
//		return true;
//	}
//	
//	public int execute(int ans) {
//		if (!rst.r || !rst.s || !rst.e)
//			return 1000000;
//		int mov = 0;
//		while (++mov < Constants.MAX_MOV && ++I < Constants.MAX_CMD)
//		{
//			if (I < 1)
//				break;
//			switch (M[I].c)
//			{
//			case 1:  // END Ri
//				if (ans == R[M[I].i])
//					return rst.c;
//				return 1000000;
//			case 2:  // CJMP Ri, Rj, Rk
//				if (R[M[I].i] == R[M[I].j])
//				{
//					I = R[M[I].k] - 1;
//					if (I < 0 || Constants.MAX_CMD - 1 <= I)
//						return 1000000;
//				}
//				break;
//			case 4:  // JMP Rk
//				I = R[M[I].k] - 1;
//				if (I < 0 || Constants.MAX_CMD - 1 <= I)
//					return 1000000;
//				break;
//			case 8:  // SUB Ri, Rj
//				R[M[I].i] -= R[M[I].j];
//				break;
//			case 16:  // ADD Ri, Rj
//				R[M[I].i] += R[M[I].j];
//				break;
//			case 32:  // SUB Ri, Num
//				R[M[I].i] -= M[I].j;
//				break;
//			case 64:  // ADD Ri, Num
//				R[M[I].i] += M[I].j;
//				break;
//			case 128:  // LOAD Ri, Num
//				R[M[I].i] = M[I].j;
//				break;
//			}
//		}
//		return 1000000;
//	}
//}
//
//class Cpu {
//	private Core core;
//	
//	Cpu(Core c) {
//		core = c;
//	}
//	
//	public boolean save(int cmd, int line) {
//		return core.save(cmd, line);
//	}
//}
//
//class Solution {
//	public static void main(String arg[]) throws Exception {
//		//System.setIn(new java.io.FileInputStream("sample_input.txt"));
//		Scanner sc = new Scanner(System.in);
//		
//		System.out.println("---- user output ----");
//		
//		int total = 0;
//		int testcase = sc.nextInt();
//		for (int t = 1; t <= testcase; ++t)
//		{
//			// input
//			int[] reg = new int[Constants.HAF_REG];
//			for (int r = 0; r < Constants.HAF_REG; ++r)
//				reg[r] = sc.nextInt();
//			String str = sc.next();
//			int ans = sc.nextInt();
//
//			// ...
//			Core core = new Core(reg);
//			Cpu cpu = new Cpu(core);
//			UserSolution user = new UserSolution(cpu);
//			
//			// implement run() function
//			user.run(str);
//			
//			// execute
//			int count = core.execute(ans);
//			total += count;
//			
//			// print result
//			System.out.println("#" + t + " " + count);
//		}
//		
//		// print total score
//		System.out.println("total : " + total);
//	}
//}
//
//
//// -- user code java
//
//public class UserSolution {
//	private Cpu cpu;
//	
//	UserSolution(Cpu c) {
//		cpu = c;
//	}
//
//    public void run(String str) {
//		// TO DO
//    }    
//}
