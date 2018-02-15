//---------------------------------- BRUTE FORCE SOLUTION
#include <iostream>
using namespace std;

int T, N;
int map[5][12];
int bombedMap[5][12];
int globalGold, recursiveGold;

void bombAt(int position);
void recursiveFlight(int x, int y, int gold);

int main() {
	cin >> T;
	for (int testCase = 1; testCase <= T; testCase++) {
		cin >> N;

		// read the map donwside-up
		for (int y = N-1; y >= 0; y--)
			for (int x = 0; x < 5; x++)
				cin >> map[x][y];

		//// test the map
		//cout << "\ntesting map\n";
		//for (int y = 0; y < N; y++) {
		//	for (int x = 0; x < 5; x++) cout << map[x][y] << " ";
		//	cout << endl;
		//}

		// do stategic bombing, before doing recursive
		globalGold = -100;
		for (int i = 0; i <= N-5; i++) {
			recursiveGold = -100;
			bombAt(i);

			// bombing successfull, use bombed map to recursively find max gold
			recursiveFlight(1, 0, 0); 
			recursiveFlight(2, 0, 0);
			recursiveFlight(3, 0, 0);

			// process the result from recursive action
			if (globalGold < recursiveGold) globalGold = recursiveGold;
		}

		// print answer
		cout << "#" << testCase << " " << globalGold << endl;
	}


	return 0;
}

void bombAt(int position) {
	// copy the map
	for (int y = N-1; y >= 0; y--)
		for (int x = 0; x < 5; x++)
			bombedMap[x][y] = map[x][y];

	// bomb the copy map
	for (int i = 0; i < 5; i++)
		for (int x = 0; x < 5; x++)
			if (bombedMap[x][position + i] == 2) 
				bombedMap[x][position + i] = 0;
}

// remember recursive flight works using copy(bombed)map!
void recursiveFlight(int x, int y, int gold) {
	if ((x < 0) || (x >=5 )) return; // out of map bound (left & right)
	if ((y >= N) || (gold == -1)) {  // is reaching the edge, or is dead!
		if (gold > recursiveGold) recursiveGold = gold;
		return;
	}

	// else continue the recursion
	if (bombedMap[x][y] == 1) gold++; // if cell is gold
	if (bombedMap[x][y] == 2) gold--; // if cell is enemy
	recursiveFlight(x-1, y+1, gold); // try next left path
	recursiveFlight(x  , y+1, gold); // try next straight path
	recursiveFlight(x+1, y+1, gold); // try next right path
}