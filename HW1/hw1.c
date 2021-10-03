#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 10000

typedef struct{
    int column_index;
    int row_index;
    int value;
} matrixNode;

typedef struct{
    int count;
    matrixNode term[MAX_SIZE];
    int column;
    int row;
} matrix;

void initMatrix(matrix **A){
    (*A)->count = 0;
    (*A)->column = 0;
    (*A)->row = 1;
}

void printMatrix(matrix *A){
    matrixNode *term = A->term;
    int k = 0;
    for (int i = 1; i <= A->row;i++){
        for (int j = 1; j <= A->column;j++){
            if(term[k].column_index==j && term[k].row_index==i){
                printf("%-5d ", term[k].value);
                k++;
            }
            else{
                printf("%-5d ", 0);
            }
        }
        printf("\n");
    }
    printf("\n");
}

void printMatrixInfo(matrix *A){
    printf("Column of Matrix: %d\n", A->column);
    printf("Row of Matrix: %d\n", A->row);
    printf("Non Zero Term of Matrix: %d\n", A->count);
    printf("The content of the matrix:\n");
    printMatrix(A);
}

void matrixTranspose(matrix *A){
    for (int i = 0; i < A->count;i++){
        int temp = A->term[i].column_index;
        A->term[i].column_index = A->term[i].row_index;
        A->term[i].row_index = temp;
    }
    int temp = A->column;
    A->column = A->row;
    A->row = temp;
}

int main(){
    matrix *A = malloc(sizeof(matrix));
    matrix *B = malloc(sizeof(matrix));
    matrix **matrixptr = &A;

    //initialize matrix A and B
    initMatrix(&A);
    initMatrix(&B);

    //temp array to store the last value of the column and row value
    //store[0] = column, store[1] = row
    int *store = malloc(sizeof(int) * 2);

    //read all line into buffer
    char buffer[MAX_SIZE];
    const char *filename = "sample.in";
    FILE *input = fopen(filename, "r");
    while(fscanf(input, "%s", buffer)!=EOF){
        //printf("%s: ", buffer);
        //meet "A"
        if(strcmp(buffer, "A")==0){
            fscanf(input, "%s", buffer); //read " ;"
        }

        //meet "B"
        else if(strcmp(buffer, "B")==0){
            //correct the true column and row for A
            A->column = store[0];
            A->row = store[1];

            fscanf(input, "%s", buffer); //read " ;"
            matrixptr = &B;
        }

        //meet ; and the end of the row
        else if (strcmp(buffer, ";") == 0){
            store[0] = (*matrixptr)->column;
            store[1] = (*matrixptr)->row;
            (*matrixptr)->row+= 1;
            (*matrixptr)->column = 0;
        }

        //construct matrix
        else if(strcmp(buffer,"0")==0){
            (*matrixptr)->column+= 1;
            //(*matrixptr)->count++;
        }
        else{
            (*matrixptr)->column+= 1;
            (*matrixptr)->term[(*matrixptr)->count].value = atoi(buffer);
            (*matrixptr)->term[(*matrixptr)->count].column_index = (*matrixptr)->column;
            (*matrixptr)->term[(*matrixptr)->count].row_index = (*matrixptr)->row;
            (*matrixptr)->count++;
        }
        //printf("%d %d %d\n", (*matrixptr)->column, (*matrixptr)->row, (*matrixptr)->count);
    }
    B->column = store[0];
    B->row = store[1];
    printMatrixInfo(A);
    printMatrixInfo(B);
    matrixTranspose(A);
    printMatrixInfo(A);
    return 0;
}