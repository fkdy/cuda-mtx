#include<stdio.h>
#include<stdlib.h>
#include"assist.h"
#include"mtxMultiplication.h"
#define Row 16
int main()
{
	if(!genMtxFile("matrix.txt", Row, Row))
		printf("generate matrix file error\n");
	int *matrix;
	int *result;
	int i, j;
	matrix=(int*)malloc(Row*Row*sizeof(int));
	result=(int*)malloc(Row*Row*sizeof(int));
	matrix=readMtxFile("matrix.txt", Row, Row);

	fprintf(stdout, "\nthe matrix:\n");
	for(i=0; i<Row; i++){
		for(j=0; j<Row; j++){
			fprintf(stdout, "%d ", matrix[i*Row + j]);
		}
		fprintf(stdout, "\n");
	}

	fprintf(stdout, "\nthe device output:\n");
	mtxMultCUDA(matrix, matrix, result, Row);
	// print out results
	for(i=0; i<Row; i++){
		for(j=0; j<Row; j++){
			fprintf(stdout, "%d ", result[i*Row + j]);
		}
		fprintf(stdout, "\n");
	}

	// for comparison
	mtxMultiplication(matrix, matrix, result, Row);
	fprintf(stdout, "\nthe host version:\n");
	for(i=0; i<Row; i++){
		for(j=0; j<Row; j++){
			fprintf(stdout, "%d ", result[i*Row + j]);
		}
		fprintf(stdout, "\n");
	}

	return(0);
}
