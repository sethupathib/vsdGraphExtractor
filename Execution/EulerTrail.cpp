//
//  main.cpp
//  EulerTrail
//
//  Created by Sethupathi on 31/07/20.
//

#include <iostream>
#include <list>
#include <string.h>
#include <algorithm>

using namespace std;
class Graph
{
private:
    int V;
    list<int> *adj;
 
public:
    Graph(int V){
        this->V= V;
        adj = new list<int>[V];
    }
    
    ~Graph()
    {
        delete [] adj;
        
    }
    
    void addEdge(int u, int v)
    {
        adj[u]. push_back(v);
        adj[v]. push_back(u);
    }
    
    void removeEdge(int u, int v);
    
    void printEulerTour();
    void printEulerUtil(int s);
    
    //counting the no. of vertices reachable from v
    int DFSCount(int v, bool visited[]);
    
    //function to check if edge u-v is a valid next edge in euler trail
    bool isValidNextEdge(int u, int v);
};


void Graph::printEulerTour()
{
    int u=0;
    for (int i=0;i<V;i++)
    {
        if(adj[i].size()&1) //Bitwise AND with 1. Checks if the number is odd
        {
            u=i;
            break;
        }
    
        }
        printEulerUtil(u);
    cout<<endl;
}

void Graph::printEulerUtil(int u)
{
    list<int>:: iterator i;
    for(i=adj[u].begin();i!=adj[u].end();++i)
    {
        int v = *i;
  
    
    if(v!= -1 && isValidNextEdge(u, v))
    {
        cout<<u<<"-"<<v<<" ";
        removeEdge(u, v);
        printEulerUtil(v);
    }
}
    
}

bool Graph::isValidNextEdge(int u, int v)
{
    
    
    //The edge u-v is valid in one of the following two cases:
    // 1) If v is the only adjacent vertex of u
    
    int count=0; // to store count of adjacent edges
    list<int>::iterator i;
    
    for (i=adj[u].begin();i!=adj[u].end();++i)
    {
        if(*i!=-1)
            count++;
        }
    
    if (count ==1)
    return true;
    
    
    // 2) If there are multiple adjacents, then u-v is not a bridge
    // Do following steps to check if u-v is a bridge
    
    // 2.a) count of vertices reachable from u
    
    bool visited[V];
    memset(visited,false,V);
    int count1 = DFSCount(u, visited);
    
    // 2.b) Remove edge (u, v) and after removing the edge, count
    // vertices reachable from u
    
    removeEdge(u, v);
    memset(visited, false, V);
    
    int count2 = DFSCount(u, visited);
     // 2.c) Add the edge back to the graph
      addEdge(u, v);
      
      // 2.d) If count1 is greater, then edge (u, v) is a bridge
      return (count1 > count2)? false: true;
    }
    


void Graph:: removeEdge(int u, int v)
{
    
    // Find v in adjacency list of u and replace it with -1
    list<int>::iterator iv = find(adj[u].begin(),adj[u].end(),v);
    *iv =-1;
    
    list<int>::iterator iu = find(adj[v].begin(),adj[v].end(),u);
    *iu =-1;
    
}


// A DFS based function to count reachable vertices from v
 int Graph::DFSCount(int v, bool visited[])
{
    visited[v] = true;
    int count=1;
    
    list<int>:: iterator i;
    for(i=adj[v].begin();i!=adj[v].end();++i)
    {
        if(*i!=-1 && !visited[*i])
            count += DFSCount(*i, visited);
    }

    return count;
}


// Driver program to test above function
int main()
{


int e,node1,node2;
//cout<<"Enter no. of edges";
cin>>e;

Graph g1(e);

for(int i=0;i<e;i++)
{
	cin>>node1>>node2;
	g1.addEdge(node1,node2);
}

g1.printEulerTour();


// Let us first create and test graphs shown in above figure
//  Graph g1(4);
//  g1.addEdge(0, 1);
//  g1.addEdge(0, 2);
//  g1.addEdge(1, 2);
//  g1.addEdge(2, 3);
//  g1.printEulerTour();
//
//  Graph g2(3);
//  g2.addEdge(0, 1);
//  g2.addEdge(1, 2);
//  g2.addEdge(0, 2);
//  g2.printEulerTour();
//  
//  Graph g3(4);
//  g3.addEdge(0, 1);
//  g3.addEdge(1, 2);
//  g3.addEdge(2, 3);
//  g3.addEdge(3, 0);
//
//  g3.printEulerTour();
//  
//    //starts from '0'
//    
//    Graph g4(6);
//      g4.addEdge(1, 2);
//      g4.addEdge(2, 4);
//      g4.addEdge(4, 3);
//      g4.addEdge(3, 1);
//      g4.addEdge(4, 5);
//      g4.addEdge(5, 4);
//      g4.addEdge(7, 5);
//      g4.addEdge(7, 0);
//      g4.addEdge(6, 0);
//      g4.addEdge(6, 0);
//      g4.addEdge(5, 6);
//      g4.addEdge(5, 6);
    
    
//          g4.addEdge(0, 1);
//          g4.addEdge(0, 1);
//          g4.addEdge(1, 2);
//          g4.addEdge(1, 2);
//          g4.addEdge(2, 3);
//          g4.addEdge(3, 0);
//    
//     g4.printEulerTour();
//    
//    Graph g5(5);
//    g5.addEdge(0, 1);
//    g5.addEdge(0, 1);
//    g5.addEdge(2, 3);
//    g5.addEdge(3, 4);
//    g5.addEdge(1, 2);
//    g5.printEulerTour();
//    
//    
//    cout<<"Euler Path for the boolean function "<<endl;
//    
//    Graph g6(12);
//    g6.addEdge(0, 6);
//    g6.addEdge(0, 6);
//    g6.addEdge(0, 7);
//    g6.addEdge(5, 6);
//    g6.addEdge(5, 6);
//    g6.addEdge(5, 7);
//    
//    g6.addEdge(5, 4);
//    g6.addEdge(5, 4);
//    g6.addEdge(4, 3);
//    g6.addEdge(3, 1);
//    g6.addEdge(1, 2);
//    g6.addEdge(2, 4);
//    
//    g6.printEulerTour();
//    
    
  return 0;
}

