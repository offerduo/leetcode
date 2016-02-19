#include "graph.h"
#include <stack>

using namespace std;

class Solution {
 public:
  UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
    if (!node) return NULL;
    UndirectedGraphNode *result = new UndirectedGraphNode(node->label);
    unordered_map<UndirectedGraphNode *, UndirectedGraphNode *> nodeMap;
    stack<UndirectedGraphNode *> s;
    nodeMap[node] = result;
    s.push(node);
    while (!s.empty()) {
      UndirectedGraphNode *src = s.top(); s.pop();
      UndirectedGraphNode *copy = nodeMap[src];
      for (auto neighbor : src->neighbors) {
        if (nodeMap.find(neighbor) == nodeMap.end()) {
          UndirectedGraphNode *neighborCopy =
              new UndirectedGraphNode(neighbor->label);
          nodeMap[neighbor] = neighborCopy;
          s.push(neighbor);
        }
        copy->neighbors.push_back(nodeMap[neighbor]);
      }
    }
    return result;
  }
};

int main(int argc, char *argv[])
{
  Graph graph;
  unordered_map<int, UndirectedGraphNode *> nodeMap;
  readUndirectedGraphNode(cin, &graph, nodeMap);
  dumpGraph(graph.vertices.front());
  Solution sol;
  cout << "\nCloning graph...\n" << endl;
  UndirectedGraphNode *result = sol.cloneGraph(graph.vertices.front());
  dumpGraph(result);
  return 0;
}
