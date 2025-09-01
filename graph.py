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
        for i, row in enumerate(self.adjacency_matrix):
            self.graph[str(i)] = []
            idx = np.nonzero(row)[0]
            for id_ in idx:
                if self.weighted:
                    self.graph[str(i)] += [(str(id_), row[id_])]
                else:
                    self.graph[str(i)] += [str(id_)]
    
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
            prev = [None for _ in range(nb_node)]
            while not queue.empty():
                node = queue.get()
                if node == node_end:
                    return prev
                for n in self.graph[str(node)]:
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
        assert self.graph != {}, "You should build the graph first"
        if node_start == node_end:
            return True
        neighbour = self.graph[str(node_start)]
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
        Apply Dijsktra's algorithm on the graph. Find all the shortest path from start_nodes
        to all other nodes.
        Requires: positively weighted graph.
        """
        if not self.weighted:
            raise ValueError("Please, consider using bfs or dfs algorithm for unweighted graphs")
        value = [np.inf for _ in range(self.nb_node)]
        unvisited = set(range(self.nb_node))
        value[start_node] = 0
        prev = [None for _ in range(self.nb_node)]
                
        while not unvisited.empty():
            v = np.argmin(value) #Closest node to v
            unvisited.remove(v)
            neigh = self.graph[v]
            for n, weight in neigh:
                if n in unvisited:
                    if value[n] > value[v] + weight:
                        value[n] = value[v] + weight
                        prev[n] = v
        return value, prev

    def Dijkstra_algorithm_with_heap(self, start_node):
        """
        Apply Dijsktra's algorithm on the graph. Find all the shortest path from start_nodes
        to all other nodes. This time, one uses a min-heap data structure to recover easily 
        Requires: positively weighted graph.
        """
        if not self.weighted:
            raise ValueError("Please, consider using bfs or dfs algorithm for unweighted graphs")
        value = [(np.inf, i) for i in range(self.nb_node)]
        unvisited = set(range(self.nb_node))
        value[start_node] = (0, start_node)
        prev = [None for _ in range(self.nb_node)]

        while not unvisited.empty():
            v = heapq.heappop(value) #Closest node to v
            unvisited.remove(v)
            neigh = self.graph[v]
            for n, weight in neigh:
                if n in unvisited:
                    if value[n][0] > value[v][0] + weight:
                        value[n][0] = value[v][0] + weight
                        prev[n] = v
            heapq.heapify(value)
        return value, prev


    def Bellman(self, start_node):
        """
        Implementation of Bellman-Ford algorithm. It has a time complexity of O(|V| |E|).
        Requires: weighted and directed graph. 
            If not directed and weightless, use BFS or DFS.
            If not directed but with weights: use Dijkstra's algorithm.
        """
        if not self.directed and self.weighted:
            raise ValueError("Please, consider using Dijkstra's algorithms")
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
    Adj = [[0,1,0,1], [1,0,1,0], [0,1,0,1], [1, 0, 1, 0]]
    G = Graph(4, Adj)
    G.build_graph()
    path = G.find_shortest_path_dfs('0', '2', ['0'], set('0'))
    print(path)