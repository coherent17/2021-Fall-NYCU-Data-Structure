#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFF_LENGTH 15
#define MAX_SIZE 1000005
//if the queue is empty when dequeuing, return ';'
#define QUEUE_EMPTY ';'

//global variable, store # of processor
int num_processor;

typedef struct queue{
    char *task; //char array to store tasks
    int task_count; //# of element in task[]
    int head;
    int tail;
    char *done; //char array to store the tasks been executed
    int done_count;  //# of element in done[]
} queue;

void initQueue(queue *q){
    q->head = -1;
    q->tail = -1;
    q->task = malloc(sizeof(char) * MAX_SIZE);
    q->done = malloc(sizeof(char) * MAX_SIZE);
    q->task_count = 0;
    q->done_count = 0;
}

//check whether the queue is empty
bool queue_empty(queue *q){
    return (q->task_count == 0);
}

//check whether the queue is full
bool queue_full(queue *q){
    if((q->head==q->tail+1)||(q->head==0&&q->tail==MAX_SIZE-1))
        return true;
    return false;
}

//add task into the circular queue
bool enqueue(queue *q, char c){
    
    if(queue_full(q)){
        //printf("Queue is full\n");
        return false;
    }

    //the first element enter the queue, change head from -1 to 0
    if(q->head==-1){
        q->head = 0;
    }

    //put the task into the task[tail]
    q->tail = (q->tail + 1) % MAX_SIZE;
    q->task[q->tail] = c;
    q->task_count++;
    return true;
}

//first in first out, get the task out of the task array
char dequeue(queue *q){
    char result;

    if(queue_empty(q)){
        //printf("Queue is empty!\n");
        return QUEUE_EMPTY;
    }
    //if the queue isn't empty, return the result of task[head]
    else{
        result = q->task[q->head];
        //init the head & tail pointer when dequeue the last task in the queue
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

//stack operation, last in first out, get the last task put into the queue
char pop(queue *q){
    char result;

    if(queue_empty(q)){
        //printf("Queue is empty!\n");
        return QUEUE_EMPTY;
    }
    //if the queue isn't empty, return the result of task[tail]
    else{
        result = q->task[q->tail];
        //init the head & tail pointer when pop the last task in the queue
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

//printout the queue content
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

//printout the all queue content
void display(queue *processor){
    printf("-----------------------------------\n");
    for (int i = 1; i <= num_processor;i++){
        printf("processor %d:\n", i);
        printQueue(&processor[i]);
        printf("\n");
    }
    printf("-----------------------------------\n");
}

void freeProcessor(queue *processor){
    for (int i = 0; i <= num_processor;i++){
        free(processor[i].task);
        free(processor[i].done);
    }
}

int main(int argc, char *argv[]){
    
    char *filename = *(argv + 1);
    char *outputname = *(argv + 2);

    //store the input string
    char buffer[BUFF_LENGTH];
    FILE *input = fopen(filename, "r");

    //get the number of processor
    fscanf(input, "%d", &num_processor);
    //the array processor start from index = 1
    queue *processor = (queue *)malloc(sizeof(queue)*(num_processor+1));

    //init all processor:
    for (int i = 1; i <= num_processor;i++){
        initQueue(&processor[i]);
        //printf("%d processor has been init\n", i);
    }

    //the index to determine to operate on which processor
    int processor_index;

    while(fscanf(input, "%s", buffer) != EOF){
        if(strcmp(buffer, "ASSIGN") == 0){
            //printf("%s ", buffer);
            fscanf(input, "%s", buffer);
            processor_index = atoi(buffer);
            //printf("%s ", buffer);
            fscanf(input, "%s", buffer);
            //printf("%s\n", buffer);
            enqueue(&processor[processor_index], buffer[0]);
            //display(processor);
        }
        else if(strcmp(buffer, "EXEC") == 0){
            //printf("%s ", buffer);
            fscanf(input, "%s", buffer);
            processor_index = atoi(buffer);
            //printf("%s\n", buffer);
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
            //display(processor);
        }
        else if(strcmp(buffer, "STOP") == 0){
            //printf("%s\n", buffer);
            break;
        }
    }
    fclose(input);

    //start to output
    FILE *outputfile;
    outputfile = fopen(outputname, "w");

    //fprintf the queuing task
    fprintf(outputfile, "Queuing\n");
    for (int i = 1; i <= num_processor;i++){
        fprintf(outputfile, "%d ", i);
        int j;
        for (j = processor[i].head; j != processor[i].tail;j=(j+1)%MAX_SIZE){
            fprintf(outputfile, "%c", processor[i].task[j]);
        }
        fprintf(outputfile, "%c\n", processor[i].task[j]);
    }

    //fprintf the executed task
    fprintf(outputfile, "Executed\n");
    for (int i = 1; i <= num_processor;i++){
        fprintf(outputfile, "%d ", i);
        for (int j = 0; j < processor[i].done_count;j++){
            fprintf(outputfile, "%c", processor[i].done[j]);
        }
        fprintf(outputfile, "\n");
    }
    fclose(outputfile);
    freeProcessor(processor);
    return 0;
}