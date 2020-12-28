#include <iostream>
#include "graph.h"
#include "DynamicArray.h"
#include "PriorityQueue.h"
#include "vector"
#include "ArraySequence.h"


int main() {
    Graph<int, int> graph{};
    int choice;

    while (true) {
        cout << "1. create vertex" << endl;
        cout << "2. make edge" << endl;
        cout << "3. algorithms" << endl;
        cout << "4. exit" << endl;
        cin >> choice;
        if (choice == 1) {
            try {
                int id;
                cout << "1. enter id" << endl;
                cin >> id;
                graph.createVertex(id);
            } catch (std::runtime_error &) {
                cout << "incorrect input" << endl;
            }
        } else if (choice == 2) {
            int ver1, ver2, weight;
            try {
                cout << "enter first vertex" << endl;
                cin >> ver1;
                cout << "enter second vertex" << endl;
                cin >> ver2;
                cout << "enter weight" << endl;
                cin >> weight;
                graph.makeEdge(ver1, ver2, weight);
            } catch (std::runtime_error &) {
                cout << "incorrect input" << endl;
            };
        } else if (choice == 3) {
            int algo, v;
            cout << "choose algorithm" << endl;
            cout << "1. dijkstra" << endl;
            cin >> algo;
            if (algo == 1) {
                try {
                    cout << "enter vertex" << endl;
                    cin >> v;
                    graph.dijkstra(1).print(cout);
                    cout << endl;
                } catch (std::runtime_error &) {
                    cout << "incorrect input" << endl;
                }
            } else cout << "incorrect input" << endl;
        } else if (choice == 4) {
            break;
        } else cout << "incorrect input" << endl;
    }
}



