#include<stdio.h>
#include<stdlib.h>
#include"assist.h"
//usage:
//  openFile("file name", "wb/...")
FILE *openFile(
	const char * const pFileName,
	const char * const pOpenMode
)
{
	FILE *fd = NULL;
	if(pFileName==NULL){
		fprintf(stdout, "file name pointer is NULL\n");
		exit(-1);
	}
	fd= fopen(pFileName, pOpenMode);
	if(fd==NULL){
		fprintf(stderr, "Opening the file %s ... failed\n", pFileName);
		exit(-1);
	}
	return (fd);
}

int *readMtxFile(
	const char* const pFileName,
	const int rows,
	const int columns)
{
	FILE* fp=NULL;
	const int mtx_size=rows*columns;

	fp=openFile(pFileName, "rb");
	int *matrix;
	matrix=(int *)malloc(mtx_size*sizeof(int));
	fread(matrix, 1, mtx_size*sizeof(int), fp);
	fclose(fp);
	return(matrix);
}
	
int writeMtxFile(
	char* pFileName,
	int* pMtx,
	int rows,
	int columns
)
{
	FILE *fp=NULL;
	const int mtx_size=rows*columns;
	if(pFileName==NULL){
		fprintf(stdout,"file name pointer is NULL\n");
		exit(-1);
	}else
		fp=openFile(pFileName, "wb");
	fwrite(pMtx, 1, mtx_size*sizeof(int), fp);
	fclose(fp);
	return 1;
}

int genMtxFile(
	const char* const pFileName,
	const int rows,
	const int columns
)
{
	FILE* fp;
	int mtx_size=rows*columns;
	fp=openFile(pFileName, "wb");
	int *matrix;
	matrix=(int*)malloc(mtx_size*sizeof(int));
	int i=0, j=0;
	for(i=0; i<rows; i++){
		for(j=0; j<columns; j++){
			matrix[i*rows + j]=i+j+1;
		}
	}
	fwrite(matrix, 1, mtx_size*sizeof(int), fp);
	fclose(fp);
	free(matrix);
	return(1);
}
