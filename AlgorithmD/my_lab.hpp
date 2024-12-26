#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <limits.h>
#include <vector>
#include <set>
#include <cstdlib>

using namespace std;

/**
 * @class Graph
 * @brief Класс для представления графа и выполнения алгоритмов обработки графа.
 *
 * Содержит методы для работы с графом, включая добавление рёбер,
 * загрузку графа из файла, визуализацию в формате Graphviz,
 * реализацию алгоритмов Дейкстры, а также анализ сложности.
 */
class Graph {
private:
    int vertices; ///< Количество вершин в графе
    vector<vector<pair<int, int>>> adjList; ///< Список смежности для представления графа
    int edgeCount; ///< Количество рёбер в графе

public:
    /**
     * @brief Конструктор класса Graph.
     * @param v Количество вершин в графе.
     */
    Graph(int v);

    /**
     * @brief Добавляет ребро в граф.
     * @param u Вершина-источник.
     * @param v Вершина-назначение.
     * @param weight Вес ребра.
     */
    void addEdge(int u, int v, int weight);

    /**
     * @brief Загружает граф из файла.
     * @param fileName Имя файла, содержащего матрицу смежности.
     * @param startVertex Начальная вершина для алгоритма.
     * @throws runtime_error Если файл не удалось открыть.
     */
    void loadFromFile(const string& fileName, int& startVertex);

    /**
     * @brief Сохраняет граф в формате Graphviz.
     * @param fileName Имя выходного файла.
     * @throws runtime_error Если файл не удалось открыть для записи.
     */
    void toGraphviz(const string& fileName) const;

    /**
     * @brief Выполняет алгоритм Дейкстры с использованием приоритетной очереди.
     * @param startVertex Начальная вершина.
     * @param fileName Имя выходного файла для визуализации результатов.
     * @return Вектор минимальных расстояний от начальной вершины.
     * @throws runtime_error Если файл не удалось создать.
     */
    vector<int> dijkstra(int startVertex, const string& fileName) const;

    /**
     * @brief Выполняет алгоритм Дейкстры без приоритетной очереди (простой алгоритм).
     * @param startVertex Начальная вершина.
     * @return Вектор минимальных расстояний от начальной вершины.
     */
    vector<int> dijkstraSimple(int startVertex) const;

    /**
     * @brief Анализирует сложность алгоритмов для различных размеров графа.
     *        Результаты сохраняются в файл "complexity.dat".
     */
    void analyzeComplexity();

    /**
     * @brief Возвращает количество рёбер в графе.
     * @return Количество рёбер.
     */
    int getEdgeCount() const { return edgeCount; }

    /**
     * @brief Возвращает количество вершин в графе.
     * @return Количество вершин.
     */
    int getVertexCount() const { return vertices; }
};









#ifndef my_lab_hpp
//#define my_lab_hpp

#include <stdio.h>

#endif /* my_lab_hpp */
#include <chrono>
#include <random>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <iostream>
#include <set>
#include <utility>
#include <stdexcept>
#include <sstream>
/*using namespace std;
using namespace chrono;

class Graph {
private:
    int vertices;
    vector<vector<pair<int, int>>> adjList;
    int edgeCount;

public:
    Graph(int v);
    void addEdge(int u, int v, int weight);
    void loadFromFile(const string& fileName, int& startVertex);
    void toGraphviz(const string& fileName) const;
    vector<int> dijkstra(int startVertex, const string& fileName) const;
    vector<int> dijkstraSimple(int startVertex) const;
    void analyzeComplexity();
    int getEdgeCount() const { return edgeCount; }
    int getVertexCount() const { return vertices; }
};



/*
#ifndef my_lab_hpp
//#define my_lab_hpp

#include <stdio.h>


#include <chrono>
#include <random>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <iostream>
#include <set>
#include <utility>
#include <stdexcept>
#include <sstream>
/*using namespace std;
using namespace chrono;

class Graph {
private:
    int vertices;
    vector<vector<pair<int, int>>> adjList;
    int edgeCount;

public:
    Graph(int v);
    void addEdge(int u, int v, int weight);
    void loadFromFile(const string& fileName, int& startVertex);
    void toGraphviz(const string& fileName) const;
    vector<int> dijkstra(int startVertex, const string& fileName) const;
    vector<int> dijkstraSimple(int startVertex) const;
    const vector<pair<int, int>>& getAdjList(int vertex) const {
            return adjList[vertex];
        }
    void generateRandomGraph(int vertices, double density, int maxWeight);
    void runComparison(Graph& graph);
    int getEdgeCount() const { return edgeCount; }
    int getVertexCount() const { return vertices; }
};
*/
