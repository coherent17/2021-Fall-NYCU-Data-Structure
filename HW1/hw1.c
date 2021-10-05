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

void printNonZeroTerm(matrix *A){
    for (int i = 0; i < A->count;i++){
        printf("value = %d, at row = %d, column = %d\n", A->term[i].value, A->term[i].row_index, A->term[i].column_index);
    }
}

void printMatrixInfo(matrix *A){
    printf("Column of Matrix: %d\n", A->column);
    printf("Row of Matrix: %d\n", A->row);
    printf("Non Zero Term of Matrix: %d\n", A->count);
    printf("The non-zero term of the matrix:\n");
    printNonZeroTerm(A);
    printf("The content of the matrix:\n");
    printMatrix(A);
}

matrix *matrixTranspose(matrix *A){
    //allocate the mamory size to store the transpose matrix;
    matrix *newMatrix = (matrix *)malloc(sizeof(matrix));
    newMatrix->column = A->row;
    newMatrix->row = A->column;
    newMatrix->count = A->count;

    //if A is nonzero matrix
    if(A->count>0){
        int newCount = 0;
        for (int i = 1; i <= A->column;i++){
            for (int j = 0; j < A->count;j++){
                if(A->term[j].column_index==i){
                    newMatrix->term[newCount].row_index = i;
                    newMatrix->term[newCount].column_index = A->term[j].row_index;
                    newMatrix->term[newCount].value = A->term[j].value;
                    newCount++;
                }
            }
        }
    }
    return newMatrix;
}

//read the input file as two matrix
void readfile(matrix *A, matrix *B, matrix **matrixptr, char *filename){
    //temp array to store the last value of the column and row value
    //store[0] = column, store[1] = row
    int *store = (int *)malloc(sizeof(int) * 2);

    //read string into buffer
    char buffer[MAX_SIZE];

    FILE *input = fopen(filename, "r");

    while(fscanf(input, "%s", buffer)!=EOF){
        printf("%s: ", buffer);
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
        printf("%d %d %d\n", (*matrixptr)->column, (*matrixptr)->row, (*matrixptr)->count);
    }
    B->column = store[0];
    B->row = store[1];
}

void PutSum(matrix *result, int *totalcount, int row, int column, int *sum){
    //make sure that the sum isn't zero
    if((*sum)!=0){
        result->term[++(*totalcount)].row_index = row;
        result->term[*totalcount].column_index = column;
        result->term[*totalcount].value = *sum;
        
        //init sum to zero
        *sum = 0;
    }
}

matrix *matrixMultiplication(matrix *A, matrix *B){
    matrix *Btranspose = matrixTranspose(B);

    //matrix to return matrix A * matrix B
    matrix *result = (matrix *)malloc(sizeof(matrix));

    int i, j, totalcount, column;
    int row_begin = 1;
    int row = A->term[0].row_index;
    int sum = 0;

    A->term[A->count + 1].row_index = A->row;
    Btranspose->term[B->count+1].row_index = B->column;
    Btranspose->term[B->count + 1].column_index = 0;

    for (i = 0; i < A->count;){
        sum = 0;
        column = Btranspose->term[0].row_index;
        for (j = 0; j < Btranspose->count+1;){
            if(A->term[i].row_index!=row){
                PutSum(result, &totalcount, row, column, &sum);
                
                //since per row of A need to dot row B, so go back to the start of the row
                i = row_begin;

                //since the corresponeing row element for A matrix become all zero
                //let B^T go to the next row
                for (; Btranspose->term[j].row_index != column;j++);
                column = Btranspose[j].row;
            }

            else if(Btranspose->term[j].row_index!=column){
                PutSum(result, &totalcount, row, column, &sum);
                i = row_begin;
                column = Btranspose->term[j].row_index;
            }

            else{
                if(A->term[i].column_index<Btranspose->term[j].column_index){
                    i++;
                }
                else if(A->term[i].column_index>Btranspose->term[j].column_index){
                    j++;
                }
                else if(A->term[i].column_index==Btranspose->term[j].column_index){
                    sum += A->term[i].value * Btranspose->term[j].value;
                    i++;
                    j++;
                }
            }
        }
        for (; A->term[i].row_index == row;i++);
        row_begin = i;
        row = A->term[i].row_index;
    }
    result->row = A->row;
    result->column = B->column;
    result->count = totalcount;

    return result;
}

int main(int argc, char *argv[]){

    char *filename = *(argv + 1);
    //char *outputName = *(argv + 2);

    matrix *A = (matrix *)malloc(sizeof(matrix));
    matrix *B = (matrix *)malloc(sizeof(matrix));
    matrix **matrixptr = &A;

    //initialize matrix A and B
    initMatrix(&A);
    initMatrix(&B);

    readfile(A, B, matrixptr, filename);

    printMatrixInfo(A);
    printMatrixInfo(B);

    matrix *C = matrixMultiplication(A, B);
    printMatrixInfo(C);

    return 0;
}