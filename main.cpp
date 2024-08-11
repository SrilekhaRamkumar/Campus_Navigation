#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <map>
#include "graph.h"
#include <bits/stdc++.h>

using namespace std;

Graph g(17);

// Function to load mapping and syllabus data from files
void loadData() {
    ifstream fileformap("texts/mapping.txt");
    ifstream fileforSyllabus("texts/syllabus.txt");
    int i;
    string s;

    // Load mapping data
    while (fileformap >> i >> s) {
        Map[i] = s;
    }

}

void printMap() {
    for (int i = 0; i < 17; i++) {
        cout << i + 1 << "-->" << Map[i] << "\n";
    }
}

void createGraph() {
    int u, v;
    ifstream file("texts/edges.txt");
    while (file >> u >> v) {
        g.addEdge(u, v, 1); 
    }
}

int main() {
    loadData();
    createGraph();

    string s, d;
    int source, destination;
    int choice;
    bool flag = false;
    do {
        cout << "\nWelcome to University Chatbot\n";
        cout << "1. Navigation\n";
        cout << "2. Display Map\n";
        cout << "3. View places\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;


        switch (choice) {
        case 1:
            cout << "\nNavigation selected\n";
            cout << "Enter the place where you are: ";
            cin >> source;
            cout << "Enter the place where you want to go: ";
            cin >> destination;
            cout<<"---------------------------------------------------\n";
            
            g.dijkstra(--source);
            g.exportShortestPath(--destination);
            system("C:\\Users\\nkgra\\AppData\\Local\\Programs\\Python\\Python39\\python.exe disp.py texts/ed.txt texts/coors.txt texts/mapping.txt");
            g.displayShortestPath(destination);
            cout << endl;
            break;
        case 2:
            cout << "\nDisplay Map selected\n";
            // Replace "python" with the full path to your Python executable
            system("C:\\Users\\nkgra\\AppData\\Local\\Programs\\Python\\Python39\\python.exe disp.py texts/edges.txt texts/coors.txt texts/mapping.txt");
            cout << "---------------------------------------------------\n";
            break;

        case 3:
            cout << "\nDisplay Places\n";
            printMap();
            cout<<"---------------------------------------------------\n";
            break;
        case 4:
            cout << "\nExiting...\n";
            break;
        default:
            cout << "Invalid choice! Please enter a valid option.\n";
            break;
        }
    } while (choice !=4);

    return 0;
}