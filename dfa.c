#include "boolean.h"
#include "dfa.h"
#include <stdio.h>

/* Kelompok Konstruktor */
void MakeEmptyArrStatus(ArrSTATUS *TabS){
	/* Algoritma */
	(*TabS).Neff=0;
}

void MakeEmptyArrALPHA(ArrALPHA *TabA){
	/* Algoritma */
	(*TabA).Neff=0;
}

void MakeEmptyArrINPUT(ArrINPUT *TabI){
	/* Kamus */
	int i;
	/* Algoritma */
	(*TabI).Neff=0;
	for(i=0;i<MaxNIn;i++){
		(*TabI).In[i].Neff = 0;	
	}
}

void MakeEmptyRELASI(RELASI *R){
	/* Algoritma */
	(*R).Neff=0;
}

/* Kelompok I/O */
void BacaFile(ArrSTATUS *TabS, ArrALPHA *TabA, RELASI *R, int *IdxStart){
	/* Kamus */
	char baca, STemp[MaxNStr], STemp2[MaxNStr], ATemp[MaxNStr];
	int i,j,t;
	FILE *f;
	/* Algoritma */
	//Buka file external "dfa.txt" untuk dibaca
	f=fopen("dfa.txt", "r");
	//Baca banyak states
	MakeEmptyArrStatus(TabS);
	baca= (char) fgetc(f);
	while(baca=='#'){
		SkipLine(f);
		baca= (char) fgetc(f);
	}
	while(baca!=';'){
		(*TabS).Neff=10*((*TabS).Neff)+baca-'0';
		baca= (char) fgetc(f);
	}
	//Baca semua states
	baca= (char) fgetc(f);
	SetStrNull((*TabS).S[0].state);
	for(i=0,j=0;baca!='\n';){
		if(baca!=';'&&baca!=','){
			(*TabS).S[i].state[j]=baca;
			j++;
		}
		else{
			(*TabS).S[i].finalstate=false;
			i++;
			SetStrNull((*TabS).S[i].state);
			j=0;
		}
		baca= (char) fgetc(f);
	}
	//Baca banyak alphabet
	MakeEmptyArrALPHA(TabA);
	baca = (char) fgetc(f);
	while(baca=='#'){
		SkipLine(f);
		baca= (char) fgetc(f);
	}
	while(baca!=';'){
		(*TabA).Neff=10*((*TabA).Neff)+baca-'0';
		baca= (char) fgetc(f);
	}
	//Baca semua alphabet
	baca= (char) fgetc(f);
	SetStrNull((*TabA).A[0].alpha);
	for(i=0,j=0;baca!='\n';){
		if(baca!=';'&&baca!=','){
			(*TabA).A[i].alpha[j]=baca;
			j++;
		}
		else{
			i++;
			SetStrNull((*TabA).A[i].alpha);
			j=0;
		}
		baca= (char) fgetc(f);
	}
	//Baca start state
	do{
		baca= (char) fgetc(f);
		while(baca=='#'){
			SkipLine(f);
			baca= (char) fgetc(f);
		}
	}while(baca!=' ');
	baca= (char) fgetc(f);
	SetStrNull(STemp);
	for(i=0;baca!='\n';){
		if(baca!=';'){
			STemp[i]=baca;
			i++;
		}
		baca= (char) fgetc(f);
	}
	*IdxStart = CariState(*TabS, STemp);
	//Baca final state
	do{
		baca= (char) fgetc(f);
		while(baca=='#'){
			SkipLine(f);
			baca= (char) fgetc(f);
		}
	}while(baca!=' ');
	baca= (char) fgetc(f);
	SetStrNull(STemp);
	for(i=0;baca!='\n';){
		if(baca!=';'&&baca!=','){
			STemp[i]=baca;
			i++;
		}
		else{
			(*TabS).S[CariState(*TabS, STemp)].finalstate=true;
			SetStrNull(STemp);
			i=0;
		}
		baca= (char) fgetc(f);
	}
	//Baca relasi
	baca= (char) fgetc(f);
	while(baca=='#'){
		SkipLine(f);
		baca= (char) fgetc(f);
	}
	SetStrNull(STemp);
	SetStrNull(ATemp);
	SetStrNull(STemp2);
	MakeEmptyRELASI(R);
	for(i=0,j=0,t=1;baca!=EOF&&i<MaxNArr*MaxNArr;){
		if(baca!=';'&&baca!=' '&&baca!='\n'){
			if(t==1){
				STemp[j]=baca;
			}
			else if(t==2){
				ATemp[j]=baca;
			}
			else{
				STemp2[j]=baca;
			}
			j++;
		}
		else{
			if(t>=3){
				(*R).IdxInState[i] = CariState(*TabS, STemp);
				(*R).IdxAlphabet[i] = CariAlphabet(*TabA, ATemp);
				(*R).IdxFState[i] = CariState(*TabS, STemp2);
				i++;
				SetStrNull(STemp);
				SetStrNull(ATemp);
				SetStrNull(STemp2);
				t=1;
			}
			else
				t++;
			j=0;
		}
		baca= (char) fgetc(f);
		if(baca=='\n'){
			baca= (char) fgetc(f);
			while(baca=='#'){
				SkipLine(f);
				baca= (char) fgetc(f);
			}
		}
	}
	(*R).Neff=i;
	//Tutup file external "dfa.txt"
	fclose(f);
}

void BacaInputDFA(ArrALPHA TabA, RELASI R, ArrINPUT *TabI, int IdxStart){
	/* Kamus */
	int i,j,k,CurIdxS;
	char baca,ATemp[MaxNStr];
	FILE *f;
	/* Algoritma */
	//Buka file external "inputdfa.txt" untuk dibaca
	f = fopen("inputdfa.txt", "r");
	//Baca banyak input
	baca= (char) fgetc(f);
	while(baca=='#'){
		SkipLine(f);
		baca= (char) fgetc(f);
	}
	MakeEmptyArrINPUT(TabI);
	while(baca!='\n'){
		if(baca!=';')
			(*TabI).Neff=(*TabI).Neff*10+baca-'0';
		baca= (char) fgetc(f);
	}
	//Baca Input
	for(i=0;i<(*TabI).Neff;i++){
		//Baca banyak alfabet input
		baca= (char) fgetc(f);
		while(baca=='#'){
			SkipLine(f);
			baca= (char) fgetc(f);
		}
		do{
			(*TabI).In[i].Neff=(*TabI).In[i].Neff*10+baca-'0';
			baca= (char) fgetc(f);
		}while(baca!=';');
		//Baca alfabet input
		baca= (char) fgetc(f);
		SetStrNull(ATemp);
		(*TabI).In[i].ValidIn=true;
		CurIdxS = IdxStart;
		for(j=0,k=0;baca!='\n'&&j<(*TabI).In[i].Neff;){
			if(baca!=','&&baca!=';'){
				ATemp[k]=baca;
				k++;
			}
			else{
				(*TabI).In[i].IdxA[j]=CariAlphabet(TabA,ATemp);
				if((*TabI).In[i].ValidIn){
					CurIdxS = FungsiTransisi(R, CurIdxS, (*TabI).In[i].IdxA[j]);
					if(CurIdxS==IdxUndef)
						(*TabI).In[i].ValidIn=false;
				}
				SetStrNull(ATemp);
				j++;
				k=0;
			}
			baca= (char) fgetc(f);
		}
		if((*TabI).In[i].Neff==0)
			baca= (char) fgetc(f);
	}
	//Tutup file external "inputdfa.txt"
	fclose(f);
}

void SkipLine(FILE *f){
	/* Kamus */
	char baca;
	/* Algoritma */
	baca=(char) fgetc(f);
	while(baca!='\n'){
		baca= (char) fgetc(f);
	}
}

void TulisData(ArrSTATUS TabS, ArrALPHA TabA, RELASI R, int IdxStart){
	/* Kamus */
	int i;
	/* Algoritma */
	//Menulis layar semua alfabet
	printf("Ada %d Alfabet, yaitu :\n",TabA.Neff);
	for(i=0;i<TabA.Neff;i++){
		printf("%d - %s\n", i+1, TabA.A[i].alpha);
	}
	//Menulis layar semua status
	printf("Ada %d Status, yaitu :\n",TabS.Neff);
	for(i=0;i<TabS.Neff;i++){
		printf("%d - %s\n", i+1, TabS.S[i].state);
	}
	//Menulis layar status awal DFA
	printf("Status awal : %s\n", TabS.S[IdxStart].state);
	//Menulis layar semua status akhir dari DFA
	printf("Status akhir : \n");
	for(i=0;i<TabS.Neff;i++){
		if(TabS.S[i].finalstate)
			printf("%s\n", TabS.S[i].state);
	}
	//Menulis layar semua status fungsi transisi dari DFA
	printf("Berikut fungsi trasisi :\n");
	for(i=0;i<R.Neff;i++){
		printf("%d) f(%s,%s)=%s\n", i+1, TabS.S[R.IdxInState[i]].state, TabA.A[R.IdxAlphabet[i]].alpha, TabS.S[R.IdxFState[i]].state);
	}
}

void TulisHasil(ArrSTATUS TabS, ArrALPHA TabA, ArrINPUT TabI, RELASI R, int IdxStart){
	/* Kamus */
	int i,j,CurIdxS;
	FILE *f;
	/* Algoritma */
	//Buka File "outputdfa.txt" untuk ditulis
	f=fopen("outputdfa.txt","w");
	//Tulis output langkah-langkah ke file external
	for(i=0;i<TabI.Neff;i++){
		fprintf(f,"Input ke-%d :\n",i+1);
		if(TabI.In[i].ValidIn){
			CurIdxS = IdxStart;
			fprintf(f,"%s", TabS.S[CurIdxS].state);
			for(j=0;j<TabI.In[i].Neff;j++){
				fprintf(f,"->");
				CurIdxS = FungsiTransisi(R, CurIdxS, TabI.In[i].IdxA[j]);
				fprintf(f,"%s", TabS.S[CurIdxS].state);
			}
			fprintf(f, "\n");
			if(TabS.S[CurIdxS].finalstate)
				fprintf(f, "Input Diterima\n");
			else
				fprintf(f, "Input Ditolak\n");
		}
		else{
			fprintf(f, "Illegal Input\n");
		}
		if(i<TabI.Neff-1)
			fprintf(f,"\n");
	}
	//Tutup file "outputdfa.txt"
	fclose(f);
}

/* Kelompok Manipulasi String */
void SetStrNull(char *s){
	/* Kamus */
	int i;
	/* Algoritma */
	//Menge-set untuk setiap char dari array jadi '\0' atau null
	for(i=0;i<MaxNStr;i++){
		s[i]='\0';
	}
}

boolean IsStrEq(char A[], char B[]){
	/* Kamus */
	int i;
	/* Algoritma */
	for(i=0;i<MaxNStr-1&&A[i]!='\0'&&B[i]!='\0';i++)
		if(A[i]!=B[i])
			return false;
	//Untuk setiap i<MaxNStr-1, A[i] = B[i]; atau B[i]='\0' atau A[i]='\0' 
	return A[i]==B[i]; 
}

/* Kelompok DFA */
int CariState(ArrSTATUS TabS, char N[]){
	/* Kamus */
	int i;
	/* Algoritma */
	for(i=0;i<TabS.Neff;i++){
		if(IsStrEq(TabS.S[i].state,N))
			return i;
	}
	return IdxUndef; //Jika tidak ditemukan status N
}

int CariAlphabet(ArrALPHA TabA, char N[]){
	/* Kamus */
	int i;
	/* Algoritma */
	for(i=0;i<TabA.Neff;i++){
		if(IsStrEq(TabA.A[i].alpha,N))
			return i;
	}
	return IdxUndef; //Jika tidak ditemukan alfabet N
}

int FungsiTransisi(RELASI R, int IdxState, int IdxAlfa){
	/* Kamus */
	int i;
	/* Algoritma */
	for(i=0;i<R.Neff;i++){
		if(R.IdxInState[i]==IdxState && R.IdxAlphabet[i] == IdxAlfa)
			return R.IdxFState[i];
	}
	//Tidak ditemukan pasangan input state State[IdxState] dan alfabet Alpha[IdxAlfa] di tabel Relasi R
	return IdxUndef;
}

boolean IsAlphaNStateValid(RELASI R, int IdxState, int IdxAlfa){
	/* Algoritma */
	return FungsiTransisi(R,IdxState,IdxAlfa) != IdxUndef;
}
