#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <string>
using namespace std;

class CampusGraph {
private:
    unordered_map<string, vector<string>> adj;

public:
    void addLocation(const string& name) {
        if (!adj.count(name)) adj[name] = {};
    }

    void addPath(const string& a, const string& b) {
        addLocation(a);
        addLocation(b);
        adj[a].push_back(b);
        adj[b].push_back(a); // Campus paths are treated as two-way.
    }

    vector<string> bfsPath(const string& source, const string& destination) const {
        if (!adj.count(source) || !adj.count(destination)) return {};

        queue<string> q;
        unordered_set<string> visited;
        unordered_map<string, string> parent;
        q.push(source);
        visited.insert(source);

        while (!q.empty()) {
            string current = q.front();
            q.pop();
            if (current == destination) break;

            auto it = adj.find(current);
            if (it == adj.end()) continue;
            for (const string& next : it->second) {
                if (!visited.count(next)) {
                    visited.insert(next);
                    parent[next] = current;
                    q.push(next);
                }
            }
        }

        if (source != destination && !parent.count(destination)) return {};
        vector<string> path;
        string current = destination;
        path.push_back(current);
        while (current != source) {
            auto it = parent.find(current);
            if (it == parent.end()) return {};
            current = it->second;
            path.push_back(current);
        }
        reverse(path.begin(), path.end());
        return path;
    }

    vector<string> dfsReachable(const string& source) const {
        vector<string> result;
        if (!adj.count(source)) return result;

        unordered_set<string> visited;
        stack<string> st;
        st.push(source);
        while (!st.empty()) {
            string current = st.top();
            st.pop();
            if (visited.count(current)) continue;
            visited.insert(current);
            result.push_back(current);

            const auto& neighbours = adj.at(current);
            // Reverse insertion order for a more readable, stable traversal.
            for (auto it = neighbours.rbegin(); it != neighbours.rend(); ++it) {
                if (!visited.count(*it)) st.push(*it);
            }
        }
        return result;
    }

    vector<string> allLocations() const {
        vector<string> names;
        for (const auto& entry : adj) names.push_back(entry.first);
        sort(names.begin(), names.end());
        return names;
    }

    void showGraph() const {
        auto names = allLocations();
        cout << "\nCampus graph (adjacency list):\n";
        for (const auto& name : names) {
            cout << "  " << name << " -> ";
            const auto& neighbours = adj.at(name);
            if (neighbours.empty()) cout << "(no paths)";
            for (size_t i = 0; i < neighbours.size(); ++i) {
                if (i) cout << ", ";
                cout << neighbours[i];
            }
            cout << '\n';
        }
    }

    void showDisconnectedFrom(const string& source) const {
        if (!adj.count(source)) {
            cout << "Unknown starting location.\n";
            return;
        }
        auto reachable = dfsReachable(source);
        unordered_set<string> seen(reachable.begin(), reachable.end());
        vector<string> disconnected;
        for (const auto& name : allLocations())
            if (!seen.count(name)) disconnected.push_back(name);

        cout << "Reachable from " << source << " (" << reachable.size() << "): ";
        for (size_t i = 0; i < reachable.size(); ++i) {
            if (i) cout << " -> ";
            cout << reachable[i];
        }
        cout << '\n';
        if (disconnected.empty()) {
            cout << "Disconnected locations: none\n";
        } else {
            cout << "Disconnected locations: ";
            for (size_t i = 0; i < disconnected.size(); ++i) {
                if (i) cout << ", ";
                cout << disconnected[i];
            }
            cout << '\n';
        }
    }

    bool hasLocation(const string& name) const { return adj.count(name) > 0; }
};

int main() {
    CampusGraph campus;

    // Eight example campus locations.
    vector<string> locations = {
        "Main Gate", "Library", "Block 1", "Block 2",
        "Cafeteria", "Auditorium", "Parking", "Lab"
    };
    for (const auto& location : locations) campus.addLocation(location);

    // Example two-way paths. Lab is initially disconnected for the test case.
    campus.addPath("Main Gate", "Library");
    campus.addPath("Main Gate", "Parking");
    campus.addPath("Library", "Block 1");
    campus.addPath("Library", "Cafeteria");
    campus.addPath("Block 1", "Block 2");
    campus.addPath("Block 2", "Lab");
    campus.addPath("Cafeteria", "Auditorium");
    campus.addPath("Parking", "Auditorium");

    int choice;
    do {
        cout << "\n=== Campus Route Finder ===\n"
             << "1. Display graph\n"
             << "2. Find minimum-edge route using BFS\n"
             << "3. Show DFS-reachable locations and disconnected locations\n"
             << "4. Add a two-way path\n"
             << "5. Exit\n"
             << "Enter choice: ";
        if (!(cin >> choice)) return 0;
        cin.ignore(10000, '\n');

        if (choice == 1) {
            campus.showGraph();
        } else if (choice == 2) {
            string source, destination;
            cout << "Enter source location (exact name): ";
            getline(cin, source);
            cout << "Enter destination location (exact name): ";
            getline(cin, destination);
            auto path = campus.bfsPath(source, destination);
            if (path.empty()) {
                cout << "No route found. Check names or the destination may be unreachable.\n";
            } else {
                cout << "BFS route (" << path.size() - 1 << " edges): ";
                for (size_t i = 0; i < path.size(); ++i) {
                    if (i) cout << " -> ";
                    cout << path[i];
                }
                cout << '\n';
            }
        } else if (choice == 3) {
            string source;
            cout << "Enter starting location (exact name): ";
            getline(cin, source);
            campus.showDisconnectedFrom(source);
        } else if (choice == 4) {
            string a, b;
            cout << "Enter first location: ";
            getline(cin, a);
            cout << "Enter second location: ";
            getline(cin, b);
            campus.addPath(a, b);
            cout << "Two-way path added.\n";
        } else if (choice == 5) {
            cout << "Goodbye!\n";
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
