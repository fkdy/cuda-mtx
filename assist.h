//usage:
//  openFile("file name", "wb/...")
#ifndef mtx_assist_h
#define mtx_assist_h
FILE *openFile(
	const char * const pFileName,
	const char * const pOpenMode
);

int *readMtxFile(
	const char* const pFileName,
	const int rows,
	const int columns
);

int writeMtxFile(
	char* pFileName,
	int* pMtx,
	int rows,
	int columns
);

int genMtxFile(
	const char* const pFileName,
	const int rows,
	const int columns
);
#endif
