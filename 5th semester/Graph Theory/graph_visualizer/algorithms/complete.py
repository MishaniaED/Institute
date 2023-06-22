from classes.graph.graph import *


def complete(graph: Graph):
    matrix = graph.getAdjacentMatrix()
    new_nodes = []
    for x in range(len(matrix)):
        for y in range(len(matrix[x])):
            if x < y:
                if matrix[x][y] > 0 and matrix[x][y] == matrix[y][x]:
                    matrix[x][y] = 0
                    matrix[y][x] = 0
                else:
                    if matrix[x][y] != matrix[y][x] and (matrix[x][y] > 0 or matrix[y][x] > 0):
                        matrix[x][y] = 0
                        matrix[y][x] = 0
                    else:
                        matrix[x][y] = 1
                        matrix[y][x] = 1
                        new_nodes.append(Edge(graph.getVertexList()[x], graph.getVertexList()[y], color=QtCore.Qt.blue,
                                              name=createName(graph, new_nodes)))
            else:
                if x == y:
                    matrix[x][y] = 0

    # adjMatrix = matrix + graph.getAdjacentMatrix()
    # print(adjMatrix)
    return new_nodes


def setVisualForComplete(graph: Graph, new_nodes):
    for i in new_nodes:
        graph.addEdge(i)


def createName(graph: Graph, new_nodes):
    if len(graph.getEdgeList()) != 0:
        name_from_graph = int(graph.getEdgeList()[-1].getName()) + 1
    else:
        name_from_graph = 1

    name_from_graph += len(new_nodes)
    return str(name_from_graph)
