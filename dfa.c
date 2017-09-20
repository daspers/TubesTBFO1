
#include "boolean.h"
#include "dfa.h"
#include <stdio.h>

void MakeEmptyArrStatus(ArrSTATUS *TabS){
	TabS->Neff=0;
}

void MakeEmptyArrALPHA(ArrALPHA *TabA){
	TabA->Neff=0;
}

void BacaFile(ArrSTATUS *TabS, ArrALPHA *TabA, RELASI *R, STATUS *start){
	//Kamus
	char baca, STemp[10];
	int i,j,t;
	FILE *f;
	//Algoritma
	f=fopen("dfa.txt", "r");
	MakeEmptyArrStatus(TabS);
	//baca banyak states
	baca= (char) fgetc(f);
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
			if(j<10)
				TabS->S[i].state[j]='\0';
			TabS->S[i].finalstate=false;
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
			if(j<10)
				TabA->A[i].alpha[j]='\0';
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
	for(i=0;baca!='\n';){
		if(baca!=';'){
			start->state[i]=baca;
			i++;
		}
		else{
			if(i<10)
				start->state[i]='\0';
		}
		baca= (char) fgetc(f);
	}
	start->state[i]='\0';
	//baca final state
	do{
		baca= (char) fgetc(f);
	}while(baca!=' ');
	baca= (char) fgetc(f);
	for(i=0;baca!='\n';){
		if(baca!=';'&&baca!=','){
			STemp[i]=baca;
			i++;
		}
		else{
			if(i<10)
				STemp[i]='\0';
			TabS->S[CariState(*TabS, STemp)].finalstate=true;
			i=0;
		}
		baca= (char) fgetc(f);
	}
	//baca relasi
	baca= (char) fgetc(f);
	for(i=0,j=0,t=1;baca!=EOF&&i<1225;){
		if(baca!=';'&&baca!=' '&&baca!='\n'){
			if(t==1){
				R->inState[i].state[j]=baca;
			}
			else if(t==2){
				R->Alphabet[i].alpha[j]=baca;
			}
			else{
				R->fState[i].state[j]=baca;
			}
			j++;
		}
		else if(baca!='\n'){
			if(i<10)
				STemp[i]='\0';
			if(t>=3){
				t=1;
				i++;
			}
			else
				t++;
			TabS->S[CariState(*TabS, STemp)].finalstate=true;
			j=0;
		}
		baca= (char) fgetc(f);
	}
	R->Neff=i;
}

void TulisData(ArrSTATUS TabS, ArrALPHA TabA, RELASI R, STATUS start){
	int i=0;
	printf("Ada %d Alfabet, yaitu :\n",TabA.Neff);
	for(i=0;i<TabA.Neff;i++){
		printf("%d - %s\n", i+1, TabA.A[i].alpha);
	}
	printf("Ada %d Status, yaitu :\n",TabS.Neff);
	for(i=0;i<TabS.Neff;i++){
		printf("%d - %s\n", i+1, TabS.S[i].state);
	}
	printf("Status awal : %s\n",start.state);
	printf("Status akhir : \n");
	for(i=0;i<TabS.Neff;i++){
		if(TabS.S[i].finalstate)
			printf("%s\n", TabS.S[i].state);
	}
	printf("Berikut fungsi trasisi :\n");
	for(i=0;i<R.Neff;i++){
		printf("%d) f(%s,%s)=%s\n", i+1, R.inState[i].state, R.Alphabet[i].alpha, R.fState[i].state);
	}
}

int CariState(ArrSTATUS TabS, char N[]){
	int i;
	for(i=0;i<TabS.Neff;i++){
		if(CompStatus(TabS.S[i].state,N))
			return i;
	}
	return IdxUndef;
}

boolean CompStatus(char A[], char B[]){
	int i;
	for(i=0;i<10&&A[i]!='\0'&&B[i]!='\0';i++)
		if(A[i]!=B[i])
			return false;
	return A[i]==B[i];
}
