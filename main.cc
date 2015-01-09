#include<stdio.h>
#include<stdlib.h>
#include"assist.h"
#include"mtxMultiplication.h"

int main()
{
	if(!genMtxFile("matrix.txt", 4, 4))
		printf("generate matrix file error\n");
	int *matrix;
	int *result;
	int i;
	matrix=(int*)malloc(16*sizeof(int));
	result=(int*)malloc(16*sizeof(int));
	matrix=readMtxFile("matrix.txt", 4, 4);
	mtxMultCUDA(matrix, matrix, result, 4);
//	mtxMultiplication(matrix, matrix, result, 4);
//	result=readMtxFile("results.txt", 4, 4);
//	for(i=0; i<16; i++){
//		printf("%d ", result[i]);
//	}
	return(0);
}
