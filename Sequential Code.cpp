// Program to print BFS traversal from a given 
// source vertex. BFS(int s) traverses vertices  
// reachable from s. 
#include<iostream> 
#include <list> 
#include<cstdlib>
#include<ctime> 
#include <sys/time.h>

using namespace std; 

double* nodes_count;  
double p=0, x;
double* BW;

struct timeval before, after;
// This class represents a directed graph using 
// adjacency list representation 
class Graph 
{ 
    int V;    // No. of vertices 
  
    // Pointer to an array containing adjacency 
    // lists 
    list<int> *adj;    
public: 
    Graph(int V);  // Constructor 
  
    // function to add an edge to graph 
    void addEdge(int v, int w);  
  
    // prints BFS traversal from a given source s 
    void BFS(int s);
	
	~Graph();   
}; 
  
Graph::Graph(int V) 
{ 
    this->V = V; 
    adj = new list<int>[V]; 
} 
  
void Graph::addEdge(int v, int w) 
{ 
    adj[v].push_back(w); // Add w to v’s list. 
} 
  
void Graph::BFS(int s) 
{ 
    // Mark all the vertices as not visited 
    bool *visited = new bool[V]; 
    for(int i = 0; i < V; i++) 
        visited[i] = false; 

    // Create a queue for BFS 
    list<int> queue; 
  
    // Mark the current node as visited and enqueue it 
    visited[s] = true; 
    queue.push_back(s); 
  
    // 'i' will be used to get all adjacent 
    // vertices of a vertex 
    list<int>::iterator i; 
  
    while(!queue.empty()) 
    { 
        // Dequeue a vertex from queue and print it 
        s = queue.front(); 
        //cout << s << " ";
		nodes_count[s]++; 
        queue.pop_front(); 
  		bool flag = false;
        // Get all adjacent vertices of the dequeued 
        // vertex s. If a adjacent has not been visited,  
        // then mark it visited and enqueue it 
        for (i = adj[s].begin(); i != adj[s].end(); ++i) 
        { 
            if (!visited[*i]) 
            { 
                visited[*i] = true; 
                queue.push_back(*i);
				flag=true; 
            } 
        } 
        if(!flag)
		nodes_count[s]--;
		
	    p++;
		//maintain a variable for total paths and increment it here
        

    } 
    
} 

Graph::~Graph() {
   // Deallocate the memory that was previously reserved
   //  for this graph.
   delete[] adj;
}
// Driver program to test methods of graph class 
int main() 
{ 
	int num_nodes,j; 
	gettimeofday(&before,NULL);
	
    // Create a graph given in the above diagram 
    num_nodes = 42000;
    nodes_count = (double*)malloc(num_nodes*sizeof(double));
    
    int comp = num_nodes/14;
    
	for(j=0;j<num_nodes;j++)
    	nodes_count[j] = 0;
    
    
    for(int k = 0; k < num_nodes; k++){
	
		Graph g(num_nodes);
		
	
		for(int i = 0; i < comp; i += 14){
			if (i > 0){
				g.addEdge(i, i - 14);
				g.addEdge(i - 14, i);
			}
			//for(j=0;j<28;j++){ 
			    g.addEdge(i + 0, i + 1); 
			    g.addEdge(i + 0, i + 2); 
			    g.addEdge(i + 1, i + 2); 
			    g.addEdge(i + 2, i + 0); 
			    g.addEdge(i + 2, i + 3); 
			    g.addEdge(i + 3, i + 3); 
			    g.addEdge(i + 1, i + 3); 
			    g.addEdge(i + 1, i + 8); 
			    g.addEdge(i + 3, i + 8);
				g.addEdge(i + 8, i + 9);  
			    g.addEdge(i + 9, i + 8); 
			    g.addEdge(i + 8, i + 10); 
			    g.addEdge(i + 10, i + 8); 
			    g.addEdge(i + 9, i + 10);
				g.addEdge(i + 3, i + 4); 
			    g.addEdge(i + 4, i + 3); 
			    g.addEdge(i + 4, i + 5); 
			    g.addEdge(i + 5, i + 7); 
			    g.addEdge(i + 4, i + 7); 
			    g.addEdge(i + 5, i + 6); 
			    g.addEdge(i + 4, i + 6); 
			    g.addEdge(i + 6, i + 6);
				g.addEdge(i + 6, i + 7);  
			    g.addEdge(i + 6, i + 13); 
			    g.addEdge(i + 7, i + 13); 
			    g.addEdge(i + 13, i + 7); 
			    g.addEdge(i + 4, i + 10); 
			    g.addEdge(i + 10, i + 11);
				g.addEdge(i + 11, i + 11); 
			    g.addEdge(i + 4, i + 11); 
			    g.addEdge(i + 11, i + 12);
				g.addEdge(i + 8, i + 4);  //
//			    g.addEdge(i + 14, i + 15); 
//			    g.addEdge(i + 14, i + 16); 
//			    g.addEdge(i + 15, i + 16); 
//			    g.addEdge(i + 16, i + 14); 
//			    g.addEdge(i + 16, i + 17); 
//			    g.addEdge(i + 17, i + 17); 
//			    g.addEdge(i + 15, i + 17); 
//			    g.addEdge(i + 15, i + 22); 
//			    g.addEdge(i + 17, i + 22);
//				g.addEdge(i + 22, i + 23);  
//			    g.addEdge(i + 23, i + 22); 
//			    g.addEdge(i + 22, i + 24); 
//			    g.addEdge(i + 24, i + 22); 
//			    g.addEdge(i + 23, i + 24);
//				g.addEdge(i + 17, i + 18); 
//			    g.addEdge(i + 18, i + 17); 
//			    g.addEdge(i + 18, i + 19); 
//			    g.addEdge(i + 19, i + 21); 
//			    g.addEdge(i + 18, i + 21); 
//			    g.addEdge(i + 19, i + 20); 
//			    g.addEdge(i + 18, i + 20); 
//			    g.addEdge(i + 20, i + 20);
//				g.addEdge(i + 20, i + 21);  
//			    g.addEdge(i + 20, i + 27); 
//			    g.addEdge(i + 21, i + 27); 
//			    g.addEdge(i + 27, i + 21); 
//			    g.addEdge(i + 18, i + 24); 
//			    g.addEdge(i + 24, i + 25);
//				g.addEdge(i + 25, i + 25); 
//			    g.addEdge(i + 18, i + 25); 
//			    g.addEdge(i + 25, i + 26);
//				g.addEdge(i + 22, i + 18); 
//				g.addEdge(i + 13, i + 14);//connection
//				g.addEdge(i + 14, i + 13);//connection
//				g.addEdge(i + 7, i + 16);//connection
//				g.addEdge(i + 16, i + 7);//connection  
			//}
	
		}
		//cout << "Breadth First Traversal for Node " <<k <<"  is \n";
        g.BFS(k);
        nodes_count[k]--;
        if(nodes_count[k] < 0){
            nodes_count[k] = 0;
		}
		//cout << "\n";
	}
	
	//for(j=0;j<num_nodes;j++)
		//cout << "Node " << j << " visited: " << nodes_count[j] << "times"<< endl; // divide by that variable i.e. 
	
	//cout << "Total Number of Paths " << p;
	
	//for(j=0;j<num_nodes;j++)
		//cout <<"\nBetweeness Centrality of Node "<<j << " is: "<< nodes_count[j]*1.0/p;
	
	gettimeofday(&after,NULL);
	double elapsed_time = ( 1000000.0*(after.tv_sec - before.tv_sec) + (after.tv_usec - before.tv_usec))/1000000.0;
	cout << "\nElapsed time: " << elapsed_time << "seconds\n" << endl;



    return 0; 
} 
