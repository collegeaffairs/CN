//CN Practical Que 6:  Dijkstra's shortest path algorithm.

#include <limits.h>
#include <stdio.h>
#include <iostream>
using namespace std;

// Number of vertices in the graph
#define V 6

int minDistance(int dist[], bool Tset[])
{
	int min = INT_MAX, min_index;

	for (int j = 0; j < V; j++)
	{
        if (Tset[j] == false && dist[j] <= min)
		{
            min = dist[j], min_index = j;
        }
    }
	return min_index;
}

void printSolution(int dist[], int n)
{
    cout<<"------------------------------------------------"<<endl;
	cout<<"Vertex\t|   Distance from Source"<<endl;
    cout<<"------------------------------------------------"<<endl;
	for (int i = 0; i < V; i++)
    { 
        cout<<"   "<<char(80+i)<<"\t|\t"<<dist[i]<<endl;
    }
    cout<<"------------------------------------------------"<<endl;
}

void dijkstra(int graph[V][V], int src)
{
	int dist[V];
	bool Tset[V];
	
    for (int i = 0; i < V; i++)
	{ 
        dist[i] = INT_MAX, Tset[i] = false;
    }

	// Distance of source vertex from itself is always 0
	dist[src] = 0;

	
	for (int i = 0; i < V - 1; i++)
    {	
        int m = minDistance(dist, Tset);
		Tset[m] = true;

		for (int j = 0; j < V; j++)
		{
            if (!Tset[j] && graph[m][j] && dist[m] != INT_MAX && dist[m] + graph[m][j] < dist[j])
			{
                dist[j] = dist[m] + graph[m][j];
            }
        }
	}

	printSolution(dist, V);
}

//Main function for execution of program
int main()
{
    //PQRSTU
	int graph[V][V] = { { 0, 1, 0, 6, 0, 7},
						{ 0, 0, 1, 4, 0, 0},
						{ 0, 0, 0, 2, 0, 1 },
						{ 0, 0, 0, 0, 3, 2},
						{ 0, 0, 0, 0, 0, 2 },
						{ 0, 0, 0, 0, 0, 0}};
    char src;
    cout<<endl<<endl<<"--> Enter a Source Node from P to U :"<<endl<<"--> ";
    cin>>src;
	if(src >= 80 && src <= 87)
    { 
        dijkstra(graph, int(src)-(80));
    }
 
    else if(src >= 112 && src <= 118)
    {
        dijkstra(graph, int(src)-112);
    }
    else
    {
        cout<<endl<<"!! Error! Enter Wrong Character !!"<<endl;
    }

	return 0;
}
