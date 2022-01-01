#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_SIZE 2000000
#define MAX_LENGTH 20
#define DEBUG_MODE false

typedef struct node{
    char string[MAX_LENGTH];
    struct node *next;
} node;

node *hashTable[TABLE_SIZE];

unsigned int hash(char *string){
    unsigned int hash_value = 0;
    for (int i = 0; i < strlen(string);i++){
        hash_value += 43 * string[i] * string[i] * string[i] + 13 * string[i] * string[i] + 17 * string[i] + string[i] * strlen(string) * strlen(string);
    }
    return hash_value%TABLE_SIZE;
}

void initHashTable(){
    for (int i = 0; i < TABLE_SIZE;i++){
        hashTable[i] = NULL;
    }
}

void printHashTable(){
    printf("------Start------\n");
    for (int i = 0; i < TABLE_SIZE;i++){
        //if there is nothing in the hash table, do nothing
        if(hashTable[i]!=NULL){
            printf("%8d: ", i);
            node *temp = hashTable[i];
            while(temp!=NULL){
                printf("%s - ", temp->string);
                temp = temp->next;
            }
            printf("\n");
        }
    }
    printf("-------End-------\n");
}

void hashTableInsert(char *string){
    //calculate the index by hash function:
    int index = hash(string);

    node *newNode = malloc(sizeof(node));
    strcpy(newNode->string, string);

    //if the hashtable is empty at that index
    if(hashTable[index]==NULL){
        hashTable[index] = newNode;
        newNode->next = NULL;
    }

    else{
        //insert the data in the tail of the linkedlist
        node *temp = hashTable[index];
        while(temp!=NULL){
            // find the tail of the linkedlist
            if(temp->next==NULL){
                break;
            }
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = NULL;
    }
}

bool arrayCompare(int *a, int *b){
    for (int i = 0; i < 26;i++){
        if(a[i]!=b[i]){
            return false;
        }
    }
    return true;
}

bool stringCompare(char *s1, char *s2){
    if(strlen(s1)!=strlen(s2)){
        return false;
    }
    else{
        int s1_char[26] = {0};
        int s2_char[26] = {0};
        for (int i = 0; i < strlen(s1);i++){
            s1_char[s1[i] - 97]++;
            s2_char[s2[i] - 97]++;
        }
        if(arrayCompare(s1_char,s2_char)){
            return true;
        }
        else{
            return false;
        }
    }
}

void hashTableLookup(char *string, FILE *output){
    //calculate the index by hash function:
    int index = hash(string);
    if(hashTable[index]==NULL){
        fprintf(output, "0");
        return;
    }
    else{
        node *temp = hashTable[index];
        while(temp!=NULL){
            if(stringCompare(string,temp->string)){
                fprintf(output, "%s ", temp->string);
            }
            temp = temp->next;
        }
    }
}

int main(int argc, char *argv[]){

    //input  and output filename:
    char *input_filename = *(argv + 1);
    char *target_filename = *(argv + 2);
    char *output_filename = *(argv + 3);

    FILE *input = fopen(input_filename, "r");
    FILE *target = fopen(target_filename,"r");
    FILE *output = fopen(output_filename, "w");

    initHashTable();
    char buffer[20];

    //build the hash table
    while(fscanf(input,"%s", buffer)!=EOF){
        hashTableInsert(buffer);
    }
    fclose(input);

    if(DEBUG_MODE==true){
        printHashTable();
    }

    //search in the hashtable
    while(fscanf(target, "%s", buffer)!=EOF){
        hashTableLookup(buffer, output);
        fprintf(output, "\n");
    }
    fclose(target);
    fclose(output);
    return 0;
}