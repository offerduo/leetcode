#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// test on git hook

typedef struct UndirectedGraphNode {
  int label;
  std::vector<UndirectedGraphNode *> neighbors;
  UndirectedGraphNode(int x) : label (x) {};
} UndirectedGraphNode;

typedef struct Graph {
  int numVertex;
  std::vector<UndirectedGraphNode *> vertices;
} Graph;

// If there is no node with nodeTag, create a new node;
// otherwise just returns the node.
UndirectedGraphNode *getUndirectedGraphNode(
    std::unordered_map<int, UndirectedGraphNode *> &nodeMap,
    const char *labelStr)
{
  UndirectedGraphNode *nodePtr;
  int label = atoi(labelStr);
  std::unordered_map<int, UndirectedGraphNode *>::const_iterator iter;
  if ((iter = nodeMap.find(label)) == nodeMap.end()) {
    nodePtr = new UndirectedGraphNode(label);
    std::cout << "Creating new node with label (" << nodePtr->label << ")" << std::endl;
    std::pair<int, UndirectedGraphNode *> mapPair(nodePtr->label, nodePtr);
    nodeMap.insert(mapPair);
  } else {
    nodePtr = iter->second;
  }
  return nodePtr;
}

// Add vertices to Graph
void addVertexToGraph(Graph *graph, UndirectedGraphNode *nodePtr)
{
  std::cout << "Adding vertex " << nodePtr->label << " to graph" << std::endl;
  ++graph->numVertex;
  graph->vertices.push_back(nodePtr);
}

// Add edge between two nodes
void addEdgeBetweenVertices(UndirectedGraphNode *src, UndirectedGraphNode *dest)
{
  std::cout << "\tAdding edge between " << src->label << " and " << dest->label
            << std::endl;
  src->neighbors.push_back(dest);
  if (src != dest)
    dest->neighbors.push_back(src);
}

// Dump the graph
void dumpGraph(UndirectedGraphNode *node)
{
  std::queue<UndirectedGraphNode *> q;
  std::unordered_set<UndirectedGraphNode *> nodeSet;
  q.push(node); nodeSet.insert(node);
  while (!q.empty()) {
    UndirectedGraphNode *vertex = q.front(); q.pop();
    std::cout << vertex->label << " :";
    for (auto neighbor : vertex->neighbors) {
      std::cout << " " << neighbor->label;
      if (nodeSet.find(neighbor) == nodeSet.end()) {
        nodeSet.insert(neighbor);
        q.push(neighbor);
      }
    }
    std::cout << std::endl;
  }
}

void readUndirectedGraphNode(
    std::istream &in,
    Graph *graph,
    std::unordered_map<int, UndirectedGraphNode *> &nodeMap)
{
  std::string node;
  char *vertexStr, *saveptr;

  while (getline(in, node, '#')) {
    vertexStr = strtok_r(const_cast<char*>(node.c_str()), ",", &saveptr);
    UndirectedGraphNode *src = getUndirectedGraphNode(nodeMap, vertexStr);
    addVertexToGraph(graph, src);
    vertexStr = strtok_r(NULL, ",", &saveptr);
    for (; vertexStr; vertexStr = strtok_r(NULL, ",", &saveptr)) {
      UndirectedGraphNode *dest = getUndirectedGraphNode(nodeMap, vertexStr);
      addEdgeBetweenVertices(src, dest);
    }
  }
}

#endif
