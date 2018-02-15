/*

Reservoir sampling is a family of randomized algorithms for randomly choosing k samples from a list of n items, where n is either a very large or unknown number. Typically n is large enough that the list doesn’t fit into main memory. For example, a list of search queries in Google and Facebook.

So we are given a big array (or stream) of numbers (to simplify), and we need to write an efficient function to randomly select k numbers where 1 <= k <= n. Let the input array be stream[].

A simple solution is to create an array reservoir[] of maximum size k. One by one randomly select an item from stream[0..n-1]. If the selected item is not previously selected, then put it in reservoir[]. To check if an item is previously selected or not, we need to search the item in reservoir[]. The time complexity of this algorithm will be O(k^2). This can be costly if k is big. Also, this is not efficient if the input is in the form of a stream.

It can be solved in O(n) time. The solution also suits well for input in the form of stream. The idea is similar to this post. Following are the steps.

1) Create an array reservoir[0..k-1] and copy first k items of stream[] to it.
2) Now one by one consider all items from (k+1)th item to nth item.
…a) Generate a random number from 0 to i where i is index of current item in stream[]. Let the generated random number is j.
…b) If j is in range 0 to k-1, replace reservoir[j] with arr[i]

Following is C implementation of the above algorithm.
*/

// An efficient program to randomly select k items from a stream of items
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
// A utility function to print an array
void printArray(int stream[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", stream[i]);
    printf("\n");
}
 
// A function to randomly select k items from stream[0..n-1].
void selectKItems(int stream[], int n, int k)
{
    int i;  // index for elements in stream[]
 
    // reservoir[] is the output array. Initialize it with
    // first k elements from stream[]
    int reservoir[k];
    for (i = 0; i < k; i++)
        reservoir[i] = stream[i];
 
    // Use a different seed value so that we don't get
    // same result each time we run this program
    srand(time(NULL));
 
    // Iterate from the (k+1)th element to nth element
    for (; i < n; i++)
    {
        // Pick a random index from 0 to i.
        int j = rand() % (i+1);
 
        // If the randomly  picked index is smaller than k, then replace
        // the element present at the index with new element from stream
        if (j < k)
          reservoir[j] = stream[i];
    }
 
    printf("Following are k randomly selected items \n");
    printArray(reservoir, k);
}
 
// Driver program to test above function.
int main()
{
    int stream[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int n = sizeof(stream)/sizeof(stream[0]);
    int k = 5;
    selectKItems(stream, n, k);
    return 0;
}
