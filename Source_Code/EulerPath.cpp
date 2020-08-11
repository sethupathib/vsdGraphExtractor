//Euler Path Existence



//
//  main.cpp
//  EulerPath
//
//  Created by Sethupathi on 30/07/20.
//
//

//This returns if the the graph contains a Euler Path.
//undirected graph

#include <iostream>
//#include <string>
#include <list>
//#include <algorithm>

using namespace std;

class Graph {

private:
    int V; //no. of vertices
    list<int> *adj; //dynamic array of adjacency list
public:

    Graph(int V) {
        this->V = V;
        adj = new list<int>[V];
    }
    ~Graph() {
        delete [] adj;
    }


void addEdge(int v, int w); //function to add edge (v- first node, w -second node)

void DFS(int v, bool visited[]); //Depth first search

bool isConnected(); //function to check if all nodes with non-zero degrees are connected

int isEulerian(); //function to check if the graph is Eulerian

    };


void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);
}


void Graph::DFS(int v, bool visited[])

{
    //mark the current node as visited
    visited[v] = true;
    list<int>:: iterator i;
    
    //This subroutine is very powerful. It's a recursive call.
    
    for(i=adj[v].begin(); i!= adj[v].end(); ++i)
    {
        if(!visited[*i])
            
            DFS(*i,visited);    //This line is important. Prone to mistakes
    }
}

bool Graph::isConnected()
{
    int i;
    bool visited[V];
    for(int i=0;i<V;i++)
    {
        visited[i] = false;
    }
    
    //find a vertex with non-zero degree
    
    for (i=0;i<V;i++)
    {
        if(adj[i].size()!=0)
            break;   //extremely important
    }
    
    //if there are no edges in the graph, return true
    
    if(i==V)
        return true;
    
    //Start DFS traversal from the vertex with non-zero degree
    
    DFS( i, visited);
    
    //check if all the non zero degree vertices are visited

    for (int i=0;i<V;i++)
    {
        if(visited[i]== false && adj[i].size()>0) //very imp. condition
        {
            return false;
        }
    }

    return true;
}


/* The function returns one of the following values
0 --> If grpah is not Eulerian
1 --> If graph has an Euler path (Semi-Eulerian)
2 --> If graph has an Euler Circuit (Eulerian)  */

//function test() contains calls to isEulerian
//function isEulerian() contains calls to isConnected()
//function isConnected() contains calls to DFS()

    int Graph::isEulerian()
{
    
    if (isConnected() == false)
    {
        return 0;
    }
    
    //Count vertices with odd degrees
    int odd=0;
    for(int i=0;i<V;i++)
    {
        if(adj[i].size() & 1)
            odd++;
    }
    
    if(odd>2)
        return 0;
    // If odd count is 2, then semi-eulerian.
    // If odd count is 0, then eulerian
    // Note that odd count can never be 1 for undirected graph
    
    return (odd)? 1:2;
}

//function to test cases

void test (Graph &g)
{
    int res = g.isEulerian();
    if(res==0)
        cout<<"Graph is not Eulerian"<<endl;
    
    else if (res==1)
        cout<<"Graph contains Eulerian Path"<<endl;
    
    else
        cout<<"Graph has a Eulerian Cycle"<<endl;
}



int main(int argc, const char * argv[]) {
    

     // graph with 5 vertices

      Graph g3(5);
      g3.addEdge(1, 0);
      g3.addEdge(0, 2);
      g3.addEdge(2, 1);
      g3.addEdge(0, 3);
      g3.addEdge(3, 4);
      g3.addEdge(1, 3);
      test(g3);

      // graph with 3 vertices
      // connected in the form of cycle
      Graph g4(3);
      g4.addEdge(0, 1);
      g4.addEdge(1, 2);
      g4.addEdge(2, 0);
      test(g4);

      //  graph with all veritces
      // with zero degree
      Graph g5(10);
      test(g5);

    return 0;
}
