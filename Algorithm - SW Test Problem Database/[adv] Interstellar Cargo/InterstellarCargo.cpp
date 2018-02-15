#include <iostream>
using namespace std;

int startX, finishX, startY, finishY;
int wormholeStartX[10];
int wormholeStartY[10];
int wormholeFinishX[10];
int wormholeFinishY[10];
bool used[10];
int jumWormhole;
int jarakMin;

int hitungJarak(int startX, int startY, int finishX, int finishY);
void jelajah(int indexLastVisited, int totalJarak);

int main() {
	// read input
	cin >> startX >> startY;
	cin >> finishX >> finishY;
	cin >> jumWormhole;
	for (int i = 0; i < jumWormhole; i++) {
		cin >> wormholeStartX[i] >> wormholeStartY[i];
		cin >> wormholeFinishX[i] >> wormholeFinishY[i];
	}

	for (int i = jumWormhole; i < 2*jumWormhole; i++) {
		wormholeFinishX[i] = wormholeStartX[i-jumWormhole];
		wormholeFinishY[i] = wormholeStartY[i-jumWormhole];
		wormholeStartX[i] = wormholeFinishX[i-jumWormhole];
		wormholeStartY[i] = wormholeFinishY[i-jumWormhole];
	}

	// test input
	
	// kosongin
	for (int i = 0; i < 2*jumWormhole; i++) used[i] = false;

	// rekursif
	jarakMin = hitungJarak(startX, startY, finishX, finishY);
	for (int i = 0; i < 2*jumWormhole; i++) {
		int jarakStart = hitungJarak(startX, startY, wormholeStartX[i], wormholeStartY[i]);
		used[i] = true;
		jelajah(i, jarakStart);
		used[i] = false;
	}

	cout << "jarakmin = " << jarakMin;


	return 0;
}




int hitungJarak(int startX, int startY, int finishX, int finishY) {
	int jarakX = startX - finishX;
	int jarakY = startY - finishY;
	if (jarakX < 0) jarakX *= -1;
	if (jarakY < 0) jarakY *= -1;
	return (jarakX + jarakY);
}


void jelajah(int indexLastVisited, int totalJarak) {
	int jarakFinish = totalJarak + hitungJarak(wormholeFinishX[indexLastVisited], wormholeFinishY[indexLastVisited],finishX, finishY);
	if (jarakMin > jarakFinish) jarakMin = jarakFinish;

	//if (totalJarak > jarakMin) return;
	//if (index > 2*jumWormhole) return;

	for (int i = 0; i < 2*jumWormhole; i++) {
		if (!used[i]) {
			used[i] = true;
			int jarakLoncat = hitungJarak(wormholeFinishX[indexLastVisited], wormholeFinishY[indexLastVisited], wormholeStartX[i], wormholeStartY[i]);
			int jarakNext = totalJarak + jarakLoncat;
			if (jarakNext < jarakMin) jelajah(i, jarakNext);
			used[i] = false;
		}	
	}
}