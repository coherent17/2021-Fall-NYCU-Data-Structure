#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int coefficient;
    int exp_x;
    int exp_y;
    int exp_z;
    struct node *next;
} node;

// head to store the start of the linkedlist
// tail to store the tail of the linkedlist
typedef struct polynomial{
    node *head;
    node *tail;
} polynomial;

//extra linkedlist to store the head pointer to each polynomial linkedlist
typedef struct listnode{
    polynomial *p;
    struct listnode *next;
} listnode;

typedef struct polylist{
    listnode *listhead;
    listnode *listtail;
} polylist;

//init the polynomial struct
void initPolynomial(polynomial *p){
    p->head = NULL;
    p->tail = NULL;
}

//init the polyist structure
void initPolylist(polylist *p){
    p->listhead = NULL;
    p->listtail = NULL;
}

node *createNode(int coefficient, int exp_x, int exp_y, int exp_z){
    node *newNode = (node *)malloc(sizeof(node));
    newNode->coefficient = coefficient;
    newNode->exp_x = exp_x;
    newNode->exp_y = exp_y;
    newNode->exp_z = exp_z;
    newNode->next = NULL;
    return newNode;
}

listnode *createListNode(polynomial *p){
    listnode *newListNode = (listnode *)malloc(sizeof(listnode));
    newListNode->p = p;
    newListNode->next = NULL;
    return newListNode;
}

polynomial *append_poly(FILE *input){
    //start of the polynomial
    polynomial *p = (polynomial *)malloc(sizeof(polynomial));
    initPolynomial(p);

    int term_count;
    int coefficient;
    int exp_x;
    int exp_y;
    int exp_z;

    fscanf(input, "%d", &term_count);

    for (int i = 0; i < term_count;i++){
        fscanf(input, "%d", &coefficient);
        fscanf(input, "%d", &exp_x);
        fscanf(input, "%d", &exp_y);
        fscanf(input, "%d", &exp_z);
        node *temp = createNode(coefficient, exp_x, exp_y, exp_z);

        //if first time to entry the loop, create a head to store the start of the linkedlist
        if(p->head==NULL){
            p->head = temp;
            p->tail = temp;
        }

        //insert the node at the tail of the linkedlist
        else{
            p->tail->next = temp;
            p->tail = temp;
        }
    }
    return p;
}

void printPolynomial(polynomial *p){
    node *temp = p->head;
    while(temp!=NULL){
        printf("coefficient: %d\n", temp->coefficient);
        printf("exp_x: %d\n", temp->exp_x);
        printf("exp_y: %d\n", temp->exp_y);
        printf("exp_z: %d\n", temp->exp_z);
        printf("\n");
        temp = temp->next;
    }
}

void printPolyList(polylist *list){
    int count = 0;
    listnode *temp = list->listhead;
    while(temp!=NULL){
        printf("Number %d polynomial:\n", count++);
        printPolynomial(temp->p);
        temp = temp->next;
    }
}

int main(int argc, char *argv[]){
    char *filename = *(argv + 1);
    //char *outputname = *(argv + 2);

    //store the number to determine what to do to the linkedlist
    int OP_ID;

    //the list is a linkedlist to store the head pointer to the node
    //in each polynomial struct
    polylist *list = malloc(sizeof(polylist));
    initPolylist(list);

    FILE *input = fopen(filename, "r");
    while(fscanf(input, "%d", &OP_ID)!=EOF){
        //append the polynomial
        if(OP_ID==0){
            polynomial *p = append_poly(input);
            listnode *temp = createListNode(p);
            if(list->listhead==NULL){
                list->listhead = temp;
                list->listtail = temp;
            }
            else{
                list->listtail->next = temp;
                list->listtail = temp;
            }
            //printPolyList(list);
        }
        else if(OP_ID==1){
            //add polynomial here
        }
        else if(OP_ID==2){
            //subtract polynomial here
        }
        else if(OP_ID==3){
            //multiply polynomial here
        }
        else if(OP_ID==4){
            //delete polynomial here
        }
    }
    printPolyList(list);
    return 0;
}