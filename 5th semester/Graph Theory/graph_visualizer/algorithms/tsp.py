import sys
import queue
import copy
from classes.graph.graph import *


class Node:
    def __init__ (self, path: list(list()), matr: list(), weight: int, vertex: int, level: int):
        self.path = copy.deepcopy(path)
        self.matr = copy.deepcopy(matr)
        self.weight = weight
        self.vertex = vertex
        self.level = level


def newNode(matrix: list(), path: list(list()), level: int, i: int, j: int):
    node = Node(path, matrix, 0, j, level)
    #print(node.matr)
    if (level != 0 ):
        node.path.append((i, j))
    for k in range(0, len(node.matr)):
        if (level == 0):
            break
        node.matr[i][k] = 2147483647
        node.matr[k][j] = 2147483647

    node.matr[j][0] = 2147483647
    return node


def reduce_row(matr: list()):
    _row = [2147483647 for i in range(len(matr))]

    for i in range(0, len(_row)):
        for j in range(0, len(_row)):
            if (matr[i][j] < _row[i]):
                _row[i] = matr[i][j]

    for i in range(0, len(_row)):
        for j in range(0, len(_row)):
            if (matr[i][j] != 2147483647 and _row[i] != 2147483647):
                matr[i][j] -= _row[i]
    return _row


def reduce_column(matr: list()):
    _col = [2147483647 for i in range(len(matr))]

    for i in range(0, len(_col)):
        for j in range(0, len(_col)):
            if (matr[i][j] < _col[j]):
                _col[j] = matr[i][j]

    for i in range(0, len(_col)):
        for j in range(0, len(_col)):
            if (matr[i][j] != 2147483647 and _col[j] != 2147483647):
                matr[i][j] -= _col[j]
    return _col


def weight_calculation(matr: list()):
    weight = 0
    row = reduce_row(matr)
    col = reduce_column(matr)
    for i in range(0, len(matr)):
        if (row[i] != 2147483647):
            weight += row[i]
        if (col[i] != 2147483647):
            weight += col[i]
    return weight


def printPath(a: list(list())):
    for i in range(0, len(a)):
        print(a[i][0] + 1, "->", a[i][1] + 1)


def TSPsolve(adjacensyMatrix: list()):
    pq = queue.PriorityQueue()
    v = list()
    root = newNode(adjacensyMatrix, v, 0, -1, 0)
    root.weight = weight_calculation(root.matr)
    pq.put((-1 * root.weight, root))
    while not pq.empty():
        l = pq.get()
        min = l[1]
        i = min.vertex
        if (min.level == len(min.matr) - 1):
            min.path.append((i, 0))
            return min.weight, min.path

        for j in range(0, len(min.matr)):
            if (min.matr[i][j] != 2147483647):
                child = newNode(min.matr, min.path, min.level + 1, i, j)
                a = weight_calculation(child.matr)
                child.weight = min.weight + min.matr[i][j] + a
                pq.put((child.weight, child))


def setVisualForTSP(a: tuple(), graph: Graph):
    b = graph.getVertexList()
    b[a[1][0][0]].setColor("red")
    b[a[1][0][0]].setServiceValue("n=" + str(a[0]))
    for i in range(0, len(a[1])):
        g = graph.findEdgeByVertexes(b[a[1][i][0]], b[a[1][i][1]])
        g.setColor("orange")
