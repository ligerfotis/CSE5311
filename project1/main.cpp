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

// Data structure to store an element and its index in the array
struct Node
{
	int elem;
	int index;
};

// overload compare operator for inserting into set
inline bool operator<(const Node& lhs, const Node& rhs)
{
	return lhs.elem < rhs.elem;
}

// Function to print LIS using parent array
void print(vector<int> input, map<int,int> parent, set<Node> S)
{
	// container to store LIS in reverse order
	stack<int> lis;

	// start from the last element of S
	int index = S.rbegin()->index;

	// get length of LIS
	int n = S.size();

	// retrieve LIS from parent array
	while (n--)
	{
		lis.push(input[index]);
		index = parent[index];
	}

	// print LIS
	cout << "LIS is ";
	while(!lis.empty())
	{
		cout << lis.top() << " ";
		lis.pop();
	}
}

// Function to find Longest Increasing Subsequence in given array
void printLIS(vector<int> arr, int n)
{
	// create an empty ordered set S (ith element in S is defined as the
	// smallest integer that ends an increasing sequence of length i)
	set<Node> S;

	// parent[i] will store the predecessor of element with index i in the
	// LIS ending at element with index i
	map<int, int> parent;

	// process every element one by one
	for (int i = 0; i < n; i++)
	{
		// construct node from current element and its index
		Node curr = {arr[i], i};

		// ignore the current element if already present in the set
		if (S.find(curr) != S.end()) {
			continue;
		}

		// insert current node into the set and get iterator to the
		// inserted node
		auto it = S.insert(curr).first;

		// if the node is not inserted at the end, then delete the next node
		if (++it != S.end())
			S.erase(it);

		// get iterator to the current node and update parent
		it = S.find(curr);
		parent[i] = (--it)->index;
	}

	// print LIS using parent map
	print(arr, parent, S);
}
/* Dynamic Programming C++ implementation of LCS problem */
int max(int a, int b);

/* Returns length of LCS for X[0..m-1], Y[0..n-1] */
int lcs( int *X, int *Y, int m, int n )
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
    /* Time function returns the time since the
        Epoch(jan 1 1970). Returned time is in seconds. */
    clock_t start_time, end_time;
    char filename[]="lab1.a.dat";
    int n,m,indicator;

    ifstream File;
    File.open(filename);
    File >> n >> m;
    cout << "Size of array: "<< n << endl;
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
    float time_taken;
    /*
    start_time = clock();
    printf("Matrix LCS length: %d ", lcs(arr1, arr2, n, m));
    end_time = clock();
    time_taken = float(end_time - start_time) / float(CLOCKS_PER_SEC);
    cout << "CPU : " << fixed
         << time_taken << setprecision(3);
    cout << " sec " << endl;
*/
//    cout << "\n";
//    for (int i = 0; i < n; i++)
//    {
//        cout << arr1[i] << " ";
//    }
//    cout << "\n";

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
    cout << "LSISinputLength: " << k;
    end_time = clock();
    time_taken = float(end_time - start_time) / float(CLOCKS_PER_SEC);
    cout << " CPU : " << fixed
         << time_taken << setprecision(3);
    cout << " sec " << endl;
    /*1.b.3
    Compute a LSIS of the intermediate sequence
    https://www.techiedelight.com/longest-increasing-subsequence/
    */
    printLIS(intermediate, k);
    //cout << "LSIS LCS length: " << printLIS(intermediate);
    end_time = clock();
    time_taken = float(end_time - start_time) / float(CLOCKS_PER_SEC);
    cout << " CPU : " << fixed
         << time_taken << setprecision(3);
    cout << " sec " << endl;
    // Print the lcs
    //lcs(arr1, arr2, n, m);


    return 0;
}

