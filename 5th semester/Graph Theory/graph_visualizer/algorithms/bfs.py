from classes.graph.graph import *
from queue import Queue


def get_end_node(begin: Vertex, edge: Edge):
    tmp_end_node = edge.getEndVertex()
    if tmp_end_node == begin:
        tmp_end_node = edge.getStartVertex()
    return tmp_end_node


def bfs(graph: Graph, vertex: Vertex):
    depth = {}

    for i in graph.getVertexList():
        depth[i] = None

    depth[vertex] = 0
    nodes_to_visit = Queue()
    nodes_to_visit.put(vertex)

    while nodes_to_visit.qsize() > 0:
        u: Vertex = nodes_to_visit.get()
        adj_list = [get_end_node(u, i) for i in u.getAdjacentEdgeList()
                    if (i.getStartVertex() == u or not i.isDirected())]
        for i in adj_list:
            if depth[i] is None:
                depth[i] = depth[u] + 1
                nodes_to_visit.put(i)
    return depth


def setVisualForBFS(depth, start_vertex: Vertex):
    for i in depth.keys():
        if depth[i] != 0 and depth[i] is not None:
            i.setColor("pink")
            i.setServiceValue("n=" + str(depth[i]))
    start_vertex.setColor("red")
