from algorithms.bfs import *


def getEndVertex(vertex_source: Vertex, edge: Edge):
    vertex_end = edge.getEndVertex()

    if vertex_end == vertex_source:
        vertex_end = edge.getStartVertex()

    return vertex_end


def dfsFirst(vertex_source: Vertex, vertices_visited, vertices_queue):
    vertices_visited.add(vertex_source)
    vertex_source_edges = [i for i in vertex_source.getAdjacentEdgeList()
                           if (i.getStartVertex() == vertex_source or not i.isDirected())]
    for edge in vertex_source_edges:
        vertex_end = edge.getEndVertex()
        if vertex_end not in vertices_visited:
            dfsFirst(vertex_end, vertices_visited, vertices_queue)

    vertices_queue.append(vertex_source)


def dfsSecond(vertex_source: Vertex, vertices_visited, strong_components, component_count):
    vertices_visited.add(vertex_source)
    strong_components[component_count].append(vertex_source)

    vertex_source_edges = [i for i in vertex_source.getAdjacentEdgeList()
                           if (i.getStartVertex() == vertex_source or not i.isDirected())]
    for edge in vertex_source_edges:
        vertex_end = edge.getEndVertex()
        if vertex_end not in vertices_visited:
            dfsSecond(vertex_end, vertices_visited, strong_components, component_count)


def isDirected(graph: Graph):
    for edge in graph.getEdgeList():
        if edge.isDirected():
            return True


def isConnected(graph: Graph):
    vertices = graph.getVertexList().copy()
    components = []
    component_count = 0

    while len(vertices) > 0:
        components.append([])
        vertices_bfs = bfs(graph, vertices[0])
        for vertex in vertices_bfs.keys():
            if vertices_bfs[vertex] is not None:
                components[component_count].append(vertex)
                vertices.remove(vertex)
        component_count += 1

    return components


def strongConnectivity(graph: Graph):
    vertices_visited = set()
    vertices_queue = []
    strong_components = []
    component_count = 0

    for vertex in graph.getVertexList():
        if vertex not in vertices_visited:
            dfsFirst(vertex, vertices_visited, vertices_queue)

    vertices_visited = set()
    graph.reverse()

    while len(vertices_queue) > 0:
        vertex = vertices_queue.pop()
        if vertex not in vertices_visited:
            strong_components.append([])
            dfsSecond(vertex, vertices_visited, strong_components, component_count)
            component_count += 1

    graph.reverse()

    return strong_components


def weakConnectivity(graph: Graph):
    directed = set()

    for edge in graph.getEdgeList():
        if edge.isDirected():
            directed.add(edge)
            edge._isDirection = False

    res = isConnected(graph)
    print("Number of weak components is:", len(res))

    for edge in directed:
        edge._isDirection = True

    return res


def dfsBridges(vertex: Vertex, vertex_parent, vertices_visited, time_discovery, low, current_time, bridges):
    vertices_visited.add(vertex)
    time_discovery[vertex] = current_time
    low[vertex] = current_time
    current_time += 1
    vertex_source_edges = [i for i in vertex.getAdjacentEdgeList()
                           if (i.getStartVertex() == vertex or not i.isDirected())]

    for edge in vertex_source_edges:
        vertex_end = getEndVertex(vertex, edge)
        if vertex_end == vertex_parent:
            continue
        if vertex_end not in vertices_visited:
            dfsBridges(vertex_end, vertex, vertices_visited, time_discovery, low, current_time, bridges)

            low[vertex] = min(low[vertex], low[vertex_end])
            if low[vertex_end] > time_discovery[vertex]:
                bridges.add(edge)
        else:
            low[vertex] = min(low[vertex], time_discovery[vertex_end])


def getBridges(graph: Graph):
    bridges = set()

    dfsBridges(graph.getVertexList()[0], None, set(), {}, {}, 0, bridges)
    print("Bridges count: ", len(bridges))

    return bridges


def dfsArticulations(vertex: Vertex, vertex_parent, vertices_visited, time_discovery, low, current_time, articulations):
    vertices_visited.add(vertex)
    time_discovery[vertex] = current_time
    low[vertex] = current_time
    current_time += 1
    vertex_children_count = 0
    edges = [i for i in vertex.getAdjacentEdgeList()
             if (i.getStartVertex() == vertex or not i.isDirected())]

    for edge in edges:
        vertex_end = getEndVertex(vertex, edge)
        if vertex_end == vertex_parent:
            continue

        if vertex_end not in vertices_visited:
            vertex_children_count += 1
            dfsArticulations(vertex_end, vertex, vertices_visited, time_discovery, low, current_time, articulations)
            low[vertex] = min(low[vertex], low[vertex_end])
            if vertex_parent is not None and low[vertex_end] >= time_discovery[vertex]:
                articulations.add(vertex)
        else:
            low[vertex] = min(low[vertex], time_discovery[vertex_end])
    if vertex_parent is None and vertex_children_count > 1:
        articulations.add(vertex)


def getArticulations(graph: Graph):
    articulations = set()

    dfsArticulations(graph.getVertexList()[0], None, set(), {}, {}, 0, articulations)
    print("Articulations count: ", len(articulations))

    return articulations


def setVisualForConnectivity(graph: Graph):
    is_directed = isDirected(graph)

    if is_directed:
        strong_components = strongConnectivity(graph)
        print("Strong components count:", len(strong_components))
        for component in strong_components:
            color = QtGui.QColor(QtCore.qrand() % 255, QtCore.qrand() % 255, QtCore.qrand() % 255)
            for vertex in component:
                print(vertex.getName(), " ", end="")
                vertex.setColor(color)
            print("")
        weakConnectivity(graph)
    else:
        components = isConnected(graph)
        print("Components count:", len(components))
        QtCore.qsrand(QtCore.QTime(0, 0, 0).secsTo(QtCore.QTime.currentTime()))
        for component in components:
            color = QtGui.QColor(QtCore.qrand() % 255, QtCore.qrand() % 255, QtCore.qrand() % 255)
            for vertex in component:
                print(vertex.getName(), " ", end="")
                vertex.setColor(color)
            print("")
        for vertex in getArticulations(graph):
            vertex.setServiceValue("Articulation")
            vertex.setColor("red")
        for edge in getBridges(graph):
            edge.setColor("red")
