// Program to find BFS traversal from a given 

// source vertex. BFS(int s) traverses vertices  

// reachable from s. 

// Find out the number of how many time a node appears in the shortest path

// Measure betweeness of centrality



#include <iostream> 

#include <list> 

#include <cstdlib>

#include <mpi.h>

#include <stdio.h>

#include <stdlib.h>



  

using namespace std; 



double* nodes_count;  

double p=0, x;

double* BW;



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

}; 

  

Graph::Graph(int V) 

{ 

    this->V = V; 

    adj = new list<int>[V]; 

} 

  

void Graph::addEdge(int v, int w) 

{ 

    adj[v].push_back(w); // Add w to v?s list. 

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

    // vertices of a verte

 

    list<int>::iterator i; 

  

    while(!queue.empty()) 

    { 

        // Dequeue a vertex from queue and print it 

        s = queue.front(); 

       // cout << s << " ";

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





// Driver program to test methods of graph class 

int main(int argc, char *argv[]) //new

{ 

    int i,j; 

    int rank, nprocs;

    double node_work;

    double* nodes_temp;

    MPI_Status status;

 

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);//new



    // Start time measurement

    double t1 = MPI_Wtime(); 

 

    // Create a graph given in the above diagram 

    int graph_nodes = 42000;

    nodes_count = (double*)malloc((graph_nodes + 1)*sizeof(double));

    

    

	for(j=0;j<graph_nodes;j++)

    	    nodes_count[j] = 0;

    

	

	//Find the number of nodes to work on for the current rank: nodes/ranks

	node_work= graph_nodes*1.0/nprocs;

	int rem = graph_nodes%nprocs;

	//Find the starting node as: rank*(nodes/ranks)

	int start = rank*node_work;

    //Find the ending node as: rank*(nodes/ranks) + nodes/rank

	int end = start + node_work;

	if(rank == (nprocs - 1)){

		end = graph_nodes;

	}

	
	int comp = graph_nodes/14;
	
	for(j=start;j<end;j++){

	    Graph g(graph_nodes);
		
		for(i = 0; i < comp; i += 14){
		if (i > 0){
			g.addEdge(i, i - 14);
			g.addEdge(i - 14, i);
		}
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
	}
	 
    	g.BFS(j);

        nodes_count[j]--;

        if(nodes_count[j] < 0){
            nodes_count[j] = 0;
	    }      
	}

	nodes_count[graph_nodes] = p*1.0;

	if(rank != 0)

	//Use MPI_Send to send the nodes_count[] array to rank 0

	    MPI_Send(nodes_count, graph_nodes + 1, MPI_DOUBLE, 0, rank, MPI_COMM_WORLD);

		

	//for(j=0;j<i;j++)

	//cout << "Node " << j << " visited: " << nodes_count[j] << "times"<< endl; // divide by that variable i.e. 

	//cout << "Total Number of Paths " << p;

	

	

	

	if(rank == 0){

	

		for(i=1;i<nprocs;i++){

		nodes_temp =(double*)malloc((graph_nodes+1)*sizeof(double));

		MPI_Recv(nodes_temp, graph_nodes + 1, MPI_DOUBLE, i,i,MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		for(j=0;j<graph_nodes;j++){

				nodes_count[j] += nodes_temp[j];

			}

	         p += nodes_temp[graph_nodes];

		}

		

	

	//for(j=0;j<graph_nodes;j++)

	//cout <<"\nBetweeness Centrality of Node "<<j << " is: "<< 	nodes_count[j]*1.0/p;

}

	//Time count end

        double t2 = MPI_Wtime();

	if(rank == 0)

        	cout << "\nThe process took " << t2 - t1 << " seconds to run." << endl;

	

    MPI_Finalize();



    return 0; 

} 
