from algorithms.bfs import *
import itertools


def isomorphism(graph: Graph):
    vertices = graph.getVertexList().copy()
    graph_first = Graph()
    graph_second = Graph()
    graph_dict_first = {'vertices': [], 'edges': []}
    graph_dict_second = {'vertices': [], 'edges': []}
    vertices_first_bfs = bfs(graph, vertices[0])
    vertices_second_bfs = {}
    vertices_first_bfs_result_none = []

    for vertex in vertices_first_bfs.keys():
        if vertices_first_bfs[vertex] is None:
            vertices_second_bfs = bfs(graph, vertex)
            break

    for vertex in vertices_second_bfs.keys():
        if vertices_second_bfs[vertex] is None:
            vertices_first_bfs_result_none.append(vertex)

    for vertex in vertices_first_bfs.keys():
        if vertices_first_bfs[vertex] is not None:
            graph_dict_first['vertices'].append(vertex)
            for edge in vertex.getAdjacentEdgeList():
                graph_dict_first['edges'].append(edge)
        else:
            graph_dict_second['vertices'].append(vertex)
            for edge in vertex.getAdjacentEdgeList():
                graph_dict_second['edges'].append(edge)

    for vertex in graph_dict_first['vertices']:
        vertices.remove(vertex)
    if len(graph_dict_first['vertices']) != len(vertices_first_bfs_result_none):
        return None

    graph_dict_first['edges'] = list(set(graph_dict_first['edges']))
    graph_dict_second['edges'] = list(set(graph_dict_second['edges']))

    for vertex in graph_dict_first['vertices']:
        graph_first.addVertex(vertex)
    for edge in graph_dict_first['edges']:
        graph_first.addEdge(edge)

    for vertex in graph_dict_second['vertices']:
        graph_second.addVertex(vertex)
    for edge in graph_dict_second['edges']:
        graph_second.addEdge(edge)

    if len(graph_first.getVertexList()) != len(graph_second.getVertexList()) or len(graph_first.getEdgeList()) != len(
            graph_second.getEdgeList()):
        return False

    return checkIsomorphismMatrix(graph_first.getAdjacentMatrix(), graph_second.getAdjacentMatrix())


def checkIsomorphismMatrix(a: np.array, b: np.array):
    if a.shape != b.shape:
        return False
    n = a.shape[0]
    permutations = [i for i in range(0, n)]

    for permutation in itertools.permutations(permutations):
        matrix = np.zeros((n, n))
        i_0 = 0
        for i in permutation:
            j_0 = 0
            for j in permutation:
                matrix[i_0][j_0] = b[i][j]
                j_0 += 1
            i_0 += 1
        result = True
        for i in range(0, n):
            for j in range(0, n):
                if matrix[i][j] != a[i][j]:
                    result = False
                    break
            if not result:
                break
        if result:
            return True
    return False
