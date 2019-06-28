#include <iostream>
#include <map>
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
		nodes[index].connectNode(target, weight);
		nodes[target].connectNode(index, weight);
	}
};
int minDistance(map<int, int> dist, map<int, bool> visited)
{
	int min = INT_MAX, min_index;
	for (int v = 0; v < dist.size(); v++)
		if (visited[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;
	return min_index; //possible crash: variable not defined; should not happen
}
map<int, int> dijkstra(map<int, Node> nodes, int n)
{
	map<int, bool> visited;
	map<int, int> dist;
	for (int i = 0; i < nodes.size(); i++) visited[i] = false, dist[i] = INT_MAX;
	dist[n] = 0;
	for (int i = 0; i < nodes.size() - 1; i++)
	{
		int u = minDistance(dist, visited);
		visited[u] = true;
		if (dist[u] != INT_MAX)
		{
			for (auto const& edgeNode : nodes[u].edges) //foreach edge in u.. (key = node, value = weight)
			{
				if (!visited[edgeNode.first])
				{
					if ((dist[u] + edgeNode.second < dist[edgeNode.first])) //pick minimum unvisited edge node in v
					{
						dist[edgeNode.first] = dist[u] + nodes[u].edges[edgeNode.first];

					}
				}
			}
		}
	}
	return dist;
}
void closeness(map<int, Node> nodes)
{
	for (int n = 0; n < nodes.size(); n++)
	{
		double sum = 0;
		map<int, int> dist = dijkstra(nodes, n);
		for (int i = 0; i < nodes.size(); i++)
		{
			if (dist[i] > 0)
			{
				sum += dist[i];
			}
		}
		double ratio = (double)(nodes.size() - 1) / sum;
		printf("%.12f\n", ratio);
	
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
	closeness(graph.nodes);
}