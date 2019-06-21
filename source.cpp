#include <iostream>
#include <map>
#include <vector>
#include <set>
using namespace std;
class Node
{
	int index;
public:
	map<int, int> edges;
	void connectNode(int target, int weight)
	{
		edges[target] = weight;
	}
	int sumEdges()
	{
		return edges.size();
	}
	int getIndex() { return index; }
	Node(int index) { this->index = index; }
	Node() {}
};
class Graph {
public:
	map<int, Node> nodes;
	void createNode(int index)
	{
		nodes.insert(pair<int, Node>(index, Node(index)));
	}
	void addEdge(int index, int target, int weight)
	{
//		createNode(index);
//		createNode(target);
		nodes[index].connectNode(target, weight);
		nodes[target].connectNode(index, weight);
	}
	void Naive()
	{
		int * Cb = new int[nodes.size()];
		for (int i = 0; i < nodes.size(); i++) Cb[i] = 0;

		delete[] Cb;
	}
};
int minDistance(map<int, int> dist, map<int, bool> visited, int nodesAmount)
{
	int min = INT_MAX, min_index;
	for (int v = 0; v < nodesAmount; v++)
		if (visited[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;
	return min_index;
}
void dijkstra(map<int, Node> nodes, int src)
{
	map<int, bool> visited;
	map<int, int> dist;
	for (int i = 0; i < nodes.size(); i++) dist[i] = INT_MAX;
	dist[src] = 0;
	for (int i =0; i < nodes.size() -1; i++)
	{	
		int u = minDistance(dist, visited, nodes.size());
		visited[u] = true;
		if (dist[u] != INT_MAX)
		{
			for (int v = 0; v < nodes.size(); v++)
			{
				if (!visited[v] && nodes[u].edges.find(v) != nodes[u].edges.end()
					&& (dist[u]
						+ nodes[u].edges[v] < dist[v]))
					dist[v] = dist[u] + nodes[u].edges[v];
			}

		}
	}
	for (int i = 0; i < nodes.size(); i++)
	{
		cout << i << " : " << dist[i] << endl;
	}
}
int main()
{
	int n, m;
	cin >> n >> m;
	Graph graph;
	int t1, t2, t3;
	for (int i = 0; i < m; i++)
	{
		cin >> t1 >> t2 >> t3;
		graph.addEdge(t1, t2, t3);
	}
	dijkstra(graph.nodes, 0);
	cin >> t1;
	cout << graph.nodes[t1].sumEdges();
}