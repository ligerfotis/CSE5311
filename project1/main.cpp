#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <bits/stdc++.h>
#include <list>
#include <vector>
#include <iterator>
#define RANGE 255

using namespace std;


/* Code of functions based on GeeksforGeeks tutorial
    https://www.geeksforgeeks.org/longest-increasing-subsequence-dp-3/
*/
int max(int a, int b);
/*Produce an intermediate sequence by replacingeach symbol in the first
sequence by its positions from the second sequence */
vector<int> replaceSeq(int *X, vector<vector<int> > positions, int m){
    vector<int> intermediate;
    for (int i = 0; i < m; i++){
        for (int j = 0; j < m; j++){
            if (positions[X[i]-1][j] != -1)
                intermediate.push_back(positions[X[i]-1][j]);
        }
    }
    return intermediate;
}


//initialize a vector of vectors size m
vector<vector<int> > positions;
/*determine the positions where the symbol appears in the second sequence*/
vector< vector<int> >& countSort(int *Y, int m)
{
    // Create a count array to store count of inidividul
    // characters and initialize count array as 0
    int count[RANGE + 1], i;
    memset(count, 0, sizeof(count));

    vector<int> vec1(m,-1);

    for(i = 0; i<m; ++i){
        positions.push_back(vec1);
    }
    // Store count of each character
    for(i = 0; i<m; ++i){
        ++count[Y[i]];
        for (int j=0; j<m;j++){
            if (positions[Y[i]-1][j] != -1)
                continue;
            else{
                positions[Y[i]-1][j] = i;
                break;
            }
        }
    }
    //descenting order
    for(i = 0; i<m; ++i){
        sort(positions[Y[i]].begin(), positions[Y[i]].end(), greater<int>());
    }
    return positions;
}

/* Dynamic Programming C++ implementation of LIS problem */

// Utility function to print LIS
void printVector(vector<int>& arr)
{
    for (int x : arr)
        cout << x << " ";
    cout << endl;
}
// Function to construct and print Longest Increasing
// Subsequence
void constructPrintLIS(vector<int> vec, int n)
{
    // L[i] - The longest increasing sub-sequence
    // ends with vec[i]
    vector<vector<int> > L(n);

    // L[0] is equal to vec[0]
    L[0].push_back(vec[0]);

    // start from index 1
    for (int i = 1; i < n; i++)
    {
        // do for every j less than i
        for (int j = 0; j < i; j++)
        {
            /* L[i] = {Max(L[j])} + vec[i]
            where j < i and vec[j] < vec[i] */
            if ((vec[i] > vec[j]) &&
                    (L[i].size() < L[j].size() + 1))
                L[i] = L[j];
        }

        // L[i] ends with vec[i]
        L[i].push_back(vec[i]);
    }

    // L[i] now stores increasing sub-sequence of
    // vec[0..i] that ends with vec[i]
    vector<int> max = L[0];

    // LIS will be max of all increasing sub-
    // sequences of vec
    for (vector<int> x : L)
        if (x.size() > max.size())
            max = x;

    // max will contain LIS
    printVector(max);
}
/* Returns length of LCS for X[0..m-1], Y[0..n-1] */
int lcs( int *X, int *Y, int m, int n )
{
    int L[m + 1][n + 1];
    int i, j;

    /* Following steps build L[m+1][n+1] in
       bottom up fashion. Note that L[i][j]
       contains length of LCS of X[0..i-1]
       and Y[0..j-1] */
    for (i = 0; i <= m; i++)
    {
        for (j = 0; j <= n; j++)
        {
        if (i == 0 || j == 0)
            L[i][j] = 0;

        else if (X[i - 1] == Y[j - 1])
            L[i][j] = L[i - 1][j - 1] + 1;

        else
            L[i][j] = max(L[i - 1][j], L[i][j - 1]);
        }
    }
    // Following code is used to print LCS and store positions where the symbol appears in the second sequence
    int index = L[m][n];

    // Create a integer array to store the lcs string
    int lcs[index+1];
    lcs[index] = '\0'; // Set the terminating character

    // Start from the right-most-bottom-most corner and
    // one by one store characters in lcs[]
    i = m;
    j = n;
    while (i > 0 && j > 0)
    {
      // If current character in X[] and Y are same, then
      // current character is part of LCS
      if (X[i-1] == Y[j-1])
      {
          lcs[index-1] = X[i-1]; // Put current character in result
                                //store the position of the character
          i--; j--; index--;     // reduce values of i, j and index
      }

      // If not same, then find the larger of two and
      // go in the direction of larger value
      else if (L[i-1][j] > L[i][j-1])
         i--;
      else
         j--;
    }

    // Print the lcs
    cout << "Longest Common Subsequence\n";
    for (int i =0; i< L[m][n]; i++){
    cout << lcs[i];
    }
    cout << "\n";

    /* L[m][n] contains length of LCS
    for X[0..n-1] and Y[0..m-1] */
    return L[m][n];
}

/* Utility function to get max of 2 integers */
int max(int a, int b)
{
    return (a > b)? a : b;
}


/* Driver program to test above function */
int main()
{
    char* filename="lab1.b.dat";
    int n,m,indicator;

    ifstream File;
    File.open(filename);
    File >> n >> m;
    cout << "Size of 1st array: "<< n << "\nSize of 2nd array: "<< m;
    int arr1[n];
    int arr2[m];
    //assess m=n
    for(int i=0; i<n; i++)
    {
        File >> arr1[i];
    }
    File >> indicator;
    for(int i=0; i<m; i++)
    {
        File >> arr2[i];
    }
    File.close();
    cout << "\n";


    /* 1.b.1
    For each of the 256 alphabet symbols, determine the positions (descending order)
    where the symbol appears in the second sequence.
    Do not do 256 passes over the second sequence!(Think about counting sort)
    */

    vector<vector<int> > pos = countSort(arr2, m);
    // Displaying the 2D vector
    for (int i = 0; i < m; i++)
    {
        if (std::count(pos[i].begin(), pos[i].end(), -1) != m){
            cout << i <<": ";
            for (int j = 0; j < m; j++)
            {
                if (pos[i][j] != -1)
                    cout << pos[i][j];
            }
            cout << "\n";
        }
    }

    /* 1.b.2
    Produce an intermediate sequence by replacingeach symbol in the first
    sequence by its positions from the second sequence
    */

    vector<int> intermediate = replaceSeq(arr1, pos, m);
    // Displaying the intermediate vector
    cout << "Intermediate Sequence\n";
    for (int i = 0; i < (int)intermediate.size(); i++)
         cout << intermediate[i];
    cout << "\n";

    /*1.b.3
    Compute a LSIS of the intermediate sequence
    */
    int k = intermediate.size();
    cout << "Longest Strictly Increasing Subsequence\n";
    constructPrintLIS( intermediate, k );
    // Print the lcs
    lcs(arr1, arr2, n, m);
    //printf("Length of LCS is %d\n", lcs(arr1, arr2, n, m));

    return 0;
}

