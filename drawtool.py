import networkx as nx
import matplotlib.pyplot as plt


G = nx.Graph()
with open("nodes.txt") as f:
    content = f.read().splitlines()

for line in content[1:]:
    [a, b, c] = line.split()
    G.add_edges_from([(a, b,)], weight=int(c))


edge_labels=dict([((u,v,),d['weight'])
                 for u,v,d in G.edges(data=True)])

pos=nx.spring_layout(G)
nx.draw_networkx_edge_labels(G,pos,edge_labels=edge_labels)
nx.draw(G,pos, node_size=1500,with_labels=True)
plt.show()
