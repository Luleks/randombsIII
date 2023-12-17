from collections import namedtuple
import random
import time
import os
import networkx as nx


GraphEdge = namedtuple('GraphEdge', ['node1', 'node2', 'weight'])


class Graph:

    def __init__(self):
        self.graph: dict[int, list[GraphEdge]] = dict()
        self.edges: set[GraphEdge] = set()
    
    def add_node(self, node_val: int) -> bool:
        if node_val in self.graph:
            return False
        self.graph[node_val] = []
        return True

    def add_edge(self, node1: int, node2: int, weight: int = 1) -> bool:
        if node1 not in self.graph or node2 not in self.graph or node1 == node2:
            return False
        edge = GraphEdge(node1, node2, weight)
        if edge in self.edges:
            return False
        self.graph[node1].append(edge)
        self.graph[node2].append(edge)
        self.edges.add(edge)
        return True

    def kruskal(self) -> list[GraphEdge]:
        parent = [i for i in range(len(self.graph))]
        rank = [0] * len(self.graph)

        def find(node):
            if parent[node] != node:
                parent[node] = find(parent[node])
            return parent[node]

        def union(node1, node2):
            root1 = find(node1)
            root2 = find(node2)

            if root1 != root2:
                if rank[root1] > rank[root2]:
                    parent[root2] = root1
                elif rank[root1] < rank[root2]:
                    parent[root1] = root2
                else:
                    parent[root1] = root2
                    rank[root2] += 1

        result = []

        edges = sorted(list(self.edges), key=lambda edge: edge.weight)
        for edge in edges:
            if find(edge.node1) != find(edge.node2):
                result.append(edge)
                union(edge.node1, edge.node2)

        return result
        

def tabelar_view(graph_type, N, k, time_custom, time_nx, correct):
    custom_kruskal = len("Custom Kruskal Time[s]") + 2
    nx_mst = len("NetworkX's MST Alg Time[s]") + 2
    correctness_size = len("Correctness") + 2
    N_space = 9
    K_space = 9
    graph_type_space = len(" GraphType ") + 2
    horizontal_line = " _________________________________________________________________________________________________________________\n"
    if not os.path.exists("report.txt"):
        with open("report.txt", "w") as f:
            f.write(horizontal_line)
            f.write("|   GraphType   |     N     |     K     |  Custom Kruskal Time[s]  |  NetworkX's MST Alg Time[s]  |  Correctness  |\n")
        return 
    
    with open("report.txt", "a") as f:
        f.write(horizontal_line)

        str_to_write = ""

        str_to_write += f'| {" " * ((graph_type_space - len(graph_type)) // 2)}{graph_type}'\
                        f'{" " * (graph_type_space - len(graph_type) - (graph_type_space - len(graph_type)) // 2)} '

        str_to_write += f'| {" " * ((N_space - len(str(N))) // 2)}{N}'\
                        f'{" " * (N_space - len(str(N)) - (N_space - len(str(N))) // 2)} '
        
        str_to_write += f'| {" " * ((K_space - len(str(k))) // 2)}{k}'\
                        f'{" " * (K_space - len(str(k)) - (K_space - len(str(k))) // 2)} '
        
        str_to_write += f'| {" " * ((custom_kruskal - len(str(time_custom))) // 2)}{time_custom}'\
                        f'{" " * (custom_kruskal - len(str(time_custom)) - (custom_kruskal - len(str(time_custom))) // 2)} '
        
        str_to_write += f'| {" " * ((nx_mst - len(str(time_nx))) // 2)}{time_nx}'\
                        f'{" " * (nx_mst - len(str(time_nx)) - (nx_mst - len(str(time_nx))) // 2)} '

        str_to_write += f'| {" " * ((correctness_size - len(correct)) // 2)}{correct}'\
                        f'{" " * (correctness_size - len(correct) - (correctness_size - len(correct)) // 2)} '

        str_to_write += "|\n"

        f.write(str_to_write)


def main():
    Ns = [100, 1000, 10_000, 100_000]
    Ks = [2, 5, 10, 20, 33, 50]

    # Testcase 1
    for N in Ns:
        for k in Ks:
            K = N * k
            
            graph = Graph()

            for i in range(N):
                graph.add_node(i)
            
            random_node = random.randint(0, N - 1)
            for i in range(N):
                graph.add_edge(random_node, i, random.randint(1, N))
            
            while len(graph.edges) < K + N - 1:
                graph.add_edge(random.randint(0, N - 1), random.randint(0, N - 1), random.randint(1, N))

            start_time_custom = time.perf_counter()
            mst = graph.kruskal()
            end_time_custom = time.perf_counter()

            nx_graph = nx.Graph()
            for edge in graph.edges:
                nx_graph.add_edge(edge.node1, edge.node2, weight=edge.weight)
                nx_graph.add_edge(edge.node2, edge.node1, weight=edge.weight)

            start_time_nx = time.perf_counter()
            nx_mst = nx.minimum_spanning_tree(nx_graph)
            end_time_nx = time.perf_counter()
            nx_mst = [GraphEdge(node1, node2, nx_graph[node1][node2]['weight']) for node1, node2 in nx_mst.edges]

            nx_graph_tree = nx.Graph()
            for edge in mst:
                nx_graph_tree.add_edge(edge.node1, edge.node2)
                nx_graph_tree.add_edge(edge.node2, edge.node1)

            correctness = "Correct" if nx.is_tree(nx_graph_tree) and len(mst) == len(nx_mst) else "Incorrect"
            tabelar_view("RandToAll", N, k, round(end_time_custom - start_time_custom, 2), round(end_time_nx - start_time_nx, 2), correctness)

    # Testcase 2
    for N in Ns:
        for k in Ks:
            K = N * k
            
            graph = Graph()

            for i in range(N):
                graph.add_node(i)
            
            for i in range(N):
                graph.add_edge(i, (i + 1) % N, random.randint(1, N))
            
            while len(graph.edges) < K + N:
                graph.add_edge(random.randint(0, N - 1), random.randint(0, N - 1), random.randint(1, N))

            start_time_custom = time.perf_counter()
            mst = graph.kruskal()
            end_time_custom = time.perf_counter()

            nx_graph = nx.Graph()
            for edge in graph.edges:
                nx_graph.add_edge(edge.node1, edge.node2, weight=edge.weight)
                nx_graph.add_edge(edge.node2, edge.node1, weight=edge.weight)

            start_time_nx = time.perf_counter()
            nx_mst = nx.minimum_spanning_tree(nx_graph)
            end_time_nx = time.perf_counter()
            nx_mst = [GraphEdge(node1, node2, nx_graph[node1][node2]['weight']) for node1, node2 in nx_mst.edges]

            nx_graph_tree = nx.Graph()
            for edge in mst:
                nx_graph_tree.add_edge(edge.node1, edge.node2)
                nx_graph_tree.add_edge(edge.node2, edge.node1)

            correctness = "Correct" if nx.is_tree(nx_graph_tree) and len(mst) == len(nx_mst) else "Incorrect"
            tabelar_view("DaisyChain", N, k, round(end_time_custom - start_time_custom, 2), round(end_time_nx - start_time_nx, 2), correctness)


if __name__ == '__main__':
    main()
