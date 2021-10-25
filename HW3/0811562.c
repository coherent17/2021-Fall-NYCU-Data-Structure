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
    node *temp_a = poly_a->head;
    node *temp_b = poly_b->head;
    node *temp = NULL;
    while(temp_a && temp_b){
        if(temp_a->exp_x == temp_b->exp_x){
            if(temp_a->exp_y == temp_b->exp_y){
                if(temp_a->exp_z == temp_b->exp_z){
                    if(temp_a->coefficient + temp_b->coefficient!=0){
                        temp = (node *)malloc(sizeof(node));
                        temp->coefficient = temp_a->coefficient + temp_b->coefficient;
                        temp->exp_x = temp_a->exp_x;
                        temp->exp_y = temp_a->exp_y;
                        temp->exp_z = temp_a->exp_z;
                        temp->next = NULL;
                        temp_a = temp_a->next;
                        temp_b = temp_b->next;
                    }
                    else{
                        temp_a = temp_a->next;
                        temp_b = temp_b->next;
                    }
                }
                else if(temp_a->exp_z > temp_b->exp_z){
                    temp = (node *)malloc(sizeof(node));
                    temp->coefficient = temp_a->coefficient;
                    temp->exp_x = temp_a->exp_x;
                    temp->exp_y = temp_a->exp_y;
                    temp->exp_z = temp_a->exp_z;
                    temp->next = NULL;
                    temp_a = temp_a->next;
                }
                else if(temp_a->exp_z < temp_b->exp_z){
                    temp = (node *)malloc(sizeof(node));
                    temp->coefficient = temp_b->coefficient;
                    temp->exp_x = temp_b->exp_x;
                    temp->exp_y = temp_b->exp_y;
                    temp->exp_z = temp_b->exp_z;
                    temp->next = NULL;
                    temp_b = temp_b->next;
                }
            }
            else if(temp_a->exp_y > temp_b->exp_y){
                temp = (node *)malloc(sizeof(node));
                temp->coefficient = temp_a->coefficient;
                temp->exp_x = temp_a->exp_x;
                temp->exp_y = temp_a->exp_y;
                temp->exp_z = temp_a->exp_z;
                temp->next = NULL;
                temp_a = temp_a->next;
            }
            else if(temp_a->exp_y < temp_b->exp_y){
                temp = (node *)malloc(sizeof(node));
                temp->coefficient = temp_b->coefficient;
                temp->exp_x = temp_b->exp_x;
                temp->exp_y = temp_b->exp_y;
                temp->exp_z = temp_b->exp_z;
                temp->next = NULL;
                temp_b = temp_b->next;
            }
        }
        else if(temp_a->exp_x > temp_b->exp_x){
            temp = (node *)malloc(sizeof(node));
            temp->coefficient = temp_a->coefficient;
            temp->exp_x = temp_a->exp_x;
            temp->exp_y = temp_a->exp_y;
            temp->exp_z = temp_a->exp_z;
            temp->next = NULL;
            temp_a = temp_a->next;
        }
        else if(temp_a->exp_x < temp_b->exp_x){
            temp = (node *)malloc(sizeof(node));
            temp->coefficient = temp_b->coefficient;
            temp->exp_x = temp_b->exp_x;
            temp->exp_y = temp_b->exp_y;
            temp->exp_z = temp_b->exp_z;
            temp->next = NULL;
            temp_b = temp_b->next;
        }

        if(addResult->head==NULL){
            addResult->head = temp;
            addResult->tail = temp;
        }
        else{
            addResult->tail->next = temp;
            addResult->tail = temp;
        }
    }
    if(temp_a == NULL){
        while(temp_b){
            temp = (node *)malloc(sizeof(node));
            temp->coefficient = temp_b->coefficient;
            temp->exp_x = temp_b->exp_x;
            temp->exp_y = temp_b->exp_y;
            temp->exp_z = temp_b->exp_z;
            temp->next = NULL;
            temp_b = temp_b->next;
            if(addResult->head==NULL){
                addResult->head = temp;
                addResult->tail = temp;
            }
            else{
                addResult->tail->next = temp;
                addResult->tail = temp;
            }
        }
    }

    if(temp_b == NULL){
        while(temp_a){
            temp = (node *)malloc(sizeof(node));
            temp->coefficient = temp_a->coefficient;
            temp->exp_x = temp_a->exp_x;
            temp->exp_y = temp_a->exp_y;
            temp->exp_z = temp_a->exp_z;
            temp->next = NULL;
            temp_a = temp_a->next;
            if(addResult->head==NULL){
                addResult->head = temp;
                addResult->tail = temp;
            }
            else{
                addResult->tail->next = temp;
                addResult->tail = temp;
            }
        }
    }
    return addResult;
}

polynomial *subPolynomial(listnode *head, int a, int b){
    polynomial *subResult = (polynomial *)malloc(sizeof(polynomial));
    initPolynomial(subResult);
    //find a_th polynomial and b_th polynomial
    polynomial *poly_a = findPolynomial(head, a);
    polynomial *poly_b = findPolynomial(head, b);
    node *temp_a = poly_a->head;
    node *temp_b = poly_b->head;
    node *temp = NULL;
    while(temp_a && temp_b){
        if(temp_a->exp_x == temp_b->exp_x){
            if(temp_a->exp_y == temp_b->exp_y){
                if(temp_a->exp_z == temp_b->exp_z){
                    if(temp_a->coefficient - temp_b->coefficient!=0){
                        temp = (node *)malloc(sizeof(node));
                        temp->coefficient = temp_a->coefficient - temp_b->coefficient;
                        temp->exp_x = temp_a->exp_x;
                        temp->exp_y = temp_a->exp_y;
                        temp->exp_z = temp_a->exp_z;
                        temp->next = NULL;
                        temp_a = temp_a->next;
                        temp_b = temp_b->next;
                    }
                    else{
                        temp_a = temp_a->next;
                        temp_b = temp_b->next;
                    }
                }
                else if(temp_a->exp_z > temp_b->exp_z){
                    temp = (node *)malloc(sizeof(node));
                    temp->coefficient = temp_a->coefficient;
                    temp->exp_x = temp_a->exp_x;
                    temp->exp_y = temp_a->exp_y;
                    temp->exp_z = temp_a->exp_z;
                    temp->next = NULL;
                    temp_a = temp_a->next;
                }
                else if(temp_a->exp_z < temp_b->exp_z){
                    temp = (node *)malloc(sizeof(node));
                    temp->coefficient = (-1) * temp_b->coefficient;
                    temp->exp_x = temp_b->exp_x;
                    temp->exp_y = temp_b->exp_y;
                    temp->exp_z = temp_b->exp_z;
                    temp->next = NULL;
                    temp_b = temp_b->next;
                }
            }
            else if(temp_a->exp_y > temp_b->exp_y){
                temp = (node *)malloc(sizeof(node));
                temp->coefficient = temp_a->coefficient;
                temp->exp_x = temp_a->exp_x;
                temp->exp_y = temp_a->exp_y;
                temp->exp_z = temp_a->exp_z;
                temp->next = NULL;
                temp_a = temp_a->next;
            }
            else if(temp_a->exp_y < temp_b->exp_y){
                temp = (node *)malloc(sizeof(node));
                temp->coefficient = (-1) * temp_b->coefficient;
                temp->exp_x = temp_b->exp_x;
                temp->exp_y = temp_b->exp_y;
                temp->exp_z = temp_b->exp_z;
                temp->next = NULL;
                temp_b = temp_b->next;
            }
        }
        else if(temp_a->exp_x > temp_b->exp_x){
            temp = (node *)malloc(sizeof(node));
            temp->coefficient = temp_a->coefficient;
            temp->exp_x = temp_a->exp_x;
            temp->exp_y = temp_a->exp_y;
            temp->exp_z = temp_a->exp_z;
            temp->next = NULL;
            temp_a = temp_a->next;
        }
        else if(temp_a->exp_x < temp_b->exp_x){
            temp = (node *)malloc(sizeof(node));
            temp->coefficient = (-1) * temp_b->coefficient;
            temp->exp_x = temp_b->exp_x;
            temp->exp_y = temp_b->exp_y;
            temp->exp_z = temp_b->exp_z;
            temp->next = NULL;
            temp_b = temp_b->next;
        }

        if(subResult->head==NULL){
            subResult->head = temp;
            subResult->tail = temp;
        }
        else{
            subResult->tail->next = temp;
            subResult->tail = temp;
        }
    }
    if(temp_a == NULL){
        while(temp_b){
            temp = (node *)malloc(sizeof(node));
            temp->coefficient = (-1) * temp_b->coefficient;
            temp->exp_x = temp_b->exp_x;
            temp->exp_y = temp_b->exp_y;
            temp->exp_z = temp_b->exp_z;
            temp->next = NULL;
            temp_b = temp_b->next;
            if(subResult->head==NULL){
                subResult->head = temp;
                subResult->tail = temp;
            }
            else{
                subResult->tail->next = temp;
                subResult->tail = temp;
            }
        }
    }

    if(temp_b == NULL){
        while(temp_a){
            temp = (node *)malloc(sizeof(node));
            temp->coefficient = temp_a->coefficient;
            temp->exp_x = temp_a->exp_x;
            temp->exp_y = temp_a->exp_y;
            temp->exp_z = temp_a->exp_z;
            temp->next = NULL;
            temp_a = temp_a->next;
            if(subResult->head==NULL){
                subResult->head = temp;
                subResult->tail = temp;
            }
            else{
                subResult->tail->next = temp;
                subResult->tail = temp;
            }
        }
    }
    return subResult;
}

polynomial *mulPolynomial(listnode *head, int a, int b){
    polynomial *mulResult = (polynomial *)malloc(sizeof(polynomial));
    initPolynomial(mulResult);
    //find a_th polynomial and b_th polynomial
    polynomial *poly_a = findPolynomial(head, a);
    polynomial *poly_b = findPolynomial(head, b);
    node *temp_a = poly_a->head;
    node *temp_b = poly_b->head;
    node *temp = NULL;

    //do the multiplication term by term
    while(temp_a){
        while(temp_b){
            temp = (node *)malloc(sizeof(node));
            temp->coefficient = temp_a->coefficient * temp_b->coefficient;
            temp->exp_x = temp_a->exp_x + temp_b->exp_x;
            temp->exp_y = temp_a->exp_y + temp_b->exp_y;
            temp->exp_z = temp_a->exp_z + temp_b->exp_z;
            temp->next = NULL;

            //linked up the linkedlist with the pattern:

            //first element entry the linkedlist
            if(mulResult->head==NULL){
                mulResult->head = temp;
                mulResult->tail = temp;
            }
            //compare with head pointer to determine whether changing head
            else{
                node *current = mulResult->head;
                // compare with head;
                if (temp->exp_x == mulResult->head->exp_x){
                    if(temp->exp_y == mulResult->head->exp_y){
                        if(temp->exp_z == mulResult->head->exp_z){
                            //term coefficient is all the same
                            mulResult->head->coefficient += temp->coefficient;
                            free(mulResult);
                            temp_b = temp_b->next;
                            continue;
                        }
                        else if(temp->exp_z > mulResult->head->exp_z){
                            //coefficient is bigger than head, insert before head
                            temp->next = mulResult->head;
                            mulResult->head = temp;
                            temp_b = temp_b->next;
                            continue;
                        }
                    }
                    else if(temp->exp_y > mulResult->head->exp_y){
                        //coefficient is bigger than head, insert before head
                        temp->next = mulResult->head;
                        mulResult->head = temp;
                        temp_b = temp_b->next;
                        continue;
                    }
                }
                else if(temp->exp_x > mulResult->head->exp_x){
                    //coefficient is bigger than head, insert before head
                    temp->next = mulResult->head;
                    mulResult->head = temp;
                    temp_b = temp_b->next;
                    continue;
                }

                //check where to insert the node in the linkedlist
                node *prev = current;
                current = current->next;

                while (current != NULL){
                    if(temp->exp_x==current->exp_x){
                        if(temp->exp_y==current->exp_y){
                            if(temp->exp_z==current->exp_z){
                                //same term
                                current->coefficient += temp->coefficient;
                                free(temp);
                                break;

                            }
                            else if(temp->exp_z > current->exp_z){
                                temp->next = current;
                                prev->next = temp;
                                break;
                            }
                        }
                        else if(temp->exp_y > current->exp_y){
                            temp->next = current;
                            prev->next = temp;
                            break;
                        }
                    }
                    else if(temp->exp_x > current->exp_x){
                        temp->next = current;
                        prev->next = temp;
                        break;
                    }
                    current = current->next;
                    prev = prev->next;
                }
                //if traverse through the tail of the linkedlist, link on the tail
                if(current==NULL){
                    prev->next = temp;
                    mulResult->tail = temp;
                }
            }
            temp_b = temp_b->next;
        }
        temp_a = temp_a->next;
    }
    return mulResult;
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

    //if delete node is the last node in the linkedlist
    if(temp->next==NULL){
        (*tailptr) = prev;
    }
    else{
        (*tailptr) = prev->next;
    }
    delete_all_node(temp->p);
    free(temp);
}

void deleteList(polylist *list){
    while(list->listhead!=NULL){
        deletePolynomial(&list->listhead, &list->listtail, 0);
    }
    free(list);
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
            printf("\nAfter adding:\n");
            printPolyList(list);
        }
        else if(OP_ID==2){
            //subtract polynomial here
            int a, b;
            fscanf(input, "%d", &a);
            fscanf(input, "%d", &b);
            polynomial *subResult = subPolynomial(list->listhead, a, b);
            listnode *temp = createListNode(subResult);
            if(list->listhead==NULL){
                list->listhead = temp;
                list->listtail = temp;
            }
            else{
                list->listtail->next = temp;
                list->listtail = temp;
            }
            printf("\nAfter substracting:\n");
            printPolyList(list);
        }
        else if(OP_ID==3){
            //multiply polynomial here
            int a, b;
            fscanf(input, "%d", &a);
            fscanf(input, "%d", &b);
            polynomial *mulResult = mulPolynomial(list->listhead, a, b);
            listnode *temp = createListNode(mulResult);
            if(list->listhead==NULL){
                list->listhead = temp;
                list->listtail = temp;
            }
            else{
                list->listtail->next = temp;
                list->listtail = temp;
            }
            printf("\nAfter multipling:\n");
            printPolyList(list);
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
    deleteList(list);
    fclose(input);
    return 0;
}