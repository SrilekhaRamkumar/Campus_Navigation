import sys
import networkx as nx
import matplotlib.pyplot as plt
import os

def read_edges(file_path):
    edges = []
    with open(file_path, 'r') as file:
        for line in file:
            edge = tuple(map(int, line.strip().split()))
            edges.append(edge)
    return edges

def read_coordinates(file_path):
    node_positions = {}
    with open(file_path, 'r') as file:
        for line in file:
            node, x, y = map(int, line.strip().split())
            node_positions[node] = (x, -y)  
    return node_positions

def read_labels(file_path):
    node_labels = {}
    with open(file_path, 'r') as file:
        for line in file:
            node, label = line.strip().split()
            node_labels[int(node)] = label
    return node_labels

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: python visualize_graph.py <edges_file> <coors_file> <mapping_file>")
        sys.exit(1)

    edges_file = sys.argv[1]
    coors_file = sys.argv[2]
    mapping_file = sys.argv[3]

    edges = read_edges(edges_file)

    node_positions = read_coordinates(coors_file)

    node_labels = read_labels(mapping_file)

    G = nx.Graph()

    G.add_edges_from(edges)

    node_size = 3600

    plt.figure(figsize=(15, 12))  
    nx.draw(G, pos=node_positions, labels=node_labels, with_labels=True, node_color='blue', font_color='white', node_size=node_size)

    # Save the graph visualization as an image
    plt.savefig('graph_visualization.png')

    plt.close()

    os.system('start graph_visualization.png') 