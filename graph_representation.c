#include <stdio.h>
#include <stdlib.h>

#define MAX 6

char vertices[MAX] = {'A', 'B', 'C', 'D', 'E', 'F'};

/* Adjacency Matrix */
int matrix[MAX][MAX] = {
    {0, 1, 1, 0, 0, 0},
    {1, 0, 0, 1, 1, 0},
    {1, 0, 0, 0, 0, 1},
    {0, 1, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 1},
    {0, 0, 1, 0, 1, 0}
};

/* Adjacency List */
typedef struct Node {
    int vertex;
    struct Node *next;
} Node;

Node *list[MAX] = {NULL};

/* Add an edge to adjacency list */
void addEdge(int u, int v) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;

    if (list[u] == NULL) {
        list[u] = newNode;
    } else {
        Node *temp = list[u];

        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newNode;
    }
}

/* Display adjacency matrix */
void displayMatrix() {
    int i, j;

    printf("\nAdjacency Matrix:\n\n  ");

    for (i = 0; i < MAX; i++)
        printf("%c ", vertices[i]);

    printf("\n");

    for (i = 0; i < MAX; i++) {
        printf("%c ", vertices[i]);

        for (j = 0; j < MAX; j++)
            printf("%d ", matrix[i][j]);

        printf("\n");
    }
}

/* Display adjacency list */
void displayList() {
    int i;

    printf("\nAdjacency List:\n");

    for (i = 0; i < MAX; i++) {
        printf("%c -> ", vertices[i]);

        Node *temp = list[i];

        while (temp != NULL) {
            printf("%c ", vertices[temp->vertex]);
            temp = temp->next;
        }

        printf("\n");
    }
}

/* BFS using adjacency matrix */
void BFS_Matrix(int start) {
    int visited[MAX] = {0};
    int queue[MAX];
    int front = 0, rear = 0;
    int i, u;

    visited[start] = 1;
    queue[rear++] = start;

    printf("\nBFS using Adjacency Matrix: ");

    while (front < rear) {
        u = queue[front++];
        printf("%c ", vertices[u]);

        for (i = 0; i < MAX; i++) {
            if (matrix[u][i] == 1 && visited[i] == 0) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }

    printf("\n");
}

/* DFS using adjacency matrix */
void DFS_Matrix_Util(int u, int visited[]) {
    int i;

    visited[u] = 1;
    printf("%c ", vertices[u]);

    for (i = 0; i < MAX; i++) {
        if (matrix[u][i] == 1 && visited[i] == 0)
            DFS_Matrix_Util(i, visited);
    }
}

void DFS_Matrix(int start) {
    int visited[MAX] = {0};

    printf("\nDFS using Adjacency Matrix: ");

    DFS_Matrix_Util(start, visited);

    printf("\n");
}

/* BFS using adjacency list */
void BFS_List(int start) {
    int visited[MAX] = {0};
    int queue[MAX];
    int front = 0, rear = 0;

    visited[start] = 1;
    queue[rear++] = start;

    printf("\nBFS using Adjacency List: ");

    while (front < rear) {
        int u = queue[front++];

        printf("%c ", vertices[u]);

        Node *temp = list[u];

        while (temp != NULL) {
            int v = temp->vertex;

            if (visited[v] == 0) {
                visited[v] = 1;
                queue[rear++] = v;
            }

            temp = temp->next;
        }
    }

    printf("\n");
}

/* DFS using adjacency list */
void DFS_List_Util(int u, int visited[]) {
    Node *temp;

    visited[u] = 1;
    printf("%c ", vertices[u]);

    temp = list[u];

    while (temp != NULL) {
        if (visited[temp->vertex] == 0)
            DFS_List_Util(temp->vertex, visited);

        temp = temp->next;
    }
}

void DFS_List(int start) {
    int visited[MAX] = {0};

    printf("\nDFS using Adjacency List: ");

    DFS_List_Util(start, visited);

    printf("\n");
}

/* Search using adjacency matrix */
int searchMatrix(char target) {
    int i;

    for (i = 0; i < MAX; i++) {
        if (vertices[i] == target)
            return i;
    }

    return -1;
}

/* Search using adjacency list */
int searchList(char target) {
    int i;

    for (i = 0; i < MAX; i++) {
        if (vertices[i] == target)
            return i;
    }

    return -1;
}

int main() {

    /* Create adjacency list */
    addEdge(0, 1);
    addEdge(0, 2);

    addEdge(1, 0);
    addEdge(1, 3);
    addEdge(1, 4);

    addEdge(2, 0);
    addEdge(2, 5);

    addEdge(3, 1);

    addEdge(4, 1);
    addEdge(4, 5);

    addEdge(5, 2);
    addEdge(5, 4);

    /* Display both representations */
    displayMatrix();
    displayList();

    /* BFS and DFS starting from A */
    BFS_Matrix(0);
    DFS_Matrix(0);

    BFS_List(0);
    DFS_List(0);

    /* Search operation */
    char target = 'F';

    printf("\nSearch for vertex %c:\n", target);

    if (searchMatrix(target) != -1)
        printf("Using Adjacency Matrix: Vertex %c found.\n", target);
    else
        printf("Using Adjacency Matrix: Vertex not found.\n");

    if (searchList(target) != -1)
        printf("Using Adjacency List: Vertex %c found.\n", target);
    else
        printf("Using Adjacency List: Vertex not found.\n");

    return 0;
}
