#ifndef DFA_H
#define DFA_H

#include "boolean.h"

#define IdxUndef -1

typedef struct{
	char state[10];
	boolean finalstate;
} STATUS;

typedef struct{
	STATUS S[35];
	int Neff;
} ArrSTATUS;

typedef struct{
	char alpha[10];
} ALPHABET;

typedef struct{
	ALPHABET A[35];
	int Neff;
} ArrALPHA;

typedef struct{
	STATUS inState[1225];
	ALPHABET Alphabet[1225];
	STATUS fState[1225];
	int Neff;
} RELASI;

void MakeEmptyArrStatus(ArrSTATUS *TabS);

void MakeEmptyArrALPHA(ArrALPHA *TabA);

void BacaFile(ArrSTATUS *TabS, ArrALPHA *TabA, RELASI *R, STATUS *start);

void TulisData(ArrSTATUS TabS, ArrALPHA TabA, RELASI R, STATUS start);

int CariState(ArrSTATUS TabS, char N[]);

boolean CompStatus (char A[], char B[]);

#endif
