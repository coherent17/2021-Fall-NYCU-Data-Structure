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
    if(temp==NULL)
        printf("There is no polynomial in the polylist\n");
    while(temp!=NULL){
        printf("Number %d polynomial:\n", count++);
        printPolynomial(temp->p);
        temp = temp->next;
    }
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

polynomial *appendPolynomial(FILE *input){
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

polynomial *findPolynomial(listnode *head, int index){
    listnode *temp = head;
    for (int i = 0; i < index;i++){
        temp = temp->next;
    }
    return temp->p;
}

polynomial *addPolynomial(listnode *head, int a, int b){
    polynomial *addResult = (polynomial *)malloc(sizeof(polynomial));
    initPolynomial(addResult);
    //find a_th polynomial and b_th polynomial
    polynomial *poly_a = findPolynomial(head, a);
    polynomial *poly_b = findPolynomial(head, b);
    return addResult;
}

void delete_node(node **headptr){

}

//go through the entire polynomial and delete all nodes
void delete_all_node(polynomial *p){
    node **head = &p->head;
    node **tail = &p->tail;
    node *cur_del_node = (*head);
    node *next_node;
    while(cur_del_node!=NULL){
        next_node = cur_del_node->next;
        free(cur_del_node);
        cur_del_node = next_node;
    }
    (*head) = NULL;
    (*tail) = NULL;
}

void deletePolynomial(listnode **headptr, listnode **tailptr, int num_to_delete){

    listnode *temp = *headptr;
    //if the delete node is the head node:
    if(num_to_delete==0 && (*headptr)!=NULL){
        if((*headptr)->next!=NULL){
            (*headptr) = temp->next;
        }
        else{
            (*headptr) = NULL;
            (*tailptr) = NULL;
        }
        //go through the entire polynomial and delete all node:
        delete_all_node(temp->p);
        free(temp);
        return;
    }

    //find which polynomial to delete:
    for (int i = 0; i < num_to_delete-1;i++){
        temp = temp->next;
    }
    listnode *prev = temp;
    temp = temp->next;
    prev->next = temp->next;
    if(temp->next==NULL){
        (*tailptr) = prev;
    }
    else{
        (*tailptr) = prev->next;
    }
    delete_all_node(temp->p);
    free(temp);
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
            polynomial *p = appendPolynomial(input);
            listnode *temp = createListNode(p);
            if(list->listhead==NULL){
                list->listhead = temp;
                list->listtail = temp;
            }
            else{
                list->listtail->next = temp;
                list->listtail = temp;
            }
            printf("\nAfter appending:\n");
            printPolyList(list);
        }
        else if(OP_ID==1){
            //add polynomial here
            int a, b;
            fscanf(input, "%d", &a);
            fscanf(input, "%d", &b);
            polynomial *addResult = addPolynomial(list->listhead, a, b);
            listnode *temp = createListNode(addResult);
            if(list->listhead==NULL){
                list->listhead = temp;
                list->listtail = temp;
            }
            else{
                list->listtail->next = temp;
                list->listtail = temp;
            }
            printf("\nAfter addding:\n");
            printPolyList(list);
        }
        else if(OP_ID==2){
            //subtract polynomial here
        }
        else if(OP_ID==3){
            //multiply polynomial here
        }
        else if(OP_ID==4){
            //delete polynomial here
            int del_index;
            fscanf(input, "%d", &del_index);
            deletePolynomial(&list->listhead, &list->listtail, del_index);
            printf("\nAfter deleting:\n");
            printPolyList(list);
        }
    }
    printf("\nFinal:\n");
    printPolyList(list);
    return 0;
}