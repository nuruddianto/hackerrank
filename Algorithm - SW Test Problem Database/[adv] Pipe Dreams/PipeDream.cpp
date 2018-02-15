#include <iostream>
using namespace std;

// neighbor matrix (up, down, left, right)
const int neighborX[4] = {  0,  0, -1, +1 };
const int neighborY[4] = { -1, +1,  0,  0 }; 

// each pipe has 4 "ends", up - down - left -right
const int pipeEnds[7][4] = {
  //  u  d  l  r
	{ 1, 1, 1, 1 }, 
	{ 1, 1, 0, 0 },
	{ 0, 0, 1, 1 },
	{ 1, 0, 0, 1 },
	{ 0, 1, 0, 1 },
	{ 0, 1, 1, 0 },
	{ 1, 0, 1, 0 },
};

struct t_pipe {
	int x, y;
	int type;
	int distance;
};

int map[50][50];
bool visited[50][50];
t_pipe queue[3000];
int qHead, qTail;

int mapX, mapY, startX, startY, maxDistance;

bool isQEmpty();
void addToQ(t_pipe nextPipe);
t_pipe getFromQ();
bool isValidPos(int x, int y);
bool isConnected(int typeFrom, int typeTo, int direction);

int main() {
	// read input & map
	cin >> mapY >> mapX >> startY >> startX >> maxDistance;
	for (int y = 0; y < mapY; y++)
		for (int x = 0; x < mapX; x++) {
			cin >> map[y][x];
			map[y][x]--; // normalized the pipe type to 0..6 instead of 1..7
			visited[y][x] = false;
		}

	// add startX and startY as the first queue
	qHead = 0;
	qTail = -1;
	t_pipe firstPipe;
		firstPipe.x = startX;
		firstPipe.y = startY;
		firstPipe.type = map[startY][startX];
		firstPipe.distance = 0;
	addToQ(firstPipe);

	// do BFS!
	while (!isQEmpty()) {
		t_pipe currentPipe = getFromQ();
		
		// mark current pipe as "visited", visited pipes will be counted as the answer
		visited[currentPipe.y][currentPipe.x] = true;

		// if we can still flood from this pipe, find a "compatible" neighbour.. ->
		if (currentPipe.distance < maxDistance-1) {
			for (int dir = 0; dir < 4; dir++) { // for each directions (up,down,left,right)
				int nextX = currentPipe.x + neighborX[dir];
				int nextY = currentPipe.y + neighborY[dir];
				
				if (isValidPos(nextX, nextY))
					if ((!visited[nextY][nextX]) && (isConnected(currentPipe.type, map[nextY][nextX], dir))) {
						// <- ..and add them to queue for next visit!
						visited[nextY][nextX] = true;
						t_pipe nextPipe;
							nextPipe.distance = currentPipe.distance + 1;
							nextPipe.type = map[nextY][nextX];
							nextPipe.x = nextX;
							nextPipe.y = nextY;
						addToQ(nextPipe);
					}
				
			}
		}
	}
	
	//debug -- print the visited map!
	cout << endl << "debug : visitedMap[][]" << endl;
	for (int y = 0; y < mapY; y++) {
		for (int x = 0; x < mapX; x++) {
			cout << visited[y][x];
		}
		cout << endl;
	}

	// after the visited map is flooded, we just need to count for visited locations
	int visitedPipes = 0;
	for (int y = 0; y < mapY; y++)
		for (int x = 0; x < mapX; x++) 
			if (visited[y][x]) visitedPipes++;

	// print the answer
	cout << visitedPipes;

	return 0;
}





bool isQEmpty() {
	return qHead > qTail;
}


void addToQ(t_pipe nextPipe) {
	qTail++;
	queue[qTail] = nextPipe;
}


t_pipe getFromQ() {
	t_pipe headPipe = queue[qHead];
	qHead++;
	return headPipe;
}


bool isValidPos(int x, int y) {
	bool isValid = ((x >= 0) && (x < mapX) && (y >= 0) && (y < mapY));
	if (isValid) if (map[y][x] == -1) return false;
	return true;
}


bool isConnected(int typeFrom, int typeTo, int direction) {
	// to check if this two pipe is connected or not, we must pay attention
	// to their "ends" and in which direction do we "connect" these pipes!
	int reverseDirection = -1;
	if (direction == 0) reverseDirection = 1;
	else if (direction == 1) reverseDirection = 0;
	else if (direction == 2) reverseDirection = 3;
	else if (direction == 3) reverseDirection = 2;

	// if the first pipe doesnt have ends that "going towards" the direction, exit!
	if (!pipeEnds[typeFrom][direction]) return false;

	// and the pipe destination must have the "reverse" direction ends to be
	// able to be connection to the first pipe!
	if (!pipeEnds[typeTo][reverseDirection]) return false;

	// else they both comply and can be connected
	return true;
}