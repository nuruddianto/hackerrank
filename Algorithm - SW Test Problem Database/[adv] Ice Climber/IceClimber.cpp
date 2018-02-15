//#include <iostream>
//using namespace std;
//
//int map[50][50];
//bool visitedMap[50][50];
//int width, height;
//int maxLevel;
//bool minimumLevelFound;
//int startX, startY, finishX, finishY;
//
//void iceClimbing(int x, int y);
//void clearVisitedMap();
//
//int main() {
//
//	// read input
//	int x, y; 
//
//	cin >> width >> height;
//
//	for (y = 0; y < height; y++)
//		for (x = 0; x < width; x++)
//		{
//			cin >> map[x][y];
//			if (map[x][y] == 2) { startX = x; startY = y; }
//			if (map[x][y] == 3) { finishX = x; finishY = y; }
//		}
//
//	//// check output
//	//cout << "\ncheck output\n";
//	//for (y = 0; y < width; y++) {
//	//	for (x = 0; x < height; x++)
//	//	{
//	//		cout << map[x][y];
//	//	}
//	//	cout << endl;
//	//}
//
//	minimumLevelFound = false;
//	for (int i = 1; i <= height; i++) {
//		maxLevel = i;
//
//		//// debug
//		//cout << "\nnow at level : " << maxLevel;
//
//		clearVisitedMap();
//		iceClimbing(startX, startY);
//
//		if (minimumLevelFound) break;
//	}
//
//	if (minimumLevelFound) {
//		cout << "\nMinimum Level = " << maxLevel;
//	}
//
//	return 0;
//}
//
//void clearVisitedMap() {
//	for (int y = 0; y < height; y++)
//		for (int x = 0; x < width; x++)
//			visitedMap[x][y] = false;
//}
//
//void iceClimbing(int x, int y) {
//	// check if out of bound 
//	if ((x < 0) || (y < 0) || (x >= width) || (y >= height)) return;
//
//	// check if this is a valid footing
//	if ((map[x][y] < 1) || (map[x][y] > 3)) return;
//
//	// check if is finish point
//	if ((x == finishX) && (y == finishY)) { minimumLevelFound = true; return; };
//
//	// continue search for finish point
//	if (!minimumLevelFound && (!visitedMap[x][y])) {
//		visitedMap[x][y] = true;
//
//		//// debug
//		//cout << "\nnow visiting : " << x << ", " << y;
//
//		// try to jump up/down! (limited by current maxLevel)
//		for (int currentLeap = 1; currentLeap <= maxLevel; currentLeap++) {
//			iceClimbing(x, y + currentLeap);
//		}
//
//		for (int currentLeap = 1; currentLeap <=  maxLevel; currentLeap++) {
//			iceClimbing(x, y - currentLeap);
//		}
//
//		// try to visit neighbour path (left & right only)
//		iceClimbing(x + 1, y);
//		iceClimbing(x - 1, y);
//
//		visitedMap[x][y] = false;
//	}
//}






#include <iostream>
using namespace std;

int map[50][50];
bool visitedMap[50][50];
int width, height;
bool minimumLevelFound;
int startX, startY, finishX, finishY;

void iceClimbing(int x, int y, int maxLevel);
void clearVisitedMap();

int main() {

	// read input
	int x, y; 

	cin >> width >> height;

	for (y = 0; y < height; y++)
		for (x = 0; x < width; x++)
		{
			cin >> map[x][y];
			if (map[x][y] == 2) { startX = x; startY = y; }
			if (map[x][y] == 3) { finishX = x; finishY = y; }
		}

	minimumLevelFound = false;
	for (int i = 1; i <= height; i++) {
		clearVisitedMap();
		iceClimbing(startX, startY, i);

		if (minimumLevelFound) {
			cout << "Max Level = " << i;
			break;
		}
	}

	return 0;
}

void clearVisitedMap() {
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
			visitedMap[x][y] = false;
}

void iceClimbing(int x, int y, int maxLevel) {
	// check if out of bound 
	if ((x < 0) || (y < 0) || (x >= width) || (y >= height)) return;

	// check if this is a valid footing
	if ((map[x][y] < 1) || (map[x][y] > 3)) return;

	// check if is finish point
	if ((x == finishX) && (y == finishY)) { minimumLevelFound = true; return; };

	// continue search for finish point
	if (!minimumLevelFound && (!visitedMap[x][y])) {
		visitedMap[x][y] = true;

		// try to jump up/down! (limited by current maxLevel)
		for (int currentLeap = 1; currentLeap <= maxLevel; currentLeap++) 
			iceClimbing(x, y + currentLeap, maxLevel);

		for (int currentLeap = 1; currentLeap <=  maxLevel; currentLeap++)
			iceClimbing(x, y - currentLeap, maxLevel);

		// try to visit neighbour path (left & right only)
		iceClimbing(x + 1, y, maxLevel);
		iceClimbing(x - 1, y, maxLevel);

		visitedMap[x][y] = false;
	}
}








































//#include <iostream>
//#include <random>
//#include <chrono>
//#include <fstream>
//using namespace std;
//
//
//int map[101][101];
//bool visited[100][101];
//int columns, rows;
//int startX, startY, finishX, finishY;
//bool finishFound;
//
//void recursiveSearch(int posX, int posY, int maxVertical);
//void generateRandomMap(int sizeX, int sizeY);
//void clearVisitedMap();
//
//int main() {
//
//	ifstream inputFile;
//	inputFile.open("inputFile.txt");
//
//    // read the map
//    inputFile >> columns >> rows;
//    for (int y = 0; y < rows; y++) {
//            for (int x = 0; x < columns; x++) {
//            inputFile >> map[x][y];
//            visited[x][y] = false;
//            if (map[x][y] == 2) { startX = x; startY = y; }
//            if (map[x][y] == 3) { finishX = x; finishY = y; }
//            }
//    }
//
//	inputFile.close();
//    
//    //// read the map
//    //cin >> columns >> rows;
//    //for (int y = 0; y < rows; y++) {
//    //    for (int x = 0; x < columns; x++) {
//    //        cin >> map[x][y];
//    //        visited[x][y] = false;
//    //        if (map[x][y] == 2) { startX = x; startY = y; }
//    //        if (map[x][y] == 3) { finishX = x; finishY = y; }
//    //    }
//    //}
//
//    // try easiest dificulty first, in the recursive search
//    finishFound = false;
//    int maxVertical = 0;
//    while(!finishFound) {
//		clearVisitedMap();
//        maxVertical++;
//        recursiveSearch(startX, startY, maxVertical);
//
//		// failsafe mechanism
//		if (maxVertical >= rows) {
//			cout << "fatal exception : maxVertical exceed row limit!" << endl;
//			finishFound = true;
//		}
//		//cout << "finished checking maxVertical : " << maxVertical << endl;
//    }
//    
//    cout << maxVertical;    
//    
//
//	//// ----------- random engine
//	//int sizeX = 50;
//	//int sizeY = 50;
//	//generateRandomMap(sizeX, sizeY);
//
//    return 0;
//}
//
//void recursiveSearch(int posX, int posY, int maxVertical) {
//    if ((posX < 0) || (posY < 0) || (posX >= columns) || (posY >= rows)) return;
//    if (visited[posX][posY]) return;
//    if ((posX == finishX) && (posY == finishY)) finishFound = true;
//    if (finishFound) return;
//    
//	//if (maxVertical == 8)
//	//	cout << "now visiting : " << posX << ", " << posY << " at " << maxVertical << endl;
//    
//    visited[posX][posY] = true;
//    
//    // check to up for max->maxVertical Jump
//    for (int i = maxVertical; i >= 1; i--)
//		if ((posY+i  < rows) && (!visited[posX][posY+i]) && (map[posX][posY+i] != 0)) {
//			for (int y = 1; y < i; y++) visited[posX][posY+y] = true;
//            recursiveSearch(posX, posY+i, maxVertical);
//			for (int y = 1; y < i; y++) visited[posX][posY+y] = false;
//		}
//
//    // check to down for max->maxVertical Jump
//    for (int i = maxVertical; i >= 1; i--)
//       if ((posY-i >= 0) && (!visited[posX][posY-i]) && (map[posX][posY-i] != 0)) {
//			for (int y = 1; y < i; y++) visited[posX][posY-y] = true;
//            recursiveSearch(posX, posY-i, maxVertical);
//			for (int y = 1; y < i; y++) visited[posX][posY-y] = false;
//		}
//
//    // check to left
//    if ((posX-1  < columns) && (map[posX-1][posY] != 0))
//        recursiveSearch(posX-1, posY, maxVertical);
//        
//    // check to right
//    if ((posX+1  < columns) && (map[posX+1][posY] != 0))
//        recursiveSearch(posX+1, posY, maxVertical);
//    
//    visited[posX][posY] = false;
//}
//
//
//void generateRandomMap(int sizeX, int sizeY) {
//	ofstream outputFile;
//	outputFile.open("generatedFile.txt");
//
//	outputFile << endl << "Ice Climber randomly generated map : " << endl;
//	outputFile << sizeX << " " << sizeY << endl;
//
//	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
//    std::mt19937_64 generator (seed);
//    std::uniform_int_distribution<int> distribution(0, 10);
//
//    for (int y = 0; y < sizeY; y++) {
//            for (int x = 0; x < sizeX; x++) {
//				int randomnya = distribution(generator);
//				if (randomnya <= 1) outputFile << "1 ";
//				else outputFile << "0 ";
//			}
//			outputFile << endl;
//	}
//
//	outputFile.close();
//
//	cout << "done generating generatedFile.txt" << endl;
//}
//
//void clearVisitedMap() {
//	for (int y = 0; y < rows; y++)
//		for (int x = 0; x < columns; x++)
//			visited[x][y] = false;
//}