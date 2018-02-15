#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS    // Ignore build errors when using unsafe functions in Visual Studio.
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
using namespace std;

#define CMD_MOVECURSOR (0)
#define CMD_REVERT (1)
#define CMD_INPUT (2)
#define CMD_GETSUBSTRING (9)

int N;
static int score, curScore;

extern void init();
extern void cmd_input(char ch[]);
extern void cmd_revert();
extern void cmd_movecursor(int mCursor);
extern void get_substring(int mPosition, int mLength, char res[]);


void make_input()
{
	char ch[30];

	scanf("%s", ch);

	cmd_input(ch);
}

static void run() {

	char ori[35], res[35];
	scanf("%d", &N);

	init();

	for (int i = 0; i < N; i++) {
		int cmd;

		scanf("%d", &cmd);

		if (cmd == CMD_INPUT)
		{
			make_input();
		}
		else if (cmd == CMD_REVERT)
		{
			cmd_revert();
		}
		else if (cmd == CMD_MOVECURSOR)
		{
			int pos;

			scanf("%d", &pos);

			cmd_movecursor(pos);
		}
		else if (cmd == CMD_GETSUBSTRING)
		{
			int pos, len;

			scanf("%d%d%s", &pos, &len, ori);

			get_substring(pos, len, res);
			if (strcmp(ori, res) != 0)
			{
				curScore = 0;
			}
		}
	}
}

int main() {
	setbuf(stdout, NULL);
	freopen("sample_input.txt", "r", stdin);

	int T;
	scanf("%d", &T);
	score = 0;

	for (int test_case = 1; test_case <= T; test_case++) {
		curScore = 100;
		run();

		printf("#%d %d\n", test_case, curScore);
		score += curScore;

	}

	printf("Total Score = %d\n", score/T);
	return 0;
}


	// my answer
	bool debug = true;
	struct t_buffer {
		char string[1500000];
		int length;
		int lastCurPos;
		int curPos;
	};
	t_buffer buffer[2];
	int primaryStr, secondaryStr;

	void switchBuffer() {
		if (primaryStr == 0) {
			primaryStr = 1;
			secondaryStr = 0;		
		} else {
			primaryStr = 0;
			secondaryStr = 1;		
		}
	}

void init()
{
	//// debug : dumping previous string
	//cout << "stringnya : " << endl << buffer[primaryStr].string << endl;
	//cout << "lengthnya : " << buffer[primaryStr].length << endl;

	primaryStr = 0;
	secondaryStr = 1;

	for (int i = 0; i <2; i++) {
		buffer[i].curPos = 0;
		buffer[i].lastCurPos = 0;
		buffer[i].length = 0;
		buffer[i].string[0] = '\0';
	}
}

void cmd_input(char ch[])
{
	if (buffer[primaryStr].curPos != buffer[primaryStr].lastCurPos) { // somebody move the cursor!
		// do the backup procedure
		for (int i = 0; i <= (buffer[primaryStr].length); i++)
			buffer[secondaryStr].string[i] = buffer[primaryStr].string[i];
		buffer[secondaryStr].curPos = buffer[primaryStr].curPos;
		buffer[secondaryStr].lastCurPos = buffer[primaryStr].lastCurPos;
		buffer[secondaryStr].length = buffer[primaryStr].length;

		if (debug) printf("doing backup at [%s]\n", ch);
	}

	

	// do the input (at the end or insert in the middle)
	if (buffer[primaryStr].curPos == buffer[primaryStr].length) { // cursor is in the end of string
		int chLength = 0;
		while (ch[chLength] != '\0') {
			buffer[primaryStr].string[buffer[primaryStr].curPos] = ch[chLength];
			buffer[primaryStr].curPos++;
			chLength++;
		}
		buffer[primaryStr].string[buffer[primaryStr].curPos] = '\0';
		buffer[primaryStr].length += chLength;
		buffer[primaryStr].lastCurPos = buffer[primaryStr].curPos;

		if (debug) printf("add [%s] -> %s | (%d,%d)\n", ch, buffer[primaryStr].string,  buffer[primaryStr].curPos, buffer[primaryStr].length);
	} else { // cursor is not in the end of string (insert at middle)
		int chLength = 0;
		while (ch[chLength] != '\0') chLength++;

		for (int i = buffer[primaryStr].length + chLength; i >= buffer[primaryStr].curPos + chLength; i--)
			buffer[primaryStr].string[i] = buffer[primaryStr].string[i - chLength];
			
		for (int i = buffer[primaryStr].curPos; i < buffer[primaryStr].curPos + chLength; i++)
			buffer[primaryStr].string[i] = ch[i-buffer[primaryStr].curPos];

		buffer[primaryStr].length += chLength;
		buffer[primaryStr].curPos += chLength;

		if (debug) printf("ins [%s] -> %s | (%d,%d)\n", ch, buffer[primaryStr].string,  buffer[primaryStr].curPos, buffer[primaryStr].length);
	}

	buffer[primaryStr].lastCurPos = buffer[primaryStr].curPos;
}

void cmd_revert()
{
	switchBuffer();

	if (debug) printf("reverted : [%s]\n", buffer[primaryStr].string);
}

void cmd_movecursor(int mCursor)
{
	buffer[primaryStr].curPos = mCursor;
	if (buffer[primaryStr].curPos > buffer[primaryStr].length) buffer[primaryStr].curPos = buffer[primaryStr].length;
}

void get_substring(int mPosition, int mLength, char res[])
{
	res[0] = '\0';
	int pos = 0;
	do {
		res[pos] = buffer[primaryStr].string[mPosition + pos];
		pos++;
	} while ((buffer[primaryStr].string[mPosition + pos] != '\0') && (pos < mLength) && (mPosition + pos <=  buffer[primaryStr].length));
	res[pos] = '\0';

	if (debug) printf("current str : [%s]\n", buffer[primaryStr].string);
	if (debug) printf("getting mPos: %d len: %d [%s]\n", mPosition, mLength, res);
}