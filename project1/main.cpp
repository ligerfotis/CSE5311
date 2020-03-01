#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <bits/stdc++.h>
#include <list>
#include <vector>
#include <iterator>
#include <ctime>
#include <stack>
#include <set>
#include <map>
#include <math.h>
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

// Utility function to print vectors
void printVector(vector<int> arr, bool vertical = false)
{
    for (int x : arr){
        cout << x ;

        if (vertical)
            cout << endl;
        else
            cout << " ";
    }
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

/*
    Function to find Longest Increasing Subsequence in given array
    https://en.wikipedia.org/wiki/Longest_increasing_subsequence
*/
vector <int> LSIS(vector<int> arr, int n){
    vector<int> pred(n,-1);

    vector<int> tail(n+1, -1);

    int length = 0;
    for (int i = 0; i < n-1; i++){
        // Binary search for the largest positive j ≤ L
        // such that X[M[j]] <= X[i]
        int lo = 1;
        int hi = length;

        while (lo <=hi){
            int mid = ceil( (lo + hi)/2 );
            if ( arr[ tail[ mid] ] < arr[ i] )
                lo = mid+1;
            else
                hi = mid-1;
        }
        // After searching, lo is 1 greater than the
        // length of the longest prefix of X[i]
        int newL = lo;

        // The predecessor of X[i] is the last index of
        // the subsequence of length newL-1
        pred[i] = tail[newL - 1];
        tail[newL] = i;

        if (newL > length)
            // If we found a subsequence longer than any we've
            // found yet, update L
            length = newL;
    }
    // Reconstruct the longest increasing subsequence
    vector<int> seq;
    stack<int> s;

    int k = tail[length];
    // fill as tack to reverse the sequence
    for (int i = 0; i < length; i++){
        s.push(arr[k]);
        k = pred[k];
    }
    // the orders sequence
    while(!s.empty())
	{
		//cout << lis.top() << " ";
		seq.push_back(s.top());
		s.pop();
	}
    return seq;

}
vector<int> getLCSFromIndexes(vector<int> LSISseq, int *Y){

    vector<int> lcs2;

    for (int i = 0; i < (int)LSISseq.size(); i++)
        lcs2.push_back(Y[LSISseq[i]]);

    return lcs2;
}


/* Returns length of LCS for X[0..m-1], Y[0..n-1] */
vector<int> lcs( int *X, int *Y, int m, int n )
{
    //int L[m + 1][n + 1];
    // Create a vector containing n
    //vectors of size m.
    vector<vector<int> > L( n+1, vector<int> (m+1, 0));
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

   // Create a vector to store the lcs string
   vector<int>  lcsSeq( index, -1); // Set the terminating character

   // Start from the right-most-bottom-most corner and
   // one by one store characters in lcs[]
   i = m, j = n;
   while (i > 0 && j > 0)
   {
      // If current character in X[] and Y are same, then
      // current character is part of LCS
      if (X[i-1] == Y[j-1])
      {
          lcsSeq[index-1] = X[i-1]; // Put current character in result
          i--; j--; index--;     // reduce values of i, j and index
      }

      // If not same, then find the larger of two and
      // go in the direction of larger value
      else if (L[i-1][j] > L[i][j-1])
         i--;
      else
         j--;
   }

    return lcsSeq;
}
/* Utility function to get max of 2 integers */
int max(int a, int b)
{
    return (a > b)? a : b;
}
/* Driver program to test above function */
int main(int argc, char** argv)
{
    /* Time function returns the time since the
        Epoch(jan 1 1970). Returned time is in seconds. */
    clock_t start_time, end_time;
    char filename[]="lab1.e.dat";
    ifstream File;
    if (argc > 1){
      cout << "Filename: " << argv[1] << endl;
      File.open((argv[1]));
    }
    else
        File.open(filename);


    int n,m,indicator;

    File >> n >> m;
    //cout << "Size of array: "<< n << endl;
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
    /* 1.a
        Matrix Method
    */
    float time_matrix_LCS;
    float time_LSIS_LCS;

    start_time = clock();
    vector <int> lcs1 = lcs(arr1, arr2, n, m);
    cout << "Matrix LCS length:" << (int)lcs1.size();
    end_time = clock();
    time_matrix_LCS = float(end_time - start_time) / float(CLOCKS_PER_SEC);
//    cout << "CPU : " << fixed
//         << time_matrix_LCS << setprecision(3);
//    cout << " sec " << endl;

    /* 1.b.1
    For each of the 256 alphabet symbols, determine the positions (descending order)
    where the symbol appears in the second sequence.
    Do not do 256 passes over the second sequence!(Think about counting sort)
    */
    start_time = clock();
    //Complexity O(2*AlhabetSize + m)
    vector< vector<int> > pos = countSort(arr2, m);

    /* 1.b.2
    Produce an intermediate sequence by replacingeach symbol in the first
    sequence by its positions from the second sequence
    */

    // Complexity O(mlogm)
    vector<int> intermediate = replaceSeq(arr1, pos, m);

    int k = intermediate.size();
    //cout << "LSISinputLength: " << k<< endl;

    /*1.b.3
    Compute a LSIS of the intermediate sequence
    https://www.techiedelight.com/longest-increasing-subsequence/
    */
    vector<int> LSISseq = LSIS(intermediate, k);
    //printVector(LSISseq);
    //int len = LSIS(intermediate, k);
    //cout << "LSIS length: " << len << endl;
    //cout << "LSIS LCS length: " << printLIS(intermediate);
    end_time = clock();
    time_LSIS_LCS = float(end_time - start_time) / float(CLOCKS_PER_SEC);


    /*1.b.4
    The sequence of values from the LSIS may be used
    as indexes to the second sequence to obtain an LCS.
    */
    vector<int> lcs2  = getLCSFromIndexes(LSISseq, arr2);
    cout << "LSIS LCS length: " << (int)lcs2.size() << endl;

    bool identical = std::equal(lcs1.begin(), lcs1.end(), lcs2.begin());
    if (identical)
        printVector(lcs1,true);
    cout << -1 << endl;
    /*
    Print CPU times
    */
    cout << "CPU Matrix LCS: " << fixed
         << time_matrix_LCS << setprecision(3);
    cout << " sec ";
    cout << "CPU Matrix LCS: " << fixed
         << time_LSIS_LCS << setprecision(3);
    cout << " sec " << endl;

    //printVector(lcs2, false);

    return 0;
}

