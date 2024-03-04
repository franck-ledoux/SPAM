from collections import defaultdict
import matplotlib.pyplot as plt
import networkx as nx
import json
import sys


def filter_params(param_dict):
    if len(param_dict) != 2:
        print("Invalid parameters, 1 json parameter file must be provided and it must contain 4 fields")
        print("\t 1.[in ] JSON file that contains the MCTS info")
        print("\t 2.[in ] Node id we want to start from ")
        print("\t 3.[in ] Subtree depth (0 means only the node previously given")
        print("\t 4.[out] File to save the graph (png)")
        print("For instance :")
        print("{")
        print("\"tree_file\":\"takuzu_2.json\",")
        print("\"image_file\":\"tree.png\",")
        print("\"source-node\":1,")
        print("\"depth\":2")
        print("}")
        exit(0)
    f = open(param_dict[1])
    data = json.load(f)
    f.close()
    return data["tree_file"], int(data["source-node"]), int(data["depth"]), data["image_file"]

def create_tree(file_name, node_id, depth):

    f = open(file_name)
    data = json.load(f)

    # Iterating through the json
    node_info = {}
    for n in data['nodes']:
        node_info[n['id']] = (n['id'],n['reward'], n['visits'], n['depth'])

    edges = []
    for e in data['links']:
        edges.append([e['parent'], e['child']])
    f.close()

    tree = nx.DiGraph()
    tree.add_edges_from(edges)
    t = nx.dfs_tree(tree, source=node_id, depth_limit=depth)
    node_layers = defaultdict(list)
    source_depth = int(node_info[node_id][3])
    for n in t.nodes():
        node_layers[node_info[n][3] - source_depth].append(n)

    for l in node_layers.values():
        print("Layer "+str(len(l)))
    max_number_nodes = max(node_layers.values())
    print("Max number of nodes: ", max_number_nodes)
    space = 700
    y=0
    x=0
    pos=defaultdict()
    for d,ns in node_layers.items():
        for n in ns:
            pos[n]=(x,y)
            x = x+space
        x=0
        y= y -600

    return t, node_info, pos


def display(tree, node_data, pos, file_out):
    labels = {}
    for n in tree:
        labels[n] = ((str(int(node_data[n][0]))
                     +"\n R="+str(int(node_data[n][1])))
                     +"\n V="+str(int(node_data[n][2])))

    plt.figure(figsize=(20,3))
    nx.draw_networkx_nodes(tree, pos, node_size=600, alpha=1, node_shape='s')
    nx.draw_networkx_edges(tree,pos,width=4, alpha=0.2, arrowsize=1)
    nx.draw_networkx_labels(tree,pos,labels,font_size=6)
    plt.tight_layout()
    plt.axis("off")
    plt.savefig(file_out)
    plt.show()




if __name__ == '__main__':
    json_in, node_id, depth, png_out = filter_params(sys.argv)
    print("Input graph file:", json_in)
    print("Node id:         ", node_id)
    print("Depth:           ", depth)
    print("Ouput file:      ", png_out)
    t, node_info, pos = create_tree(json_in, node_id, depth)
    display(t, node_info, pos, png_out)
