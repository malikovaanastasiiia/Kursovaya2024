/**
 * @file main.cpp
 * @brief Основной файл программы для работы с графами, включающий визуализацию и поиск кратчайших путей с использованием алгоритма Дейкстры.
 */

#include "my_lab.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <limits.h>

using namespace std;

/**
 * @brief Точка входа в программу.
 * @details Программа позволяет загрузить граф из файла, отобразить его и найти кратчайшие пути с помощью алгоритма Дейкстры.
 * @return Код завершения программы (0 - успешно, 1 - ошибка).
 */
int main() {
    try {
        string inputFile;
        cout << "Введите имя входного файла: ";
        cin >> inputFile;

        // Формируем путь к файлу
        string current_path = "/Users/anastasiamalikova/Desktop/SUAI/ОП/kursovaya/AlgorithmD/AlgorithmD/" + inputFile;
        
        // Проверяем существование файла
        ifstream fileCheck(current_path);
        if (!fileCheck.is_open()) {
            cerr << "Ошибка открытия файла: " << inputFile << " Проверьте путь или наличие файла." << endl;
            return 1;
        }
        fileCheck.close();

        // Загружаем граф из файла
        Graph graph(0);
        int startVertex;
        graph.loadFromFile(current_path, startVertex);

        // Основное меню программы
        cout << "Выберите действие:\n";
        cout << "1. Отобразить граф\n";
        cout << "2. Применить Алгоритм Дейкстры\n";
        cout << "Ваш выбор: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            // Отображение графа
            cout << "Введите имя выходного файла (без расширения): ";
            string outputFile;
            cin >> outputFile;

            string outputDotFile = "/Users/anastasiamalikova/Desktop/SUAI/ОП/kursовaya/AlgorithmD/AlgorithmD/output.dot";
            string outputPngFile = "/Users/anastasiamalikova/Desktop/SUAI/ОП/kursовaya/AlgorithmD/AlgorithmD/output.png";
            
            cout << "Создаётся файл: " << outputDotFile << endl;
            graph.toGraphviz(outputDotFile);
            cout << "Файл успешно создан: " << outputDotFile << endl;

            // Генерация PNG с помощью Graphviz
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

            string outputDotFile = "/Users/anastasiamalikova/Desktop/SUAI/ОП/kursовaya/AlgorithmD/AlgorithmD/output.dot";
            string outputPngFile = "/Users/anastasiamalikova/Desktop/SUAI/ОП/kursовaya/AlgorithmD/AlgorithmD/output.png";

            cout << "Применяем алгоритм Дейкстры с начальной вершины: " << startVertex << endl;
            vector<int> distances = graph.dijkstra(startVertex, outputDotFile);

            // Генерация PNG с помощью Graphviz
            string command = "/opt/homebrew/bin/dot -Tpng " + outputDotFile + " -o " + outputPngFile;
            int result = system(command.c_str());
            if (result != 0) {
                cerr << "Ошибка выполнения команды dot. Код возврата: " << result << endl;
            } else {
                cout << "Результат работы Алгоритма Дейкстры сохранён в файле: " << outputPngFile << endl;
            }

            // Вывод статистики графа
            cout << "Количество вершин: " << graph.getVertexCount() << endl;
            cout << "Количество рёбер: " << graph.getEdgeCount() << endl;

            // Вывод кратчайших расстояний
            cout << "Кратчайшие расстояния от вершины " << startVertex << ":\n";
            for (size_t i = 0; i < distances.size(); ++i) {
                cout << "До вершины " << i << ": " << distances[i] << endl;
            }
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


#include "my_lab.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <limits.h>

using namespace std;

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
            
            //cout << "Количество вершин: " << graph.getVertexCount() << endl;
            //cout << "Количество рёбер: " << graph.getEdgeCount() << endl;

            cout << "Кратчайшие расстояния от вершины " << startVertex << ":\n";
            for (size_t i = 0; i < distances.size(); ++i) {
                cout << "До вершины " << i << ": " << distances[i] << endl;
            }
            
        } else {
            cerr << "Неверный выбор. Завершение программы.\n";
        }
    } catch (const exception &e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}

*/
