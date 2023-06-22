from classes.graph.graph import *
import heapq


def heuristic(a: Vertex, b: Vertex) -> float:
    (x1, y1) = a.getPos()
    (x2, y2) = b.getPos()
    return sqrt((x1 - x2)**2 + (y1 - y2)**2) / 120


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


def bestFirst(vertex_start: Vertex, vertex_end: Vertex):
    if vertex_start == vertex_end:
        return {}

    visited = dict()
    full_path = dict()
    unvisited_vertices = []
    heapq.heappush(unvisited_vertices, (0, vertex_start))

    while unvisited_vertices.__len__() > 0:
        vertex_current: Vertex = heapq.heappop(unvisited_vertices)[1]
        if vertex_current == vertex_end:
            break
        vertex_current_edges = [i for i in vertex_current.getAdjacentEdgeList()
                                if (i.getStartVertex() == vertex_current or not i.isDirected())]

        for edge in vertex_current_edges:
            vertex_next = edge.getEndVertex()
            if vertex_next == vertex_current:
                vertex_next = edge.getStartVertex()
            if vertex_next is None:
                continue
            if edge in visited or vertex_next == vertex_current:
                continue
            priority = heuristic(vertex_next, vertex_end)
            full_path[vertex_next] = vertex_current
            heapq.heappush(unvisited_vertices, (priority, vertex_next))
            visited[edge] = True

    shortest_path = reconstructPath(full_path, vertex_start, vertex_end)
    if not shortest_path:
        return shortest_path

    path_length = 0
    i = 0
    while i < shortest_path.__len__() - 1:
        vertex_current_edges = shortest_path[i].getAdjacentEdgeList()
        vertex_current_edges_path = []
        for edge in vertex_current_edges:
            if edge.getEndVertex() == shortest_path[i + 1] or edge.getStartVertex() == shortest_path[i + 1]:
                vertex_current_edges_path.append(edge)

        edge_path = sorted(vertex_current_edges_path, key=(lambda x: int(x.getWeight())))[0]
        path_length += edge_path.getWeight()
        edge_path.setColor("green")
        shortest_path[i].setColor("green")
        i += 1
    shortest_path[i].setColor("green")
    vertex_start.setColor("red")

    return path_length


def setVisualForBestFS(path_length, vertex_end: Vertex):
    vertex_end.setServiceValue("D=" + str(path_length))
