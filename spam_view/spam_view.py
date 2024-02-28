import networkx as nx
from networkx.readwrite import json_graph
from networkx.drawing.nx_pydot import graphviz_layout
import matplotlib.pyplot as plt

# Replace graph_json variable with JSON representation of graph
graph_json = {"nodes": [{"id": 1, "name": "A"},{"id": 2, "name": "B"}],"links": [{"source":1,"target":2}]}

node_labels = {node['id']:node['name'] for node in graph_json['nodes']}
for n in graph_json['nodes']:
    del n['name']
g = json_graph.node_link_graph(graph_json, directed=True, multigraph=False)
pos = graphviz_layout(g, prog="dot")
nx.draw(g.to_directed(), pos, labels=node_labels, with_labels=True)
plt.show()
