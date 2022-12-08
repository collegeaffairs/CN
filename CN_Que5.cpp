//CN Practical Que. 5

#include<stdio.h>
#include<iostream>
using namespace std;

#define SIZE 6

class node
{
    public:
        unsigned dist[SIZE];
        unsigned from[SIZE];
}DVR[10];

int main()
{
    cout<<endl<<endl<<"------------------ Distance Vector Routing Algorithm --------------------"<<endl;
    int costmat[SIZE][SIZE];
    int nodes, i, j, k;
    cout<<endl<<"--> Enter the number of nodes : ";
    cin>>nodes;
    cout<<endl<<"--> Enter the cost matrix : "<<endl ;
    for(int i = 0; i < nodes; i++)
     {
        for(int j = 0; j < nodes; j++)
        {
            cin>>costmat[i][j];
            costmat[i][i] = 0;
            DVR[i].dist[j] = costmat[i][j]; //initialise the distance equal to cost matrix
            DVR[i].from[j] = j;
        }
    }
    //calculate the direct distance from the node i to k using the cost matrix and add the distance from k to node j
    for(int i = 0; i < nodes; i++) 
    {
        for(int j = i+1; j < nodes; j++)
        {
            for(int k = 0; k < nodes; k++)
            {
                if(DVR[i].dist[j] > costmat[i][k] + DVR[k].dist[j])
                {
                    //calculate the minimum distance
                    DVR[i].dist[j] = DVR[i].dist[k] + DVR[k].dist[j];
                    DVR[j].dist[i] = DVR[i].dist[j];
                    DVR[i].from[j] = k;
                    DVR[j].from[i] = k;
                }
            }
        }
    }
    for(int a= 0; a <40; a++) {
        cout<<"-";
    }
    cout<<endl;
    for(int i = 0; i < nodes; i++)
    {
        cout<<endl<<endl<<"--> For Router: "<<i+1;
        for(int j = 0; j < nodes; j++)
        {
            cout<<endl<<"\t-> node "<<j+1<<" via "<<DVR[i].from[j]+1<<" Distance "<<DVR[i].dist[j];
        }
    }
    cout<<endl<<endl;
    return 0;
}