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
	int i;
	matrix=(int*)malloc(Row*Row*sizeof(int));
	result=(int*)malloc(Row*Row*sizeof(int));
	matrix=readMtxFile("matrix.txt", Row, Row);
	mtxMultCUDA(matrix, matrix, result, Row);
//	mtxMultiplication(matrix, matrix, result, 4);
//	result=readMtxFile("results.txt", 4, 4);
//	for(i=0; i<16; i++){
//		printf("%d ", result[i]);
//	}
	return(0);
}
