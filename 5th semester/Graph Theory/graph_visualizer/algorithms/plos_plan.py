from classes.graph.graph import *


def flat_graph(graph: Graph):
    edge_list = graph.getEdgeList().copy()

    for edge in graph.getEdgeList():
        start_v1 = edge.getStartVertex()
        end_v1 = edge.getEndVertex()
        edge_list.remove(edge)
        for edge2 in edge_list:
            start_v2 = edge2.getStartVertex()
            end_v2 = edge2.getEndVertex()
            if (start_v1 == start_v2) or (start_v1 == end_v2) or \
                    (end_v1 == start_v2) or (end_v1 == end_v2):
                continue
            elif crossing(start_v1, end_v1, start_v2, end_v2):
                return False
    return True


def crossing(a: Vertex, b: Vertex, c: Vertex, d: Vertex):
    a_x, a_y = a.getPos()
    b_x, b_y = b.getPos()
    c_x, c_y = c.getPos()
    d_x, d_y = d.getPos()
    return intersect(a_x, b_x, c_x, d_x) and \
           intersect(a_y, b_y, c_y, d_y) and \
           (area(a, b, c) * area(a, b, d) <= 0) and \
           (area(c, d, a) * area(c, d, b) <= 0)


def intersect(a: int, b: int, c: int, d: int):
    if a > b:
        a, b = b, a
    if c > d:
        c, d = d, c
    return max(a, c) <= min(b, d)


def area(a: Vertex, b: Vertex, c: Vertex):
    a_x, a_y = a.getPos()
    b_x, b_y = b.getPos()
    c_x, c_y = c.getPos()
    return (b_x - a_x) * (c_y - a_y) - (b_y - a_y) * (c_x - a_x)


def planar_graph(graph: Graph):
    i = flat_graph(graph)
    if i:
        return True
    else:
        count3, coutn2 = 0, 0
        p = len(graph.getVertexList())
        if p <= 4:
            return True
        for vert in graph.getVertexList():
            degree_v = len(vert.getAdjacentVertexList())
            if degree_v > 3:
                coutn2 += 1
                count3 += 1
            elif degree_v > 2:
                coutn2 += 1
        if (count3 <= 4) and (coutn2 <= 5):
            return True
        q = len(graph.getEdgeList())
        if q <= 3 * p - 6:
            return True
        else:
            return False
