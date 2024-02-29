import matplotlib.pyplot as plt
import networkx as nx
import pygraphviz
from networkx.drawing.nx_pydot import graphviz_layout
import json

# Opening JSON file
f = open('takuzu_1.json')

# returns JSON object as
# a dictionary
data = json.load(f)

# Iterating through the json
node_info= {}
for n in data['nodes']:
    node_info[n['id']]="R="+str(n['reward'])+"\n V="+str(n['visits'])

edges=[]
for e in data['links']:
    edges.append([e['parent'],e['child']])
   # edges = [[0,1],[0,2],[1,3],[1,4]]

# Closing file
f.close()
#T = nx.balanced_tree(2, 5)

T = nx.Graph()

T.add_edges_from(edges)


pos = nx.nx_agraph.graphviz_layout(T,prog="dot")

nx.draw(T, pos,labels=node_info, with_labels = True)# node_size=500)
plt.show()