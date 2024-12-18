#include "test.h"
#include <iostream>
#include <cassert>
#include "DirectedGraph.h"



void displayMenu() {
    std::cout << "\n--- Меню ---\n";
    std::cout << "1. Создать граф\n";
    std::cout << "2. Добавить ребро\n";
    std::cout << "3. Отобразить граф\n";
    std::cout << "4. Найти кратчайший путь\n";
    std::cout << "5. Найти компоненты сильной связности\n";
    std::cout << "6. Выход\n";
    std::cout << "Выберите опцию (1-6): ";
}

int main() {
    setlocale(LC_ALL, "Russian"); // 
    testAddEdge();
    testShortestPath();
    testStronglyConnectedComponents();
    DirectedGraph* graph = nullptr; 
    int choice;

    while (true) {
        displayMenu();
        std::cin >> choice;

        try {
            switch (choice) {
            case 1: { // Создать граф
                int vertices;
                std::cout << "Введите количество вершин: ";
                std::cin >> vertices;
                if (vertices <= 0) {
                    throw std::invalid_argument("Количество вершин должно быть положительным.");
                }
                if (graph != nullptr) {
                    delete graph;
                }
                graph = new DirectedGraph(vertices);
                std::cout << "Граф создан с " << vertices << " вершинами.\n";
                break;
            }
            case 2: { // Добавить ребро
                if (graph == nullptr) {
                    throw std::logic_error("Сначала создайте граф.");
                }
                int from, to;
                std::cout << "Введите исходную вершину (0 - " << graph->getNumVertices() - 1 << "): ";
                std::cin >> from;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw std::invalid_argument("Некорректный ввод для исходной вершины.");
                }
                std::cout << "Введите конечную вершину (0 - " << graph->getNumVertices() - 1 << "): ";
                std::cin >> to;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw std::invalid_argument("Некорректный ввод для конечной вершины.");
                }

                // Проверка существования вершин
                if (from < 0 || from >= graph->getNumVertices()) {
                    std::cout << "Ошибка: исходная вершина " << from << " не существует.\n";
                    break;
                }
                if (to < 0 || to >= graph->getNumVertices()) {
                    std::cout << "Ошибка: конечная вершина " << to << " не существует.\n";
                    break;
                }

                graph->addEdge(from, to);
                std::cout << "Ребро добавлено от " << from << " к " << to << ".\n";
                break;
            }
            case 3: { // Отобразить граф
                if (graph == nullptr) {
                    throw std::logic_error("Сначала создайте граф.");
                }
                std::cout << "Текущий граф:\n";
                graph->printGraph();
                break;
            }
            case 4: { // Найти кратчайший путь
                if (graph == nullptr) {
                    throw std::logic_error("Сначала создайте граф.");
                }
                int start, end;
                std::cout << "Введите начальную вершину: ";
                std::cin >> start;
                std::cout << "Введите конечную вершину: ";
                std::cin >> end;
                Dynamic_Array<int> distances = graph->shortestPath(start, end);
                if (distances[end] != -1)
                    std::cout << "Кратчайшее расстояние от " << start << " до " << end << " равно " << distances[end] << ".\n";
                else
                    std::cout << "Нет пути от " << start << " до " << end << ".\n";
                break;
            }
            case 5: { // Найти компоненты сильной связности
                if (graph == nullptr) {
                    throw std::logic_error("Сначала создайте граф.");
                }
                Dynamic_Array<Dynamic_Array<int>> scc = graph->stronglyConnectedComponents();
                std::cout << "Компоненты сильной связности:\n";
                int count = 1;
                for (int i = 0; i < scc.get_colElm(); i++ ) {
                    std::cout << "Компонента " << count++ << ": ";
                    for (int j = 0; j < scc[i].get_colElm(); j++)
                        std::cout << scc[i][j] << " ";
                    std::cout << "\n";
                }
                break;
            }
            case 6: { // Выход
                std::cout << "Выход из программы.\n";
                if (graph != nullptr) {
                    delete graph;
                }
                return 0;
            }
            default:
                std::cout << "Неверный выбор. Пожалуйста, выберите опцию от 1 до 6.\n";
            }
        }
        catch (const std::out_of_range& e) {
            std::cerr << "Ошибка: " << e.what() << "\n";
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Ошибка: " << e.what() << "\n";
        }
        catch (const std::logic_error& e) {
            std::cerr << "Ошибка: " << e.what() << "\n";
        }
        catch (...) { 
            std::cerr << "Произошла непредвиденная ошибка.\n";
        }
    }

    return 0;
}









/*

int main() {
    setlocale(LC_ALL, "Russian");
    testAddEdge();
    testShortestPath();
    testStronglyConnectedComponents();

    //// Создание графа с 5 вершинами
    //DirectedGraph graph(5);

    //// Добавление рёбер
    //graph.addEdge(0, 2);
    //graph.addEdge(2, 1);
    //graph.addEdge(1, 0);
    //graph.addEdge(0, 3);
    //graph.addEdge(3, 4);
    //graph.addEdge(3, 2);
    //graph.addEdge(1, 4);
    //graph.addEdge(3, 1);

    //std::cout << "Граф:\n";
    //graph.printGraph();

    //// Поиск кратчайшего пути от 0 до 4 других вершин
    //try {
    //    Dynamic_Array<int> distances = graph.shortestPath(0, 4);
    //    std::cout << "\nКратчайшие расстояния от вершины 0:\n";
    //    for (int i = 0; i < distances.get_colElm(); ++i) {
    //        if (distances[i] != -1)
    //            std::cout << "До " << i << ": " << distances[i] << "\n";
    //        else
    //            std::cout << "До " << i << ": Нет пути\n";
    //    }
    //}
    //catch (const std::invalid_argument& e) {
    //    std::cerr << e.what() << "\n";
    //}

    //// Нахождение компонент сильной связности
    //Dynamic_Array<Dynamic_Array<int>> scc = graph.stronglyConnectedComponents();
    //std::cout << "\nКомпоненты сильной связности:\n";
    //for (int i = 0; i < scc.get_colElm(); i++) {
    //    for (int j = 0 ; j < scc[i].get_colElm(); j++)
    //        std::cout << scc[i][j] << " ";
    //    std::cout << "\n";
    //}

    return 0;
}
*/