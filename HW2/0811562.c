#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFF_LENGTH 15
#define MAX_SIZE 5
//if the queue is empty when dequeuing, return ';'
#define QUEUE_EMPTY ';'

//global variable, store # of processor
int num_processor;

typedef struct queue{
    char *task;
    int task_count;
    int head;
    int tail;
    char *done;
    int done_count;
} queue;

void initQueue(queue *q){
    q->head = -1;
    q->tail = -1;
    q->task = malloc(sizeof(char) * MAX_SIZE);
    q->done = malloc(sizeof(char) * MAX_SIZE);
    q->task_count = 0;
    q->done_count = 0;
}

bool queue_empty(queue *q){
    return (q->task_count == 0);
}

bool queue_full(queue *q){
    if((q->head==q->tail+1)||(q->head==0&&q->tail==MAX_SIZE-1))
        return true;
    return false;
}

bool enqueue(queue *q, char c){
    
    if(queue_full(q)){
        printf("queue is full\n");
        return false;
    }

    //the first element enter the queue
    if(q->head==-1){
        q->head = 0;
    }

    q->tail = (q->tail + 1) % MAX_SIZE;
    q->task[q->tail] = c;
    q->task_count++;
    return true;
}

char dequeue(queue *q){
    char result;

    if(queue_empty(q)){
        printf("Queue is empty!\n");
        return QUEUE_EMPTY;
    }
    else{
        result = q->task[q->head];
        if(q->head==q->tail){
            q->head = -1;
            q->tail = -1;
        }
        else{
            q->head = (q->head + 1) % MAX_SIZE;
        }
        q->task_count--;
    }
    return result;
}

char pop(queue *q){
    char result;

    if(queue_empty(q)){
        printf("Queue is empty!\n");
        return QUEUE_EMPTY;
    }
    else{
        result = q->task[q->tail];
        if(q->head==q->tail){
            q->head = -1;
            q->tail = -1;
        }
        else{
            q->tail = (q->tail - 1 + MAX_SIZE) % MAX_SIZE;
        }
        q->task_count--;
    }
    return result;
}

void printQueue(queue *q){
    if(queue_empty(q)){
        printf("QueueEmpty\n");
        //printf("head = %d\n", q->head);
        //printf("tail = %d\n", q->tail);
    }
    else{
        int i;
        //printf("head -> %d\n", q->head);
        //printf("tail -> %d\n", q->tail);
        printf("number of tasks: %d\n", q->task_count);
        printf("Queueing Tasks:\n");
        for (i = q->head; i != q->tail;i=(i+1)%MAX_SIZE){
            printf("%c ", q->task[i]);
        }
        printf("%c\n", q->task[i]);
    }

    //print done task
    printf("done count = %d\n", q->done_count);
    for (int i = 0; i < q->done_count;i++){
        printf("%c ", q->done[i]);
    }
    printf("\n");
}

void display(queue *processor){
    printf("-----------------------------------\n");
    for (int i = 1; i <= num_processor;i++){
        printf("processor %d:\n", i);
        printQueue(&processor[i]);
        printf("\n");
    }
    printf("-----------------------------------\n");
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

    
    int processor_index;

    while(fscanf(input, "%s", buffer) != EOF){
        if(strcmp(buffer, "ASSIGN") == 0){
            printf("%s ", buffer);
            fscanf(input, "%s", buffer);
            processor_index = atoi(buffer);
            printf("%s ", buffer);
            fscanf(input, "%s", buffer);
            printf("%s\n", buffer);
            enqueue(&processor[processor_index], buffer[0]);
            display(processor);
        }
        else if(strcmp(buffer, "EXEC") == 0){
            printf("%s ", buffer);
            fscanf(input, "%s", buffer);
            processor_index = atoi(buffer);
            printf("%s\n", buffer);
            if(!queue_empty(&processor[processor_index])){
                //if the queue isn't empty
                char done_temp = dequeue(&processor[processor_index]);
                processor[processor_index].done[processor[processor_index].done_count++] = done_temp;
            }
            else{
                //if the queue is empty:
                int max_task_count = 0;
                int max_processor_index = 1;
                for (int i = 1; i <= num_processor;i++){
                    //find the maximum task count in each procesor
                    if(processor[i].task_count>max_task_count){
                        max_processor_index = i;
                        max_task_count = processor[i].task_count;
                    }
                }
                processor[processor_index].done[processor[processor_index].done_count++] = pop(&processor[max_processor_index]);
            }
            display(processor);
        }
        else if(strcmp(buffer, "STOP") == 0){
            printf("%s\n", buffer);
            break;
        }
    }
    return 0;
}