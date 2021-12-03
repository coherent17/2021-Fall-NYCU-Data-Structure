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

void BellmanFord(Graph *g){
    int *distance = malloc(sizeof(int) * g->vertex_num);
    int *previous = malloc(sizeof(int) * g->vertex_num);

    //initialize the distance element to inf(INT_MAX) and previous to NAN(-1)
    for (int i = 0; i < g->vertex_num;i++){
        distance[i] = INF;
        previous[i] = NAN;
    }
    //disance from start to start is 0
    distance[0] = 0;
    
}

void printGraphData(Graph *g){
    printf("number of vertex in the graph: %d\n", g->vertex_num);
    printf("number of edge in the graph: %d\n", g->edge_num);
    printf("edge data: (start, end, edge_weight):\n");
    for (int i = 0; i < g->edge_num;i++){
        printf("(%d %d %d)\n", (g->edge[i]).start, (g->edge[i]).end, (g->edge[i]).edge_weight);
    }
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

    //free the allocated memory
    free(Mygraph->edge);
    free(Mygraph);
    return 0;
}