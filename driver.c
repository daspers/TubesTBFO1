#include "dfa.h"
#include "boolean.h"

int main(){
	ArrSTATUS TabS;
	ArrALPHA TabA;
	RELASI R;
	STATUS start;
	BacaFile(&TabS, &TabA, &R, &start);
	TulisData(TabS, TabA, R, start);
	return 0;
}
