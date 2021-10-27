#include <stdio.h>
#include <stdlib.h>

// the term node of the polynomial
typedef struct node{
    int coefficient;
    int exp_x;
    int exp_y;
    int exp_z;
    struct node *next;
} node;

// store the head and tail pointer for all polynomials
typedef struct polynomial{
    node *head;
    node *tail;
    int count;
} polynomial;

// store the head and tail pointer for each polynomials
typedef struct listnode{
    polynomial *polynomial;
    struct listnode *next;
} listnode;

//to store the head and tail pointer of the listnode
typedef struct polylist{
    listnode *head;
    listnode *tail;
} polylist;

void initPolynomial(polynomial *p){
    p->head = NULL;
    p->tail = NULL;
    p->count = 0;
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

void printPolyList(listnode *head){
    int count = 0;
    listnode *temp = head;
    if(temp == NULL){
        printf("There is no polynomial in the list\n");
        return;
    }
    while(temp!=NULL){
        printf("Number %d polynomial, there are %d nodes in the polynomial\n", count++, temp->polynomial->count);
        printPolynomial(temp->polynomial);
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
    newListNode->polynomial = p;
    newListNode->next = NULL;
    return newListNode;
}

polynomial *appendPolynomial(FILE *input){
    polynomial *p = (polynomial *)malloc(sizeof(polynomial));
    initPolynomial(p);

    int term_count;
    int coefficient;
    int exp_x;
    int exp_y;
    int exp_z;

    //scanf how many term to create
    fscanf(input, "%d", &term_count);
    p->count = term_count;
    for (int i = 0; i < term_count;i++){
        fscanf(input, "%d", &coefficient);
        fscanf(input, "%d", &exp_x);
        fscanf(input, "%d", &exp_y);
        fscanf(input, "%d", &exp_z);
        node *temp = createNode(coefficient, exp_x, exp_y, exp_z);

        //link node up:
        //<case 1>: the first node entry the loop
        if(p->head == NULL){
            p->head = temp;
            p->tail = temp;
        }

        //<case 2>: head node exist -> insert at the tail, and update tail
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
    return temp->polynomial;
}

/*
polynomial *insertNode(polynomial *p, node *node_to_insert){
    node **head = &(p->head);
    node **tail = &(p->tail);
    //add the first element into the linkedlist
    if(*head == NULL){
        *head = node_to_insert;
        *tail = node_to_insert;
        return p;
    }

    //find the location to insert the node
    node *temp = *head;
    while(temp != NULL){
        if(temp->exp_x == node_to_insert->exp_x){
            if(temp->exp_y == node_to_insert->exp_y){
                if(temp->exp_z == node_to_insert->exp_z){
                    temp->coefficient += node_to_insert->coefficient;
                    free(node_to_insert);
                    break;
                }
                else if(temp->exp_z > node_to_insert->exp_z){
                    temp = temp->next;
                }
                else if(temp->exp_z < node_to_insert->exp_z){

                }
            }
            else if(temp->exp_y > node_to_insert->exp_y){

            }
            else if(temp->exp_y < node_to_insert->exp_y){

            }
        }
        else if(temp->exp_x > node_to_insert->exp_x){

        }
        else if(temp->exp_x < node_to_insert->exp_x){

        }
    }
    return p;
}
*/

polynomial *addPolynomial(listnode *head, int a, int b){
    polynomial *result = (polynomial *)malloc(sizeof(polynomial));
    initPolynomial(result);
    //find a_th polynomial and b_th polynomial
    polynomial *poly_a = findPolynomial(head, a);
    polynomial *poly_b = findPolynomial(head, b);
    node *temp_a = poly_a->head;
    node *temp_b = poly_b->head;
    node *newnode = NULL;

    while(temp_a != NULL && temp_b != NULL){
        if(temp_a->exp_x == temp_b->exp_x){
            if(temp_a->exp_y == temp_b->exp_y){
                if(temp_a->exp_z == temp_b->exp_z){
                    if((temp_a->coefficient + temp_b->coefficient)!=0){
                        newnode = createNode(temp_a->coefficient + temp_b->coefficient, temp_a->exp_x, temp_a->exp_y, temp_a->exp_z);
                        temp_a = temp_a->next;
                        temp_b = temp_b->next;
                    }
                    else{
                        temp_a = temp_a->next;
                        temp_b = temp_b->next;
                        continue;
                    }
                }
                else if(temp_a->exp_z > temp_b->exp_z){
                    newnode = createNode(temp_a->coefficient, temp_a->exp_x, temp_a->exp_y, temp_a->exp_z);
                    temp_a = temp_a->next;
                }
                else if(temp_a->exp_z < temp_b->exp_z){
                    newnode = createNode(temp_b->coefficient, temp_b->exp_x, temp_b->exp_y, temp_b->exp_z);
                    temp_b = temp_b->next;
                }
            }
            else if(temp_a->exp_y > temp_b->exp_y){
                newnode = createNode(temp_a->coefficient, temp_a->exp_x, temp_a->exp_y, temp_a->exp_z);
                temp_a = temp_a->next;
            }
            else if(temp_a->exp_y < temp_b->exp_y){
                newnode = createNode(temp_b->coefficient, temp_b->exp_x, temp_b->exp_y, temp_b->exp_z);
                temp_b = temp_b->next;
            }
        }
        else if(temp_a->exp_x > temp_b->exp_x){
            newnode = createNode(temp_a->coefficient, temp_a->exp_x, temp_a->exp_y, temp_a->exp_z);
            temp_a = temp_a->next;
        }
        else if(temp_a->exp_x < temp_b->exp_x){
            newnode = createNode(temp_b->coefficient, temp_b->exp_x, temp_b->exp_y, temp_b->exp_z);
            temp_b = temp_b->next;
        }
        //insert the node into the list through the rule
        if(result->head == NULL){
            result->count += 1;
            result->head = newnode;
            result->tail = newnode;
        }
        else{
            result->count += 1;
            result->tail->next = newnode;
            result->tail = newnode;
        }
    }

    //if traverse all of the node in linkedlist a, insert remaining b node
    if(temp_a == NULL){
        while(temp_b){
            newnode = createNode(temp_b->coefficient, temp_b->exp_x, temp_b->exp_y, temp_b->exp_z);
            temp_b = temp_b->next;

            //insert the node into the list through the rule
            if(result->head == NULL){
                result->count += 1;
                result->head = newnode;
                result->tail = newnode;
            }
            else{
                result->count += 1;
                result->tail->next = newnode;
                result->tail = newnode;
            }
        }
    }

    //if traverse all of the node in linkedlist b, insert remaining a node
    if(temp_b == NULL){
        while(temp_a){
            newnode = createNode(temp_a->coefficient, temp_a->exp_x, temp_a->exp_y, temp_a->exp_z);
            temp_a = temp_a->next;

            //insert the node into the list through the rule
            if(result->head == NULL){
                result->count += 1;
                result->head = newnode;
                result->tail = newnode;
            }
            else{
                result->count += 1;
                result->tail->next = newnode;
                result->tail = newnode;
            }
        }
    }
    //if the result is the zero polynomial, add a zero term:
    if(result->head == NULL){
        result->count += 1;
        newnode = createNode(0, 0, 0, 0);
        result->head = newnode;
        result->tail = newnode;
    }
    //remove the duplicate zero term:
    else if(result->head != NULL && result->tail->coefficient == 0){
        result->count--;
        node *temp = result->head;
        while(temp->next!=result->tail){
            temp = temp->next;
        }
        free(temp->next);
        result->tail = temp;
        result->tail->next = NULL;
    }
    return result;
}

polynomial *subPolynomial(listnode *head, int a, int b){
    polynomial *result = (polynomial *)malloc(sizeof(polynomial));
    initPolynomial(result);
    //find a_th polynomial and b_th polynomial
    polynomial *poly_a = findPolynomial(head, a);
    polynomial *poly_b = findPolynomial(head, b);
    node *temp_a = poly_a->head;
    node *temp_b = poly_b->head;
    node *newnode = NULL;

    while(temp_a != NULL && temp_b != NULL){
        if(temp_a->exp_x == temp_b->exp_x){
            if(temp_a->exp_y == temp_b->exp_y){
                if(temp_a->exp_z == temp_b->exp_z){
                    if((temp_a->coefficient - temp_b->coefficient)!=0){
                        newnode = createNode(temp_a->coefficient - temp_b->coefficient, temp_a->exp_x, temp_a->exp_y, temp_a->exp_z);
                        temp_a = temp_a->next;
                        temp_b = temp_b->next;
                    }
                    else{
                        temp_a = temp_a->next;
                        temp_b = temp_b->next;
                        continue;
                    }
                }
                else if(temp_a->exp_z > temp_b->exp_z){
                    newnode = createNode(temp_a->coefficient, temp_a->exp_x, temp_a->exp_y, temp_a->exp_z);
                    temp_a = temp_a->next;
                }
                else if(temp_a->exp_z < temp_b->exp_z){
                    newnode = createNode((-1) *temp_b->coefficient, temp_b->exp_x, temp_b->exp_y, temp_b->exp_z);
                    temp_b = temp_b->next;
                }
            }
            else if(temp_a->exp_y > temp_b->exp_y){
                newnode = createNode(temp_a->coefficient, temp_a->exp_x, temp_a->exp_y, temp_a->exp_z);
                temp_a = temp_a->next;
            }
            else if(temp_a->exp_y < temp_b->exp_y){
                newnode = createNode((-1) *temp_b->coefficient, temp_b->exp_x, temp_b->exp_y, temp_b->exp_z);
                temp_b = temp_b->next;
            }
        }
        else if(temp_a->exp_x > temp_b->exp_x){
            newnode = createNode(temp_a->coefficient, temp_a->exp_x, temp_a->exp_y, temp_a->exp_z);
            temp_a = temp_a->next;
        }
        else if(temp_a->exp_x < temp_b->exp_x){
            newnode = createNode((-1) * temp_b->coefficient, temp_b->exp_x, temp_b->exp_y, temp_b->exp_z);
            temp_b = temp_b->next;
        }
        //insert the node into the list through the rule
        if(result->head == NULL){
            result->count += 1;
            result->head = newnode;
            result->tail = newnode;
        }
        else{
            result->count += 1;
            result->tail->next = newnode;
            result->tail = newnode;
        }
    }

    //if traverse all of the node in linkedlist a, insert remaining b node
    if(temp_a == NULL){
        while(temp_b){
            newnode = createNode((-1) * temp_b->coefficient, temp_b->exp_x, temp_b->exp_y, temp_b->exp_z);
            temp_b = temp_b->next;

            //insert the node into the list through the rule
            if(result->head == NULL){
                result->count += 1;
                result->head = newnode;
                result->tail = newnode;
            }
            else{
                result->count += 1;
                result->tail->next = newnode;
                result->tail = newnode;
            }
        }
    }

    //if traverse all of the node in linkedlist b, insert remaining a node
    if(temp_b == NULL){
        while(temp_a){
            newnode = createNode(temp_a->coefficient, temp_a->exp_x, temp_a->exp_y, temp_a->exp_z);
            temp_a = temp_a->next;

            //insert the node into the list through the rule
            if(result->head == NULL){
                result->count += 1;
                result->head = newnode;
                result->tail = newnode;
            }
            else{
                result->count += 1;
                result->tail->next = newnode;
                result->tail = newnode;
            }
        }
    }
    //if the result is the zero polynomial, add a zero term:
    if(result->head == NULL){
        result->count += 1;
        newnode = createNode(0, 0, 0, 0);
        result->head = newnode;
        result->tail = newnode;
    }
    //remove the duplicate zero term:
    else if(result->head != NULL && result->tail->coefficient == 0){
        result->count--;
        node *temp = result->head;
        while(temp->next!=result->tail){
            temp = temp->next;
        }
        free(temp->next);
        result->tail = temp;
        result->tail->next = NULL;
    }
    return result;
}

polynomial *mulPolynomial(listnode *head, int a, int b){
    polynomial *result = (polynomial *)malloc(sizeof(polynomial));
    initPolynomial(result);
    //find a_th polynomial and b_th polynomial
    polynomial *poly_a = findPolynomial(head, a);
    polynomial *poly_b = findPolynomial(head, b);
    node *temp_a = poly_a->head;
    node *temp_b = poly_b->head;

    //check whether a or b is the zero polynomial:
    if(temp_a->coefficient == 0 || temp_b->coefficient ==0){
        result->count += 1;
        node *newnode = createNode(0, 0, 0, 0);
        result->head = newnode;
        result->tail = newnode;
        return result;
    }



    //do the multiplication term by term
    while(temp_a){
        temp_b = poly_b->head;
        while(temp_b){
            node *newnode = createNode(temp_a->coefficient * temp_b->coefficient, temp_a->exp_x + temp_b->exp_x, temp_a->exp_y + temp_b->exp_y, temp_a->exp_z + temp_b->exp_z);

            //linked up the linkedlist with the pattern:

            //first element entry the linkedlist
            if(result->head == NULL){
                result->count += 1;
                result->head = newnode;
                result->tail = newnode;
            }

            //compare with head pointer to determine whether changing head
            else{
                //compare with head
                if(newnode->exp_x == result->head->exp_x){
                    if(newnode->exp_y == result->head->exp_y){
                        if(newnode->exp_z == result->head->exp_z){
                            //term coeffieicnt is all the same
                            result->head->coefficient += newnode->coefficient;
                            free(newnode);
                            temp_b = temp_b->next;
                            continue;
                        }
                        else if(newnode->exp_z > result->head->exp_z){
                            //coeffieint is bigger than head, insert before head
                            newnode->next = result->head;
                            result->head = newnode;
                            temp_b = temp_b->next;
                            result->count += 1;
                            continue;
                        }
                        else if(newnode->exp_z < result->head->exp_z){
                            //insert after head somewhere
                        }
                    }
                    else if(newnode->exp_y > result->head->exp_y){
                        newnode->next = result->head;
                        result->head = newnode;
                        temp_b = temp_b->next;
                        result->count += 1;
                        continue;
                    }
                    else if(newnode->exp_y < result->head->exp_y){
                        //insert after head somewhere
                    }
                }
                else if(newnode->exp_x > result->head->exp_x){
                    newnode->next = result->head;
                    result->head = newnode;
                    temp_b = temp_b->next;
                    result->count += 1;
                    continue;
                }
                else if(newnode->exp_x < result->head->exp_x){
                    //insert after head somewhere
                }
                //check where to insert the node in the linkedlist
                node *current = result->head->next;
                node *prev = result->head;

                while(current != NULL){
                    if(newnode->exp_x == current->exp_x){
                        if(newnode->exp_y == current->exp_y){
                            if(newnode->exp_z == current->exp_z){
                                //same term:
                                current->coefficient += newnode->coefficient;
                                free(newnode);
                                break;
                            }
                            else if(newnode->exp_z > current->exp_z){
                                newnode->next = current;
                                prev->next = newnode;
                                result->count += 1;
                                break;
                            }
                            else if(newnode->exp_z < current->exp_z){
                                //keep finding where to insert
                            }
                        }
                        else if(newnode->exp_y > current->exp_y){
                            newnode->next = current;
                            prev->next = newnode;
                            result->count += 1;
                            break;
                        }
                        else if(newnode->exp_y < current->exp_y){
                            //keep finding where to insert
                        }
                    }
                    else if(newnode->exp_x > current->exp_x){
                        newnode->next = current;
                        prev->next = newnode;
                        result->count += 1;
                        break;
                    }
                    else if(newnode->exp_x < current->exp_x){
                        //keep finding where to insert
                    }
                    current = current->next;
                    prev = prev->next;
                }
                // if traverse the all linkedlist, link on the tail
                if(current == NULL){
                    prev->next = newnode;
                    result->tail = newnode;
                    result->count += 1;
                }
            }
            temp_b = temp_b->next;
        }
        temp_a = temp_a->next;
    }
    return result;
}

//go throught all terms of the polynomial to free the allocate memory
void delete_all_node(polynomial *p){
    node **head = &(p->head);
    node *current_node = *head;
    node *next_node;
    while(current_node != NULL){
        next_node = current_node->next;
        free(current_node);
        current_node = next_node;
    }
    free(p);
}

//delete polynomial from the list
void deletePolynomial(listnode **head, listnode **tail, int delete_index){
    listnode *temp = *head;

    //if index = 0, delete the head node
    if(delete_index == 0 && *head != NULL){
        //there still some polynomial in the list
        if((*head)->next != NULL){
            *head = temp->next;
        }
        //no more polynomial in the list
        else{
            *head = NULL;
            *tail = NULL;
        }
        delete_all_node(temp->polynomial);
        free(temp);
        return;
    }

    //if not delete the head node
    //traverse to find which node to delete:
    //make sure to find the previous pointer to connect the linkedlist
    for (int i = 0; i < delete_index - 1;i++){
        temp = temp->next;
    }
    listnode *prev = temp;
    temp = temp->next;
    prev->next = temp->next;
    //if delete node is the last node in the linkedlist
    if(temp->next == NULL){
        *tail = prev;
    }
    else{
        *tail = prev->next;
    }
    delete_all_node(temp->polynomial);
    free(temp);
}

void deleteList(listnode **head, listnode **tail){
    while(*head != NULL){
        deletePolynomial(head, tail, 0);
    }
}

void appendList(listnode **head, listnode **tail, polynomial *p){
    listnode *newListNode = createListNode(p);
    //first time to append the polynomial to the list
    if(*head == NULL){
        *head = newListNode;
        *tail = newListNode;
    }
    //add the node to the last, and update tail
    else{
        (*tail)->next = newListNode;
        *tail = newListNode;
    }
}

int main(int argc, char *argv[]){

    //input  and output filename:
    char *input_filename = *(argv + 1);
    //char *output_filename = *(argv + 2);

    //the register to store what to do to the polynomial
    int OP_ID;

    polylist list;
    //initialize the list
    list.head = NULL;
    list.tail = NULL;

    FILE *input = fopen(input_filename, "r");
    while(fscanf(input, "%d", &OP_ID)!=EOF){
        //append polynomial in to the list
        if(OP_ID == 0){
            polynomial *p = appendPolynomial(input);
            appendList(&list.head, &list.tail, p);
            printf("\nAfter appending:\n");
            printPolyList(list.head);
        }
        //add polynomial
        else if(OP_ID == 1){
            int a, b;
            fscanf(input, "%d", &a);
            fscanf(input, "%d", &b);
            polynomial *p = addPolynomial(list.head, a, b);
            appendList(&list.head, &list.tail, p);
            printf("\nAfter adding:\n");
            printPolyList(list.head);
        }
        //substract polynomial
        else if(OP_ID == 2){
            int a, b;
            fscanf(input, "%d", &a);
            fscanf(input, "%d", &b);
            polynomial *p = subPolynomial(list.head, a, b);
            appendList(&list.head, &list.tail, p);
            printf("\nAfter substracting:\n");
            printPolyList(list.head);
        }
        //multiply polynomial
        else if(OP_ID == 3){
            int a, b;
            fscanf(input, "%d", &a);
            fscanf(input, "%d", &b);
            polynomial *p = mulPolynomial(list.head, a, b);
            appendList(&list.head, &list.tail, p);
            printf("\nAfter multipling:\n");
            printPolyList(list.head);
        }
        //delete polynomial
        else if(OP_ID == 4){
            int delete_index;
            fscanf(input, "%d", &delete_index);
            deletePolynomial(&list.head, &list.tail, delete_index);
            printf("\nAfter deleting:\n");
            printPolyList(list.head);
        }
    }
    //free all allocate memory
    deleteList(&list.head, &list.tail);
    fclose(input);
    return 0;
}