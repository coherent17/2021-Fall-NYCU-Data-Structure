#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10000005

int global_swap_count = 0;
int length;

int readfile(char *filename, int *array){
	FILE *input = fopen(filename, "r");
	int index = 0;
	while(fscanf(input,"%d",&array[index])!=EOF){
		index++;
	}
	fclose(input);
	return index;
}

void printArray(int *data, int length){
	for (int i = 0; i < length;i++){
		printf("%d ", data[i]);
	}
	printf("\n");
}

void swap(int *a, int *b){
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
	global_swap_count++;
}

void quicksort(int *data, int left, int right){
	int i, j, pivot;
	if(left<right){
		pivot = left;
		i = left;
		j = right;
		while(i<j){
			while(data[i]<=data[pivot]&&i<right)
				i++;
			while(data[j]>data[pivot])
				j--;
			if(i<j){
				if(data[i]!=data[j]){
					swap(&data[i], &data[j]);
					//printArray(data, length);
				}
			}
		}
		if(data[pivot]!=data[j]){
			swap(&data[pivot], &data[j]);
			//printArray(data, length);
		}
		quicksort(data, left, j - 1);
		quicksort(data, j + 1, right);
	}
}

int main(int argc, char *argv[]){

	//input  and output filename:
    char *input_filename = *(argv + 1);
    char *output_filename = *(argv + 2);

	int *data = malloc(sizeof(int) * MAX_SIZE);
	length = readfile(input_filename, data);
	//printArray(data, length);
	quicksort(data, 0, length - 1);
	//printArray(data, length);
	//printf("swap count = %d\n", global_swap_count);
	FILE *output = fopen(output_filename, "w");
	fprintf(output,"%d", global_swap_count);
	fclose(output);
	free(data);
	return 0;
}