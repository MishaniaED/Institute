from classes.graph.graph import *
from algorithms.bfs import bfs
from queue import Queue


def cloneConnections(path, path_edges):
    i = 0
    while (i + 1) < len(path):
        nxt = i + 1
        for edge in path[i].getAdjacentEdgeList():
            if edge.getStartVertex() == path[nxt] or edge.getEndVertex() == path[nxt]:
                path_edges.append(edge)
        i += 1


def cycle(graph: Graph):
    cycles = []
    cycle_found = False
    for vertex in graph.getVertexList():
        cycle_found = False
        paths = [[vertex]]
        path_edges = []
        vertices_visited = set()
        vertices_unvisited = Queue()

        vertices_unvisited.put(vertex)
        vertices_visited.add(vertex)

        while vertices_unvisited.qsize() > 0 and not cycle_found:
            vertex_current: Vertex = vertices_unvisited.get()
            path = []

            for p in paths:
                if p.count(vertex):
                    paths.remove(p)
                    path = p
                    break

            for vertex_current_neighbor in vertex_current.getAdjacentVertexList():
                if vertex_current_neighbor in path:
                    continue
                path_extended = path.copy()
                path_extended.append(vertex_current_neighbor)

                if vertex_current_neighbor not in vertices_visited:
                    paths.append(path_extended)
                else:
                    for p in paths:
                        if p.count(vertex_current_neighbor):
                            cloneConnections(p, path_edges)
                            break

                    cloneConnections(path_extended, path_edges)

                    cycle_found = True
                    break

                vertices_visited.add(vertex_current_neighbor)
                vertices_unvisited.put(vertex_current_neighbor)
        if cycle_found:
            cycles.append(path_edges)

    if cycle_found:
        cycles.sort(key=lambda x: len(x))
        for edge in cycles[0]:
            edge.getStartVertex().setColor("green")
            edge.getEndVertex().setColor("green")
            edge.setColor("green")
    else:
        centre_search(graph)


def centre_search(graph: Graph):
    vertices = graph.getVertexList()
    depth = dict()

    for vertex in vertices:
        depths = bfs(graph, vertex)
        depth[vertex] = max(depths.values())
    if len(depth):
        sorted_depth = sorted(depth.items(), key=lambda x: x[1])
        depth_min = sorted_depth[0][0]
        for v in sorted_depth:
            if v[1] != depth_min:
                v[0].setColor("red")
                v[0].setServiceValue("D = " + str(v[1]))
                break
    return
