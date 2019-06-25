// A C++ Program to generate test cases for 
// an weighted undirected graph 
#include<set> 
#include<iostream>
#include<time.h>
#include<fstream>

using namespace std; 

// Define the number of runs for the test data 
// generated 
#define RUN 1

// Define the maximum number of vertices of the graph 
#define MAX_VERTICES 100

	

// Define the maximum weight of edges 
#define MAXWEIGHT 100

//void generate_graph();
void file_to_py();
void generate_graph();
int main() 
{ 
	generate_graph();
	//file_to_py();
} 

void file_to_py()
{
	int v,e;
	cin>> v >> e;
	ofstream file_;
	file_.open("t3py.txt");

		for(int i = 0; i < e; i++)
		{
			int t1,t2,t3;
			cin >>t1>>t2>>t3;
			file_<<",("<<t1<<","<<t2<<","<<t3<<")";
		}
		
		
	file_.close();
}

void generate_graph()
{
	set<pair<int, int>> container; 
	set<pair<int, int>>::iterator it; 

	
	// the test data in a file 
	

	ofstream file_;
	file_.open("test_cases.txt");

	//For random values every time 
	srand(time(NULL)); 

	int NUM; // Number of Vertices 
	int NUMEDGE; // Number of Edges 
	
	for (int i=1; i<=RUN; i++) 
	{ 
		NUM = 1 + rand() % MAX_VERTICES; 
		int MAX_EDGES = (NUM*(NUM-1))/2;
		// Define the maximum number of edges of the graph 
		// Since the most dense graph can have N*(N-1)/2 edges 
		// where N = nnumber of vertices in the graph 
		NUMEDGE = 1 + rand() % MAX_EDGES; 

		while (NUMEDGE > NUM*(NUM-1)/2) 
			NUMEDGE = 1 + rand() % MAX_EDGES; 

		// First print the number of vertices and edges 
		printf("%d %d\n", NUM, NUMEDGE); 
		file_ << NUM <<" "<<NUMEDGE<<endl;

		// Then print the edges of the form (a b) 
		// where 'a' is connected to 'b' 
		for (int j=1; j<=NUMEDGE; j++) 
		{ 
			int a = rand() % NUM; 
			int b = rand() % NUM; 
			pair<int, int> p = make_pair(a, b); 
			pair<int, int> reverse_p = make_pair(b, a); 

			// Search for a random "new" edge everytime 
			// Note - In a tree the edge (a, b) is same 
			// as the edge (b, a) 
			while (container.find(p) != container.end() || 
					container.find(reverse_p) != container.end()) 
			{ 
				a = rand() % NUM; 
				b = rand() % NUM; 
				p = make_pair(a, b); 
				reverse_p = make_pair(b, a); 
			} 
			container.insert(p); 
		} 

		for (it=container.begin(); it!=container.end(); ++it) 
		{ 
			int wt = 1 + rand() % MAXWEIGHT; 
			printf("%d %d %d\n", it->first, it->second, wt); 
			file_ << it->first << " " <<it->second << " " << wt <<endl;
		} 

		container.clear(); 
		printf("\n"); 
		file_ <<"\n";


	} 

	// Uncomment the below line to store 
	// the test data in a file 
	 //fclose(stdout); 
	file_.close();
	
}