/**
 * @file my_lab.hpp
 * @brief Реализация класса Graph и функций анализа сложности алгоритмов Дейкстры.
 */

#include "my_lab.hpp"

/**
 * @brief Конструктор класса Graph.
 * @param v Количество вершин в графе.
 */
Graph::Graph(int v) : vertices(v), adjList(v) {}

/**
 * @brief Добавляет ребро в граф.
 * @param u Номер первой вершины.
 * @param v Номер второй вершины.
 * @param weight Вес ребра.
 */

void Graph::addEdge(int u, int v, int weight) {
    adjList[u].emplace_back(v, weight);
}

/**
 * @brief Загружает граф из файла.
 * @param fileName Имя файла для загрузки графа.
 * @param startVertex Начальная вершина, считанная из файла.
 * @throws runtime_error Если файл не может быть открыт.
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
 * @brief Генерирует представление графа в формате Graphviz и записывает его в файл.
 * @param fileName Имя выходного файла.
 * @throws runtime_error Если файл не может быть открыт.
 */
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

/**
 * @brief Реализация алгоритма Дейкстры с использованием приоритетной очереди.
 * @param startVertex Начальная вершина.
 * @param fileName Имя файла для сохранения визуализации графа.
 * @return Вектор кратчайших расстояний от начальной вершины.
 * @throws runtime_error Если файл для записи не может быть создан.
 */
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
            outFile << "  " << u << " -> " << v << " [label=\"" << weight << "\", color=" << color << "]\n";
        }
    }
    outFile << "}\n";

    outFile.close();

    cout << "Операции вставки: " << insertions << endl;
    cout << "Операции удаления: " << deletions << endl;
    cout << "Операции релаксации: " << relaxations << endl;

    return dist;
}

/**
 * @brief Реализация простого алгоритма Дейкстры.
 * @param startVertex Начальная вершина.
 * @return Вектор кратчайших расстояний от начальной вершины.
 */
vector<int> Graph::dijkstraSimple(int startVertex) const {
    vector<int> dist(vertices, numeric_limits<int>::max());
    vector<bool> visited(vertices, false);
    dist[startVertex] = 0;

    for (int i = 0; i < vertices; ++i) {
        int u = -1;
        for (int j = 0; j < vertices; ++j) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        visited[u] = true;

        for (const auto& [v, weight] : adjList[u]) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    return dist;
}

/**
 * @brief Генерирует случайный граф и сохраняет его в файл.
 * @param fileName Имя выходного файла.
 * @param vertices Количество вершин в графе.
 * @throws runtime_error Если файл не может быть создан.
 */
void generateGraph(const string& fileName, int vertices) {
    ofstream outFile(fileName);
    if (!outFile.is_open()) {
        throw runtime_error("Ошибка создания файла: " + fileName);
    }

    outFile << "0\n" << vertices << "\n";
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            outFile << (i != j ? rand() % 10 + 1 : 0) << " ";
        }
        outFile << "\n";
    }

    outFile.close();
}

/**
 * @brief Оценивает сложность простого и логарифмического алгоритмов Дейкстры.
 */
void analyzeComplexity() {
    vector<int> vertexCounts = {100, 200, 600, 1000};

    ofstream outFile("/Users/anastasiamalikova/Desktop/SUAI/ОП/kursовaya/AlgorithmD/AlgorithmD/complexity.dat");
    outFile << "Vertices Simple Logarithmic\n";

    for (int vertices : vertexCounts) {
        // Генерация графа сразу в объект Graph
        Graph graph(vertices);
        int startVertex = 0; // Начальная вершина
        for (int i = 0; i < vertices; ++i) {
            for (int j = 0; j < vertices; ++j) {
                if (i != j) {
                    int weight = rand() % 10 + 1;
                    graph.addEdge(i, j, weight);
                }
            }
        }

        // Оценка простого алгоритма
        auto simpleStart = chrono::high_resolution_clock::now();
        graph.dijkstraSimple(startVertex);
        auto simpleEnd = chrono::high_resolution_clock::now();
        auto simpleTime = chrono::duration_cast<chrono::milliseconds>(simpleEnd - simpleStart).count();

        // Оценка логарифмического алгоритма
        auto logStart = chrono::high_resolution_clock::now();
        graph.dijkstra(startVertex, "temp.dot");
        auto logEnd = chrono::high_resolution_clock::now();
        auto logTime = chrono::duration_cast<chrono::milliseconds>(logEnd - logStart).count();

        // Запись результатов в файл
        outFile << vertices << " " << simpleTime << " " << logTime << "\n";
    }

    outFile.close();
}







/*
#include "my_lab.hpp"

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
            outFile << "  " << u << " -> " << v << " [label=\"" << weight << "\", color=" << color << "]\n";
        }
    }
    outFile << "}\n";

    outFile.close();

    cout << "Операции вставки: " << insertions << endl;
    cout << "Операции удаления: " << deletions << endl;
    cout << "Операции релаксации: " << relaxations << endl;

    return dist;
}

vector<int> Graph::dijkstraSimple(int startVertex) const {
    vector<int> dist(vertices, numeric_limits<int>::max());
    vector<bool> visited(vertices, false);
    dist[startVertex] = 0;

    for (int i = 0; i < vertices; ++i) {
        int u = -1;
        for (int j = 0; j < vertices; ++j) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        visited[u] = true;

        for (const auto& [v, weight] : adjList[u]) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    return dist;
}

void generateGraph(const string& fileName, int vertices) {
    ofstream outFile(fileName);
    if (!outFile.is_open()) {
        throw runtime_error("Ошибка создания файла: " + fileName);
    }

    outFile << "0\n" << vertices << "\n";
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            outFile << (i != j ? rand() % 10 + 1 : 0) << " ";
        }
        outFile << "\n";
    }

    outFile.close();
}

void analyzeComplexity() {
    vector<int> vertexCounts = {100, 200, 600, 1000};

    ofstream outFile("/Users/anastasiamalikova/Desktop/SUAI/ОП/kursовaya/AlgorithmD/AlgorithmD/complexity.dat");
    outFile << "Vertices Simple Logarithmic\n";

    for (int vertices : vertexCounts) {
        // Генерация графа сразу в объект Graph
        Graph graph(vertices);
        int startVertex = 0; // Начальная вершина
        for (int i = 0; i < vertices; ++i) {
            for (int j = 0; j < vertices; ++j) {
                if (i != j) {
                    int weight = rand() % 10 + 1;
                    graph.addEdge(i, j, weight);
                }
            }
        }

        // Оценка простого алгоритма
        auto simpleStart = chrono::high_resolution_clock::now();
        graph.dijkstraSimple(startVertex);
        auto simpleEnd = chrono::high_resolution_clock::now();
        auto simpleTime = chrono::duration_cast<chrono::milliseconds>(simpleEnd - simpleStart).count();

        // Оценка логарифмического алгоритма
        auto logStart = chrono::high_resolution_clock::now();
        graph.dijkstra(startVertex, "temp.dot");
        auto logEnd = chrono::high_resolution_clock::now();
        auto logTime = chrono::duration_cast<chrono::milliseconds>(logEnd - logStart).count();

        // Запись результатов в файл
        outFile << vertices << " " << simpleTime << " " << logTime << "\n";
    }

    outFile.close();
}

 
 
 
 
 

/*void analyzeComplexity() {
    
    vector<int> vertexCounts = {100, 200, 500, 1000};

    ofstream outFile("/Users/anastasiamalikova/Desktop/SUAI/ОП/kursovaya/AlgorithmD/AlgorithmD/complexity.dat");
    outFile << "Vertices Simple Logarithmic\n";

    for (int vertices : vertexCounts) {
        string fileName = "graph_" + to_string(vertices) + ".txt";
        generateGraph(fileName, vertices);

        Graph graph(vertices);
        int startVertex;
        graph.loadFromFile(fileName, startVertex);

        // Оценка простого алгоритма
        auto simpleStart = chrono::high_resolution_clock::now();
        graph.dijkstraSimple(startVertex);
        auto simpleEnd = chrono::high_resolution_clock::now();
        auto simpleTime = chrono::duration_cast<chrono::milliseconds>(simpleEnd - simpleStart).count();

        // Оценка логарифмического алгоритма
        auto logStart = chrono::high_resolution_clock::now();
        graph.dijkstra(startVertex, "temp.dot");
        auto logEnd = chrono::high_resolution_clock::now();
        auto logTime = chrono::duration_cast<chrono::milliseconds>(logEnd - logStart).count();

        outFile << vertices << " " << simpleTime << " " << logTime << "\n";
    }

    outFile.close();
}
*/
