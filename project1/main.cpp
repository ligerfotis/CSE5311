#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <bits/stdc++.h>

using namespace std;

/* Code of functions based on GeeksforGeeks tutorial
    https://www.geeksforgeeks.org/longest-increasing-subsequence-dp-3/
*/
int max(int a, int b);

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
    // Following code is used to print LCS
    int index = L[m][n];

    // Create a character array to store the lcs string
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
    cout << "LCS is ";
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
    char* filename="lab1.a.dat";
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


    printf("Length of LCS is %d\n", lcs(arr1, arr2, n, m));

    return 0;
}

