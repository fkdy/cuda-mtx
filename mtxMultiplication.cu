#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"mtxMultiplication.h"
#include<cuda_runtime.h>
#include<cuda.h>
#include"assist.h"

// square matrix multiplication
// used for checking the results
void mtxMultiplication(int *m, int *n, int *p, int rows)
{
	int i, j, k, temp, isNULL=0;
	if(m==NULL || n==NULL){
		fprintf(stdout, "input matrix pointer is NULL\n");
		exit(-1);
	}else if(p==NULL){
		isNULL=1;
		p=(int *)malloc(rows*rows*sizeof(int));
	}
	for(i=0; i<rows; i++){
		for(j=0; j<rows; j++){
			p[i*rows + j]=0;
			for(k=0; k<rows; k++){
				temp=m[i*rows + k]*n[k*rows + j];
				p[i*rows + j]=p[i*rows + j]+temp;
			}
		}
	}
	writeMtxFile("results.txt", p, rows, rows);
	if(isNULL)
		free(p);
}

__global__ void mtxMultKernel(int *pmDev, int *pnDev, int *ppDev, int tileRow, int mtxRow);

// function port to cuda device
void mtxMultCUDA(int *pm, int *pn, int *pp, int rows)
{
	int size=rows*rows*sizeof(int);
	int *pmDev, *pnDev, *ppDev;
	// allocate memory on device
	cudaMalloc((void**)&pmDev, size);
	cudaMalloc((void**)&pnDev, size);
	cudaMalloc((void**)&ppDev, size);
	// copy content of the matrix from host to device
	cudaMemcpy(pmDev, pm, size, cudaMemcpyHostToDevice);
	cudaMemcpy(pnDev, pn, size, cudaMemcpyHostToDevice);

	// kernel invocation code
	// 1.kernel configuration
	dim3 dimBlock(rows/4, rows/4);
	dim3 dimGrid(4,4);
	// 2.lunch the kernel
	mtxMultKernel<<<dimGrid, dimBlock>>>(pmDev, pnDev, ppDev, 4, rows);
	
	// copy content of the result matrix form device to host
	cudaMemcpy(pp, ppDev, size, cudaMemcpyDeviceToHost);
	// free allocated device memory
	cudaFree(ppDev);
	cudaFree(pmDev);
	cudaFree(pnDev);

	// print out
	int i=0;
	int j=0;
	for(i=0; i<rows; i++){
		for(j=0; j<rows; j++){
			fprintf(stdout, "%d ", pp[i*rows + j]);
		}
		fprintf(stdout, "\n");
	}
	fprintf(stdout, "\nthe matrix:\n");
	for(i=0; i<rows; i++){
		for(j=0; j<rows; j++){
			fprintf(stdout, "%d ", pm[i*rows + j]);
		}
		fprintf(stdout, "\n");
	}
/*	for(i=0; i<rows*rows; i++){
		fprintf(stdout, "%d ", pm[i]);
	}
*/
}

// matrix multipliction kernel function
__global__ void mtxMultKernel(int *pmDev, int *pnDev, int *ppDev, int tileRow, int mtxRow)
{
	// thread id 
	//   n
	// m p
	// tx corresponding to matrix column indice
	// tx -> matrix row number
	int c=blockIdx.x*tileRow+ threadIdx.x;
	int r=blockIdx.y*tileRow+ threadIdx.y;
	int i;
	ppDev[r*mtxRow + c]=0;
	for(i=0; i<mtxRow; i++)
		ppDev[r*mtxRow + c]+=pmDev[r*mtxRow + i]*pnDev[i*mtxRow + c];
}
