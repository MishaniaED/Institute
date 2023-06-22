from classes.graph.graph import *


def setVisualForColorize(graph: Graph):
    colors_of_nodes = colorize(graph)
    for i in colors_of_nodes.keys():
        i.setColor(getColorFromColorNumber(colors_of_nodes[i]))
        i.setServiceValue("color=" + str(colors_of_nodes[i]))



def colorize(graph: Graph):
    sorted_vertex = sorted(graph.getVertexList(), key=(lambda x: len(x.getAdjacentVertexList())),
                           reverse=True)  # сортировка по количеству смежных вершин
    color = 1
    colors_of_nodes = {}  # dict

    for i in sorted_vertex:
        colors_of_nodes[i] = None
    colors_of_nodes[sorted_vertex[0]] = color

    while True:
        flag = True
        for i in sorted_vertex:  # покрасить вершины в текущий цвет если это возможно 4 элемент
            tmp = color
            while tmp >= 1:
                tryColor(tmp, colors_of_nodes, i)
                tmp -= 1

        for i in colors_of_nodes.keys():
            if colors_of_nodes[i] is None:
                flag = False

        color += 1
        if flag:
            return colors_of_nodes

def getColorFromColorNumber(color: int):
    color = color * 20
    R = (int)(color * 4 % 255)
    G = (int)(color * 2 * pow(color, 2) % 255)
    B = (int)(color / 2 % 255)

    return QtGui.QColor(R, G, B)


# проверка смежных вершин на тот же самый цвет
def tryColor(color: int, colors: dict, vertex: Vertex):
    if colors[vertex] is not None:
        return

    for i in vertex.getAdjacentVertexList():
        if colors[i] == color:
            return

    colors[vertex] = color
