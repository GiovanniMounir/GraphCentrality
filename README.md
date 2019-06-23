# Graph Centrality
Developed by Giovanni Mounir, Paul Ragheb and Beshoy Abd El Sayed, this project provides a tool to calculate the following graph centrality measures:
- Degree Centrality
- Closeness Centrality
- Betweenness Centrality.
The calculations are implemented in C++.

The project also provides a DrawTool to visualize the graph, implemented in Python.

## Installing DrawTool dependencies
1. Install latest python version from <a href="https://www.python.org/downloads/" >here</a>  
2. Download pip from <a href="https://bootstrap.pypa.io/get-pip.py">here</a>  
3. Run on python's terminal <code>$ python get-pip.py</code>  
4. Run on python's terminal <code>$ pip install matplotlib </code>  
5. Run on python's terminal <code>$ pip install networkx</code>  
6. Run our `drawtool.py` present in our repo: <code>$ python drawtool.py</code>
7. Add a `nodes.txt` file which contains your input in the following format:
```
%NodesCount% %EdgesCount%
%Edge1NodeFrom% %Edge1NodeTo% %Edge1Weight%
%Edge2NodeFrom% %Edge2NodeTo% %Edge2Weight%
...
```
**Example Input**<br>
For 5 nodes and 6 edges, supply the following:

```
5 6
0 1 1
1 3 1
3 2 1
3 4 1
4 2 3
2 0 1
```
