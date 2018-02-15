/*
 Problem Statement
 
 There are N cities in the Hacker Country. There is a unique directed road connecting each pair of different cities directly. However, each road has its own cost which you must pay for passing it each time. You are planning to visit the country. Here are the conditions to be satisfied:
 
 You can start at any city you'd like to
 You can pass through as many roads as you can
 You must pass at least 2 different cities
 At the end of the trip, you should come back to the city where you started
 The average cost per road should be minimum
 As a top programmer, could you calculate the minimum average cost?
 
 Input format
 The first line of the input is an integer N.
 Each of the next N lines contains N integers separated by a single space. The jth integer of the ith row denotes the amount you must pay to go from the ith city to the jth city.
 There are no roads that connect a city to itself.
 
 Constraints
 1 < N <= 500
 0 < cost of any road <= 200.
 ith integer of the ith row will always be 0 implying there is no self connecting road.
 
 Output format
 Output the minimum cost as a rational number p/q. The greatest common divisor of p and q should be 1.
 
 Sample input
 
 2
 0 1
 2 0
 Sample Output
 
 3/2
 Explanation
 
 You travel across both the cities with an average cost of (2+1)/2 = 3/2
 
 Timelimits
 Timelimits for this challenge is given here
*/

#include <iostream>
#include <map>

#define INFINITY 0x3f3f3f3f
#define MAXN 505
using namespace std;

typedef long long LL;

LL get_difference(pair<int, int> a, pair<int, int> b) {
    LL t = (LL)a.first * b.second - (LL)a.second * b.first;
    return t;
}

int get_GCD(int a, int b) {
    return b == 0 ? a : get_GCD(b, a % b);
}

void get_min_cost(pair<int, int> p) {
    int g = get_GCD(p.first, p.second);
    cout << p.first / g << "/" << p.second / g << endl;
}

int main() {
    int input, s, roads[MAXN][MAXN], cities[MAXN][MAXN];
    pair<int, int> directions, max_roads;
    
    while (cin >> input) {
        for (int i = 0; i < input; i++) {
            for (int j = 0; j < input; j++) {
                cin >> roads[i][j];
                
                if (i == j)
                    roads[i][j] = INFINITY;
            }
        }
        
        for (int i = 0; i <= input + 1; i++) {
            for (int j = 0; j < input + 1; j++) {
                cities[i][j] = INFINITY;
            }
        }
        
        s = input++;
        
        for (int i = 0; i < input - 1; i++) {
            roads[s][i] = 0;
            roads[i][s] = INFINITY;
        }
        
        roads[s][s] = INFINITY;
        cities[0][s] = 0;
        
        for (int k = 0; k < input; k++) {
            for (int i = 0; i < input; i++) {
                for (int j = 0; j < input; j++) {
                    if (cities[k][i] + roads[i][j] < cities[k + 1][j]) {
                        cities[k + 1][j] = cities[k][i] + roads[i][j];
                    }
                }
            }
        }
        
        directions = make_pair(INFINITY, 1);
        
        for(int i = 0; i < input - 1; i++) {
            if(cities[input][i] == INFINITY) continue;
            
            max_roads = make_pair(-INFINITY, 1);
            
            for(int k = 0; k < input - 1; k++) {
                if(get_difference(make_pair(cities[input][i] - cities[k][i], input - k), max_roads) > 0)
                    max_roads = make_pair(cities[input][i] - cities[k][i], input - k);
            }
            
            if (get_difference(max_roads, directions) < 0)
                directions = max_roads;
        }
        
        get_min_cost(directions);
    }
    
    return 0;
}