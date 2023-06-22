from classes.graph.graph import *
import heapq
import math


def heuristic(a: Vertex, b: Vertex) -> float:
    (x1, y1) = a.getPos()
    (x2, y2) = b.getPos()
    return sqrt((x1 - x2) ** 2 + (y1 - y2) ** 2) / 120


def reconstructPath(full_path, vertex_start: Vertex, vertex_end: Vertex):
    current_vertex = vertex_end
    shortest_path = []

    while current_vertex != vertex_start:
        shortest_path.append(current_vertex)
        if current_vertex in full_path.keys():
            current_vertex = full_path[current_vertex]
        else:
            return False
    shortest_path.append(vertex_start)
    shortest_path.reverse()

    return shortest_path


def algorythmAStar(graph: Graph, vertex_start: Vertex, vertex_end: Vertex, print_distances: bool):
    if vertex_start == vertex_end:
        return {}
    graph_vertices = graph.getVertexList()
    distances = dict()
    visited = dict()
    full_path = dict()
    unvisited_vertices = []

    heapq.heappush(unvisited_vertices, (0, vertex_start))

    for vertex in graph_vertices:
        distances[vertex] = math.inf
        visited[vertex] = False
    distances[vertex_start]: int = 0
    full_path[vertex_start] = None

    while unvisited_vertices.__len__() > 0:
        vertex_current: Vertex = heapq.heappop(unvisited_vertices)[1]
        if vertex_current == vertex_end:
            break
        vertex_current_edges = sorted([i for i in vertex_current.getAdjacentEdgeList()
                                       if (i.getStartVertex() == vertex_current or not i.isDirected())],
                                      key=(lambda x: int(x.getWeight())))
        print(vertex_current.getName())

        for edge in vertex_current_edges:
            vertex_next = edge.getEndVertex()
            if vertex_next == vertex_current:
                vertex_next = edge.getStartVertex()
            elif vertex_next is None:
                continue

            weight = edge.getWeight()

            new_distance = distances[vertex_current] + weight
            if vertex_next not in distances or new_distance < distances[vertex_next]:
                distances[vertex_next] = new_distance
                priority = new_distance + heuristic(vertex_next, vertex_end)
                full_path[vertex_next] = vertex_current
                if not visited[vertex_next]:
                    heapq.heappush(unvisited_vertices, (priority, vertex_next))
        visited[vertex_current] = True

    shortest_path = reconstructPath(full_path, vertex_start, vertex_end)
    if not shortest_path:
        return shortest_path

    i = 0
    while i < shortest_path.__len__() - 1:
        vertex_current_edges = shortest_path[i].getAdjacentEdgeList()
        vertex_current_edges_path = []
        for edge in vertex_current_edges:
            if edge.getEndVertex() == shortest_path[i + 1] or edge.getStartVertex() == shortest_path[i + 1]:
                vertex_current_edges_path.append(edge)

        sorted(vertex_current_edges_path, key=(lambda x: int(x.getWeight())))[0].setColor("green")
        shortest_path[i].setColor("green")
        i += 1
    shortest_path[i].setColor("green")
    vertex_start.setColor("red")

    if print_distances:
        distances_values = [i for i in distances.values()]
        print(distances_values)

    return distances


def setVisualForAStar(distances):
    for i in distances.keys():
        if distances[i] is not None:
            i.setServiceValue("D=" + str(distances[i]))
