
#include "boolean.h"
#include "dfa.h"
#include <stdio.h>

void MakeEmptyArrStatus(ArrSTATUS *TabS){
	TabS->Neff=0;
}

void MakeEmptyArrALPHA(ArrALPHA *TabA){
	TabA->Neff=0;
}

void BacaFile(ArrSTATUS *TabS, ArrALPHA *TabA, STATUS *start){
	char baca;
	int i,j;
	FILE *f;
	f=fopen("dfa.txt", "r");
	baca= (char) fgetc(f);
	//baca banyak states
	MakeEmptyArrStatus(TabS);
	while(baca!=';'){
		TabS->Neff=10*(TabS->Neff)+baca-'0';
		baca= (char) fgetc(f);
	}
	//baca semua states
	baca= (char) fgetc(f);
	for(i=0,j=0;baca!='\n';){
		if(baca!=';'&&baca!=','){
			TabS->S[i].state[j]=baca;
			j++;
		}
		else{
			i++;
			j=0;
		}
		baca= (char) fgetc(f);
	}
	//baca banyak alphabet
	MakeEmptyArrALPHA(TabA);
	baca = (char) fgetc(f);
	while(baca!=';'){
		TabA->Neff=10*(TabA->Neff)+baca-'0';
		baca= (char) fgetc(f);
	}
	//baca semua alphabet
	baca= (char) fgetc(f);
	for(i=0,j=0;baca!='\n';){
		if(baca!=';'&&baca!=','){
			TabA->A[i].alpha[j]=baca;
			j++;
		}
		else{
			i++;
			j=0;
		}
		baca= (char) fgetc(f);
	}
	//baca start state
	do{
		baca= (char) fgetc(f);
	}while(baca!=' ');
	baca= (char) fgetc(f);
	
	
}
