#include <iostream>
#include <map>
#include <string>
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
	return min_index; //possible crash: variable not defined; should not happen
}
string printPath(int parent[], int j)
{
	if (parent[j] == -1)
		return "";
	return  printPath(parent, parent[j]) + "->" + to_string(j);
}
void dijkstra(map<int, Node> nodes, int intermediate)
{
	map<int, bool> visited;
	map<int, int> dist;
	int * parent = new int[nodes.size()];
	for (int n = 0; n < nodes.size(); n++)
	{
		for (int i = 0; i < nodes.size(); i++) parent[i] = -1, visited[i] = false, dist[i] = INT_MAX;
		dist[n] = 0;
		cout << "[" << n << "]" << endl;
		int j = 0;
		while (j < nodes.size())
		{
			int u = minDistance(dist, visited, nodes.size());
			visited[u] = true;
			j++;
			if (dist[u] != INT_MAX)
			{
				for (auto const& edgeNode : nodes[u].edges) //foreach edge in u.. (key = node, value = weight)
				{
					if (!visited[edgeNode.first] && (dist[edgeNode.first] + edgeNode.second < dist[edgeNode.first])) //pick minimum unvisited edge node in v
					{
						parent[edgeNode.first] = u;
						dist[edgeNode.first] = dist[u] + nodes[u].edges[edgeNode.first];
					}
				}
			}
		}
		for (int i = 0; i < nodes.size(); i++)
		{
			if (dist[i] > 0) {
				cout << n << printPath(parent, i);
				cout << " : " << dist[i] << endl;
			}
		}
	}
	delete[] parent;
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
	dijkstra(graph.nodes, 2);
	cin >> t1;
	cout << graph.nodes[t1].sumEdges();
}