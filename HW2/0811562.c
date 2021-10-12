#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_LENGTH 15
#define MAX_SIZE 1000005
#define EMPTY (-1)

typedef struct queue{
    char task[MAX_SIZE];
    int head;
    int tail;
    char done[MAX_SIZE];
    int done_index;
} queue;

void initQueue(queue *q){
    q->head = EMPTY;
    q->tail = EMPTY;
    q->done_index = 0;
}


int main(int argc, char *argv[]){
    
    char *filename = *(argv + 1);
    char *outputName = *(argv + 2);

    char buffer[BUFF_LENGTH];
    FILE *input = fopen(filename, "r");

    //get the number of processor
    int num_processor;
    fscanf(input, "%d", &num_processor);
    queue *processor = (queue *)malloc(sizeof(queue)*(num_processor+1));

    //init all processor:
    for (int i = 1; i <= num_processor;i++){
        initQueue(&processor[i]);
        printf("%d processor has been init\n", i);
    }

    while(fscanf(input, "%s", buffer) != EOF){
        if(strcmp(buffer, "ASSIGN") == 0){
            printf("%s ", buffer);
            fscanf(input, "%s", buffer);
            printf("%s ", buffer);
            fscanf(input, "%s", buffer);
            printf("%s\n", buffer);
        }
        else if(strcmp(buffer, "EXEC") == 0){
            printf("%s ", buffer);
            fscanf(input, "%s", buffer);
            printf("%s\n", buffer);
        }
        else if(strcmp(buffer, "STOP") == 0){
            printf("%s\n", buffer);
            break;
        }
    }
    return 0;
}