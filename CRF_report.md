# Mini Project Report: Campus Route Finder Using Graphs

## 1. Aim
To create a campus route finder that represents campus locations as vertices and paths as edges, then uses BFS and DFS to explore routes and reachability.

## 2. Graph representation
The program stores the graph as an adjacency list using `unordered_map<string, vector<string>>`. Each campus location is a vertex. Each two-way path is stored in both locations' neighbour lists. Eight sample locations are included: Main Gate, Library, Block 1, Block 2, Cafeteria, Auditorium, Parking, and Lab.

An adjacency list stores only existing edges and is usually suitable for sparse campus maps. An adjacency matrix uses a V-by-V table, requiring O(V^2) space, but can check whether a particular edge exists in O(1) time.

## 3. Algorithms
### Breadth-First Search (BFS)
BFS uses a queue and visits locations level by level. A parent map records the predecessor of each visited location. The route is reconstructed by walking backwards from the destination to the source and reversing the result. In an unweighted graph, this gives a route with the minimum number of edges.

### Depth-First Search (DFS)
DFS uses a stack to explore one branch before returning to other branches. The visited set prevents repeated visits. It is used to list reachable locations and identify locations not reachable from the selected source.

## 4. Complexity
Let V be the number of vertices and E the number of edges.

| Operation | Time | Auxiliary space |
|---|---|---|
| BFS route | O(V + E) | O(V) |
| DFS reachability | O(V + E) | O(V) |
| Adjacency list storage | — | O(V + E) |
| Adjacency matrix storage | — | O(V^2) |

## 5. Test cases
| Test | Input / setup | Expected result |
|---|---|---|
| Direct route | Main Gate to Library | One edge: Main Gate -> Library |
| Multi-stop route | Main Gate to Block 2 | Minimum of three edges via Library and Block 1 |
| Same source and destination | Library to Library | One location, zero edges |
| Unreachable destination | Temporarily remove Block 2–Lab edge and search Main Gate to Lab | No route found |

## 6. Conclusion
The project demonstrates graph representation, queue-based BFS, stack-based DFS, route reconstruction, and reachability analysis. The menu allows users to inspect the graph, find routes, and add paths.
