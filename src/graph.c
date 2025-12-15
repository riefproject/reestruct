#include "graph.h"
#include <stdio.h>

static void freeEdges(GraphEdge* edge) {
    while (edge != NULL) {
        GraphEdge* next = edge->next;
        delete(edge);
        edge = next;
    }
}

Graph* createGraph(bool directed) {
    Graph* graph = new(Graph);
    if (graph == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for Graph\n");
        return NULL;
    }
    graph->vertices = NULL;
    graph->vertexCount = 0;
    graph->directed = directed;
    return graph;
}

GraphVertex* graphAddVertex(Graph* graph, void* data) {
    if (graph == NULL) {
        fprintf(stderr, "Error: Graph is NULL\n");
        return NULL;
    }
    GraphVertex* vertex = new(GraphVertex);
    if (vertex == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for GraphVertex\n");
        return NULL;
    }
    vertex->data = data;
    vertex->edges = NULL;
    vertex->next = graph->vertices;
    graph->vertices = vertex;
    graph->vertexCount++;
    return vertex;
}

static bool removeEdgeOneWay(GraphVertex* from, GraphVertex* to) {
    GraphEdge* current = from->edges;
    GraphEdge* prev = NULL;
    while (current != NULL) {
        if (current->to == to) {
            if (prev == NULL) {
                from->edges = current->next;
            } else {
                prev->next = current->next;
            }
            delete(current);
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

void graphAddEdge(Graph* graph, GraphVertex* from, GraphVertex* to) {
    if (graph == NULL || from == NULL || to == NULL) {
        fprintf(stderr, "Error: Graph or vertices are NULL\n");
        return;
    }
    GraphEdge* edge = new(GraphEdge);
    if (edge == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for GraphEdge\n");
        return;
    }
    edge->to = to;
    edge->next = from->edges;
    from->edges = edge;

    if (!graph->directed && from != to) {
        GraphEdge* reverse = new(GraphEdge);
        if (reverse == NULL) {
            fprintf(stderr, "Error: Memory allocation failed for reverse edge\n");
            return;
        }
        reverse->to = from;
        reverse->next = to->edges;
        to->edges = reverse;
    }
}

bool graphRemoveEdge(Graph* graph, GraphVertex* from, GraphVertex* to) {
    if (graph == NULL || from == NULL || to == NULL) {
        fprintf(stderr, "Error: Graph or vertices are NULL\n");
        return false;
    }
    bool removed = removeEdgeOneWay(from, to);
    if (!graph->directed) {
        removeEdgeOneWay(to, from);
    }
    return removed;
}

size_t graphSize(Graph* graph) {
    if (graph == NULL) return 0;
    return graph->vertexCount;
}

bool graphIsDirected(Graph* graph) {
    if (graph == NULL) return false;
    return graph->directed;
}

void graphForEach(Graph* graph, void (*visit)(GraphVertex* vertex)) {
    if (graph == NULL) {
        fprintf(stderr, "Error: Graph is NULL\n");
        return;
    }
    if (visit == NULL) return;
    GraphVertex* current = graph->vertices;
    while (current != NULL) {
        visit(current);
        current = current->next;
    }
}

void clearGraph(Graph* graph) {
    if (graph == NULL) {
        fprintf(stderr, "Error: Graph is NULL\n");
        return;
    }
    GraphVertex* current = graph->vertices;
    while (current != NULL) {
        GraphVertex* nextVertex = current->next;
        freeEdges(current->edges);
        delete(current);
        current = nextVertex;
    }
    graph->vertices = NULL;
    graph->vertexCount = 0;
}

void freeGraph(Graph* graph) {
    if (graph == NULL) return;
    clearGraph(graph);
    delete(graph);
}

