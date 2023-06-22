from algorithms.coloration import tryColor, colorize
from classes.graph.graph import *
import itertools


def check_bipartition(graph: Graph):  # проверка хроматического числа, оно должно = 2

    sorted_vertex = sorted(graph.getVertexList(), key=(lambda x: len(x.getAdjacentVertexList())),
                           reverse=True)
    color = 1
    colors_of_nodes = {}  # dict

    for i in sorted_vertex:
        colors_of_nodes[i] = None
    colors_of_nodes[sorted_vertex[0]] = color

    while True:
        flag = True
        for i in sorted_vertex:
            tryColor(color, colors_of_nodes, i)

        for i in colors_of_nodes.keys():
            if colors_of_nodes[i] is None:
                flag = False

        color += 1
        if flag:
            return color - 1 == 2


# def try_kuhn(v, mt, used, g):
#     if used[v]:
#         return False
#     used[v] = True
#
#     for i in g[v]:
#         to = i
#         y = mt[to]
#         x = try_kuhn(i.getName(), mt, used, g)
#         if mt[to.getName()] == -1 or try_kuhn(i.getName(), mt, used, g):
#             mt[to.getName()] = v
#             return True
#     return False


def wedding(graph: Graph):  # необходимо найти такое паросочетание, чтобы у каждого М была Д

    # mt = {}
    # used = {}
    # g = {}
    men_list = []
    girls_list = []

    colors_of_nodes = colorize(graph)
    for i in colors_of_nodes.keys():
        if colors_of_nodes[i] == 1:
            men_list.append(i)
            i.setServiceValue('M')
        else:
            girls_list.append(i)
            i.setServiceValue('W')

    if len(men_list) > len(girls_list):  # проверка на то что М >= Д
        men_list, girls_list = girls_list, men_list
        for i in colors_of_nodes.keys():
            if colors_of_nodes[i] == 1:
                i.setServiceValue('W')
            else:
                i.setServiceValue('M')

    for i in men_list:  # проверка на то что у каждого М может быть хотя бы 1 Д
        if len(i.getAdjacentVertexList()) == 0:
            return False

    # в каждом проходимся по всем мужчинам
    # проходимся по всем доступным девушкам для текущего мужчины и добовляем их в множество женщин
    # check_set = set()
    # for man_vertex in men_list:
    #     for verFromCombWoman in man_vertex.getAdjacentVertexList():
    #         check_set.add(verFromCombWoman)
    # # если количество девушек, у которых есть связь с мужчинами < количества мужчин, то задача неразрешима
    # if len(check_set) < len(men_list):
    #     return False

    edges_matchings = list(itertools.combinations(graph.getEdgeList(), len(men_list)))  # список комбинаций ребер
    for matching in edges_matchings:
        vertex_from_edges = set()
        for edge in matching:
            vertex_from_edges.add(edge.getEndVertex())
            vertex_from_edges.add(edge.getStartVertex())

        if len(vertex_from_edges) == len(men_list) * 2:
            # for i in matching:
            #     print('[{0}, {1}]'.format(str(i.getStartVertex().getName()), str(i.getEndVertex().getName())))
            return matching
    return False

    # for i in girls_list:
    #     mt[i] = -1
    # mt = [-1] * len(girls_list)

    # for i in men_list:
    #     g[i.getName()] = i.getAdjacentVertexList()
    #     # g.append(men_list[i])
    #     # g[men_list[i]].append(i.getAdjacentVertexList())
    #     # for f in i.getAdjacentVertexList():
    #     #     g.append(f)
    #     #g.append(i.getAdjacentEdgeList())
    #     #g[men_list[i]] = i.getAdjacentVertexList() # в g ключ -- это имя вершины мужчины, а значение лежащее по этому ключу список из доступных девушек
    #     #g.update({men_list[i].getName(), i.getAdjacentEdgeList()})
    #
    # for v in men_list:
    #     for i in men_list:
    #         used[i.getName()] = False
    #     try_kuhn(v.getName(), mt, used, g)
    #
    # for i in girls_list:
    #     if mt[i] != -1:
    #         print(mt[i] + 1, i + 1)

    # return mt


def setVisualForWedding(result):  # вывести сочетания(ввиде пар вершин) и проиллюстрировать(раскрасить)
    for i in result:
        i.setColor(QtCore.Qt.GlobalColor.red)
