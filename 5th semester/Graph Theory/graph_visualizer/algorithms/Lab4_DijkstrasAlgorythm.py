from classes.graph.graph import *
from queue import Queue
import math


def algorythmDijkstra(graph: Graph, vertex_source: Vertex, print_names: bool, print_distances: bool):
    graph_vertices = graph.getVertexList()
    distances = dict()
    visited = dict()
    unvisited_vertices = Queue()
    unvisited_vertices.put(vertex_source)

    for vertex in graph_vertices:
        distances[vertex] = math.inf
        visited[vertex] = False
    distances[vertex_source]: int = 0

    while unvisited_vertices.qsize() > 0:
        vertex_current: Vertex = unvisited_vertices.get()
        vertex_current_edges = sorted([i for i in vertex_current.getAdjacentEdgeList()
                                       if (i.getStartVertex() == vertex_current or not i.isDirected())],
                                      key=(lambda x: int(x.getWeight())))

        for edge in vertex_current_edges:
            vertex_next = edge.getEndVertex()
            if vertex_next == vertex_current:
                vertex_next = edge.getStartVertex()

            if vertex_next is None:
                continue

            weight = edge.getWeight()
            if distances[vertex_next] == math.inf:
                distances[vertex_next] = distances[vertex_current] + weight
            elif distances[vertex_next] > distances[vertex_current] + weight:
                distances[vertex_next] = distances[vertex_current] + weight

            if not visited[vertex_next]:
                unvisited_vertices.put(vertex_next)
        visited[vertex_current] = True

    if print_names:
        distances_names = [i.getName() for i in distances.keys()]
        print('\n', distances_names)
    if print_distances:
        distances_values = [i for i in distances.values()]
        print(distances_values)

    return distances


def startDijkstra(graph: Graph, vertex_source: Vertex):
    graph_vertices = graph.getVertexList()

    for vertex in graph_vertices:
        algorythmDijkstra(graph, vertex, False, True)

    return algorythmDijkstra(graph, vertex_source, True, True)


def setVisualForDijkstra(distances):
    for i in distances.keys():
        if distances[i] is not None:
            i.setServiceValue("D=" + str(distances[i]))
