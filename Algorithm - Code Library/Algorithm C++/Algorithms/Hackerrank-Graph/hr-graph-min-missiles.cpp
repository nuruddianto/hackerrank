/*
 Problem Statement
 
 Evil Nation A is angry and plans to launch N guided-missiles at the peaceful Nation B in an attempt to wipe out all of Nation B's people. Nation A's missile i will arrive in nation B at time ti. Missile i communicates with its headquarters by unique radio signals with a frequency equal to fi. Can you help the peaceful Nation B survive by building a defensive system that will stop the missiles dead in the sky?
 
 Defensive system:
 
 The only way to defend Nation B from the attacking missile is by counter attacking them with a hackerX missile. You have a lot of hackerX missiles and each one of them has its own radio frequency. An individual hackerX missile can destroy Evil Nation A’s attacking missile if the radio frequency of both of the missiles match. Each hackerX missile can be used an indefinite number of times. Its invincible and doesn't get destroyed in the collision.
 
 The good news is you can adjust the frequency of the hackerX missile to match the evil missiles' frequency. When changing the hackerX missile's initial frequency fA to the new defending frequency fB, you will need \|fB - fA\| units of time to do.
 
 Each hackerX missile can only destroy one of Nation A's missile at a time. So if two evil missiles with same frequency arrive at the same time, you need at least two hackerX missiles with the same frequency as the evil missiles to avoid damage.
 
 If two evil missles with same frequency arrive at the same time, we can destroy them both with one hackerX missile. You can set the frequency of a hackerX missile to any value when its fired.
 
 What is the minimum number of hackerX missiles you must launch to keep Nation B safe?
 
 Input Format:
 The first line contains a single integer N denoting the number of missiles.
 This is followed by N lines each containing two integers ti and fi denoting the time & frequency of the ith missile.
 
 Output Format:
 A single integer denoting the minimum number of hackerX missiles you need to defend the nation.
 
 Constraints:
 1 <= N <= 100000
 0 <= ti <= 100000
 0 <= fi <= 100000
 t1 <= t2 <= ... <= tN
 
 Sample Input #00
 
 4
 1 1
 2 2
 3 1
 5 1
 Sample Output #00
 
 1
 Explanation #00
 
 A HackerX missile is launched at t = 1 with a frequency f = 1, and destroys the first missile. It re-tunes its frequency to f = 2 in 1 unit of time, and destroys the missile that is going to hit Nation B at t = 2. It re-tunes its frequency back to 1 in 1 unit of time and destroys the missile that is going to hit the nation at t = 3. It is relaunched at t = 5 with f = 1 and destroys the missile that is going to hit nation B at t = 5. Hence, you need only 1 HackerX to protect nation B.
 
 Sample Input #01
 
 4
 1 1
 2 3
 3 1
 5 1
 Sample Output #01
 
 2
 Explanation #01
 
 Destroy 1 missile at t = 1, f = 1. now at t = 2, there is a missile with frequency 3. The launched missile takes 2 units of time to destroy this, hence we need a new hackerX missile to destroy this one. The first hackerX missile can destroy the 3rd missile which has the same frequency as itself. The same hackerX missile destroys the missile that is hitting its city at t = 5. Thus, we need atleast 2 hackerX missiles.
*/

#include <stdio.h>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

#define NMAX 131072

int N, M, i, j, f, t, x, y, lmax, v[NMAX << 1];
map<pair<int, int>, int> cnt;
map<pair<int, int>, int>::iterator it;
map<int, int> ycoord_map;
set<int> ycoord;
set<int>::iterator yit;

int get_query(int a) {
    int b = NMAX + a - 1, result = 0;
    
    while (b > 1) {
        if ((b & 1) == 1)
            result = max(result, v[b - 1]);
        
        b = b >> 1;
    }
    
    return result;
}

void update(int a, int val) {
    int b = NMAX + a - 1;
    
    while (b >= 1) {
        v[b] = max(v[b], val);
        b = b >> 1;
    }
}

int main() {
    scanf("%d", &N);
    
    for (i = 0; i < N; i++) {
        scanf("%d %d", &t, &f);
        x = t - f;
        y = f + t;
        cnt[make_pair(-x, -y)]++;
        ycoord.insert(y);
    }
    
    for (M = 0, yit = ycoord.begin(); yit != ycoord.end(); yit++) {
        M++;
        ycoord_map[*yit] = M;
    }
    
    for (it = cnt.begin(); it != cnt.end(); it++) {
        j = ycoord_map[-(it->first.second)];
        lmax = get_query(j);
        lmax++;
        update(j, lmax);
    }
    
    printf("%d\n", v[1]);
    
    return 0;
}