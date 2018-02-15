#include <iostream>
using namespace std;

    struct t_deck {
        int card[12];
    };

    bool isInOrder(t_deck cardDeck, int deckLength);
    void recursiveFind(int shuffleCount, t_deck currentDeck, int *minShuffle, int deckLength);
    t_deck doShuffle(t_deck currentDeck, int X, int deckLength);
    void testShuffleMachine(t_deck currentDeck, int deckLength);
    void printDeck(t_deck currentDeck, int deckLength);

int main()
{
    int T, N;
    
    cin >> T; 
    for (int testCase = 1; testCase <= T; testCase++) {
        // read input & prepare for recursive shuffle
        cin >> N;
        t_deck originalCards;
        for (int i = 0; i < N; i++) cin >> originalCards.card[i];
        int minShuffle = -1;
        
//        // debug --> test the shuffle machine!
//        testShuffleMachine(originalCards, N);
        
        // do recursive shuffle to find minimum shuffles needed to get an in-order deck
        // this recursive shuffling will stop when the cards are either in ascending or descending order or if it takes more than 5 shuffle and the cards are still not in-order
        // but first, check if the original deck is already in-order!
        if (isInOrder(originalCards, N)) {
            minShuffle = 0;
        } else 
            recursiveFind(0, originalCards, &minShuffle, N);
            
        // write the answer
        cout << "#" << testCase << " " << minShuffle << endl;
    }
}




// debug
void testShuffleMachine(t_deck currentDeck, int deckLength) {
    cout << " debug ---------------------------------------- " << endl;
    cout << " 0 : "; printDeck(currentDeck, deckLength);
    for (int i = 1; i <= deckLength - 1; i++) {
        currentDeck = doShuffle(currentDeck, i, deckLength);
        cout << " " << i << " : "; printDeck(currentDeck, deckLength);
    }
}

void printDeck(t_deck currentDeck, int deckLength) {
    for (int i = 0; i < deckLength; i++)
        cout << currentDeck.card[i] << " ";
    cout << endl;
}







// check the deck whether it is in-order or not
// in-order means that the card could be in an ascending or descending order
bool isInOrder(t_deck cardDeck, int deckLength) {
    bool isAscending = true;
    bool isDescending = true;
    
    for (int i = 0; i < deckLength; i++) if (cardDeck.card[i] != i + 1) isAscending = false;
    for (int i = 0; i < deckLength; i++) if (cardDeck.card[i] != deckLength - i) isDescending = false;
    
    return (isAscending || isDescending);
}




// function to do the special shuffle-o-matic shuffle with (X = 1 .. N-1) as the parameters
// will return a copy of the shuffled deck 
t_deck doShuffle(t_deck currentDeck, int X, int deckLength) {
    int middle = (deckLength / 2);
    
    if (X <= middle) {

        int pos = middle - X;
        for (int j = 1; j <= X; j++) {
            int temp = currentDeck.card[pos];
            currentDeck.card[pos] = currentDeck.card[pos+1];
            currentDeck.card[pos+1] = temp;
            pos += 2;
        }

    } else {

        int pos = middle - (deckLength - X);
        for (int j = 1; j <= (deckLength - X); j++) {
            int temp = currentDeck.card[pos];
            currentDeck.card[pos] = currentDeck.card[pos+1];
            currentDeck.card[pos+1] = temp;
            pos += 2;
        }
   
    }
    
    return currentDeck;
}





// recursive function to find the minimum shuffle needed to make an in-order deck (DFS style)
// the currentDeck is a local (copy by value) state of the current (recursive stack of) card deck
// the minShuffle is a pointer to the (global) minimum shuffle needed to make an in-order deck. If this variable changes from it's initial state (-1) then an in-order deck is found!
void recursiveFind(int shuffleCount, t_deck currentDeck, int *minShuffle, int deckLength) {
    // check whether we already found an in-order deck on another recursive stack
    // and this shuffleCount is bigger than that (over the minimum). If yes then exit from the stack! 
    if ((*minShuffle != -1) && (shuffleCount > *minShuffle)) return;
    
    // if we already shuffle it more than 5 times, exit the recursive (hard limit stated by the problem)
    if (shuffleCount > 5) return;
    
    // if the current deck is already in-order (caused by the previous recursive-stack shuffling), change the minShuffle value and then exit the recursive!
    // (updating the minimum shuffle count needed to get an in-order deck
    if (isInOrder(currentDeck, deckLength)) {
        if (*minShuffle == -1) *minShuffle = shuffleCount; // if *minShuffle is still -1, then this is the 1st minimum shuffle count found!
        else if (*minShuffle > shuffleCount) *minShuffle = shuffleCount; // else compare it to the current shuffle count
        
        return;
    }
    
    // else we continue to shuffle these cards! (using the shuffle-o-matic machine)
    // and make new recursion using the shuffle result
    for (int i = 1; i < deckLength; i++) { // shuffling using x=1, x=2, .., x=N-1 as a parameters for the shuffle-o-matic machine
        currentDeck = doShuffle(currentDeck, i, deckLength);
        // debug, show current state of the deck
        //cout << shuffleCount << " : " << i << " | "; printDeck(currentDeck, deckLength); 
        recursiveFind(shuffleCount + 1, currentDeck, minShuffle, deckLength);
    }
}


