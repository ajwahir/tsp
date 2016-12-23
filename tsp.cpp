#include "iostream"
#include "fstream"
#include "math.h"
#include "time.h"
#include "stdlib.h"

using namespace std;
int nodes=100;
double **edge_matrix;

int eval_cost(int path[])
{
	int cost=0;
	for(int i=0;i<nodes;i++)
	{
		if(i==nodes-1)
			cost+=edge_matrix[path[i]][path[0]];
		else
			cost+=edge_matrix[path[i]][path[i+1]];
	}
	return cost;
}
int RandomSwap(int path[])
{
	int p=rand()%nodes;
	int q=rand()%nodes;
	int temp=path[p];
	path[p]=path[q];
	path[q]=temp;
	//return path;
}

int two_opt(int path[])
{   
	int temp_path[nodes];
	for(int j=0;j<nodes;j++)
		temp_path[j]=path[j];
	int p=rand()%nodes;
	int q=rand()%nodes;
	if(p>q)
	{
		int temp=p;
		p=q;
		q=temp;
	}
	for(int i=p,t=0;i<q+1;i++,t++)
		path[i]=temp_path[q-t];
}

int three_opt(int path[])
{   
	int temp_path[nodes],p=rand()%nodes,q=rand()%nodes;
	for(int j=0;j<nodes;j++)
		temp_path[j]=path[j];
	int difference=0;
	while(difference<4){	
		 p=rand()%nodes;
		 q=rand()%nodes;
		if(p>q)
		{
			int temp=p;
			p=q;
			q=temp;
		}
       difference=q-p+1;
   }
   int t1=floor(difference/2),t2=difference-t1;
   for(int i=p,t=0;i<p+t1;i++,t++)
		path[i]=temp_path[p+t1-t-1];
   for(int i=p+t1,t=0;i<q+1;i++,t++)
		path[i]=temp_path[q-t];

}


int main()
{
	clock_t start;
    double duration;

    start = clock();

	int i=0,j=0,epoch,reset=500;

	char file[20];
	cin>>file;
	cin>>nodes;
	double coordinates[nodes][2],delta_e,T,P;
	edge_matrix=new double*[nodes];
	for(i=0;i<nodes;i++)
		edge_matrix[i]=new double[nodes];
	for(i=0;i<nodes;i++)
		for(j=0;j<2;j++)
			cin>>coordinates[i][j];
	for(i=0;i<nodes;i++)
		for(j=0;j<nodes;j++)
			cin>>edge_matrix[i][j];
    int tour[nodes],best_tour[nodes],new_tour[nodes];
    for(i=0;i<nodes;i++)
    	{tour[i]=i;
    	 best_tour[i]=i;}
    int best_cost=eval_cost(best_tour);
    // Params
    int cooling_rate=0.9999;
    T=1000000000000000000;
    

    for(int k=0;k>-1;k++)
    {
    	for(int epoch=101;epoch>0;epoch--)
    	{
    		for(i=0;i<nodes;i++)
    			new_tour[i]=tour[i];
    		//RandomSwap(new_tour);
    		two_opt(new_tour);
    		//three_opt(new_tour);
            delta_e=eval_cost(new_tour)-eval_cost(tour);
            P=1/(1+pow(M_E,(delta_e/T)));
            if(P>((double) rand() / (RAND_MAX)))
            	for(i=0;i<nodes;i++)
            		tour[i]=new_tour[i];
            
            
            if(eval_cost(new_tour)<best_cost)
            {
            	
            	best_cost=eval_cost(new_tour);
            	//cout<<best_cost<<endl;
            	for(int j=0;j<nodes;j++)
            		best_tour[j]=new_tour[j];
            	cout<<endl;
            	for(int j=0;j<nodes;j++)
            		cout<<best_tour[j]<<" ";
            	//cout<<endl<<"Best cost is : "<<best_cost;
            	//duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
            	//cout<<endl<<"DURATION : "<<duration;
            }

    	}
    	duration = (clock() - start ) / (double) CLOCKS_PER_SEC;
    	if(duration>300)
    		break;
    	T*=cooling_rate;
    	if(T==0 && reset<1)
    	{
    		T=10000000000000000;
    		reset = reset-1;
    	}
    }			
	return 0;
}
