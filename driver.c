#include "dfa.h"

int main(){
	/* Kamus */
	ArrSTATUS TabS;
	ArrALPHA TabA;
	ArrINPUT TabI;
	RELASI R;
	int IdxStart;
	/* Algoritma */
	//Baca DFA dari file external dan disimpan ke variabel
	BacaFile(&TabS, &TabA, &R, &IdxStart);
	//Tulis data-data DFA yang dibaca ke layar console/terminal
	TulisData(TabS, TabA, R, IdxStart);
	//Baca Input DFA dari file external dan disimpan ke variabel
	BacaInputDFA(TabA, R, &TabI, IdxStart);
	//Tulis hasil dari Input DFA ke file external
	TulisHasil(TabS, TabA, TabI, R, IdxStart);
	return 0;
}
