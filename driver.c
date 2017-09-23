#include "dfa.h"
#include "boolean.h"

int main(){
	//Kamus
	ArrSTATUS TabS;
	ArrALPHA TabA;
	ArrINPUT TabI;
	RELASI R;
	int start;
	//Algoritma
	BacaFile(&TabS, &TabA, &R, &start);
	TulisData(TabS, TabA, R, start);
	BacaInputDFA(TabA, R, &TabI, start);
	TulisHasil(TabS,TabA,TabI,R,start);
	return 0;
}
