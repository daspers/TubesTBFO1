#ifndef DFA_H
#define DFA_H

#include "boolean.h"

typedef struct{
	char state[10];
	boolean finalstate;
} STATUS;

typedef struct{
	STATUS S[50];
	int Neff;
} ArrSTATUS;

typedef struct{
	char alpha[10];
} ALPHABET;

typedef struct{
	ALPHABET A[50];
	int Neff;
} ArrALPHA;

typedef struct{
	STATUS inState[1000];
	ALPHABET Alphabet[1000];
	STATUS fState[1000];
	int Neff;
} RELASI;

void MakeEmptyArrStatus(ArrSTATUS *TabS);

void MakeEmptyArrALPHA(ArrALPHA *TabA);

void BacaFile(ArrSTATUS *TabS, ArrALPHA *TabA);


#endif
