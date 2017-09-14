#ifndef DFA_H
#define DFA_H

#include "boolean.h"

typedef struct{
	char state[10];
	int statenum;
	boolean finalstate;
} STATUS;

typedef struct{
	STATUS S[100];
	int Neff;
} ArrSTATUS;

typedef struct{
	
} RELASI;

#endif
