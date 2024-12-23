
#ifndef my_lab_hpp
#define my_lab_hpp

#include <stdio.h>

#endif /* my_lab_hpp */
#define MY_LAB_H

#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <iostream>
#include <set>
#include <utility>
#include <stdexcept>
#include <sstream>

using namespace std;

/**
 * @file my_lab.hpp
 * @brief Определения класса Graph и его методов для работы с графами.
 */

/**
 * @class Graph
 * @brief Класс для представления направленного взвешенного графа.
 */
class Graph {
public:
    /**
     * @brief Конструктор графа.
     * @param v Количество вершин в графе.
     */
    Graph(int v);

    /**
     * @brief Добавляет ребро в граф.
     * @param u Начальная вершина.
     * @param v Конечная вершина.
     * @param weight Вес ребра.
     */
    void addEdge(int u, int v, int weight);

    /**
     * @brief Загружает граф из файла.
     * @param fileName Имя файла.
     * @param startVertex Начальная вершина.
     * @throws std::runtime_error Если файл не может быть открыт.
     */
    void loadFromFile(const std::string& fileName, int& startVertex);

    /**
     * @brief Экспортирует граф в формате Graphviz.
     * @param fileName Имя файла для экспорта.
     * @throws std::runtime_error Если файл не может быть открыт.
     */
    void toGraphviz(const std::string& fileName) const;

    /**
     * @brief Реализует алгоритм Дейкстры для поиска кратчайших путей.
     * @param startVertex Начальная вершина.
     * @param fileName Имя файла для сохранения результатов.
     * @return Вектор кратчайших расстояний до каждой вершины.
     * @throws std::runtime_error Если файл не может быть создан.
     */
    std::vector<int> dijkstra(int startVertex, const std::string& fileName) const;

private:
    int vertices; ///< Количество вершин.
    int edgeCount; ///< Количество рёбер.
    std::vector<std::vector<std::pair<int, int>>> adjList; ///< Список смежности.
};

/*class Graph {
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

    int getEdgeCount() const { return edgeCount; }
    int getVertexCount() const { return vertices; }
};
*/
//test
