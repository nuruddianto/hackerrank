#include <iostream>

using namespace std;

const int MAX_REG = 32;
const int HAF_REG = MAX_REG / 2;
const int MAX_CMD = 4096;
const int MAX_STR = MAX_CMD * 2 + 1;
const int MAX_MOV = MAX_CMD * 500;

extern void run(const char* str);

	// static int dummy1[...];

static int R[MAX_REG];  // Register : R0 ~ R31
static struct
{
	int c;  // cmd
	int i;  // Ri
	int j;  // Rj or Num
	int k;  // Rk
}   M[MAX_CMD];  // Memory
static int I = 0;  // Instruction Pointer

	// static int dummy2[...];

static int testcase;
static char str[MAX_STR];
static int ans;

	// static int dummy3[...];

static struct
{
	int c;  // count of cmd
	bool r;  // valid or invalid
	bool s;  // start command exist
	bool e;  // end command exist
}   rst;

	// static int dummy4[...];

bool save(int cmd, int line)
{
	if (!rst.r)
		return false;
	++rst.c;
	if (line < 0 || MAX_CMD <= line)
		return (rst.r = false);
	if (line == 0)
	{
		if (cmd != (1 << 31))
			return (rst.r = false);
		M[0].c = 0;
		return (rst.s = true);
	}
	if (0 < line  && cmd == (1 << 31))
		return (rst.r = false);
	M[line].c = cmd >> 23;
	if (M[line].c == 128 || M[line].c == 64 || M[line].c == 32)  // (LOAD, Ri, Num) or (ADD, Ri, Num) or (SUB, Ri, Num)
	{
		M[line].i = cmd >> 18 & 31;
		M[line].j = cmd & 262143;
	}
	else if (M[line].c == 16 || M[line].c == 8)  // (ADD Ri, Rj) or (SUB Ri, Rj)
	{
		if (0 < (cmd & 8191))
			return (rst.r = false);
		M[line].i = cmd >> 18 & 31;
		M[line].j = cmd >> 13 & 31;
	}
	else if (M[line].c == 4)  // JMP Rk
	{
		if (0 < (cmd  & 8380671))
			return (rst.r = false);
		M[line].k = cmd >> 8 & 31;
	}
	else if (M[line].c == 2)  // CJMP Ri, Rj, Rk
	{
		if (0 < (cmd & 255))
			return (rst.r = false);
		M[line].i = cmd >> 18 & 31;
		M[line].j = cmd >> 13 & 31;
		M[line].k = cmd >> 8 & 31;
	}
	else if (M[line].c == 1)  // END Ri
	{
		if (0 < (cmd & 262143))
			return (rst.r = false);
		M[line].i = cmd >> 18 & 31;
		rst.e = true;
	}
	else
	{
		return (rst.r = false);
	}
	return true;
}

static bool execute(void)
{
	if (!rst.r || !rst.s || !rst.e)
		return false;
	int mov = 0;
	while (++mov < MAX_MOV && ++I < MAX_CMD)
	{
		if (I < 1)
			break;
		switch (M[I].c)
		{
		case 1:  // END Ri
			if (ans == R[M[I].i])
				return true;
			return false;
		case 2:  // CJMP Ri, Rj, Rk
			if (R[M[I].i] == R[M[I].j])
			{
				I = R[M[I].k] - 1;
				if (I < 0 || MAX_CMD - 1 <= I)
					return false;
			}
			break;
		case 4:  // JMP Rk
			I = R[M[I].k] - 1;
			if (I < 0 || MAX_CMD - 1 <= I)
				return false;
			break;
		case 8:  // SUB Ri, Rj
			R[M[I].i] -= R[M[I].j];
			break;
		case 16:  // ADD Ri, Rj
			R[M[I].i] += R[M[I].j];
			break;
		case 32:  // SUB Ri, Num
			R[M[I].i] -= M[I].j;
			break;
		case 64:  // ADD Ri, Num
			R[M[I].i] += M[I].j;
			break;
		case 128:  // LOAD Ri, Num
			R[M[I].i] = M[I].j;
			break;
		}
	}
	return false;
}

static void init(void)
{
	for (int r = 0; r < HAF_REG; ++r)
		R[HAF_REG + r] = 0;  // Register : R[16] ~ R[31] = 0
	for (int c = 0; c < MAX_CMD; ++c)
		M[c].c = M[c].i = M[c].j = M[c].k = 0;  // Memory
	I = 0;  // instruction pointer initialize

	rst.c = 0;
	rst.r = true;
	rst.s = false;
	rst.e = false;
}

int main(void)
{
	freopen("sample_input.txt", "r", stdin);

	cout << "---- user output ----" << endl;
	
	int total = 0;  // total count
	cin >> testcase;
	for (int t = 1; t <= testcase; ++t)
	{
		// input
		for (int r = 0; r < HAF_REG; ++r)
			cin >> R[r];
		cin >> str >> ans;

		// initialize
		init();
		
		// implement run() function
		run(str);

		// execute
		if (!execute())
			rst.c = 1000000;
		total += rst.c;

		// print result
		cout << "#" << t << " " << rst.c << endl;
	}

	// print total count
	cout << "total : " << total << endl;

	return 0;
}













// -- solution

//#define MAX_CMD 4096
//#define MAX_STR (MAX_CMD * 2 + 1)

int ii;
int command;
char *endPtr;

extern bool save(int cmd, int line);

void goSave(int command) {
	save(command, ii);
	//cout << "save(" << command << ", " << ii << ")" << endl;
	ii++;
}

struct t_data {
	bool isRegister;
	int value;
};



t_data parseFormula(char* expr) {
	t_data result;

	endPtr = expr;
	while (endPtr[0] != '\0' && endPtr[0] != '+' && endPtr[0] != '-' && endPtr[0] != '*') endPtr++;

	if (expr[0] == 'R') {
		result.isRegister = true;
		if (expr[1] == '0') result.value = 0;
		if (expr[1] == '1') result.value = 1;
		if (expr[1] == '2') result.value = 2;
		if (expr[1] == '3') result.value = 3;
		if (expr[1] == '4') result.value = 4;
		if (expr[1] == '5') result.value = 5;
		if (expr[1] == '6') result.value = 6;
		if (expr[1] == '7') result.value = 7;
		if (expr[1] == '8') result.value = 8;
		if (expr[1] == '9') result.value = 9;
		if (expr[2] == '0') result.value = 0;
		if (expr[2] == '1') result.value = 11;
		if (expr[2] == '2') result.value = 12;
		if (expr[2] == '3') result.value = 13;
		if (expr[2] == '4') result.value = 14;
		if (expr[2] == '5') result.value = 15;
	} else {
		result.isRegister = false;
		int total = 0;
		int value = 0;
		int factor = 1;
		char *p = endPtr;
		do {
			p--;
			if (p[0] == '0') value = 0;
			if (p[0] == '1') value = 1;
			if (p[0] == '2') value = 2;
			if (p[0] == '3') value = 3;
			if (p[0] == '4') value = 4;
			if (p[0] == '5') value = 5;
			if (p[0] == '6') value = 6;
			if (p[0] == '7') value = 7;
			if (p[0] == '8') value = 8;
			if (p[0] == '9') value = 9;

			total = total + (value * factor);
			factor *= 10;
			
		} while(p != expr);

		result.value = total;
	}

	//cout << "parse formula : " << expr << " -> " << result.value << " remaining : " << endPtr << endl;
	return result;
}


t_data parseAtom(char*& expr) {
	t_data data = parseFormula(expr);
	expr = endPtr;
	return data;
}

// parse multiplication
t_data parseFactors(char*& expr) {
	t_data num1 = parseAtom(expr);
	for(;;) {
		char op = *expr;
		if (op != '/' && op != '*') return num1;
		expr++;

		t_data num2 = parseAtom(expr);

		if (op == '*') {
			//cout << "  must do : " << num1.value << " * " << num2.value << endl;
			if (num1.isRegister && num2.isRegister) {
				
			} else { 
				// load (Ri, N) always use 17 for multiplication
				command = 0;
				command += (1 << 30);
				command += (17 << 18);
				command += (0);
				goSave(command);

				for (int i = 0; i < num2.value; i++) {
					// then add Ri times num2 into register 17
					command = 0;
					command += (1 << 29);
					command += (17 << 18);
					command += (num1.value << 13);
					goSave(command);
				}

				num1.isRegister = true;
				num1.value = 17;
			}
		}
	}
}

// parse addition and subtraction
t_data parseSums(char*& expr) {
	t_data num1 = parseFactors(expr);
	for(;;) {
		char op = *expr;
		if (op != '-' && op != '+') return num1;
		expr++;

		t_data num2 = parseFactors(expr);

		if (op == '-') {
			//cout << "  must do : " << num1.value << " - " << num2.value << endl;
		}

		if (op == '+') {
			//cout << "  must do : " << num1.value << " + " << num2.value << endl;
			if (num1.isRegister && num2.isRegister) {
			
			} else {
				// num1 = register, num2 = constant
				command = 0;
				command += (1 << 29);
				command += (num1.value << 18);
				command += (num2.value << 0);
				goSave(command);
			}
		}
	}
}

t_data evaluateExpression(char* expr) {
	return parseSums(expr);
}


char formula[MAX_STR];
void run(const char* str)
{
	//char *a = "R3*5+100+R14*2";
	//cout << "coba parsing : " << a << " = " << evaluateExpression(a).value << endl;
	//cout << "coba shift : " << (1 << 0) << endl;
	//cout << "coba shift : " << (1 << 1) << endl;
	//cout << "coba shift : " << (1 << 2) << endl;
	//cout << "coba shift : " << (1 << 3) << endl;
	//cout << "coba shift : " << (1 << 4) << endl;
	t_data result;

	ii = 0;
	goSave(1 << 30);

	int i = 0;
	do {
		formula[i] = str[i];
		i++;
	} while (str[i] != '\0');
	formula[i] = '\0';
	result = evaluateExpression(formula);
	
	command = 0;
	command += (1 << 23);
	command += (result.value << 18);
}
