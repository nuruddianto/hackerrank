// S6TradeIn
// Samsung SW Test - Advanced, 20 Jan 2016

#include <iostream>
using namespace std;

const int maxN = 105;
const int maxTestCases = 51;
const int maxType = 5+3;
const int checkX[4] = { 0, 1, 0, -1};
const int checkY[4] = {-1, 0, 1,  0};


int mainMap[maxN][maxN];
bool visitedMap[maxN][maxN], visitedZero[maxN][maxN];
int samsungCount[maxType];
int answers[maxTestCases];

int N, testCase;

void clearMaps();
void clearVisitedMap();
void clearSamsungCount();
int highestSamsungCount();
void printMap(int n);
void countAdjacentMap(int n);
void traceZero(int locX, int locY);
void traceNumber(int locX, int locY, int value);
void fillZero(int locX, int locY, int highestType);
void normalizeMap();
void traceBooth(int locX, int locY, int value);


int main() {	
	// read the map
	cin >> N;
	for (int x = 0; x < N; x++)
		for (int y = 0; y < N; y++)
			cin >> mainMap[x][y];

	// core logic starts here
	for (int x = 0; x < N; x++) { 
		for (int y = 0; y < N; y++) { // foreach element of array
			if ((mainMap[x][y] == 0) && (!visitedMap[x][y])) { // if found unvisited 0, start recursive check here
				clearSamsungCount();
				clearVisitedMap();
				traceZero(x, y);
				fillZero(x, y, highestSamsungCount());
			}
		}
	}

	//printMap(N);
	normalizeMap();
	clearSamsungCount();
	clearVisitedMap();

	// save the output;
	int boothCount = 0;
	for (int x = 0; x < N; x++) { 
		for (int y = 0; y < N; y++) { // foreach element of array
			if ((!visitedMap[x][y]) && (mainMap[x][y] > 0)) { // if booth unvisited, visit it (and count)
				traceBooth(x, y, mainMap[x][y]);
				boothCount++;
			}
		}
	}

	cout << boothCount;

	return 0;
}


// -----------------------------------------------------------


// clear the main map
void clearMaps() {
	for (int x = 0; x < N; x++)
		for (int y = 0; y < N; y++) {
			mainMap[x][y] = 0;
		}	
}

// clear the visited map
void clearVisitedMap() {
	for (int x = 0; x < N; x++)
		for (int y = 0; y < N; y++) {
			visitedMap[x][y] = false;
			visitedZero[x][y] = false;
		}	
}

// clear the samsung count
void clearSamsungCount() {
	for (int x = 0; x < maxType; x++)
		samsungCount[x] = 0;
}

// return the current highest samsung type count
// if same, return highest type version
int highestSamsungCount() {
	bool locMaxFound = false;
	int locMaxCount = 0;
	int locMaxType = 0;

	for (int x = 0; x < maxType; x++) 
		if (samsungCount[x] > locMaxCount) {
			locMaxFound = true;
			locMaxCount = samsungCount[x];
		}

	if (locMaxFound) {
		for (int x = 0; x < maxType; x++) {
			if (samsungCount[x] == locMaxCount) locMaxType = x;
		}

		return (locMaxType)*-1;
	} else return 0;	
}

// print the main map with size n
void printMap(int n) {
	cout << endl << "Main map with size " << n << endl;
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			if (mainMap[x][y] >= 0) cout << mainMap[x][y] << "  ";
			else cout << mainMap[x][y] << " ";
		}
		cout << endl;
	}
}

// main recursive call for if encountering zero 
void traceZero(int locX, int locY) {
	if ((locX < 0) || (locX >= N) || (locY < 0) || (locY >= N)) return;
	if (visitedMap[locX][locY]) return;
	

	visitedMap[locX][locY] = true;

	//for (int p = 0; p < 4; p++)
	if ((mainMap[locX + 1][locY    ] > 0) && (!visitedMap[locX + 1][locY    ])) traceNumber(locX+1, locY  , mainMap[locX + 1][locY    ]);
	if ((mainMap[locX    ][locY + 1] > 0) && (!visitedMap[locX    ][locY + 1])) traceNumber(locX  , locY+1, mainMap[locX    ][locY + 1]);
	if ((mainMap[locX - 1][locY    ] > 0) && (!visitedMap[locX - 1][locY    ])) traceNumber(locX-1, locY  , mainMap[locX - 1][locY    ]);
	if ((mainMap[locX    ][locY - 1] > 0) && (!visitedMap[locX    ][locY - 1])) traceNumber(locX  , locY-1, mainMap[locX    ][locY - 1]);


	if ((mainMap[locX + 1][locY    ] == 0) && (!visitedMap[locX + 1][locY    ])) traceZero(locX+1, locY  );
	if ((mainMap[locX    ][locY + 1] == 0) && (!visitedMap[locX    ][locY + 1])) traceZero(locX  , locY+1);
	if ((mainMap[locX - 1][locY    ] == 0) && (!visitedMap[locX - 1][locY    ])) traceZero(locX-1, locY  );
	if ((mainMap[locX    ][locY - 1] == 0) && (!visitedMap[locX    ][locY - 1])) traceZero(locX  , locY-1);
}

// side recursive call for if when encounter cluster of zero and need to count how many neighbor this cluster of zero has
void traceNumber(int locX, int locY, int value) {
	if ((locX < 0) || (locX >= N) || (locY < 0) || (locY >= N)) return;
	if (visitedMap[locX][locY]) return;
	if (mainMap[locX][locY] != value) return;

	visitedMap[locX][locY] = true;
	samsungCount[value]++;

	traceNumber(locX+1, locY  , value);
	traceNumber(locX  , locY+1, value);
	traceNumber(locX-1, locY  , value);
	traceNumber(locX  , locY-1, value);
}

// recursive call to paint all zero (that is currently checked) to max type found
void fillZero(int locX, int locY, int highestType) {
	if ((locX < 0) || (locX >= N) || (locY < 0) || (locY >= N)) return;
	if (visitedZero[locX][locY]) return;

	mainMap[locX][locY] = highestType;
	visitedZero[locX][locY] = true;

	if (mainMap[locX + 1][locY    ] == 0) fillZero(locX+1, locY  , highestType);
	if (mainMap[locX    ][locY + 1] == 0) fillZero(locX  , locY+1, highestType);
	if (mainMap[locX - 1][locY    ] == 0) fillZero(locX-1, locY  , highestType);
	if (mainMap[locX    ][locY - 1] == 0) fillZero(locX  , locY-1, highestType);
}

// painted the map's zeroes with negative number to avoid wrong count, normalize it for final count
void normalizeMap() {
	for (int x = 0; x < N; x++)
		for (int y = 0; y < N; y++) {
			if (mainMap[x][y] < 0) mainMap[x][y] *= -1;
		}
}

// another recursive call to mark the map (grouping)
void traceBooth(int locX, int locY, int value) {
	if ((locX < 0) || (locX >= N) || (locY < 0) || (locY >= N)) return;
	if (visitedMap[locX][locY]) return;
	if (mainMap[locX][locY] != value) return;

	visitedMap[locX][locY] = true;

	traceNumber(locX+1, locY  , value);
	traceNumber(locX  , locY+1, value);
	traceNumber(locX-1, locY  , value);
	traceNumber(locX  , locY-1, value);
}