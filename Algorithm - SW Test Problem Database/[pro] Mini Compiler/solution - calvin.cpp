//-- do not alter these code, you must start writing your code -------------------
//-- from line 200 ---------------------------------------------------------------

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
#include <map>
#include <math.h>
#include <stack>
#include <bitset>
#include <list>
#include <limits.h>
#include <iomanip>
#include <time.h>

using namespace std;

const int MAX_REG = 32;
const int HAF_REG = MAX_REG / 2;
const int MAX_CMD = 4096;
const int MAX_STR = MAX_CMD * 2 + 1;
const int MAX_MOV = MAX_CMD * 500;
bool IS_DEBUG = false;

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
   {
      return false;
   }
   int mov = 0;
   while (++mov < MAX_MOV && ++I < MAX_CMD)
   {
      if (I < 1) break;

      switch (M[I].c)
      {
      case 1:  // END Ri
          if (IS_DEBUG)cout << "END "<< R[M[I].i] << endl;
          // cout << "Result : " << R[M[I].i] << endl;
         if (ans == R[M[I].i])
            return true;
         return false;
      case 2:  // CJMP Ri, Rj, Rk
          if (IS_DEBUG)cout << "CJUMP " << R[M[I].i] << " " << R[M[I].j] << endl;
         if (R[M[I].i] == R[M[I].j])
         {
            I = R[M[I].k] - 1;
            if (I < 0 || MAX_CMD - 1 <= I)
            {
               return false;
            }

         }
         break;
      case 4:  // JMP Rk
          if (IS_DEBUG)cout << "JUMP " << M[I].k << " " << R[M[I].k] - 1 << endl;
         I = R[M[I].k] - 1;
         if (I < 0 || MAX_CMD - 1 <= I)
            return false;
         break;
      case 8:  // SUB Ri, Rj
          if (IS_DEBUG)cout << "SubRR " << M[I].i << " " << M[I].j << endl;
         R[M[I].i] -= R[M[I].j];
         break;
      case 16:  // ADD Ri, Rj
          if (IS_DEBUG)cout << "AddRR " << M[I].i << " " << M[I].j << endl;
         R[M[I].i] += R[M[I].j];
         break;
      case 32:  // SUB Ri, Num
          if (IS_DEBUG)cout << "SubRN " << M[I].i << " " << M[I].j << endl;
         R[M[I].i] -= M[I].j;
         break;
      case 64:  // ADD Ri, Num
          if (IS_DEBUG)cout << "AddRN " << M[I].i << " " << M[I].j << endl;
         R[M[I].i] += M[I].j;
         break;
      case 128:  // LOAD Ri, Num
          if (IS_DEBUG)cout << "LoadRN " << M[I].i << " " << M[I].j << endl;
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
   // freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);

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

// -- user code ------------------------------------------------------------------

//#define MAX_CMD 4096
//#define MAX_STR (MAX_CMD * 2 + 1)

class Token{
public:
    enum Type {Operator, Number, Register};
    enum TypeOperator {Plus, Minus, Multiplication};

    Token(Type type, int value, int addressRegister, TypeOperator typeOperator)
    {
        this->type = type;
        this->value = value;
        this->addressRegister = addressRegister;
        this->typeOperator = typeOperator;
    }

    Type type;
    int value; // Number
    int addressRegister; // Register
    TypeOperator typeOperator; // Operator
};

vector <Token> vToken;
int currentLine;

extern bool save(int cmd, int line);

void LoadRN(int r, int n, int line)
{
    save(1<<30 | r << 18 | n, line);
}

void AddRN(int r, int n, int line)
{
    save(1<<29 | r << 18 | n, line);
}

void AddRR(int r1, int r2, int line)
{
    save(1<<27 | r1 << 18 | r2 << 13, line);
}

void SubRN(int r, int n, int line)
{
    save(1<<28 | r << 18 | n, line);
}

void SubRR(int r1, int r2, int line)
{
    save(1<<26 | r1 << 18 | r2 << 13, line);
}

void Jmp(int r, int line)
{
    save(1<<25 | r << 8 , line);
}

void CJmp(int r1, int r2, int r3, int line)
{
    save(1<<24 | r1 << 18 | r2 << 13 | r3 << 8 , line);
}

void ParseStringToToken(const char* _str)
{
    string str = _str;
    vToken.clear();

    vToken.push_back( Token(Token::Type::Number, 0, 0, Token::TypeOperator::Plus) );
    vToken.push_back( Token(Token::Type::Operator, 0, 0, Token::TypeOperator::Plus) );

    int i=0, startIndex = 0;
    for (;i<str.size();i++)
    {
        if (str[i] == '+' || str[i] == '-' || str[i] == '*')
        {
            if (str[startIndex] == 'R')
            {
                vToken.push_back( Token(Token::Type::Register, 0, atoi(str.substr(startIndex+1, i-startIndex).c_str()), Token::TypeOperator::Plus) );
            }
            else
            {
                vToken.push_back( Token(Token::Type::Number, atoi(str.substr(startIndex, i-startIndex).c_str()), 0, Token::TypeOperator::Plus) );
            }

            if (str[i] == '+')vToken.push_back( Token(Token::Type::Operator, 0, 0, Token::TypeOperator::Plus) );
            else if (str[i] == '-')vToken.push_back( Token(Token::Type::Operator, 0, 0, Token::TypeOperator::Minus) );
            else vToken.push_back( Token(Token::Type::Operator, 0, 0, Token::TypeOperator::Multiplication) );

            startIndex = i+1;
        }
    }

    if (str[startIndex] == 'R')
    {
        vToken.push_back( Token(Token::Type::Register, 0, atoi(str.substr(startIndex+1, i-startIndex).c_str()), Token::TypeOperator::Plus) );
    }
    else
    {
        vToken.push_back( Token(Token::Type::Number, atoi(str.substr(startIndex, i-startIndex).c_str()), 0, Token::TypeOperator::Plus) );
    }
}

void ProcessX(int position)
{
    // Init
    LoadRN(16, 0, currentLine++);
    LoadRN(20, 0, currentLine++);
    LoadRN(17, vToken[position+1].value, currentLine++);
    LoadRN(18, 1, currentLine++);
    LoadRN(19, currentLine + 2, currentLine); currentLine++;
    LoadRN(22, currentLine + 5, currentLine); currentLine++;

    if (vToken[position-1].type==Token::Type::Register)AddRR(16, vToken[position-1].addressRegister, currentLine++);
    else AddRN(16, vToken[position-1].value, currentLine++);

    CJmp(17, 18, 22,currentLine); currentLine++;
    AddRN(18, 1,currentLine++);
    Jmp(19, currentLine++);
    AddRR(20, 16, currentLine++); // value is saved in R20
}

void ProcessAll()
{
    // Save everything in R21
    AddRN(21, vToken[0].value, currentLine++);

    for (int i=1;i<vToken.size();)
    {
        bool isThereX = false;
        if (i + 2 < vToken.size() && vToken[i+2].typeOperator ==  Token::TypeOperator::Multiplication)
        {
            isThereX = true;
            ProcessX(i+2);
        }

        if (vToken[i].typeOperator ==  Token::TypeOperator::Plus)
        {
            if (isThereX)
            {
                AddRR(21, 20, currentLine++);
                i+=4;
            }
            else
            {
                if (vToken[i+1].type == Token::Type::Number) AddRN(21, vToken[i+1].value, currentLine++);
                else AddRR(21, vToken[i+1].addressRegister, currentLine++);
                i+=2;
            }
        }
        else
        {
            if (isThereX)
            {
                SubRR(21, 20, currentLine++);
                i+=4;
            }
            else
            {
                if (vToken[i+1].type == Token::Type::Number) SubRN(21, vToken[i+1].value, currentLine++);
                else SubRR(21, vToken[i+1].addressRegister, currentLine++);
                i+=2;
            }
        }
    }
}

void run(const char* str)
{
    currentLine = 0;

    ParseStringToToken(str);

    save(1<<31, currentLine++);
    ProcessAll();
    save(1<<23 | 21 << 18, currentLine++);
}
