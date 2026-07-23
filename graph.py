# -*- coding: utf-8 -*-
"""
Created on Sat Feb 22 13:30:31 2025

@author: hugon
"""
from dataclasses import dataclass, field
from queue import Queue
import numpy as np
import heapq

@dataclass
class Graph:
    nb_of_node: int
    adjacency_matrix: list[list[int]]
    weighted: bool = False
    directed: bool = False
    graph: dict() = field(default_factory=dict)

    def build_graph(self):
        if self.weighted:
            for i, row in enumerate(self.adjacency_matrix):
                self.graph.update({i: []})
                idx = np.nonzero(row)[0]
                for id_ in idx:
                        self.graph[i] += [(row[id_], id_)]
        else:
            for i, row in enumerate(self.adjacency_matrix):
                self.graph.update({i: []})
                idx = np.nonzero(row)[0]
                for id_ in idx:
                    self.graph[i] += [id_]

    def find_shortest_path_bfs(self, node_start, node_end):
        """
        Find shortest path between node_start and node_end using breadth-first-search strategy.
        The algorithm's time complexity scales as O(|V| + |E|)
        """
        def shortest_path(node_start, node_end, nb_node):
            if self.weighted: 
                raise ValueError("The graph should be unweighted")
            queue = Queue()
            queue.put(node_start)
            visited=set()
            prev = [None]*self.nb_of_node
            while not queue.empty():
                node = queue.get()
                if node == node_end:
                    return prev
                for n in self.graph[node]:
                    if n not in visited:
                        visited.add(n)
                        prev[n] = node
                        queue.put(n)

        prev = shortest_path(node_start, node_end, self.nb_of_node)
        path = [node_end]
        node = node_end
        while node != node_start:
            path += [prev[node]]
            node = prev[node]
        return path[::-1]

    def find_shortest_path_dfs(self, node_start, node_end, path: list[int], visited: set):
        """
        Find shortest path between node_start and node_end using depth-first-search strategy.
        The algorithm's time complexity scales as O(|V| + |E|)
        """
        if self.weighted:
            raise ValueError("The graph should be unweighted")
        assert self.graph != {}, "You should build the graph first"
        if node_start == node_end:
            return True
        neighbour = self.graph[node_start]
        for n in neighbour:
            if n not in visited:
                visited.add(n)
                path.append(n)
                if self.find_shortest_path_dfs(n, node_end, path, visited):
                    return path
                path.remove(n)
        return False

    def Dijkstra_algorithm(self, start_node):
        """
        Apply Dijsktra's algorithm on the graph. Find all the shortest path from start_node
        to all other nodes. This time, one uses a min-heap data structure to recover easily 
        Requires: positively weighted graph. Time complexity scales as O(|V| + |E| log(|V|)).
        """

        value=[[np.inf, i] for i in range(self.nb_of_node)]
        unvisited = set(range(self.nb_of_node))
        value[start_node] = [0, start_node]
        paths=[[start_node]]*self.nb_of_node

        heapq.heapify(value)
        while len(unvisited)>0:
            v=heapq.heappop(value)
            dist, idx=v
            unvisited.remove(idx)
            neighbors=self.graph[idx]
            for val, node in neighbors:
                if node in unvisited:
                    k = np.where(np.array(value)[:,1]==node)[0].item()
                    if value[k][0] > dist + val:
                        value[k][0] = dist + val
                        paths[k] = paths[idx]+[idx]
            heapq.heapify(value)
        return value, paths

    def Dijkstra_algorithm_optimized(self, start_node):
        """
        Apply Dijsktra's algorithm on the graph. Find all the shortest path from start_node
        to all other nodes. This time, one uses a min-heap data structure to recover easily 
        Requires: positively weighted graph. Time complexity scales as O(|V| + |E| log(|V|)).
        """
        value=[np.inf]*self.nb_of_node
        start_node=int(start_node)
        value[start_node] = 0
        heap=[[0, start_node]]
        paths=[[start_node]]*self.nb_of_node
        while len(heap)>0:
            val, idx=heapq.heappop(heap)
            if value[idx]<val:
                continue
            neighbours=self.graph[idx]
            for node, weight in neighbours:
                if value[node]>val+weight:
                    value[node]=val+weight
                    heapq.heappush(heap, [node, value[node]])
                    paths[node]=paths[idx] + [idx]
        return value, paths



    def Bellman(self, start_node):
        """
        Implementation of Bellman-Ford algorithm. It has a time complexity of O(|V| |E|).
        Requires: weighted and directed graph. 
            If not directed and weightless, use BFS or DFS.
            If not directed but with weights: use Dijkstra's algorithm.
        """
        if not self.directed and self.weighted:
            raise ValueError("Please, consider using Dijkstra's algorithm.")
        elif not self.directed and not self.weighted:
            raise ValueError("Please, consider using bfs algorithm.")

        dist, prev = np.inf*np.ones((self.nb_node)), np.empty((self.nb_node))
        dist[start_node] = 0

        for _ in range(self.nb_node):
            for i, row in enumerate(self.adjacency_matrix):
                edge = np.nonzero(row)[0]
                for e in edge:
                    if dist[i] + row[e] < dist[e]:
                        dist[e] = dist[i] + row[e]
                        prev[e] = i
        return dist, prev

    def Ford(self, start_node):
        pass

    def Kruskal(self, start_node):
        pass

if __name__ == "__main__":
    import matplotlib.pyplot as plt
    import time
    N=[5, 10, 100, 50, 100]
    Time_DFS=[]
    Time_BFS=[]
    Time_Dijkstra=[]
    Time_Dijkstra_optimized=[]
    for n in N:
        Adj = np.random.randint(low=0, high=3, size=(n, n))
        G = Graph(n, Adj)
        G.build_graph()

        t0=time.time()
        path = G.find_shortest_path_dfs(0, 2, [0], set([0]))
        t1=time.time()
        Time_DFS.append(t1-t0)

        t0=time.time()
        path = G.find_shortest_path_bfs(0, 2)
        t1=time.time()
        Time_BFS.append(t1-t0)
    
        G.weighted=True
        G.build_graph()
        t0=time.time()
        val, paths = G.Dijkstra_algorithm(0)
        t1=time.time()
        Time_Dijkstra.append(t1-t0)

        t0=time.time()
        val, paths = G.Dijkstra_algorithm_optimized(0)
        t1=time.time()
        Time_Dijkstra_optimized.append(t1-t0)
    
    plt.plot(Time_DFS, label="Depth-First Search")
    plt.plot(Time_BFS, label="Breadth-First Search")
    plt.plot(Time_Dijkstra, label="Dijkstra algorithm")
    plt.plot(Time_Dijkstra_optimized, label="Heap optimized Dijkstra algorithm")
    plt.yscale("log")
    plt.legend()
    plt.show()
    