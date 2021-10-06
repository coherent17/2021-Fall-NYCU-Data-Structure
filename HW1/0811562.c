#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 10000

typedef struct{
    int column_index;
    int row_index;
    int value;
} term;

typedef struct{
    //term index 0 store the row, column, # if non-zero count
    term array[MAX_SIZE];
} matrix;

void initMatrix(matrix **A){
    (*A)->array[0].row_index = 0;
    (*A)->array[0].column_index = -1;
    (*A)->array[0].value = 0;
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
        //printf("%s: ", buffer);
        //meet "A"
        if(strcmp(buffer, "A")==0){
            fscanf(input, "%s", buffer); //read " ;"
        }

        //meet "B"
        else if(strcmp(buffer, "B")==0){
            //correct the true column and row for A
            A->array[0].column_index = store[0]+1;
            A->array[0].row_index = store[1]+1;

            fscanf(input, "%s", buffer); //read " ;"
            matrixptr = &B;
        }

        //meet ; and the end of the row
        else if (strcmp(buffer, ";") == 0){
            store[0] = (*matrixptr)->array[0].column_index;
            store[1] = (*matrixptr)->array[0].row_index;
            (*matrixptr)->array[0].row_index+= 1;
            (*matrixptr)->array[0].column_index = -1;
        }

        //construct matrix
        else if(strcmp(buffer,"0")==0){
            (*matrixptr)->array[0].column_index+= 1;
            //(*matrixptr)->count++;
        }
        else{
            (*matrixptr)->array[0].column_index+= 1;
            (*matrixptr)->array[(*matrixptr)->array[0].value+1].value = atoi(buffer);
            (*matrixptr)->array[(*matrixptr)->array[0].value+1].column_index = (*matrixptr)->array[0].column_index;
            (*matrixptr)->array[(*matrixptr)->array[0].value+1].row_index = (*matrixptr)->array[0].row_index;
            (*matrixptr)->array[0].value++;
        }
        //printf("%d %d %d\n", (*matrixptr)->array[0].row_index, (*matrixptr)->array[0].column_index, (*matrixptr)->array[0].value);
    }
    B->array[0].column_index = store[0]+1;
    B->array[0].row_index = store[1]+1;
    fclose(input);
}

void printMatrix(matrix *A){
    int k = 1;
    for (int i = 0; i < A->array[0].row_index;i++){
        for (int j = 0; j < A->array[0].column_index;j++){
            if(A->array[k].column_index==j && A->array[k].row_index==i){
                printf("%-5d ", A->array[k].value);
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
    for (int i = 1; i <= A->array->value;i++){
        printf("value = %-5d, row = %-5d, column = %-5d\n", A->array[i].value, A->array[i].row_index, A->array[i].column_index);
    }
}

void printMatrixInfo(matrix *A){
    printf("Row of Matrix: %d\n", A->array[0].row_index);
    printf("Column of Matrix: %d\n", A->array[0].column_index);
    printf("Non Zero Term of Matrix: %d\n", A->array[0].value);
    printf("\nThe Non-Zero Term content of the Matrix:\n");
    printNonZeroTerm(A);
    printf("\nThe whole matrix content: \n");
    printMatrix(A);
}


matrix *Transpose(matrix *A){
    //allocate the memory size to store the transpose result
    matrix *result = (matrix *)malloc(sizeof(matrix));
    result->array[0].column_index = A->array[0].row_index;
    result->array[0].row_index = A->array[0].column_index;
    result->array[0].value = A->array[0].value;

    //check whether A is a zero matrix or not
    if(A->array[0].value>0){
        int newCount = 1;
        for (int i = 0; i < A->array[0].column_index;i++){
            for (int j = 1; j <= A->array[0].value;j++){
                if(A->array[j].column_index==i){
                    result->array[newCount].row_index = A->array[j].column_index;
                    result->array[newCount].column_index = A->array[j].row_index;
                    result->array[newCount].value = A->array[j].value;
                    newCount++;
                }
            }
        }
    }
    return result;
}

void PutSum(matrix **result, int *totalcount, int row, int column, int *sum){
    if(*sum!=0){
        (*result)->array[++*totalcount].row_index = row;
        (*result)->array[*totalcount].column_index = column;
        (*result)->array[*totalcount].value = *sum;
        //init sum to zero
        *sum = 0;
    }
}

matrix *Multiply(matrix *A, matrix *B){
    matrix *Btranspose = Transpose(B);

    //matrix to return the the result of A * B
    matrix *result = (matrix *)malloc(sizeof(matrix));

    int i, j, column, totalcount = 0;
    int row_begin = 1;
    int row = A->array[1].row_index;
    int sum = 0;

    for (i = 1; i <= A->array[0].value;){
        sum = 0;
        column = Btranspose->array[1].row_index;
        for (j = 1; j <= B->array[0].value + 1;){
            if(A->array[i].row_index!=row){
                PutSum(&result, &totalcount, row, column, &sum);
                i = row_begin;
                for (; Btranspose->array[j].row_index == column;j++);
                column = Btranspose->array[j].row_index;
            }
            else if(Btranspose->array[j].row_index!=column){
                PutSum(&result, &totalcount, row, column, &sum);
                i = row_begin;
                column = Btranspose->array[j].row_index;
            }
            else{
                if(A->array[i].column_index > Btranspose->array[j].column_index){
                    j++;
                }
                else if(A->array[i].column_index < Btranspose->array[j].column_index){
                    i++;
                }
                else{
                    sum += A->array[i++].value * Btranspose->array[j++].value;
                }
            }
        }
        for (; A->array[i].row_index == row;i++);
        row_begin = i;
        row = A->array[i].row_index;
    }
    result->array[0].row_index = A->array[0].row_index;
    result->array[0].column_index = B->array[0].column_index;
    result->array[0].value = totalcount;

    return result;
}


int main(int argc, char *argv[]){

    char *filename = *(argv + 1);
    char *outputName = *(argv + 2);

    matrix *A = (matrix *)malloc(sizeof(matrix));
    matrix *B = (matrix *)malloc(sizeof(matrix));
    matrix **matrixptr = &A;

    initMatrix(&A);
    initMatrix(&B);

    readfile(A, B, matrixptr, filename);

    int m, n, p, q;
    m = A->array[0].row_index;
    n = A->array[0].column_index;
    p = B->array[0].row_index;
    q = B->array[0].column_index;

    matrix *result = (matrix *)malloc(sizeof(matrix));

    if(n==p){
        result = Multiply(A, B);
    }
    else if(m==p){
        result = Multiply(Transpose(A), B);
    }
    else if(n==q){
        result = Multiply(A, Transpose(B));
    }
    else if(m==q){
        result = Multiply(Transpose(A), Transpose(B));
    }

    FILE *outputfile;
    outputfile = fopen(outputName, "w");
    int k = 1;
    for (int i = 0; i < result->array[0].row_index;i++){
        for (int j = 0; j < result->array[0].column_index;j++){
            if(result->array[k].column_index==j && result->array[k].row_index==i){
                fprintf(outputfile, "%d ", result->array[k].value);
                k++;
            }
            else{
                fprintf(outputfile, "0 ");
            }
        }
        fprintf(outputfile, ";\n");
    }
    fclose(outputfile);
    return 0;
}