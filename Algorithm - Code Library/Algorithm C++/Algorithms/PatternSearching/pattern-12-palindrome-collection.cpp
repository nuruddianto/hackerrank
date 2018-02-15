// 1 : Recursive program to check if a given linked list is palindrome
// ===================================================================

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 
/* Link list node */
struct node
{
    char data;
    struct node* next;
};
 
// Initial parameters to this function are &head and head
bool isPalindromeUtil(struct node **left, struct  node *right)
{
   /* stop recursion when right becomes NULL */
   if (right == NULL)
      return true;
 
   /* If sub-list is not palindrome then no need to
       check for current left and right, return false */
   bool isp = isPalindromeUtil(left, right->next);
   if (isp == false)
      return false;
 
   /* Check values at current left and right */
   bool isp1 = (right->data == (*left)->data);
 
   /* Move left to next node */
   *left = (*left)->next;
 
   return isp1;
}
 
// A wrapper over isPalindromeUtil()
bool isPalindrome(struct node *head)
{
   isPalindromeUtil(&head, head);
}
 
/* Push a node to linked list. Note that this function
  changes the head */
void push(struct node** head_ref, char new_data)
{
    /* allocate node */
    struct node* new_node =
            (struct node*) malloc(sizeof(struct node));
 
    /* put in the data  */
    new_node->data  = new_data;
 
    /* link the old list off the new node */
    new_node->next = (*head_ref);
 
    /* move the head to pochar to the new node */
    (*head_ref)    = new_node;
}
 
// A utility function to print a given linked list
void printList(struct node *ptr)
{
    while (ptr != NULL)
    {
        printf("%c->", ptr->data);
        ptr = ptr->next;
    }
    printf("NULL\n");
}
 
/* Drier program to test above function*/
int main()
{
    /* Start with the empty list */
    struct node* head = NULL;
    char str[] = "abacaba";
    int i;
 
    for (i = 0; str[i] != '\0'; i++)
    {
       push(&head, str[i]);
       printList(head);
       isPalindrome(head)? printf("Is Palindrome\n\n"):
                           printf("Not Palindrome\n\n");
    }
 
    return 0;
}


// 2: Dynamic Programming Solution for Palindrome Partitioning Problem
// ===================================================================

#include <stdio.h>
#include <string.h>
#include <limits.h>
  
// A utility function to get minimum of two integers
int min (int a, int b) { return (a < b)? a : b; }
  
// Returns the minimum number of cuts needed to partition a string
// such that every part is a palindrome
int minPalPartion(char *str)
{
    // Get the length of the string
    int n = strlen(str);
  
    /* Create two arrays to build the solution in bottom up manner
       C[i][j] = Minimum number of cuts needed for palindrome partitioning
                 of substring str[i..j]
       P[i][j] = true if substring str[i..j] is palindrome, else false
       Note that C[i][j] is 0 if P[i][j] is true */
    int C[n][n];
    bool P[n][n];
  
    int i, j, k, L; // different looping variables
  
    // Every substring of length 1 is a palindrome
    for (i=0; i<n; i++)
    {
        P[i][i] = true;
        C[i][i] = 0;
    }
  
    /* L is substring length. Build the solution in bottom up manner by
       considering all substrings of length starting from 2 to n.
       The loop structure is same as Matrx Chain Multiplication problem (
       See http://www.geeksforgeeks.org/archives/15553 )*/
    for (L=2; L<=n; L++)
    {
        // For substring of length L, set different possible starting indexes
        for (i=0; i<n-L+1; i++)
        {
            j = i+L-1; // Set ending index
  
            // If L is 2, then we just need to compare two characters. Else
            // need to check two corner characters and value of P[i+1][j-1]
            if (L == 2)
                P[i][j] = (str[i] == str[j]);
            else
                P[i][j] = (str[i] == str[j]) && P[i+1][j-1];
  
            // IF str[i..j] is palindrome, then C[i][j] is 0
            if (P[i][j] == true)
                C[i][j] = 0;
            else
            {
                // Make a cut at every possible localtion starting from i to j,
                // and get the minimum cost cut.
                C[i][j] = INT_MAX;
                for (k=i; k<=j-1; k++)
                    C[i][j] = min (C[i][j], C[i][k] + C[k+1][j]+1);
            }
        }
    }
  
    // Return the min cut value for complete string. i.e., str[0..n-1]
    return C[0][n-1];
}
  
// Driver program to test above function
int main()
{
   char str[] = "ababbbabbababa";
   printf("Min cuts needed for Palindrome Partitioning is %d",
           minPalPartion(str));
   return 0;
}


// 3: C program for online algorithm for palindrome checking
// ===================================================================

#include<stdio.h>
#include<string.h>
 
// d is the number of characters in input alphabet
#define d 256
 
// q is a prime number used for evaluating Rabin Karp's Rolling hash
#define q 103
 
void checkPalindromes(char str[])
{
    // Length of input string
    int N = strlen(str);
 
    // A single character is always a palindrome
    printf("%c Yes\n", str[0]);
 
    // Return if string has only one character
    if (N == 1) return;
 
    // Initialize first half reverse and second half for 
    // as firstr and second characters
    int firstr  = str[0] % q;
    int second = str[1] % q;
 
    int h = 1, i, j;
 
    // Now check for palindromes from second character
    // onward
    for (i=1; i<N; i++)
    {
        // If the hash values of 'firstr' and 'second' 
        // match, then only check individual characters
        if (firstr == second)
        {
            /* Check if str[0..i] is palindrome using
               simple character by character match */
            for (j = 0; j < i/2; j++)
            {
                if (str[j] != str[i-j])
                    break;
            }
            (j == i/2)?  printf("%c Yes\n", str[i]):
            printf("%c No\n", str[i]);
        }
        else printf("%c No\n", str[i]);
 
        // Calculate hash values for next iteration.
        // Don't calculate hash for next characters if
        // this is the last character of string
        if (i != N-1)
        {
            // If i is even (next i is odd) 
            if (i%2 == 0)
            {
                // Add next character after first half at beginning 
                // of 'firstr'
                h = (h*d) % q;
                firstr  = (firstr + h*str[i/2])%q;
                 
                // Add next character after second half at the end
                // of second half.
                second = (second*d + str[i+1])%q;
            }
            else
            {
                // If next i is odd (next i is even) then we
                // need not to change firstr, we need to remove
                // first character of second and append a
                // character to it.
                second = (d*(second + q - str[(i+1)/2]*h)%q
                          + str[i+1])%q;
            }
        }
    }
}
 
/* Driver program to test above function */
int main()
{
    char *txt = "aabaacaabaa";
    checkPalindromes(txt);
    getchar();
    return 0;
}

// 4: Given a number, find the next smallest palindrome
// ===================================================================


#include <stdio.h>
 
// A utility function to print an array
void printArray (int arr[], int n);
 
// A utility function to check if num has all 9s
int AreAll9s (int num[], int n );
 
// Returns next palindrome of a given number num[].
// This function is for input type 2 and 3
void generateNextPalindromeUtil (int num[], int n )
{
    // find the index of mid digit
    int mid = n/2;
 
    // A bool variable to check if copy of left side to right is sufficient or not
    bool leftsmaller = false;
 
    // end of left side is always 'mid -1'
    int i = mid - 1;
 
    // Begining of right side depends if n is odd or even
    int j = (n % 2)? mid + 1 : mid;
 
   // Initially, ignore the middle same digits 
    while (i >= 0 && num[i] == num[j])
        i--,j++;
 
    // Find if the middle digit(s) need to be incremented or not (or copying left 
    // side is not sufficient)
    if ( i < 0 || num[i] < num[j])
        leftsmaller = true;
 
    // Copy the mirror of left to tight
    while (i >= 0)
    {
        num[j] = num[i];
        j++;
        i--;
    }
 
    // Handle the case where middle digit(s) must be incremented. 
    // This part of code is for CASE 1 and CASE 2.2
    if (leftsmaller == true)
    {
        int carry = 1;
        i = mid - 1;
 
        // If there are odd digits, then increment
        // the middle digit and store the carry
        if (n%2 == 1)
        {
            num[mid] += carry;
            carry = num[mid] / 10;
            num[mid] %= 10;
            j = mid + 1;
        }
        else
            j = mid;
 
        // Add 1 to the rightmost digit of the left side, propagate the carry 
        // towards MSB digit and simultaneously copying mirror of the left side 
        // to the right side.
        while (i >= 0)
        {
            num[i] += carry;
            carry = num[i] / 10;
            num[i] %= 10;
            num[j++] = num[i--]; // copy mirror to right
        }
    }
}
 
// The function that prints next palindrome of a given number num[]
// with n digits.
void generateNextPalindrome( int num[], int n )
{
    int i;
 
    printf("\nNext palindrome is:\n");
 
    // Input type 1: All the digits are 9, simply o/p 1
    // followed by n-1 0's followed by 1.
    if( AreAll9s( num, n ) )
    {
        printf( "1 ");
        for( i = 1; i < n; i++ )
            printf( "0 " );
        printf( "1" );
    }
 
    // Input type 2 and 3
    else
    {
        generateNextPalindromeUtil ( num, n );
 
        // print the result
        printArray (num, n);
    }
}
 
// A utility function to check if num has all 9s
int AreAll9s( int* num, int n )
{
    int i;
    for( i = 0; i < n; ++i )
        if( num[i] != 9 )
            return 0;
    return 1;
}
 
/* Utility that prints out an array on a line */
void printArray(int arr[], int n)
{
    int i;
    for (i=0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
 
// Driver Program to test above function
int main()
{
    int num[] = {9, 4, 1, 8, 7, 9, 7, 8, 3, 2, 2};
 
    int n = sizeof (num)/ sizeof(num[0]);
 
    generateNextPalindrome( num, n );
 
    return 0;
}



// 5: A Naive recursive program to find minimum number insertions
// needed to make a string palindrome
// ===================================================================

#include <stdio.h>
#include <limits.h>
#include <string.h>
 
// A utility function to find minimum of two numbers
int min(int a, int b)
{  return a < b ? a : b; }
 
// Recursive function to find minimum number of insersions
int findMinInsertions(char str[], int l, int h)
{
    // Base Cases
    if (l > h) return INT_MAX;
    if (l == h) return 0;
    if (l == h - 1) return (str[l] == str[h])? 0 : 1;
 
    // Check if the first and last characters are same. On the basis of the
    // comparison result, decide which subrpoblem(s) to call
    return (str[l] == str[h])? findMinInsertions(str, l + 1, h - 1):
                               (min(findMinInsertions(str, l, h - 1),
                                   findMinInsertions(str, l + 1, h)) + 1);
}
 
// Driver program to test above functions
int main()
{
    char str[] = "geeks";
    printf("%d", findMinInsertions(str, 0, strlen(str)-1));
    return 0;
}


// 6: C++ program to find all distinct palindrome sub-strings
// of a given string
// ===================================================================

#include <iostream>
#include <map>
using namespace std;
 
// Function to print all distinct palindrome sub-strings of s
void palindromeSubStrs(string s)
{
    map<string, int> m;
    int n = s.size();
 
    // table for storing results (2 rows for odd-
    // and even-length palindromes
    int R[2][n+1];
 
    // Find all sub-string palindromes from the given input
    // string insert 'guards' to iterate easily over s
    s = "@" + s + "#";
 
    for (int j = 0; j <= 1; j++)
    {
        int rp = 0;   // length of 'palindrome radius'
        R[j][0] = 0;
 
        int i = 1;
        while (i <= n)
        {
            //  Attempt to expand palindrome centered at i
            while (s[i - rp - 1] == s[i + j + rp])
                rp++;  // Incrementing the length of palindromic
                       // radius as and when we find vaid palindrome
 
            // Assigning the found palindromic length to odd/even
            // length array
            R[j][i] = rp;
            int k = 1;
            while ((R[j][i - k] != rp - k) && (k < rp))
            {
                R[j][i + k] = min(R[j][i - k],rp - k);
                k++;
            }
            rp = max(rp - k,0);
            i += k;
        }
    }
 
    // remove 'guards'
    s = s.substr(1, n);
 
    // Put all obtained palindromes in a hash map to
    // find only distinct palindromess
    m[string(1, s[0])]=1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= 1; j++)
            for (int rp = R[j][i]; rp > 0; rp--)
               m[s.substr(i - rp - 1, 2 * rp + j)]=1;
        m[string(1, s[i])]=1;
    }
 
    //printing all distinct palindromes from hash map
   cout << "Below are " << m.size()-1
        << " palindrome sub-strings";
   map<string, int>::iterator ii;
   for (ii = m.begin(); ii!=m.end(); ++ii)
      cout << (*ii).first << endl;
}
 
// Driver program
int main()
{
    palindromeSubStrs("abaaa");
    return 0;
}


// 7: A dynamic programming solution for longest palindr.
// This code is adopted from following link
// http://www.leetcode.com/2011/11/longest-palindromic-substring-part-i.html
// ===================================================================

 
#include <stdio.h>
#include <string.h>
 
// A utility function to print a substring str[low..high]
void printSubStr( char* str, int low, int high )
{
    for( int i = low; i <= high; ++i )
        printf("%c", str[i]);
}
 
// This function prints the longest palindrome substring
// of str[].
// It also returns the length of the longest palindrome
int longestPalSubstr( char *str )
{
    int n = strlen( str ); // get length of input string
 
    // table[i][j] will be false if substring str[i..j]
    // is not palindrome.
    // Else table[i][j] will be true
    bool table[n][n];
    memset(table, 0, sizeof(table));
 
    // All substrings of length 1 are palindromes
    int maxLength = 1;
    for (int i = 0; i < n; ++i)
        table[i][i] = true;
 
    // check for sub-string of length 2.
    int start = 0;
    for (int i = 0; i < n-1; ++i)
    {
        if (str[i] == str[i+1])
        {
            table[i][i+1] = true;
            start = i;
            maxLength = 2;
        }
    }
 
    // Check for lengths greater than 2. k is length
    // of substring
    for (int k = 3; k <= n; ++k)
    {
        // Fix the starting index
        for (int i = 0; i < n-k+1 ; ++i)
        {
            // Get the ending index of substring from
            // starting index i and length k
            int j = i + k - 1;
 
            // checking for sub-string from ith index to
            // jth index iff str[i+1] to str[j-1] is a
            // palindrome
            if (table[i+1][j-1] && str[i] == str[j])
            {
                table[i][j] = true;
 
                if (k > maxLength)
                {
                    start = i;
                    maxLength = k;
                }
            }
        }
    }
 
    printf("Longest palindrome substring is: ");
    printSubStr( str, start, start + maxLength - 1 );
 
    return maxLength; // return length of LPS
}
 
// Driver program to test above functions
int main()
{
    char str[] = "forgeeksskeegfor";
    printf("\nLength is: %d\n", longestPalSubstr( str ) );
    return 0;
}

// 8: Check if a given string is a rotation of a palindrome
// ===================================================================


#include<iostream>
#include<string>
using namespace std;
 
// A utility function to check if a string str is palindrome
bool isPalindrome(string str)
{
    // Start from leftmost and rightmost corners of str
    int l = 0;
    int h = str.length() - 1;
 
    // Keep comparing characters while they are same
    while (h > l)
        if (str[l++] != str[h--])
            return false;
 
    // If we reach here, then all characters were matching
    return true;
}
 
// Function to chech if a given string is a rotation of a
// palindrome.
bool isRotationOfPalindrome(string str)
{
   // If string iteself is palindrome
   if (isPalindrome(str))
         return true;
 
   // Now try all rotations one by one
   int n = str.length();
   for (int i = 0; i < n-1; i++)
   {
       string str1 = str.substr(i+1, n-i-1);
       string str2 = str.substr(0, i+1);
 
       // Check if this rotation is palindrome
       if (isPalindrome(str1.append(str2)))
          return true;
   }
   return false;
}
 
// Driver program to test above function
int main()
{
    cout << isRotationOfPalindrome("aab") << endl;
    cout << isRotationOfPalindrome("abcde") << endl;
    cout << isRotationOfPalindrome("aaaad") << endl;
    return 0;
}

// 9: A recursive C++ program to check whether a given number is
// palindrome or not
// ===================================================================


#include <stdio.h>
 
// A function that reurns true only if num contains one digit
int oneDigit(int num)
{
    // comparison operation is faster than division operation.
    // So using following instead of "return num / 10 == 0;"
    return (num >= 0 && num < 10);
}
 
// A recursive function to find out whether num is palindrome
// or not. Initially, dupNum contains address of a copy of num.
bool isPalUtil(int num, int* dupNum)
{
    // Base case (needed for recursion termination): This statement
    // mainly compares the first digit with the last digit
    if (oneDigit(num))
        return (num == (*dupNum) % 10);
 
    // This is the key line in this method. Note that all recursive
    // calls have a separate copy of num, but they all share same copy
    // of *dupNum. We divide num while moving up the recursion tree
    if (!isPalUtil(num/10, dupNum))
        return false;
 
    // The following statements are executed when we move up the
    // recursion call tree
    *dupNum /= 10;
 
    // At this point, if num%10 contains i'th digit from beiginning,
    // then (*dupNum)%10 contains i'th digit from end
    return (num % 10 == (*dupNum) % 10);
}
 
// The main function that uses recursive function isPalUtil() to
// find out whether num is palindrome or not
int isPal(int num)
{
    // If num is negative, make it positive
    if (num < 0)
       num = -num;
 
    // Create a separate copy of num, so that modifications made
    // to address dupNum don't change the input number.
    int *dupNum = new int(num); // *dupNum = num
 
    return isPalUtil(num, dupNum);
}
 
// Driver program to test above functions
int main()
{
    int n = 12321;
    isPal(n)? printf("Yes\n"): printf("No\n");
 
    n = 12;
    isPal(n)? printf("Yes\n"): printf("No\n");
 
    n = 88;
    isPal(n)? printf("Yes\n"): printf("No\n");
 
    n = 8999;
    isPal(n)? printf("Yes\n"): printf("No\n");
    return 0;
}


// 10: C Program to Check if a Given String is Palindrome
// ===================================================================

#include <stdio.h>
#include <string.h>
 
// A function to check if a string str is palindrome
void isPalindrome(char str[])
{
    // Start from leftmost and rightmost corners of str
    int l = 0;
    int h = strlen(str) - 1;
 
    // Keep comparing characters while they are same
    while (h > l)
    {
        if (str[l++] != str[h--])
        {
            printf("%s is Not Palindrome\n", str);
            return;
        }
    }
    printf("%s is palindrome\n", str);
}
 
// Driver program to test above function
int main()
{
    isPalindrome("abba");
    isPalindrome("abbccbba");
    isPalindrome("geeks");
    return 0;
}

// 11: Check if characters of a given string can be rearranged to form a palindrome
// ================================================================================

#include <iostream>
using namespace std;
#define NO_OF_CHARS 256
 
/* function to check whether characters of a string can form 
   a palindrome */
bool canFormPalindrome(char *str)
{
    // Create a count array and initialize all values as 0
    int count[NO_OF_CHARS] = {0};
 
    // For each character in input strings, increment count in
    // the corresponding count array
    for (int i = 0; str[i];  i++)
        count[str[i]]++;
 
    // Count odd occurring characters
    int odd = 0;
    for (int i = 0; i < NO_OF_CHARS; i++)
        if (count[i] & 1)
            odd++;
     
    // Return true if odd count is 0 or 1, otherwise false
    return (odd <= 1);
}
 
/* Driver program to test to pront printDups*/
int main()
{
  canFormPalindrome("geeksforgeeks")? cout << "Yes\n": 
                                     cout << "No\n";
  canFormPalindrome("geeksogeeks")? cout << "Yes\n": 
                                    cout << "No\n";
  return 0;
}



// 11: C++ Program to print all palindromes in a given range
// ================================================================================

#include<iostream>
using namespace std;
 
// A function to check if n is palindrome
int isPalindrome(int n)
{
    // Find reverse of n
    int rev = 0;
    for (int i = n; i > 0; i /= 10)
        rev = rev*10 + i%10;
 
    // If n and rev are same, then n is palindrome
    return (n==rev);
}
 
// prints palindrome between min and max
void countPal(int min, int max)
{
    for (int i = min; i <= max; i++)
        if (isPalindrome(i))
          cout << i << " ";
}
 
// Driver program to test above function
int main()
{
    countPal(100, 2000);
    return 0;
}
