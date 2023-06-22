from classes.graph.graph import *


def addTreeEdge(vertex_set, tree, edge):
    vertex_set.add(edge.getStartVertex())
    vertex_set.add(edge.getEndVertex())
    tree.add(edge)
    edge.setColor("green")

    return True


def kruskalAlgorythm(graph: Graph):
    vertex_sets = []
    spanning_tree_edges = set()
    edges_sorted = sorted(graph.getEdgeList(), key=lambda x: int(x.getWeight()))

    for edge in edges_sorted:
        vertices_start = set()
        vertices_end = set()
        spanning_tree_found = False

        for vertex_set in vertex_sets:
            if edge.getStartVertex() in vertex_set:
                vertices_start = vertex_set
            if edge.getEndVertex() in vertex_set:
                vertices_end = vertex_set

        if vertices_start and vertices_end:
            spanning_tree_found = True
            if vertices_start != vertices_end:
                vertices_union = set.union(vertices_start, vertices_end)

                vertex_sets.remove(vertices_end)
                vertex_sets.remove(vertices_start)
                vertex_sets.append(vertices_union)

                spanning_tree_edges.add(edge)
                edge.setColor("green")
        elif vertices_start:
            spanning_tree_found = addTreeEdge(vertices_start, spanning_tree_edges, edge)
        elif vertices_end:
            spanning_tree_found = addTreeEdge(vertices_end, spanning_tree_edges, edge)

        if not spanning_tree_found:
            vertex_set = set()
            addTreeEdge(vertex_set, spanning_tree_edges, edge)
            vertex_sets.append(vertex_set)
