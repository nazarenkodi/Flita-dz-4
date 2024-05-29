#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define MAX_VERTICES 100


typedef struct {
    int matrix[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
} Graph;


void initGraph(Graph* graph, int numVertices) {
    graph->numVertices = numVertices;
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            graph->matrix[i][j] = 0;
        }
    }
}


void addEdge(Graph* graph, int src, int dest) {
    graph->matrix[src][dest] = 1;
    graph->matrix[dest][src] = 1;
}


void removeEdgesConnectedToVertex(Graph* graph, int vertex) {
    if (vertex >= graph->numVertices) {
        printf("Ошибка: Недопустимая вершина\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->matrix[vertex][i] == 1) {
            graph->matrix[vertex][i] = 0;
            graph->matrix[i][vertex] = 0;
        }
    }
}


int getDegree(Graph* graph, int vertex) {
    int degree = 0;
    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->matrix[vertex][i] == 1) {
            degree++;
        }
    }
    return degree;
}


void sortVerticesByDegreeDesc(Graph* graph, int* sortedVertices) {
    for (int i = 0; i < graph->numVertices; i++) {
        sortedVertices[i] = i;
    }

   
    for (int i = 0; i < graph->numVertices - 1; i++) {
        for (int j = 0; j < graph->numVertices - i - 1; j++) {
            if (getDegree(graph, sortedVertices[j]) < getDegree(graph, sortedVertices[j + 1])) {
                int temp = sortedVertices[j];
                sortedVertices[j] = sortedVertices[j + 1];
                sortedVertices[j + 1] = temp;
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    printf("Введите количество ребер: ");
    int n = 0;
    scanf("%d", &n);
    Graph graph;
    initGraph(&graph, n);

    addEdge(&graph, 0, 2);
    for (int i = 1; i <= n; i++) {
        addEdge(&graph, i - 1, i);
    }

    printf("Исходный граф:\n");
    for (int i = 0; i < graph.numVertices; i++) {
        for (int j = 0; j < graph.numVertices; j++) {
            printf("%d ", graph.matrix[i][j]);
        }
        printf("\n");
    }

    printf("Какую вершину хотите удалить?\n ");
    int vertexToRemoveEdgesFrom = 0;
    scanf("%d", &vertexToRemoveEdgesFrom);
    removeEdgesConnectedToVertex(&graph, vertexToRemoveEdgesFrom);

    printf("\nГраф после удаления ребер, смежных с вершиной %d:\n", vertexToRemoveEdgesFrom);
    for (int i = 0; i < graph.numVertices; i++) {
        for (int j = 0; j < graph.numVertices; j++) {
            printf("%d ", graph.matrix[i][j]);
        }
        printf("\n");
    }

   
    int sortedVertices[MAX_VERTICES];
    sortVerticesByDegreeDesc(&graph, sortedVertices);

    printf("\nВершины, отсортированные по убыванию степени:\n");
    for (int i = 0; i < graph.numVertices; i++) {
        printf("%d ", sortedVertices[i]);
    }

    return 0;
}
