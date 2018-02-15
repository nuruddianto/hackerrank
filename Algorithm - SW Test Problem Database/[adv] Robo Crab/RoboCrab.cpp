#include <iostream>
using namespace std;

// direction table : NULL, N, S, E, W
const int t_directionX[5] = { 0, 0, 0, 1,-1 };
const int t_directionY[5] = { 0, 1,-1, 0, 0 };

struct t_coordinates {
	int x, y;
};

struct t_movements {
    int direction, distance;
	t_coordinates start, stop;
};

t_movements movements[100];
int moveCounts;


bool isInvalidMoves(t_movements moveA, t_movements moveB);
bool isInside(int A, int B1, int B2);
bool isInside(int A1, int A2, int B1, int B2);




int main() {
	// read input
	cin >> moveCounts;
	for (int i = 0; i < moveCounts; i++) {
		cin >> movements[i].direction >> movements[i].distance;
	}
    
	// translate input to X, Y coordinate
	movements[0].start.x = 0;
	movements[0].start.y = 0;
	movements[0].stop.x = 0 + (movements[0].distance * t_directionX[movements[0].direction]);
	movements[0].stop.y = 0 + (movements[0].distance * t_directionY[movements[0].direction]);
	for (int i = 1; i < moveCounts; i++) {
		movements[i].start.x = movements[i-1].stop.x;
		movements[i].start.y = movements[i-1].stop.y;
		movements[i].stop.x = movements[i-1].stop.x + (movements[i].distance * t_directionX[movements[i].direction]);
		movements[i].stop.y = movements[i-1].stop.y + (movements[i].distance * t_directionY[movements[i].direction]);            
	}

	//// debug : print each movements coordinate
	//cout << "debug, movements stop coordinate are :" << endl;
	//cout << "#0 : 0, 0" << endl;
	//for (int i = 0; i < moveCounts; i++) {
	//	cout << "#" << i+1 << " start : (" << movements[i].start.x << ", " << movements[i].start.y 
	//			<< ") stop : (" << movements[i].stop.x << ", " << movements[i].stop.y << ")" << endl;
	//}

	// compare each move with it's previous move
	bool invalidMoveFound = false;
	int invalidMoveAt = -1;
	for (int y = 1; y < moveCounts; y++) {
		for (int x = 0; x < y; x++) {
			if (isInvalidMoves(movements[y], movements[x]))  {
				invalidMoveFound = true;
				invalidMoveAt = y+1;
			}
			if (invalidMoveFound) break;
		}
		if (invalidMoveFound) break;
	}

	cout << invalidMoveAt;

    return 0;
}





bool isInside(int A, int B1, int B2) {
	// make sure B1 < B2
	if (B1 > B2) {
		int temp = B1;
		B1 = B2;
		B2 = temp;
	}

	// check whether (B1 <= A <= B2)
	if ((B1 < A) && (A < B2)) return true;
	else return false;
}

bool isInside(int A1, int A2, int B1, int B2) {
	// make sure B1 < B2
	if (A1 > A2) {
		int temp = A1;
		A1 = A2;
		A2 = temp;
	}

	// make sure B1 < B2
	if (B1 > B2) {
		int temp = B1;
		B1 = B2;
		B2 = temp;
	}

	if ((B1 < A1) && (A1 < B2)) return true;
	if ((B1 < A2) && (A2 < B2)) return true;
	if ((A1 < B1) && (B1 < A2)) return true;
	if ((A1 < B2) && (B2 < A2)) return true;
	if ((A1 == B1) && (A2 == B2)) return true;
	return false;
}


bool isInvalidMoves(t_movements moveA, t_movements moveB) {
    // check if movements are vertical / horizontal
    bool isAVertical = (moveA.start.x == moveA.stop.x);
    bool isAHorizontal = !isAVertical;
    bool isBVertical = (moveB.start.x == moveB.stop.x);
    bool isBHorizontal = !isBVertical;
    
    // if both are vertical and are on same X coordinate
	// check if either B.Y coordinates is inside of A.Y coordinates
    if (isAVertical && isBVertical && (moveA.start.x == moveB.start.x))
		if (isInside(moveA.start.y, moveA.stop.y, moveB.start.y, moveB.stop.y)) return true;
    
    // also do it on horizontal
    if (isAHorizontal && isBHorizontal && (moveA.start.y == moveB.start.y))
		if (isInside(moveA.start.x, moveA.stop.x, moveB.start.x, moveB.stop.x)) return true;
    
    // for if intersecting probabilites, check :
    if (isAHorizontal && isBVertical)
		if (isInside(moveB.start.x, moveA.start.x, moveA.stop.x)) // if B.X is inside A.Xs
            if (isInside(moveA.start.y, moveB.start.y, moveB.stop.y)) // and A.Y is inside B.Ys
				return true;
        
    // vice versa
    if (isBHorizontal && isAVertical)
		if (isInside(moveA.start.x, moveB.start.x, moveB.stop.x)) // if A.X is inside B.Xs
            if (isInside(moveB.start.y, moveA.start.y, moveA.stop.y)) // and B.Y is inside A.Ys
				return true;
    
    return false;
}


















//#include <iostream>
//using namespace std;
//
//// direction table : NULL, N, S, E, W
//const int t_directionX[5] = { 0, 0, 0, 1,-1 };
//const int t_directionY[5] = { 0, 1,-1, 0, 0 };
//
//struct t_coordinates {
//	int x, y;
//};
//
//struct t_movements {
//    int direction, distance;
//	t_coordinates start, stop;
//};
//
//t_movements movements[100];
//int moveCounts;
//
//
//bool isAInsideB(t_coordinates A, t_coordinates B); 
//bool isInvalidMoves(t_movements moveA, t_movements moveB);
//bool isSameLine(int A1, int A2, int B1, int B2);
//
//
//
//int main() {
//	//int testCases;
//	//cin >> testCases;
//	//for (int testCase = 0; testCase < testCases; testCase++) {
//
//		// read input
//		cin >> moveCounts;
//		for (int i = 0; i < moveCounts; i++) {
//			cin >> movements[i].direction >> movements[i].distance;
//		}
//    
//		// translate input to X, Y coordinate
//		//movements[0].start.x = 0 + (t_directionX[movements[0].direction]);
//		//movements[0].start.y = 0 + (t_directionY[movements[0].direction]);
//		movements[0].start.x = 0;
//		movements[0].start.y = 0;
//		movements[0].stop.x = 0 + (movements[0].distance * t_directionX[movements[0].direction]);
//		movements[0].stop.y = 0 + (movements[0].distance * t_directionY[movements[0].direction]);
//		for (int i = 1; i < moveCounts; i++) {
//			//movements[i].start.x = movements[i-1].stop.x + (t_directionX[movements[i].direction]);
//			//movements[i].start.y = movements[i-1].stop.y + (t_directionY[movements[i].direction]);
//			movements[i].start.x = movements[i-1].stop.x;
//			movements[i].start.y = movements[i-1].stop.y;
//			movements[i].stop.x = movements[i-1].stop.x + (movements[i].distance * t_directionX[movements[i].direction]);
//			movements[i].stop.y = movements[i-1].stop.y + (movements[i].distance * t_directionY[movements[i].direction]);            
//		}
//    
//		//// debug : print each movements coordinate
//		//cout << "debug, movements stop coordinate are :" << endl;
//		//cout << "#0 : 0, 0" << endl;
//		//for (int i = 0; i < moveCounts; i++) {
//		//	cout << "#" << i+1 << " start : (" << movements[i].start.x << ", " << movements[i].start.y 
//		//		 << ") stop : (" << movements[i].stop.x << ", " << movements[i].stop.y << ")" << endl;
//		//}
//    
//		// compare each move with it's previous move
//		bool invalidMoveFound = false;
//		int invalidMoveAt = -1;
//		for (int y = 1; y < moveCounts; y++) {
//			for (int x = 0; x < y; x++) {
//				if (isInvalidMoves(movements[y], movements[x]))  {
//					invalidMoveFound = true;
//					invalidMoveAt = y+1;
//				}
//				if (invalidMoveFound) break;
//			}
//			if (invalidMoveFound) break;
//		}
//    
//		// print the answer;
//		//cout << "#" << testCase+1 << " answer = " << invalidMoveAt << endl;
//		cout << invalidMoveAt;
//	//}
//
//    return 0;
//}
//
//
//
//
//
//bool isInside(int A, int B1, int B2) {
//	// make sure B1 < B2
//	if (B1 > B2) {
//		int temp = B1;
//		B1 = B2;
//		B2 = temp;
//	}
//
//	// check whether (B1 <= A <= B2)
//	if ((B1 < A) && (A < B2)) return true;
//	else return false;
//}
//
//bool isInside(int A1, int A2, int B1, int B2) {
//	// make sure B1 < B2
//	if (A1 > A2) {
//		int temp = A1;
//		A1 = A2;
//		A2 = temp;
//	}
//
//	// make sure B1 < B2
//	if (B1 > B2) {
//		int temp = B1;
//		B1 = B2;
//		B2 = temp;
//	}
//
//	if ((A1 == B1) && (A2 == B2)) return true;
//	else return false;
//	
//}
//
//bool isInside(int A1, int A2, int B1, int B2) {
//	// make sure B1 < B2
//	if (A1 > A2) {
//		int temp = A1;
//		A1 = A2;
//		A2 = temp;
//	}
//
//	// make sure B1 < B2
//	if (B1 > B2) {
//		int temp = B1;
//		B1 = B2;
//		B2 = temp;
//	}
//
//	if ((B1 < A1) && (A1 < B2)) return true;
//	if ((B1 < A2) && (A2 < B2)) return true;
//	if ((A1 < B1) && (B1 < A2)) return true;
//	if ((A1 < B2) && (B2 < A2)) return true;
//	if ((A1 == B1) && (A2 == B2)) return true;
//	return false;
//}
//
//
//bool isInvalidMoves(t_movements moveA, t_movements moveB) {
//    // check if movements are vertical / horizontal
//    bool isAVertical = (moveA.start.x == moveA.stop.x);
//    bool isAHorizontal = !isAVertical;
//    bool isBVertical = (moveB.start.x == moveB.stop.x);
//    bool isBHorizontal = !isBVertical;
//    
//    // if both are vertical and are on same X coordinate
//    if (isAVertical && isBVertical && (moveA.start.x == moveB.start.x)) {
//		//// check if either B.Y coordinates is inside of A.Y coordinates
//		//if (isAInsideB(moveB.start.y, moveA.start.y, moveA.stop.y)) return true;
//		//if (isAInsideB(moveB.stop.y , moveA.start.y, moveA.stop.y)) return true;
//		//if (isAInsideB(moveA.start.y, moveB.start.y, moveB.stop.y)) return true;
//		//if (isAInsideB(moveA.stop.y , moveB.start.y, moveB.stop.y)) return true;
//
//		//// or is a counter line with same width (N1 vs S1)
//		//if (isSameLine(moveA.start.y, moveA.stop.y, moveB.start.y, moveB.stop.y)) return true;
//
//		if (isInside(moveA.start.y, moveA.stop.y, moveB.start.y, moveB.stop.y)) return true;
//    } 
//    
//    // if both are horizontal and are on same Y coordinate
//    if (isAHorizontal && isBHorizontal && (moveA.start.y == moveB.start.y)) {
//		//// check if either B.X coordinates is inside of A.X coordinates
//		//if (isAInsideB(moveB.start.x, moveA.start.x, moveA.stop.x)) return true;
//		//if (isAInsideB(moveB.stop.x , moveA.start.x, moveA.stop.x)) return true;
//		//
//		//// or is a counter line with same width (E1 vs W1)
//		//if (isSameLine(moveA.start.x, moveA.stop.x, moveB.start.x, moveB.stop.x)) return true;
//
//		if (isInside(moveA.start.x, moveA.stop.x, moveB.start.x, moveB.stop.x)) return true;
//    }
//    
//    // for if intersecting probabilites, check :
//    if (isAHorizontal && isBVertical)
//		if (isAInsideB(moveB.start.x, moveA.start.x, moveA.stop.x)) // if B.X is inside A.Xs
//            if (isAInsideB(moveA.start.y, moveB.start.y, moveB.stop.y)) // and A.Y is inside B.Ys
//				return true;
//        
//    // vice versa
//    if (isBHorizontal && isAVertical)
//		if (isAInsideB(moveA.start.x, moveB.start.x, moveB.stop.x)) // if A.X is inside B.Xs
//            if (isAInsideB(moveB.start.y, moveA.start.y, moveA.stop.y)) // and B.Y is inside A.Ys
//				return true;
//    
//    return false;
//}
//
//
//
