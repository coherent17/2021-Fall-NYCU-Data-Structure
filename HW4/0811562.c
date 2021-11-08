#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 10005

int size = 0;
int MaxHeap[SIZE];

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int *MaxHeap, int size, int i){
    int largest = i;
    int left_children = 2 * i + 1;
    int right_children = 2 * i + 2;

    if(left_children<size && MaxHeap[left_children]>MaxHeap[largest]) largest = left_children;
    if(right_children<size && MaxHeap[right_children]>MaxHeap[largest]) largest = right_children;

    //check need to swap or not?
    if(largest!=i){
        swap(&MaxHeap[i], &MaxHeap[largest]);
    }
}

void insert(int *MaxHeap, int element_to_insert){
    MaxHeap[size] = element_to_insert;
    size += 1;
    //loop to heapify
    int i;
    for (i = size / 2 - 1; i >= 0;i--){
        heapify(MaxHeap, size, i);
    }
}

void delete(int *MaxHeap){
    swap(&MaxHeap[0], &MaxHeap[size - 1]);
    size -= 1;
    for (int i = size / 2 - 1; i >= 0;i--){
        heapify(MaxHeap, size, i);
    }
}

void inorderTraversal(FILE *output, int *MaxHeap, int i){
    int left_children = 2 * i + 1;
    int right_children = 2 * i + 2;
    if(left_children < size){
        inorderTraversal(output, MaxHeap, left_children);
    }
    fprintf(output, "%d ", MaxHeap[i]);
    if(right_children < size){
        inorderTraversal(output, MaxHeap, right_children);
    }
}

void preorderTraversal(FILE *output, int *MaxHeap, int i){
    int left_children = 2 * i + 1;
    int right_children = 2 * i + 2;
    fprintf(output, "%d ", MaxHeap[i]);
    if(left_children < size){
        preorderTraversal(output, MaxHeap, left_children);
    }
    if(right_children < size){
        preorderTraversal(output, MaxHeap, right_children);
    }
}

void postorderTraversal(FILE *output, int *MaxHeap, int i){
    int left_children = 2 * i + 1;
    int right_children = 2 * i + 2;
    if(left_children < size){
        postorderTraversal(output, MaxHeap, left_children);
    }
    if(right_children < size){
        postorderTraversal(output, MaxHeap, right_children);
    }
    fprintf(output, "%d ", MaxHeap[i]);
}

void levelorderTraversal(FILE *output, int *MaxHeap){
    for (int i = 0; i < size;i++){
        fprintf(output, "%d ", MaxHeap[i]);
    }
}

int main(int argc, char *argv[]){

    //input  and output filename:
    char *input_filename = *(argv + 1);
    char *output_filename = *(argv + 2);

    int OP_ID;

    FILE *input = fopen(input_filename, "r");
    FILE *output = fopen(output_filename, "w");
    while(fscanf(input, "%d", &OP_ID)!=EOF){
        if(OP_ID==0){
            int element_to_insert;
            fscanf(input, "%d", &element_to_insert);
            insert(MaxHeap, element_to_insert);
        }
        else if(OP_ID==1){
            delete (MaxHeap);
        }
        else if(OP_ID==2){
            //levelorderTraversal
            levelorderTraversal(output, MaxHeap);
            fprintf(output, "\n");
        }
        else if(OP_ID==3){
            //preorderTraversal
            preorderTraversal(output, MaxHeap, 0);
            fprintf(output, "\n");
        }
        else if(OP_ID==4){
            //inorderTraversal
            inorderTraversal(output, MaxHeap, 0);
            fprintf(output, "\n");
        }
        else if(OP_ID==5){
            //postorderTraversal
            postorderTraversal(output, MaxHeap, 0);
            fprintf(output, "\n");
        }
    }
    fclose(input);
    fclose(output);
    return 0;
}