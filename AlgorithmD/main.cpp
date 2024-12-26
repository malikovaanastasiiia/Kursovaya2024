
#include "my_lab.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <limits.h>

using namespace std;

/**
 * @brief Анализирует сложность алгоритмов для различных размеров графа.
 *        Результаты сохраняются в файл "complexity.dat".
 */
void analyzeComplexity();

int main() {
    try {
        string inputFile;
        cout << "Введите имя входного файла: ";
        cin >> inputFile;

        // Формирование полного пути к входному файлу
        string current_path = "/Users/anastasiamalikova/Desktop/SUAI/ОП/kursovaya/AlgorithmD/AlgorithmD/" + inputFile;

        // Проверка существования файла
        ifstream fileCheck(current_path);
        if (!fileCheck.is_open()) {
            cerr << "Ошибка открытия файла: " << inputFile << " Проверьте путь или наличие файла." << endl;
            return 1;
        }
        fileCheck.close();

        // Создание объекта графа
        Graph graph(0);
        int startVertex;
        graph.loadFromFile(current_path, startVertex);

        cout << "Выберите действие:\n";
        cout << "1. Отобразить граф\n";
        cout << "2. Применить Алгоритм Дейкстры\n";
        cout << "3. Сравнить алгоритмы\n";
        cout << "Ваш выбор: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            // Вывод графа в файл .dot и генерация изображения
            cout << "Введите имя выходного файла (без расширения): ";
            string outputFile;
            cin >> outputFile;

            string outputDotFile = "/Users/anastasiamalikova/Desktop/SUAI/ОП/kursovaya/AlgorithmD/AlgorithmD/output.dot";
            string outputPngFile = "/Users/anastasiamalikova/Desktop/SUAI/ОП/kursovaya/AlgorithmD/AlgorithmD/output.png";

            cout << "Создаётся файл: " << outputDotFile << endl;
            graph.toGraphviz(outputDotFile);
            cout << "Файл успешно создан: " << outputDotFile << endl;

            // Вызов команды dot для создания изображения
            string command = "/opt/homebrew/bin/dot -Tpng " + outputDotFile + " -o " + outputPngFile;
            int result = system(command.c_str());
            if (result != 0) {
                cerr << "Ошибка выполнения команды dot. Код возврата: " << result << endl;
            } else {
                cout << "Граф сохранён в файле: " << outputPngFile << endl;
            }
        } else if (choice == 2) {
            // Применение алгоритма Дейкстры
            cout << "Введите имя выходного файла (без расширения): ";
            string outputFile;
            cin >> outputFile;

            string outputDotFile = "/Users/anastasiamalikova/Desktop/SUAI/ОП/kursovaya/AlgorithmD/AlgorithmD/output.dot";
            string outputPngFile = "/Users/anastasiamalikova/Desktop/SUAI/ОП/kursovaya/AlgorithmD/AlgorithmD/output.png";

            cout << "Применяем алгоритм Дейкстры с начальной вершины: " << startVertex << endl;
            vector<int> distances = graph.dijkstra(startVertex, outputDotFile);

            // Вызов команды dot для создания изображения
            string command = "/opt/homebrew/bin/dot -Tpng " + outputDotFile + " -o " + outputPngFile;
            int result = system(command.c_str());
            if (result != 0) {
                cerr << "Ошибка выполнения команды dot. Код возврата: " << result << endl;
            } else {
                cout << "Результат работы Алгоритма Дейкстры сохранён в файле: " << outputPngFile << endl;
            }

            // Вывод информации о графе
            cout << "Количество вершин: " << graph.getVertexCount() << endl;
            cout << "Количество рёбер: " << graph.getEdgeCount() << endl;

            // Вывод кратчайших расстояний
            cout << "Кратчайшие расстояния от вершины " << startVertex << ":\n";
            for (size_t i = 0; i < distances.size(); ++i) {
                cout << "До вершины " << i << ": " << distances[i] << endl;
            }
        } else if (choice == 3) {
            // Сравнение алгоритмов
            analyzeComplexity();
        } else {
            cerr << "Неверный выбор. Завершение программы.\n";
        }
    } catch (const exception &e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}



/*
using namespace std;
void analyzeComplexity();
int main() {
    try {
        string inputFile;
        cout << "Введите имя входного файла: ";
        cin >> inputFile;
        string current_path = "/Users/anastasiamalikova/Desktop/SUAI/ОП/kursovaya/AlgorithmD/AlgorithmD/" + inputFile;
        ifstream fileCheck(current_path);
        if (!fileCheck.is_open()) {
            cerr << "Ошибка открытия файла: " << inputFile << " Проверьте путь или наличие файла." << endl;
            return 1;
        }
        fileCheck.close();
        

        Graph graph(0);
        int startVertex;
        graph.loadFromFile(current_path, startVertex);

        cout << "Выберите действие:\n";
        cout << "1. Отобразить граф\n";
        cout << "2. Применить Алгоритм Дейкстры\n";
        cout << "3. Сравнить алгоритмы\n";
        cout << "Ваш выбор: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            cout << "Введите имя выходного файла (без расширения): ";
            string outputFile;
            cin >> outputFile;

            string outputDotFile = "/Users/anastasiamalikova/Desktop/SUAI/ОП/kursovaya/AlgorithmD/AlgorithmD/output.dot";
            string outputPngFile = "/Users/anastasiamalikova/Desktop/SUAI/ОП/kursovaya/AlgorithmD/AlgorithmD/output.png";
            
            cout << "Создаётся файл: " << outputDotFile << endl;
            graph.toGraphviz(outputDotFile);
            cout << "Файл успешно создан: " << outputDotFile << endl;

            string command = "/opt/homebrew/bin/dot -Tpng " + outputDotFile + " -o " + outputPngFile;
            int result = system(command.c_str());
            if (result != 0) {
                cerr << "Ошибка выполнения команды dot. Код возврата: " << result << endl;
            } else {
                cout << "Граф сохранён в файле: " << outputPngFile << endl;
            }
        } else if (choice == 2) {
            cout << "Введите имя выходного файла (без расширения): ";
            string outputFile;
            cin >> outputFile;
            
            string outputDotFile = "/Users/anastasiamalikova/Desktop/SUAI/ОП/kursovaya/AlgorithmD/AlgorithmD/output.dot";
            string outputPngFile = "/Users/anastasiamalikova/Desktop/SUAI/ОП/kursovaya/AlgorithmD/AlgorithmD/output.png";
            
            cout << "Применяем алгоритм Дейкстры с начальной вершины: " << startVertex << endl;
            vector<int> distances = graph.dijkstra(startVertex, outputDotFile);
            
            string command = "/opt/homebrew/bin/dot -Tpng " + outputDotFile + " -o " + outputPngFile;
            int result = system(command.c_str());
            if (result != 0) {
                cerr << "Ошибка выполнения команды dot. Код возврата: " << result << endl;
            } else {
                cout << "Результат работы Алгоритма Дейкстры сохранён в файле: " << outputPngFile << endl;
            }
            
            cout << "Количество вершин: " << graph.getVertexCount() << endl;
            cout << "Количество рёбер: " << graph.getEdgeCount() << endl;
            
            cout << "Кратчайшие расстояния от вершины " << startVertex << ":\n";
            for (size_t i = 0; i < distances.size(); ++i) {
                cout << "До вершины " << i << ": " << distances[i] << endl;
            }
        }
        else if (choice == 3) {
            analyzeComplexity();
        } else{
            cerr << "Неверный выбор. Завершение программы.\n";
        }
    } catch (const exception &e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}

*/
