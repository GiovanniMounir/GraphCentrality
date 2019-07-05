#include <iostream>
#include <map>
#include <algorithm>
#include <string>
#include <set>
#include <list>
#include <stack>
#include <time.h>
#include <filesystem>
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
		//cout << j;
		bool _intermediate = false;
		//start: j;
		while (!s.empty())
		{
			int i = s.top();
			//cout << "," << i;
			s.pop();
			if (i == intermediate && !s.empty())
				_intermediate = true;
			else if (s.empty()) incrementPoint(_intermediate ? stv : st, j, i);
		}
		//cout << endl;

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
					{
						parent[edgeNode.first].insert(u);
					}
				}
			}
		}
	}
}
float betweenness(map<int, Node> nodes, set<int> * parent, int n, int intermediate = -1)
{
	map<pair<int, int>, int> stv;
	map<pair<int, int>, int> st;
	for (int i = n; i < nodes.size(); i++)
	{
		stack<int> s;
		find_st_stv(parent, s, i, intermediate, st, stv);
	}
	float sum = 0;
	for (auto i : stv)
	{
		sum += ((float)i.second / (float)((st.find(pair<int, int>(i.first.first, i.first.second)) != st.end()) ? (st[pair<int, int>(i.first.first, i.first.second)] + i.second) : i.second));
	}

	return sum;
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
				if (!visited[edgeNode.first] && (dist[u] + edgeNode.second < dist[edgeNode.first])) //pick minimum unvisited edge node in v
					dist[edgeNode.first] = dist[u] + nodes[u].edges[edgeNode.first];
			}
		}
	}
	return dist;
}

double closeness_node(int n, map<int, Node> & nodes) {
	double sum = 0;
	map<int, int> dist = dijkstra(nodes, n);
	for (int i = 0; i < nodes.size(); i++)
	{
		if (dist[i] > 0)
		{
			sum += dist[i];
		}
	}
	return (double)(nodes.size() - 1) / sum;
}
void closeness(map<int, Node> nodes)
{
	for (int n = 0; n < nodes.size(); n++)
		printf("g(%d) = %.12f\n",n, closeness_node(n, nodes));
}
void toLower(string &input)
{
	std::transform(input.begin(), input.end(), input.begin(), ::tolower);
}

const char *fname = tmpnam(NULL);
void exiting()
{
	_unlink((string(fname) + ".png").c_str());
	_unlink(fname);
	exit(0);
}

int main()
{
	int n, m;
	cin >> n >> m;
	Graph graph;
	int t1, t2, t3;
	FILE *fp = fopen(fname, "w");

	fputs("digraph {\n", fp);
	string input;


	for (int i = 0; i < m; i++)
	{
		cin >> t1 >> t2 >> t3;
		input = to_string(t1) + " -> " + to_string(t2) + " [dir=none,label=\"" + to_string(t3) + "\",weight=\"" + to_string(t3) + "\"];\n";
		fputs(input.c_str(), fp);
		graph.addEdge(t1, t2, t3);
	}
	fputs("}", fp);
	fclose(fp);
	fp = fopen((string(fname) + ".png").c_str(), "w");
	fclose(fp);
	std::atexit(exiting);
	std::string cmd;
	while (true)
	{
		getline(cin, cmd);
		toLower(cmd);
		
		if (cmd == "degree")
		{
			for (int n = 0; n < graph.nodes.size(); n++)	
				cout << "g(" << n << ")" << "= " << graph.nodes[n].sumEdges() << "\n";
		}
		else if (cmd == "closeness" || cmd == "close")
		{
			closeness(graph.nodes);
		}
		else if (cmd == "between" || cmd == "betweenness")
		{
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
			for (int n = 0; n < graph.nodes.size(); n++)
			{
				printf("g(%d)= %.12f\n", n, sum[n]);
				delete[] parent[n];
			}
			delete sum;
		}
		else if (cmd == "graph")
		{
			input = "dot.exe -Tpng \"" + string(fname) + "\" -o \"" + (string(fname) + ".png") + "\"";
			system(input.c_str());	
			system(string("mspaint.exe " + (string(fname) + ".png")).c_str());
		}
		else if (cmd == "quit" || cmd == "exit")
		{
			exiting();
		}
		else
		{
			cout << "----\nVALID COMMANDS:\n";
			cout << "degree\t\tDegree centerality\n";
			cout << "close\t\tCloseness centerality\n";
			cout << "between\t\tBetween Centerality\n";
			cout << "graph\t\tShow graph\n";
			cout << "quit\t\tExit\n----\n";
		}
	}
}