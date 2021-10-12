#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_LENGTH 15
#define MAX_SIZE 1000005
#define EMPTY (-1)
//if the queue is empty when dequeuing, return ';'
#define QUEUE_EMPTY ';'

//global variable, store # of processor
int num_processor;

typedef struct queue{
    char task[MAX_SIZE];
    int head;
    int tail;//know how many task in the queue by tail & head
    char done[MAX_SIZE];
    int done_count;
} queue;

void initQueue(queue *q){
    q->head = EMPTY;
    q->tail = EMPTY;
    q->done_count = 0;
}

void enqueue(queue *q, char c){
    q->tail++;
    q->task[q->tail] = c;
}

char dequeue(queue *q){
    //if queue is empty, return ';'
    if(q->tail==EMPTY)
        return QUEUE_EMPTY;

    char result = q->task[q->head+1];
    q->head++;
    return result;
}

char pop(queue *q){
    //if queue is empty, return ';'
    if(q->tail==EMPTY)
        return QUEUE_EMPTY;

    char result = q->task[q->tail];
    q->tail--;
    return result;
}

void printQueue(queue *q){
    //queuing task:
    printf("Queuing:\n");
    for (int i = q->head + 1; i <= q->tail;i++){
        printf("%c ", q->task[i]);
    }
    printf("\n");

    //executed task:
    printf("Executed:\n");
    for (int i = 0; i < q->done_count; i++){
        printf("%c ", q->done[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]){
    
    char *filename = *(argv + 1);
    char *outputName = *(argv + 2);

    char buffer[BUFF_LENGTH];
    FILE *input = fopen(filename, "r");

    //get the number of processor
    fscanf(input, "%d", &num_processor);
    //the array processor start from index = 1
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
            int processor_index = atoi(buffer);
            printf("%s ", buffer);
            fscanf(input, "%s", buffer);
            printf("%s\n", buffer);
            enqueue(&processor[processor_index], buffer[0]);
            //printQueue(&processor[processor_index]);
        }
        else if(strcmp(buffer, "EXEC") == 0){
            printf("%s ", buffer);
            fscanf(input, "%s", buffer);
            int processor_index = atoi(buffer);
            printf("%s\n", buffer);
        }
        else if(strcmp(buffer, "STOP") == 0){
            printf("%s\n", buffer);
            break;
        }
    }
    return 0;
}