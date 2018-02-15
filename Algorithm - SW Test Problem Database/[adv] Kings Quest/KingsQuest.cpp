#include <iostream>
using namespace std;

struct t_monsters {
	int size, cost;
};

struct t_army {
	int size[20];
	int battleCount[20];
};


int T;
int minCost, encounterCount;
t_monsters orcEnemy[20];


void doSimulation(int encounter, t_army ourArmy, int costNow);

int main() {

	cin >> T;

	for (int testCase = 1; testCase <= T; testCase++) {
		cin >> encounterCount;
		for (int i = 0; i < encounterCount; i++) {
			cin  >> orcEnemy[i].cost >> orcEnemy[i].size;
		}
		
		minCost = 0;
		for (int i = 0; i < encounterCount; i++) {
			minCost += orcEnemy[i].cost * 2;
		}

		t_army initialArmy;
		for (int i = 0; i < encounterCount; i++) {
			initialArmy.size[i] = 0;
			initialArmy.battleCount[i] = 0;
		}
		doSimulation(0, initialArmy, 0);

		cout << "#" << testCase << " " << minCost << endl;

	}

	return 0;
}


void doSimulation(int encounter, t_army ourArmy, int costNow) {
	if (encounter >= encounterCount) { // udah sampe ujung, hitung!
		if (costNow < minCost) {
			minCost = costNow;
		}	
	} else {

		// bisa pilih untuk bayar (pass)	
		int costToPass = costNow + orcEnemy[encounter].cost;
		if (costToPass < minCost) 
			doSimulation(encounter+1, ourArmy, costToPass);
		
		// atau pilih untuk hire
		int costToHire = costNow + (orcEnemy[encounter].cost * 2);
		if (costToHire < minCost) {
			ourArmy.size[encounter] = orcEnemy[encounter].size;
			doSimulation(encounter+1, ourArmy, costToHire);

			// after exit from that choice, return to previous state
			ourArmy.size[encounter] = 0;
		}


		//atau pilih untuk perang!
		
		// pastikan orcHire[] di posisi ini normalized (disband after 3 battle)
		for (int i = 0; i < encounterCount; i++) {
			if (ourArmy.battleCount[i] >= 3) ourArmy.size[i] = 0;
		}

		// hitung ulang total army saat ini
		int totalArmyNow = 0;
		for (int i = 0; i < encounterCount; i++) {
			totalArmyNow += ourArmy.size[i];
		}

		// kalo bisa, pilih untuk perang
		int totalEnemy = orcEnemy[encounter].size;
		if (totalArmyNow >= totalEnemy) {
			// do battle simulation : kurangin pasukan dari yang paling lama di hire
			
			int selectedArmy = 0;
			while (totalEnemy > 0) {
				if (totalEnemy > ourArmy.size[selectedArmy]) {
					totalEnemy -=  ourArmy.size[selectedArmy];
					ourArmy.size[selectedArmy] = 0;
				} else {
					ourArmy.size[selectedArmy] -= totalEnemy;
					totalEnemy = 0;
				}

				selectedArmy++;
			}

			// after battle, increase the battle count for any remaining army
			for (int i = 0; i < encounterCount; i++) if (ourArmy.size[i] != 0) ourArmy.battleCount[i]++;

			// continue the simulation
			doSimulation(encounter+1, ourArmy, costNow);
		}
		


	}
}