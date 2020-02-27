#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <bits/stdc++.h>
#include <list>
#include <vector>
#include <iterator>
#define ALPHABET_SIZE 256

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
        for (int j = 0; j < (int)positions[X[i]].size(); j++){
            //if (positions[X[i]][j] != -1)
            intermediate.push_back(positions[X[i]][j]);
        }
    }
    return intermediate;
}

// Utility function to print LIS
void printVector(vector<int>& arr)
{
    for (int x : arr)
        cout << x << " ";
    cout << endl;
}

/*determine the positions where the symbol appears in the second sequence*/
std::vector<std::vector<int>> countSort(int *Y, int m)
{
    int i;
    //initialize a vector of vectors size m
    std::vector<std::vector<int>> positions;

    for(i = 0; i<ALPHABET_SIZE; ++i){
        positions.push_back(std::vector<int>());
    }
    // Store count of each character
    for(i = 0; i < m; ++i){
        positions[Y[i]].push_back(i);
    }
    //descenting order
    for(i = 0; i<(int)positions.size(); ++i){
        sort(positions[i].begin(), positions[i].end(), greater<int>());
    }
    return positions;
}

/* Dynamic Programming C++ implementation of LIS problem */


// Binary search
int GetCeilIndex(std::vector<int> arr, vector<int>& T, int l, int r,
                 int key)
{
    while (r - l > 1) {
        int m = l + (r - l) / 2;
        if (arr[T[m]] >= key)
            r = m;
        else
            l = m;
    }

    return r;
}

int LSIS(std::vector<int> arr, int n)
{
    // Add boundary case, when array n is zero
    // Depend on smart pointers

    vector<int> tailIndices(n, 0); // Initialized with 0
    vector<int> prevIndices(n, -1); // initialized with -1

    int len = 1; // it will always point to empty location
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[tailIndices[0]]) {
            // new smallest value
            tailIndices[0] = i;
        }
        else if (arr[i] > arr[tailIndices[len - 1]]) {
            // arr[i] wants to extend largest subsequence
            prevIndices[i] = tailIndices[len - 1];
            tailIndices[len++] = i;
        }
        else {
            // arr[i] wants to be a potential condidate of
            // future subsequence
            // It will replace ceil value in tailIndices
            int pos = GetCeilIndex(arr, tailIndices, -1,
                                   len - 1, arr[i]);

            prevIndices[i] = tailIndices[pos - 1];
            tailIndices[pos] = i;
        }
    }

    vector<int> output;

    for (int i = tailIndices[len - 1]; i >= 0; i = prevIndices[i])
        output.push_back(arr[i]);

    sort(output.begin(), output.end());
    printVector(output);

    return len;
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
    cout << lcs[i] << " ";
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
    char filename[]="lab1.d.dat";
    int n,m,indicator;

    ifstream File;
    File.open(filename);
    File >> n >> m;
    cout << "Size of array: "<< n;
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
    for (int i = 0; i < n; i++)
    {
        cout << arr1[i] << " ";
    }
    cout << "\n";

    /* 1.b.1
    For each of the 256 alphabet symbols, determine the positions (descending order)
    where the symbol appears in the second sequence.
    Do not do 256 passes over the second sequence!(Think about counting sort)
    */
    //Complexity O(2*AlhabetSize + m)
    vector< vector<int> > pos = countSort(arr2, m);
    // Displaying the 2D vector
        // Store count of each character
    for (int i = 0; i < ALPHABET_SIZE; i++){
        if (pos[i].size() != 0){
            cout  << i << ": " ;
            for (int j = 0; j < (int)pos[i].size(); j++)
                cout << pos[i][j] << " ";
            cout << endl;
        }
    }
    /* 1.b.2
    Produce an intermediate sequence by replacingeach symbol in the first
    sequence by its positions from the second sequence
    */
    // Complexity O(mlogm)
    vector<int> intermediate = replaceSeq(arr1, pos, m);
    // Displaying the intermediate vector
    cout << "Intermediate Sequence\n";
    for (int i = 0; i < (int)intermediate.size(); i++)
         cout << intermediate[i] << " ";
    cout << "\n";
    /*1.b.3
    Compute a LSIS of the intermediate sequence
    */
    int k = intermediate.size();

    cout << "Longest Strictly Increasing Subsequence\n";
    // Complexity O()
    LSIS(intermediate, k );
    // Print the lcs
    //lcs(arr1, arr2, n, m);
    //printf("Length of LCS is %d\n", lcs(arr1, arr2, n, m));

    return 0;
}

