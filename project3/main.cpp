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
#include <limits.h>
#include <string.h>
#include <algorithm>
#define NINF INT_MIN
using namespace std;

bool checkifSubstring(std::string input[], int n)
{
    for (int i; i < n; i++){
        for (int j; j < n; j++){
            if (i !=j){
                    if (input[i].find(input[j]) != string::npos) {
                        return true;
                    }
            }
        }

    }
    return false;
}
/*
https://www.geeksforgeeks.org/shortest-superstring-problem/
*/
// Utility function to calculate minimum of two numbers
int min(int a, int b)
{
    return (a < b) ? a : b;
}
// Function to calculate maximum overlap in two given strings
int findOverlappingPair(string str1, string str2, string &str)
{
    // max will store maximum overlap i.e maximum
    // length of the matching prefix and suffix
    int max = 0;
    int len1 = str1.length();
    int len2 = str2.length();

    // check suffix of str1 matches with prefix of str2
    for (int i = 1; i <= min(len1, len2); i++)
    {
        // compare last i characters in str1 with first i
        // characters in str2
        if (str1.compare(len1-i, i, str2, 0, i) == 0)
        {
            if (max < i)
            {
                //update max and str
                max = i;
                str = str1 + str2.substr(i);
            }
        }
    }

    // check prefix of str1 matches with suffix of str2
    for (int i = 1; i <= min(len1, len2); i++)
    {
        // compare first i characters in str1 with last i
        // characters in str2
        if (str1.compare(0, i, str2, len2-i, i) == 0)
        {
            if (max < i)
            {
                //update max and str
                max = i;
                str = str2 + str1.substr(i);
            }
        }
    }

    return max;
}

/*
longest Hamiltonian path
*/

// Graph is represented using adjacency list. Every
// node of adjacency list contains vertex number of
// the vertex to which edge connects. It also
// contains weight of the edge
struct AdjListNode {
    int v;
    int weight;
};
// Compares two intervals according to staring times.
bool compare(AdjListNode n1, AdjListNode n2)
{
  if ( n1.weight > n2.weight)
    return true;
  else
    return false;
}


// Class to represent a graph using adjacency list
// representation
class Graph {
    int V; // No. of vertices'

    // Pointer to an array containing adjacency vectors
    list<AdjListNode>* adj;

    void getBigestSubstring();

public:
    Graph(int V); // Constructor

    // function to add an edge to graph
    void addEdge(int u, int v, int weight);
    // Finds longest distances from given source vertex
    void longestPath(string str_array[]);
};

Graph::Graph(int V) // Constructor
{
    this->V = V;
    adj = new list<AdjListNode>[V];
}


void Graph::addEdge(int u, int v, int weight)
{
    AdjListNode node;
    node.v = v;
    node.weight= weight;
//    auto it = std::find_if(adj[v].begin(), adj[v].end(),
//                       [u] (const AdjListNode& n) {
//                          return n.v == u;
//                       })!= adj[v].end();
//    if (!it)
    adj[u].push_back(node); // Add v to u's list
}

void Graph::getBigestSubstring()
{
    for (int v = 0; v<V; v++){
        adj[v].sort(compare);
        adj[v].resize(1);
        list<AdjListNode>::const_iterator it_v =  adj[v].begin();
        list<AdjListNode>::const_iterator it_u = adj[it_v->v].begin();
        while ( it_u != adj[it_v->v].end() ){
            if (v == it_u->v){
                    adj[it_v->v].erase(it_u++);
            }
            else{
                ++it_u;
            }
        }
    }
}

void Graph::longestPath(string str_array[])
{
    getBigestSubstring();
//    for (int i = 0; i < V; i++){
//        for (auto it = adj[i].begin(); it != adj[i].end(); ++it)
//        cout << i << ":" << it->v << endl;
//    }
    int total_overlap = 0;
    for (int i = 0; i < V; i++){
        for (auto it = adj[i].begin(); it != adj[i].end(); ++it){
            string str;
            cout << string( total_overlap, ' ' ) << str_array[i] << endl;
            total_overlap += (str_array[i].length()-findOverlappingPair(str_array[i], str_array[it->v], str));
            //cout << string( total_overlap, ' ' ) << str_array[it->v] << endl;
        }
    }
    cout << "Length of SCS "<< total_overlap << endl;

}
Graph fillEdgesHamiltonian(string arr[], int len)
{

    Graph g(len);
    // involved in maximum overlap
    string resStr;    // to store resultant string after
    // maximum overlap

    // For all pairs of strings s_i and s_j in S
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len; j++)
        {
            if (i!=j){
                    string str;

                    int overlap = findOverlappingPair(arr[i], arr[j], str);

                    g.addEdge(i, j, overlap);
            }
        }
    }

    return g;
}

int main(int argc, char** argv)
{
    char filename[]="lab3spr20.a.dat";
    ifstream File;
    if (argc > 1){
      cout << "Filename: " << argv[1] << endl;
      File.open((argv[1]));
    }
    else
        File.open(filename);

    string tmp;
    getline(File, tmp);
    int n = std::stoi(tmp);
    cout << "Number of Strings in file is " << n << endl;

    string str_array[n];

    if (File.is_open()){   //checking whether the file is open
          for(int i=0; i<n; i++)
            getline(File, str_array[i]); //read data from file object and put it into string.

          File.close(); //close the file object.
       }

    if (checkifSubstring(str_array, n))
        {cout << "NOT OK"; return 1;}

    Graph g = fillEdgesHamiltonian(str_array,n);

    g.longestPath(str_array);


    return 0;
}
