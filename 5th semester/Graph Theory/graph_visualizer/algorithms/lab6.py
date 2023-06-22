from classes.graph.graph import *
from classes.graph.graph import *
from algorithms.Lab4_DijkstrasAlgorythm import *


def Weight_Vertex(graph: Graph):  # ф-ция, отвечающая за вес вершины
    if graph.empty() or len(graph.getVertexList()) == 0:  # проверка на то, что граф непустой и длина списка вершин
        # не равна нулю
        return
    weight = 0
    if (graph._isDirectedGraph == True):  # цикл для ориентированного графа
        for vertex in graph.getVertexList():  # для каждой вершины задаём начальное значение 0
            weight = 0
            for edge in vertex.getAdjacentEdgeList():  # для каждого ребра, если оно входит в данную веришну или если
                # ребро неориентированное, добавляем значение
                if vertex == edge.getEndVertex() or not edge.isDirected():
                    weight += edge.getWeight()
                    vertex.setServiceValue("wgt(" + vertex.getName() + ") = " + str(weight))  # установка значения веса
    if (graph._isDirectedGraph == False):  # цикл для неориентированного графа
        for vertex in graph.getVertexList():
            weight = 0;
            for edge in vertex.getAdjacentEdgeList():  # то же самое, что для ориентированного цикла, но здесь не нужна
                # проверка с 19 строки, сразу прибавляем
                weight += edge.getWeight()
                vertex.setServiceValue("wgt(" + vertex.getName() + ") = " + str(weight))  # установка значения веса


def Radius_Diameter(graph: Graph):
    dijkstraMax = {}
    for vertex in graph.getVertexList():
        dijkstraMax[vertex] = max([x for x in algorythmDijkstra(graph, vertex, False, False).values() if x is not None])

    return dijkstraMax
    # messageDialod = QtWidgets.QMessageBox()  # установка визуальщины
    # messageDialod.setWindowTitle("R(G), D(G)\n")
    # messageDialod.setText('Радиус графа: \nR = ' + str(min(dijkstraMax.values()))) + '\nДиаметр графа: \nD = ' + str(
    #     max(dijkstraMax.values()))
    # messageDialod.exec_()


def Vect_Degree(graph: Graph):
    if graph.empty() or len(graph.getVertexList()) == 0:
        return
    vectDegree = {}

    for i in graph.getVertexList():
        vectDegree[i] = None
        degree = 0

        if (graph._isDirectedGraph == True):

            for vertex in graph.getVertexList():
                degree = 0
                for edge in vertex.getAdjacentEdgeList():
                    if vertex == edge.getEndVertex() or not edge.isDirected():
                        degree += 1
                        vectDegree[vertex] = degree

        if (graph._isDirectedGraph == False):
            for vertex in graph.getVertexList():
                degree = 0
                for edge in vertex.getAdjacentEdgeList():
                    degree += 1
                    vectDegree[vertex] = degree

        return vectDegree
