#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 500
#define INF 2147483647
#define NAN -1

typedef struct _EdgeNode{
    int start;
    int end;
    int edge_weight;
}EdgeNode;

typedef struct _Graph{
    int vertex_num;
    int edge_num;
    EdgeNode *edge;
}Graph;

typedef struct _Arrays{
    int *distance;
    int *previous;
}Arrays;

int getVertexNum(char *input_filename){
    int vertex_count = 0;
    FILE *input = fopen(input_filename, "r");
    char *buffer = malloc(sizeof(char) * BUFFER_SIZE);
    fscanf(input, "%[^\n]%*c", buffer);

    //string token:
    char *temp;
    temp = strtok(buffer, " ");
    while(temp!=NULL){
        vertex_count++;
        temp = strtok(NULL, " ");
    }
    free(buffer);
    fclose(input);
    return vertex_count;
}

int getEdgeNum(char *input_filename, int vertice_count){
    int edge_count = 0;
    int temp;
    FILE *input = fopen(input_filename, "r");
    for (int i = 0; i < vertice_count;i++){
        for (int j = 0; j < vertice_count;j++){
            fscanf(input, "%d", &temp);
            if(temp!=0){
                edge_count++;
            }
        }
    }
    fclose(input);
    return edge_count;
}

void initGraph(Graph *g, int edge_count, int vertex_count){
    g->edge_num = edge_count;
    g->vertex_num = vertex_count;
    g->edge = malloc(sizeof(EdgeNode) * edge_count);
}

void readfile(char *input_filename, Graph *g){
    FILE *input = fopen(input_filename, "r");
    int temp;
    int edge_index = 0;
    for (int i = 0; i < g->vertex_num;i++){
        for (int j = 0; j < g->vertex_num;j++){
            fscanf(input, "%d", &temp);
            if(temp!=0){
                (g->edge[edge_index]).start = i;
                (g->edge[edge_index]).end = j;
                (g->edge[edge_index]).edge_weight = temp;
                edge_index++;
            }
        }
    }
    fclose(input);
}

void printArray(int *array, int size){
    for (int i = 0; i < size;i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}

void printReverseArray(int *array, int size){
    for (int i = size - 1; i >= 0;i--){
        printf("%d ", array[i]);
    }
    printf("\n");
}

Arrays *BellmanFord(Graph *g){
    int *distance = malloc(sizeof(int) * g->vertex_num);
    int *previous = malloc(sizeof(int) * g->vertex_num);

    //initialize the distance element to inf(INT_MAX) and previous to NAN(-1)
    for (int i = 0; i < g->vertex_num;i++){
        distance[i] = INF;
        previous[i] = NAN;
    }
    //disance from start to start is 0
    distance[0] = 0;

    for (int i = 1; i < g->vertex_num - 1;i++){
        for (int j = 0; j < g->edge_num;j++){
            if(distance[g->edge[j].start]!=INF && distance[g->edge[j].end]>distance[g->edge[j].start] + g->edge[j].edge_weight){
                distance[g->edge[j].end] = distance[g->edge[j].start] + g->edge[j].edge_weight;
                previous[g->edge[j].end] = g->edge[j].start;
            }
        }
    }

    //check whether there exist negative cycle
    for (int i = 0; i < g->edge_num;i++){
        if(distance[g->edge[i].start]!=INF && distance[g->edge[i].end]>distance[g->edge[i].start] + g->edge[i].edge_weight){
            printf("Negative weight cycle detected!\n");
            return NULL;
        }
    }

    Arrays *returnArray = malloc(sizeof(Arrays));
    returnArray->distance = distance;
    returnArray->previous = previous;
    return returnArray;
}

void printGraphData(Graph *g){
    printf("number of vertex in the graph: %d\n", g->vertex_num);
    printf("number of edge in the graph: %d\n", g->edge_num);
    printf("edge data: (start, end, edge_weight):\n");
    for (int i = 0; i < g->edge_num;i++){
        printf("(%d %d %d)\n", (g->edge[i]).start, (g->edge[i]).end, (g->edge[i]).edge_weight);
    }
}

int *getShortestPath(int *previous, int destination, int *path_node_count){
    int path_index = 0;
    int temp = previous[destination];
    //calculate how many node to pass
    while(temp!=0){
        path_index++;
        temp = previous[temp];
    }
    int *path = malloc(sizeof(int) * (path_index + 1));

    temp = previous[destination];
    while(temp!=0){
        path[path_index] = temp;
        path_index++;
        temp = previous[temp];
    }
    *path_node_count = path_index + 1;
    return path;
}

int main(int argc, char *argv[]){

    //input  and output filename:
    char *input_filename = *(argv + 1);
    char *output_filename = *(argv + 2);

    //get how many vertices are in the graph
    int vertex_count = getVertexNum(input_filename);
    int edge_count = getEdgeNum(input_filename, vertex_count);

    //construct the graph
    Graph *Mygraph = malloc(sizeof(Graph));
    initGraph(Mygraph, edge_count, vertex_count);

    //construct edge list
    readfile(input_filename, Mygraph);
    printGraphData(Mygraph);

    //BellmanFord Algorithm:
    int *distance = NULL;
    int *previous = NULL;
    Arrays *temp = BellmanFord(Mygraph);
    if(temp==NULL){
        printf("Negative cycle detected\n");
    }
    else{
        distance = temp->distance;
        previous = temp->previous;
        printArray(distance, Mygraph->vertex_num);
        printArray(previous, Mygraph->vertex_num);

        int *path = NULL;
        int path_node_count = 0;
        path = getShortestPath(previous, 1, &path_node_count);
        printReverseArray(path, path_node_count);
        path = getShortestPath(previous, 2, &path_node_count);
        printReverseArray(path, path_node_count);
        path = getShortestPath(previous, 3, &path_node_count);
        printReverseArray(path, path_node_count);
        path = getShortestPath(previous, 4, &path_node_count);
        printReverseArray(path, path_node_count);
    }


    //free the allocated memory
    free(Mygraph->edge);
    free(Mygraph);
    return 0;
}