#include <iostream>
#include <bits/stdc++.h>
using namespace std;

extern map<int, string> Map;

class Graph
{
    int no_of_vertices;
    struct vertex
    {
        int vertex_no;
        bool visited;
        int path;
        int distance;
    };
    struct edge
    {
        int weight;
        struct vertex *from;
        struct vertex *to;
    };

    vector<vertex> vertices;
    vector<edge> edges;

public:
    Graph(int n)
    {
        no_of_vertices = n;
        vertices.resize(n);
        for (int i = 0; i < n; i++)
        {
            vertices[i].vertex_no = i;
            vertices[i].visited = false;
            vertices[i].path = -1;
            vertices[i].distance = INT_MAX;
        }
        mapping("mapping.txt");  
    }

    void resetVisited()
    {
        for (int i = 0; i < no_of_vertices; i++)
        {
            vertices[i].visited = false;
        }
    }

    void addEdge(int from, int to, int weight)
    {
        edge e;
        e.weight = weight;
        e.from = &vertices[from];
        e.to = &vertices[to];
        edges.push_back(e);
        e.from = &vertices[to];
        e.to = &vertices[from];
        edges.push_back(e);
    }

    void displayAdjacencyList()
    {
        vector<vector<int>> adjacencyList(no_of_vertices);
        for (int i = 0; i < edges.size(); i++)
        {
            adjacencyList[edges[i].from->vertex_no].push_back(edges[i].to->vertex_no);
        }
        for (int i = 0; i < no_of_vertices; i++)
        {
            cout << Map[i] << " -> ";
            for (int j = 0; j < adjacencyList[i].size(); j++)
            {
                cout << Map[adjacencyList[i][j]] << " ";
            }
            cout << endl;
        }
    }

    void dijkstra(int source)
    {
        resetVisited();
        vertices[source].distance = 0;
        vertices[source].path = -1;
        vector<pair<int, int>> shortest_path_edges;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, source});
        while (!pq.empty())
        {
            int u = pq.top().second;
            pq.pop();
            if (vertices[u].visited)
            {
                continue;
            }
            vertices[u].visited = true;
            for (int i = 0; i < edges.size(); i++)
            {
                if (edges[i].from->vertex_no == u)
                {
                    int v = edges[i].to->vertex_no;
                    if (vertices[v].distance > vertices[u].distance + edges[i].weight)
                    {
                        vertices[v].distance = vertices[u].distance + edges[i].weight;
                        vertices[v].path = u;
                        shortest_path_edges.push_back({u, v});
                        pq.push({vertices[v].distance, v});
                    }
                }
            }
        }
    }

    void exportShortestPath(int destination) {
    ofstream path_out("texts/path.txt");
    ofstream edges_out("texts/ed.txt");

    if (vertices[destination].distance == INT_MAX) {
        path_out << "No path exists" << endl;
        return;
    }

    vector<int> path;
    int current = destination;
    while (current != -1) {
        path.push_back(current);
        current = vertices[current].path;
    }

    reverse(path.begin(), path.end());

    for (int i = 0; i < path.size(); ++i) {
        path_out << path[i] << (i == path.size() - 1 ? "\n" : " ");
    }

    for (const auto& edge : edges) {
        if (find(path.begin(), path.end(), edge.from->vertex_no) != path.end() &&
            find(path.begin(), path.end(), edge.to->vertex_no) != path.end()) {
            edges_out << edge.from->vertex_no << " " << edge.to->vertex_no << "\n";
        }
    }

    path_out.close();
    edges_out.close();

}

    void displayShortestPath(int destination)
    {
        if (vertices[destination].distance == INT_MAX)
        {
            cout << "No path exists" << endl;
            return;
        }
        if (vertices[destination].path != -1)
            displayShortestPath(vertices[destination].path);
        cout << Map[destination] << " ";
        cout << "---->  ";
    }

    void mapping(string file_name)
    {
        ifstream file(file_name);
        int i;
        string s;
        while (file >> i >> s)
        {
            Map[i] = s;
        }
    }

};

map<int, string> Map; 