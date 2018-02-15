#include <iostream>
using namespace std;

int N, M;
char map[100][100]; 
int  rectMap[100][100];
int  maxRect[100][100];
bool debug = false;


int main() {
	cin >> N >> M;
	cin;

	// read the input
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			cin >> map[x][y];		
		}
		cin;
	}

	// test input
	if (debug) {
		cout << endl << "test input : " << endl;
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < M; x++) cout << map[x][y];		
			cout << endl;
		}
	}

	// create rectangle map
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			if (map[x][y] == '#') rectMap[x][y] = 0;
			else if ((y-1 < 0) || (x-1 <0)) rectMap[x][y] = 1;
			else if ((map[x-1][y] == '#') || (map[x-1][y-1] == '#') || (map[x][y-1] == '#')) rectMap[x][y] = 1;
			else {
				int smallest = rectMap[x-1][y];
				if (rectMap[x-1][y-1] < smallest) smallest = rectMap[x-1][y-1];
				if (rectMap[x][y-1] < smallest) smallest = rectMap[x][y-1];
				rectMap[x][y] = smallest+1;
			}
		}
	}

	// test rectMap
	if (debug) {
		cout << endl << "test rectMap : " << endl;
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < M; x++) cout << rectMap[x][y];		
			cout << endl;
		}
	}

	// clear maximum rectangle map
	for (int y = 0; y < N; y++)
		for (int x = 0; x < M; x++)
			maxRect[x][y] = 0;

	// flood fill maximum rectangle map
	for (int y = N-1; y >=0; y--) {
		for (int x = M-1; x >= 0; x--) {
			int rectDimen = rectMap[x][y];
			for (int b = y-rectDimen+1; b <= y; b++)
				for (int a = x-rectDimen+1; a <= x; a++)
					if (maxRect[a][b] < rectDimen) maxRect[a][b] = rectDimen;
		}
	}

	// test max rectangle map
	if (debug) {	
		cout << endl << "test maxRect : " << endl;
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < M; x++) cout << maxRect[x][y];		
			cout << endl;
		}
	}

	// find out the answer
	int maxRectAns = 100*100;
	for (int y = 0; y < N; y++)
		for (int x = 0; x < M; x++)
			if ((maxRect[x][y] != 0) && (map[x][y] != '?') && (maxRect[x][y] < maxRectAns))
				maxRectAns = maxRect[x][y];

	cout << maxRectAns;

	return 0;
}