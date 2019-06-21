#include <iostream>
#include <map>
#include <vector>
using namespace std;
/*class Edge {
	int src;
	int target;
	int weight;
public:
	Edge(int src, int target, int weight)
	{
		this->src = src;
		this->target = target;	
		this->weight = weight;
	}
};*/
class Node
{
	map<int, int> edges;
public:
	void connectNode(int target, int weight)
	{
		edges[target] = weight;
	}
	int sumEdges()
	{
		return edges.size();
	}
	Node(){}
};
class Graph {
public:
	map<int, Node> nodes;
	void addEdge(int index, int target, int weight)
	{	
		nodes[index].connectNode(target, weight);
		nodes[target].connectNode(index, weight);
	}
};
int main()
{
	Graph graph;
	int n,m;
	cin >> n >> m;
	int t1, t2, t3;
	for (int i = 0; i < m; i++)
	{
		cin >> t1 >> t2 >> t3;
		graph.addEdge(t1, t2, t3);
	}
	cin >> t1;
	cout << graph.nodes[t1].sumEdges();
}