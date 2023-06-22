# Presenter
import sys

from classes.cache.cache import *
from algorithms.bfs import *

from algorithms.Lab3_BestFirstAlgorythm import *
from algorithms.Lab4_DijkstrasAlgorythm import *
from algorithms.Lab5_AStarAlgorythm import *
from algorithms.lab6 import *
from algorithms.Lab7_Isomorphism import *
from algorithms.Lab8_Connectivity import *
from algorithms.complete import *
from algorithms.plos_plan import *
from algorithms.Lab13_MinimumSpanningTree import *
from algorithms.Lab14_CycleProblem import *
from algorithms.coloration import *
from algorithms.wedding_problem import *
from algorithms.tsp import *

from utils.colorpalletes import *

import main
import sip


class View(QtWidgets.QGraphicsView):
    def __init__(self, window):
        super().__init__()

        # Graph variables
        self._mainWindow = window
        self._graph = Graph()
        self._start = None
        self._end = None

        # Scene and view settings
        self._scene = QtWidgets.QGraphicsScene(self)
        self.setScene(self._scene)
        self.setStyleSheet(FIELD_DARK)
        self.setRenderHint(QtGui.QPainter.Antialiasing)
        self.setViewportUpdateMode(QtWidgets.QGraphicsView.FullViewportUpdate)
        self.setMouseTracking(True)

    # Algorithms
    def viewBFS(self):
        inputDialog = QtWidgets.QInputDialog(self)
        inputDialog.setInputMode(QtWidgets.QInputDialog.TextInput)
        inputDialog.setWindowTitle('ЛР №2. Поиска пути в ширину')

        inputDialog.setStyleSheet(WINDOW_DARK)
        inputDialog.setFont(QtGui.QFont('Arial', 15))
        inputDialog.setLabelText('Выберите начальную вершину:')
        ok1 = inputDialog.exec_()
        name1 = inputDialog.textValue()

        if self._graph.isWeighted():  # что-то не проходит это условие
            self.popDialog('Ошибка', 'граф не должен быть взвешенным и/или ориентированным')
        else:
            if ok1:
                v = self._graph.findVertexByName(name1)
                if v is not None:
                    self.setDefaults()
                    setVisualForBFS(bfs(self._graph, v), v)
            else:
                self.popDialog('Ошабка', 'Такой вершины не существует')

    def viewBestFirst(self):
        inputDialog = QtWidgets.QInputDialog(self)
        inputDialog.setInputMode(QtWidgets.QInputDialog.TextInput)
        inputDialog.setWindowTitle('ЛР №3 Алгоритм Best-First')
        inputDialog.setStyleSheet(WINDOW_DARK)
        inputDialog.setFont(QtGui.QFont('Arial', 15))
        inputDialog.setLabelText('Выберите начальную и конечную вершину:')
        ok = inputDialog.exec_()
        s = inputDialog.textValue()

        if ok:
            vertices = s.split(' ')
            vertex_start = self._graph.findVertexByName(vertices[0])
            vertex_end = self._graph.findVertexByName(vertices[1])
            if vertex_start is not None and vertex_end is not None:
                self.setDefaults()
                if isConnected(self._graph):
                    result = bestFirst(vertex_start, vertex_end)
                    if not result:
                        self.popDialog('Результат', 'Путь не найден')
                    else:
                        setVisualForBestFS(result, vertex_end)
                else:
                    self.popDialog('Ошибка', 'Граф должен быть взвешенным')
            else:
                self.popDialog('Ошибка', 'Такой вершины не существует')

    def checkDijkstra(self):
        if self._graph.isWeighted() and isConnected(self._graph):
            return True
        return False

    def viewDijkstra(self):
        inputDialog = QtWidgets.QInputDialog(self)
        inputDialog.setInputMode(QtWidgets.QInputDialog.TextInput)
        inputDialog.setWindowTitle('ЛР №4 Алгоритм Дейкстры')
        inputDialog.setStyleSheet(WINDOW_DARK)
        inputDialog.setFont(QtGui.QFont('Arial', 15))
        inputDialog.setLabelText('Выберите начальную вершину:')
        ok = inputDialog.exec_()
        name = inputDialog.textValue()

        if ok:
            vertex = self._graph.findVertexByName(name)
            if vertex is not None:
                self.setDefaults()
                if isConnected(self._graph):
                    setVisualForDijkstra(startDijkstra(self._graph, vertex))
                else:
                    self.popDialog('Ошибка', "Граф должен быть взвешенным")
            else:
                self.popDialog('Ошибка', "Такой вершины не существует")

    def viewAstar(self):
        inputDialog = QtWidgets.QInputDialog(self)
        inputDialog.setInputMode(QtWidgets.QInputDialog.TextInput)
        inputDialog.setWindowTitle('ЛР №5 Алгоритм A Star')
        inputDialog.setStyleSheet(WINDOW_DARK)
        inputDialog.setFont(QtGui.QFont('Arial', 15))
        inputDialog.setLabelText('Выберите начальную и конечную вершину:')
        ok = inputDialog.exec_()
        s = inputDialog.textValue()

        if ok:
            vertices = s.split(' ')
            vertex_start = self._graph.findVertexByName(vertices[0])
            vertex_end = self._graph.findVertexByName(vertices[1])
            if vertex_start is not None and vertex_end is not None:
                self.setDefaults()
                if isConnected(self._graph):
                    result = algorythmAStar(self._graph, vertex_start, vertex_end, True)
                    if not result:
                        self.popDialog('Результат', 'Путь не найден')
                    else:
                        setVisualForAStar(result)
                else:
                    self.popDialog('Ошикбка', "Граф должен быть взвешенным")
            else:
                self.popDialog('Ошикбка', "Такой вершины не существует")

    def viewParams(self):
        messageDialod = QtWidgets.QMessageBox()
        messageDialod.setWindowTitle("ЛР №6 Вектор степеней вершин графа:\n")
        messageDialod.setStyleSheet(WINDOW_DARK)

        if len(isConnected(self._graph)) >= 2:
            self.popDialog('Ошибка', 'Граф не связный')
            return
        result = Radius_Diameter(self._graph)
        lisy1 = []
        messageDialod.setWindowTitle("R(G), D(G)\n")
        lisy1 = result.values()

        a = min(lisy1)
        b = max(lisy1)
        messageDialod.setText('Радиус графа: \nR = ' + str(a) + '\nДиаметр графа: \nD = ' + str(b))

        vectDegree = Vect_Degree(self._graph)
        messageDialod1 = QtWidgets.QMessageBox()
        messageDialod1.setWindowTitle("Вектор степеней вершин графа:\n")
        # print(vectDegree.values())
        res = ' '
        j = 1
        for i in vectDegree.values():
            res += str(j) + ' = [' + str(i) + ']\n'
            j += 1
        messageDialod1.setText(res)
        messageDialod1.exec_()

        messageDialod.exec_()

    def viewIsomorphism(self):
        result = isomorphism(self._graph)
        if result is None:
            self.popDialog('Ошибка', 'Задано неверное число графов.')
        elif result is True:
            self.popDialog('Результат', 'Графы изоморфны.')
        else:
            self.popDialog('Результат', 'Графы не изоморфны.')

    def viewConnectivity(self):
        setVisualForConnectivity(self._graph)

    def viewComp(self):
        matrix = self._graph.getAdjacentMatrix()
        edges = 0

        for x in range(len(matrix)):
            for y in range(len(matrix[x])):
                if (matrix[x][y] > 0 or matrix[y][x] > 0) and x < y:
                    edges += 1
        if edges >= (len(matrix) * (len(matrix) - 1)) / 2:
            messageDialod = QtWidgets.QMessageBox(self)
            messageDialod.setWindowTitle("ЛР №9. Дополнение графа")
            messageDialod.setStyleSheet(WINDOW_DARK)
            messageDialod.setText('Текущий граф является полным')
            messageDialod.exec_()
        else:
            cpy = self.copyGraph(self._graph)
            setVisualForComplete(cpy, complete(cpy))
            self.addGraph(cpy)

    def viewPlanarity(self):
        self.setDefaults()
        messageDialod = QtWidgets.QMessageBox(self)
        messageDialod.setWindowTitle("ЛР №10. Планарность графа")
        messageDialod.setStyleSheet(WINDOW_DARK)
        i = flat_graph(self._graph)
        j = planar_graph(self._graph)
        if i:
            messageDialod.setText('1) Граф является плоским\n2) Граф является планарным')
        elif j:
            messageDialod.setText('1) Граф не является плоским\n2) Граф является планарным')
        else:
            messageDialod.setText('1) Граф не является плоским\n2) Граф не является планарным')
        messageDialod.exec_()

    def viewVector(self):
        pass

    def viewExtreme(self):
        pass

    def viewKruskal(self):
        self.setDefaults()
        kruskalAlgorythm(self._graph)

    def viewCycle(self):
        self.setDefaults()
        if not self._graph.isDirected() and isConnected(self._graph):
            cycle(self._graph)
        else:
            self.popDialog('Ошибка', 'Граф должен быть ненаправленным и связанным')

    def viewColorize(self):
        self.setDefaults()
        setVisualForColorize(self._graph)

    def viewWedding(self):  # Добавить проверку на ненаправленность ребер
        messageDialod = QtWidgets.QMessageBox(self)
        messageDialod.setWindowTitle("ЛР №16. Задача о свадьбах")
        messageDialod.setStyleSheet(WINDOW_DARK)

        self.setDefaults()
        cpy = self.copyGraph(self._graph)
        if not check_bipartition(cpy):  # Проверка на двудольность
            messageDialod.setText('Граф не является двудольным')
        else:
            result = wedding(self._graph)
            if result is False:
                messageDialod.setText('Задача не имеет решения')
            else:
                setVisualForWedding(result)
                string = ''
                for i in result:
                    string += '[{0}, {1}]\n'.format(str(i.getStartVertex().getName()), str(i.getEndVertex().getName()))
                messageDialod.setText(string)
        messageDialod.exec_()

    def view17(self):
        pass

    def view18(self):
        pass

    def view19(self):
        pass

    def view20(self):
        # if self._graph.isWeighted():
        #     messageDialod = QtWidgets.QMessageBox(self)
        #     messageDialod.setWindowTitle("ЛР №20. Задача коммивояжёра")
        #     messageDialod.setStyleSheet(WINDOW_DARK)
        #     messageDialod.setText("Граф должен быть взвешенным")
        #     messageDialod.exec_()
        #     return
        # if isConnected(self._graph):
        #     messageDialod = QtWidgets.QMessageBox(self)
        #     messageDialod.setWindowTitle("ЛР №20. Задача коммивояжёра")
        #     messageDialod.setStyleSheet(WINDOW_DARK)
        #     messageDialod.setText("Граф должен быть без висячих вершин")
        #     messageDialod.exec_()
        #     return
        # проверка на направленность ребер и их кол-во
        matr = self._graph.getAdjacentMatrix()
        for i in range(0, len(matr)):
            matr[i][i] = 2147483647
        setVisualForTSP(TSPsolve(matr), self._graph)

    def view21(self):
        pass

    def popDialog(self, title, text):
        messageDialog = QtWidgets.QMessageBox(self)
        messageDialog.setWindowTitle(title)
        messageDialog.setStyleSheet(WINDOW_DARK)
        messageDialog.setText(text)
        messageDialog.exec_()

    def setDefaults(self):
        for item in self._graph.getVertexList():
            item.setColor(VERTEX_COLOR)
            item.setServiceValue("")
        for item in self._graph.getEdgeList():
            item.setColor(QtCore.Qt.white)
        self._scene.update()

    def addGraph(self, graph: Graph):
        self._scene.clear()
        self._graph.clear()
        self._graph = graph

        vertexList = self._graph.getVertexList()
        edgeList = self._graph.getEdgeList()

        for item in vertexList:
            if not sip.isdeleted(item):
                self._scene.addItem(item)

        for item in edgeList:
            if not sip.isdeleted(item) and \
                    not (sip.isdeleted(item.getStartVertex())) and \
                    not (sip.isdeleted(item.getEndVertex())):
                self._scene.addItem(item)
        self._scene.update()

        # Update adjacent table widget
        self._mainWindow.updateAdjacentTable()

    def getGraph(self):
        return self._graph

    def copyGraph(self, srcGraph: Graph):
        graph = Graph(directed=srcGraph.isDirected(), weighted=srcGraph.isWeighted())

        for item in srcGraph.getVertexList():
            vertex = Vertex(0, 0, name=item.getName(), color=item.getColor())
            x, y = item.getPos()

            vertex.setPos(self.mapToScene(x, y))
            graph.addVertex(vertex)

        for item in srcGraph.getEdgeList():
            startVertex = graph.findVertexByName(item.getStartVertex().getName())
            endVertex = graph.findVertexByName(item.getEndVertex().getName())

            edge = Edge(startVertex, endVertex, name=item.getName(), weight=item.getWeight(),
                        direction=item.isDirected(), factor=item.getFactor())

            graph.addEdge(edge)
        return graph

    # Vertex methods
    def _createVertexName(self):
        vertexList = self._graph.getVertexList()

        if len(vertexList) == 0:
            name = '1'
        else:
            name = str(int(vertexList[-1].getName()) + 1)
        return name

    def _contextMenuAddVertex(self, x, y):
        name = self._createVertexName()
        vertex = Vertex(0, 0, name=name, color=VERTEX_COLOR)
        vertex.setPos(self.mapToScene(x, y))

        self._scene.addItem(vertex)
        self._graph.addVertex(vertex)
        self._scene.update()

        # Update adjacent table widget
        self._mainWindow.updateAdjacentTable()

        # Update cache
        self._mainWindow.getCache().updateCache(self.copyGraph(self._graph))

    def _contextMenuRemoveVertex(self, vertex):
        self._graph.removeVertex(vertex)
        redrawGraph = self.copyGraph(self._graph)
        self._scene.clear()

        self._graph = redrawGraph
        for item in self._graph.getVertexList():
            self._scene.addItem(item)
            self._scene.update()

        for item in self._graph.getEdgeList():
            self._scene.addItem(item)
            self._scene.update()

        # Update adjacent table widget
        self._mainWindow.updateAdjacentTable()

        # Update cache
        self._mainWindow.getCache().updateCache(self.copyGraph(self._graph))

    # Edge methods
    @staticmethod
    def countEdgeFactor(startVertex, endVertex):
        if startVertex.getName() > endVertex.getName():
            factorStart = startVertex
            factorEnd = endVertex
        else:
            factorStart = endVertex
            factorEnd = startVertex

        endAdjVertexList = factorEnd.getAdjacentVertexList().copy()
        startAdjVertexList = factorStart.getAdjacentVertexList().copy()

        factor = 0
        for vertex in endAdjVertexList:
            if vertex == factorStart:
                factor += 1
                for i in range(startAdjVertexList.count(factorEnd)):
                    startAdjVertexList.remove(factorEnd)

        for vertex in startAdjVertexList:
            if vertex == factorEnd:
                factor += 1

        if factor > 0 and factor % 2 == 0:
            factor /= -2
        elif factor > 0 and factor % 2 != 0:
            factor = (factor + 1) / 2

        if startVertex.getName() > endVertex.getName():
            factor = -factor

        return factor

    def _createEdgeName(self):
        edgeList = self._graph.getEdgeList()

        if len(edgeList) == 0:
            name = '1'
        else:
            name = str(int(edgeList[-1].getName()) + 1)
        return name

    def _contextMenuAddEdge(self, startVertex, endVertex):
        # Count bezier factor
        factor = self.countEdgeFactor(startVertex, endVertex)

        # Create default name
        name = self._createEdgeName()

        # Create edge
        edge = Edge(startVertex, endVertex, name, weight=1, direction=False, factor=factor)

        if startVertex == endVertex:
            startVertex.setLoop(value=True)

        self._scene.addItem(edge)
        self._graph.addEdge(edge)
        self._scene.update()

        # Update adjacent table widget
        self._mainWindow.updateAdjacentTable()

        # Update cache
        self._mainWindow.getCache().updateCache(self.copyGraph(self._graph))

    def _contextMenuToggleDirection(self):
        inputDialog = QtWidgets.QInputDialog(self)
        inputDialog.setInputMode(QtWidgets.QInputDialog.TextInput)
        inputDialog.setWindowTitle('Вкл/Выкл направление ребра')

        if self._mainWindow.getTheme():
            inputDialog.setStyleSheet('background-color: #303030; color: white;')
        else:
            inputDialog.setStyleSheet('background-color: white; color: black;')

        inputDialog.setFont(QtGui.QFont('Arial', 15))
        inputDialog.setLabelText('Название ребра:')
        ok = inputDialog.exec_()
        name = inputDialog.textValue()

        if ok:
            edge = self._graph.findEdgeByName(name)
            self._graph.toggleEdgeDirection(edge)
            self._scene.update()

            # Update adjacent table widget
            self._mainWindow.updateAdjacentTable()

            # Update cache
            self._mainWindow.getCache().updateCache(self.copyGraph(self._graph))

    def _contextMenuSetWeight(self):
        inputDialog = QtWidgets.QDialog(self)
        inputDialog.setWindowTitle('Установить вес ребра')
        inputDialog.setFont(QtGui.QFont('Arial', 15))

        if self._mainWindow.getTheme():
            inputDialog.setStyleSheet('background-color: #303030; color: white;')
        else:
            inputDialog.setStyleSheet('background-color: white; color: black;')

        form = QtWidgets.QFormLayout(inputDialog)

        textBox1 = QtWidgets.QLineEdit()
        form.addRow(QtWidgets.QLabel('Название ребра'))
        form.addRow(textBox1)

        textBox2 = QtWidgets.QSpinBox()
        textBox2.setMinimum(1)
        textBox2.setMaximum(10000)
        form.addRow(QtWidgets.QLabel('Вес ребра'))
        form.addRow(textBox2)

        buttonBox = QtWidgets.QDialogButtonBox(QtWidgets.QDialogButtonBox.Cancel | QtWidgets.QDialogButtonBox.Ok)
        form.addRow(buttonBox)
        buttonBox.accepted.connect(inputDialog.accept)
        buttonBox.rejected.connect(inputDialog.reject)

        ok = inputDialog.exec_()

        if ok:
            name = textBox1.text()
            weight = int(textBox2.text())
            edge = self._graph.findEdgeByName(name)
            self._graph.setEdgeWeight(edge, weight)
            self._scene.update()

            # Update adjacent table widget
            self._mainWindow.updateAdjacentTable()

            # Update cache
            self._mainWindow.getCache().updateCache(self.copyGraph(self._graph))

    def _contextMenuRemoveEdge(self):
        inputDialog = QtWidgets.QInputDialog(self)
        inputDialog.setInputMode(QtWidgets.QInputDialog.TextInput)
        inputDialog.setWindowTitle('Удаление ребра')
        inputDialog.setFont(QtGui.QFont('Arial', 15))
        inputDialog.setLabelText('Название ребра:')

        if self._mainWindow.getTheme():
            inputDialog.setStyleSheet('background-color: #303030; color: white;')
        else:
            inputDialog.setStyleSheet('background-color: white; color: black;')

        ok = inputDialog.exec_()
        name = inputDialog.textValue()

        if ok:
            edge = self._graph.findEdgeByName(name)
            if edge is not None:
                self._graph.removeEdge(edge)
                redrawGraph = self.copyGraph(self._graph)
                self._scene.clear()

                self._graph = redrawGraph
                for item in self._graph.getVertexList():
                    self._scene.addItem(item)

                for item in self._graph.getEdgeList():
                    self._scene.addItem(item)
                self._scene.update()

            # Update adjacent table widget
            self._mainWindow.updateAdjacentTable()

            # Update cache
            self._mainWindow.getCache().updateCache(self.copyGraph(self._graph))

    # Utils
    def _contextMenuClearScene(self):
        self._graph.clear()
        self._scene.clear()
        self._scene.update()

        # Update adjacent table widget
        self._mainWindow.updateAdjacentTable()

        # Update cache
        self._mainWindow.getCache().updateCache(self.copyGraph(self._graph))

    # Events
    def contextMenuEvent(self, event):
        pos = event.pos()
        mnu = QtWidgets.QMenu()

        mnu.addSection('Вершина:')
        mnu.addAction('Добавить вершину').setObjectName('add vertex')
        mnu.addAction('Создать петлю').setObjectName('make loop')
        mnu.addAction('Удалить вершину').setObjectName('delete vertex')

        mnu.addSection('Ребро:')
        mnu.addAction('Вкл/Выкл направление ребра...').setObjectName('toggle direction')
        mnu.addAction('Установить вес ребра...').setObjectName('set weight')
        mnu.addAction('Удалить ребро...').setObjectName('delete edge')

        mnu.addSection('Дополнительно:')
        mnu.addAction('Очистить экран').setObjectName('clear all')

        ret = mnu.exec_(self.mapToGlobal(pos))
        if not ret:
            return

        obj = ret.objectName()
        if obj == 'add vertex':
            pos_x, pos_y = event.pos().x(), event.pos().y()
            self._contextMenuAddVertex(pos_x, pos_y)

        elif obj == 'delete vertex':
            pos_x, pos_y = event.pos().x(), event.pos().y()
            item = self._scene.itemAt(pos_x, pos_y, QtGui.QTransform())
            if item is not None:
                if isinstance(item, Vertex):
                    self._contextMenuRemoveVertex(item)

        elif obj == 'make loop':
            pos_x, pos_y = event.pos().x(), event.pos().y()
            item = self._scene.itemAt(pos_x, pos_y, QtGui.QTransform())
            if item is not None:
                if isinstance(item, Vertex):
                    if not item.isLoopExist():
                        item.setLoop(value=True)
                        self._contextMenuAddEdge(item, item)

        elif obj == 'toggle direction':
            self._contextMenuToggleDirection()

        elif obj == 'set weight':
            self._contextMenuSetWeight()

        elif obj == 'delete edge':
            self._contextMenuRemoveEdge()

        elif obj == 'clear all':
            self._contextMenuClearScene()
        self._scene.update()

    def resizeEvent(self, event):
        width, height = self.viewport().width(), self.viewport().height()
        self.setSceneRect(0, 0, width, height)

        for item in self._scene.items():
            if isinstance(item, Vertex):
                x, y = item.getPos()
                x = max(min(x, self.width() - VERTEX_SIZE), 0)
                y = max(min(y, self.height() - VERTEX_SIZE), 0)
                item.setPos(self.mapToScene(x, y))
        self._scene.update()

    def mousePressEvent(self, event):
        if event.button() == QtCore.Qt.MiddleButton:
            pos_x, pos_y = event.pos().x(), event.pos().y()
            item = self._scene.itemAt(pos_x, pos_y, QtGui.QTransform())
            if item is not None:
                self._start = item

        self._scene.update()
        super(View, self).mousePressEvent(event)

    def mouseReleaseEvent(self, event):
        if event.button() == QtCore.Qt.MiddleButton:
            pos_x, pos_y = event.pos().x(), event.pos().y()
            item = self._scene.itemAt(pos_x, pos_y, QtGui.QTransform())
            if item is not None:
                self._end = item
                if isinstance(self._start, Vertex) and isinstance(self._end, Vertex):
                    if self._start != self._end:
                        self._contextMenuAddEdge(self._start, self._end)
                        self._start = None
                        self._end = None

        self._scene.update()
        super(View, self).mouseReleaseEvent(event)
