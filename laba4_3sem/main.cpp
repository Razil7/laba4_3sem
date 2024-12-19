#include "test.h"
#include <iostream>
#include <cassert>
#include "DirectedGraph.h"



void displayMenu() {
    std::cout << "\n--- ���� ---\n";
    std::cout << "1. ������� ����\n";
    std::cout << "2. �������� �����\n";
    std::cout << "3. ���������� ����\n";
    std::cout << "4. ����� ���������� ����\n";
    std::cout << "5. ����� ���������� ������� ���������\n";
    std::cout << "6. �����\n";
    std::cout << "�������� ����� (1-6): ";
}

int main() {
    setlocale(LC_ALL, "Russian"); // 
    testAddEdge();
    testShortestPath();
    testStronglyConnectedComponents();
    DirectedGraph<int>* graph = nullptr; 
    int choice;

    while (true) {
        displayMenu();
        std::cin >> choice;

        try {
            switch (choice) {
            case 1: { // ������� ����
                int vertices;
                std::cout << "������� ���������� ������: ";
                std::cin >> vertices;
                if (vertices <= 0) {
                    throw std::invalid_argument("���������� ������ ������ ���� �������������.");
                }
                if (graph != nullptr) {
                    delete graph;
                }
                graph = new DirectedGraph<int>(vertices);
                std::cout << "���� ������ � " << vertices << " ���������.\n";
                break;
            }
            case 2: { // �������� �����
                if (graph == nullptr) {
                    throw std::logic_error("������� �������� ����.");
                }
                int from, to;
                std::cout << "������� �������� ������� (0 - " << graph->getNumVertices() - 1 << "): ";
                std::cin >> from;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw std::invalid_argument("������������ ���� ��� �������� �������.");
                }
                std::cout << "������� �������� ������� (0 - " << graph->getNumVertices() - 1 << "): ";
                std::cin >> to;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw std::invalid_argument("������������ ���� ��� �������� �������.");
                }

                // �������� ������������� ������
                if (from < 0 || from >= graph->getNumVertices()) {
                    std::cout << "������: �������� ������� " << from << " �� ����������.\n";
                    break;
                }
                if (to < 0 || to >= graph->getNumVertices()) {
                    std::cout << "������: �������� ������� " << to << " �� ����������.\n";
                    break;
                }

                graph->addEdge(from, to);
                std::cout << "����� ��������� �� " << from << " � " << to << ".\n";
                break;
            }
            case 3: { // ���������� ����
                if (graph == nullptr) {
                    throw std::logic_error("������� �������� ����.");
                }
                std::cout << "������� ����:\n";
                graph->printGraph();
                break;
            }
            case 4: { // ����� ���������� ����
                if (graph == nullptr) {
                    throw std::logic_error("������� �������� ����.");
                }
                int start, end;
                std::cout << "������� ��������� �������: ";
                std::cin >> start;
                std::cout << "������� �������� �������: ";
                std::cin >> end;
                Dynamic_Array<int> distances = graph->shortestPath(start, end);
                if (distances[end] != -1)
                    std::cout << "���������� ���������� �� " << start << " �� " << end << " ����� " << distances[end] << ".\n";
                else
                    std::cout << "��� ���� �� " << start << " �� " << end << ".\n";
                break;
            }
            case 5: { // ����� ���������� ������� ���������
                if (graph == nullptr) {
                    throw std::logic_error("������� �������� ����.");
                }
                Dynamic_Array<Dynamic_Array<int>> scc = graph->stronglyConnectedComponents();
                std::cout << "���������� ������� ���������:\n";
                int count = 1;
                for (int i = 0; i < scc.get_colElm(); i++ ) {
                    std::cout << "���������� " << count++ << ": ";
                    for (int j = 0; j < scc[i].get_colElm(); j++)
                        std::cout << scc[i][j] << " ";
                    std::cout << "\n";
                }
                break;
            }
            case 6: { // �����
                std::cout << "����� �� ���������.\n";
                if (graph != nullptr) {
                    delete graph;
                }
                return 0;
            }
            default:
                std::cout << "�������� �����. ����������, �������� ����� �� 1 �� 6.\n";
            }
        }
        catch (const std::out_of_range& e) {
            std::cerr << "������: " << e.what() << "\n";
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "������: " << e.what() << "\n";
        }
        catch (const std::logic_error& e) {
            std::cerr << "������: " << e.what() << "\n";
        }
        catch (...) { 
            std::cerr << "��������� �������������� ������.\n";
        }
    }

    return 0;
}







