from algorithms.graph.graph import Graph
from classes.graph.graph import *
from tkinter import *
from tkinter import messagebox
from algorithms.dijkstra import *
from utils.colorpalletes import *


def Weight_Vertex(graph: Graph):
    if graph.empty() or len(graph.getVertexList()) == 0:
        return
    weight = 0
    if (graph._isDirectedGraph == True):
        for vertex in graph.getVertexList():
            weight = 0;
            for edge in vertex.getAdjacentEdgeList():
                if vertex == edge.getEndVertex() or not edge.isDirected():
                    weight += edge.getWeight()
                    vertex.setServiceValue("wgt(" + vertex.getName() + ") = " + str(weight))
    if (graph._isDirectedGraph == False):
        for vertex in graph.getVertexList():
            weight = 0;
            for edge in vertex.getAdjacentEdgeList():
                weight += edge.getWeight()
                vertex.setServiceValue("wgt(" + vertex.getName() + ") = " + str(weight))


def Radius_Diameter(graph: Graph):
    dijkstraMax = {}
    for vertex in graph.getVertexList():
        dijkstraMax[vetrex] = max([x for x in dijkstra_algo(graph, vertex).values() if x is not None])

    messageDialod = QtWidjets.QMessageBox()
    messageDialod.setWindowTitle("R(G), D(G)\n")
    messageDialod.setText('Радиус графа: \nR = ' + str(min(djikstraMax.values()))) +
    '\nДиаметр графа: \nD = ' + str(max(djikstraMax.values()))


messageDialod.exec_()


def Vect_Degree(graph: Graph)

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
