#include <iostream>
#include <map>
#include <set>
#include <stack>
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

void incrementPoint(map<pair<int, int>, int> & table, int start, int end)
{
	if (table.find(pair<int, int>(start, end)) != table.end()) table[pair<int, int>(start, end)]++;
	else table[pair<int, int>(start, end)] = 1;
}
void find_st_stv(set<int> * parent, stack<int> s, int j, int intermediate, map<pair<int, int>, int> & st, map<pair<int, int>, int> & stv)
{
	if (*parent[j].begin() == -1)
	{
		if (s.empty()) return;
		bool _intermediate = false;
		while (!s.empty())
		{
			int i = s.top();
			s.pop();
			if (i == intermediate && !s.empty())
				_intermediate = true;
			else if (s.empty()) incrementPoint(_intermediate ? stv : st, j, i);
		}

		return;
	}
	s.push(j);

	for (auto i : parent[j])
	{
		find_st_stv(parent, s, i, intermediate, st, stv);
	}
	return;
}

int minDistance(map<int, int> dist, map<int, bool> visited)
{
	int min = INT_MAX, min_index;
	for (int v = 0; v < dist.size(); v++)
		if (visited[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;
	return min_index; //possible crash: variable not defined; should not happen
}

void dijkstra_parent(map<int, Node> nodes, int n, set<int> * parent)
{
	map<int, bool> visited;
	map<int, int> dist;
	for (int i = 0; i < nodes.size(); i++) visited[i] = false, dist[i] = INT_MAX;
	dist[n] = 0;
	parent[n].insert(-1);
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
						parent[edgeNode.first].clear();
						parent[edgeNode.first].insert(u);
						dist[edgeNode.first] = dist[u] + nodes[u].edges[edgeNode.first];
					}
					else if (dist[u] + edgeNode.second == dist[edgeNode.first])
						parent[edgeNode.first].insert(u);
				}
			}
		}
	}
}
double betweenness(map<int, Node> nodes, set<int> * parent, int n, int intermediate = -1)
{
	map<pair<int, int>, int> stv;
	map<pair<int, int>, int> st;
	for (int i = n; i < nodes.size(); i++)
	{
		stack<int> s;
		find_st_stv(parent, s, i, intermediate, st, stv);
	}
	double sum = 0;
	for (auto i : stv)
		sum += ((double)i.second / (double)((st.find(pair<int, int>(i.first.first, i.first.second)) != st.end()) ? (st[pair<int, int>(i.first.first, i.first.second)] + i.second) : i.second));
	return sum;
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
	map<int, set<int> *> parent;
	
	double  * sum = new double[graph.nodes.size()];
	
	for (int n = 0; n < graph.nodes.size(); n++)
		sum[n] = 0;

	for (int n = 0; n < graph.nodes.size(); n++)
	{
		parent[n] = new set<int>[graph.nodes.size()];
		dijkstra_parent(graph.nodes, n, parent[n]);
		for (int i = 0; i < graph.nodes.size(); i++)
			sum[i] += betweenness(graph.nodes, parent[n], n, i);
	}
	for (int n = 0; n < graph.nodes.size() -1 ; n++)
		printf("%.12f\n", sum[n]);
	printf("%.12f\n", sum[graph.nodes.size() - 1]);
}