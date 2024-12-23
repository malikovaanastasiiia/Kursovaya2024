
#include "my_lab.hpp"
/**
 * @file my_lab.hpp
 * @brief Реализация класса Graph и его методов для работы с графами.
 */

#include "my_lab.hpp"

/**
 * @class Graph
 * @brief Класс для представления направленного взвешенного графа.
 */

/**
 * @brief Конструктор графа.
 * @param v Количество вершин в графе.
 */
Graph::Graph(int v) : vertices(v), adjList(v) {}

/**
 * @brief Добавляет ребро в граф.
 * @param u Начальная вершина.
 * @param v Конечная вершина.
 * @param weight Вес ребра.
 */
void Graph::addEdge(int u, int v, int weight) {
    adjList[u].emplace_back(v, weight);
}

/**
 * @brief Загружает граф из файла.
 * @details Метод читает граф из текстового файла, где каждая строка представляет веса рёбер между вершинами.
 * @param fileName Имя файла с данными о графе.
 * @param startVertex Начальная вершина, указанная в файле.
 * @throws std::runtime_error Если файл не может быть открыт.
 */
void Graph::loadFromFile(const string& fileName, int& startVertex) {
    edgeCount = 0;
    ifstream inFile(fileName);
    if (!inFile) {
        throw runtime_error("Ошибка открытия файла: " + fileName);
    }

    inFile >> startVertex;
    inFile >> vertices;
    adjList.assign(vertices, vector<pair<int, int>>());

    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            int weight;
            inFile >> weight;
            if (weight > 0) {
                addEdge(i, j, weight);
                edgeCount++;
            }
        }
    }
    inFile.close();
}

/**
 * @brief Экспортирует граф в формате Graphviz.
 * @details Создаёт файл, который можно использовать с инструментами Graphviz для визуализации графа.
 * @param fileName Имя файла для экспорта.
 * @throws std::runtime_error Если файл не может быть открыт для записи.
 */
void Graph::toGraphviz(const string& fileName) const {
    ofstream out(fileName);
    if (!out.is_open()) {
        throw runtime_error("Ошибка открытия файла для записи: " + fileName);
    }

    out << "digraph G {" << endl;
    for (size_t u = 0; u < adjList.size(); ++u) {
        for (const auto& [v, weight] : adjList[u]) {
            out << "    " << u << " -> " << v << " [label=\"" << weight << "\"];" << endl;
        }
    }
    out << "}" << endl;
    out.close();
}

/**
 * @brief Реализует алгоритм Дейкстры для поиска кратчайших путей.
 * @details Метод ищет кратчайшие пути от заданной начальной вершины до всех остальных вершин графа.
 * @param startVertex Начальная вершина для алгоритма.
 * @param fileName Имя файла для сохранения результатов работы алгоритма в формате Graphviz.
 * @return Вектор минимальных расстояний от начальной вершины до всех остальных вершин.
 * @throws std::runtime_error Если файл не может быть создан для записи.
 */
vector<int> Graph::dijkstra(int startVertex, const string& fileName) const {
    vector<int> dist(vertices, numeric_limits<int>::max());
    dist[startVertex] = 0;

    set<pair<int, int>> pq; ///< Множество для хранения вершин с их расстояниями.
    pq.insert({0, startVertex});

    vector<int> parent(vertices, -1); ///< Вектор для отслеживания путей.

    int insertions = 0; ///< Количество операций вставки.
    int deletions = 0;  ///< Количество операций удаления.
    int relaxations = 0; ///< Количество операций релаксации.

    while (!pq.empty()) {
        int u = pq.begin()->second;
        pq.erase(pq.begin());
        deletions++;

        for (const auto& [v, weight] : adjList[u]) {
            if (dist[u] + weight < dist[v]) {
                pq.erase({dist[v], v});
                dist[v] = dist[u] + weight;
                pq.insert({dist[v], v});
                parent[v] = u;
                insertions++;
                relaxations++;
            }
        }
    }

    ofstream outFile(fileName);
    if (!outFile) {
        throw runtime_error("Ошибка создания файла: " + fileName);
    }

    // Записываем результаты в формате Graphviz
    outFile << "digraph G {\n";
    for (int u = 0; u < vertices; ++u) {
        for (const auto& [v, weight] : adjList[u]) {
            string color = (parent[v] == u) ? "red" : "black";
            outFile << "  " << u << " -> " << v << " [label=\"" << weight << "\", color=" << color << "];\n";
        }
    }
    outFile << "}\n";

    outFile.close();

    // Вывод статистики алгоритма
    cout << "Операции вставки: " << insertions << endl;
    cout << "Операции удаления: " << deletions << endl;
    cout << "Операции релаксации: " << relaxations << endl;

    return dist;
}

/*

    Graph::Graph(int v) : vertices(v), adjList(v) {}

    void Graph::addEdge(int u, int v, int weight) {
        adjList[u].emplace_back(v, weight);
    }

    void Graph::loadFromFile(const string& fileName, int& startVertex) {
        edgeCount = 0;
        ifstream inFile(fileName);
        if (!inFile) {
            throw runtime_error("Ошибка открытия файла: " + fileName);
        }

        inFile >> startVertex;
        inFile >> vertices;
        adjList.assign(vertices, vector<pair<int, int>>());

        for (int i = 0; i < vertices; ++i) {
            for (int j = 0; j < vertices; ++j) {
                int weight;
                inFile >> weight;
                if (weight > 0) {
                    addEdge(i, j, weight);
                    edgeCount++;
                }
            }
        }
        inFile.close();
        //cout << "Граф загружен: " << vertices << " вершин и " << edgeCount << " рёбер." << endl;
    }

    void Graph::toGraphviz(const string& fileName) const {
        ofstream out(fileName);
        if (!out.is_open()) {
            throw runtime_error("Ошибка открытия файла для записи: " + fileName);
        }

        out << "digraph G {" << endl;
        for (size_t u = 0; u < adjList.size(); ++u) {
            for (const auto& [v, weight] : adjList[u]) {
                out << "    " << u << " -> " << v << " [label=\"" << weight << "\"]:" << endl;
            }
        }
        out << "}" << endl;
        out.close();
    }

    vector<int> Graph::dijkstra(int startVertex, const string& fileName) const {
        vector<int> dist(vertices, numeric_limits<int>::max());
        dist[startVertex] = 0;

        set<pair<int, int>> pq;
        pq.insert({0, startVertex});

        vector<int> parent(vertices, -1);

        int insertions = 0;
        int deletions = 0;
        int relaxations = 0;

        while (!pq.empty()) {
            int u = pq.begin()->second;
            pq.erase(pq.begin());
            deletions++;

            for (const auto& [v, weight] : adjList[u]) {
                if (dist[u] + weight < dist[v]) {
                    pq.erase({dist[v], v});
                    dist[v] = dist[u] + weight;
                    pq.insert({dist[v], v});
                    parent[v] = u;
                    insertions++;
                    relaxations++;
                }
            }
        }

        ofstream outFile(fileName);
        if (!outFile) {
            throw runtime_error("Ошибка создания файла: " + fileName);
        }

        outFile << "digraph G {\n";
        for (int u = 0; u < vertices; ++u) {
            for (const auto& [v, weight] : adjList[u]) {
                string color = (parent[v] == u) ? "red" : "black";
                outFile << "  " << u << " -> " << v << " [label=\"" << weight << "\", color=" << color << "];\n";
            }
        }
        outFile << "}\n";

        outFile.close();

        cout << "Операции вставки: " << insertions << endl;
        cout << "Операции удаления: " << deletions << endl;
        cout << "Операции релаксации: " << relaxations << endl;

        return dist;
    }
*/
