
#ifndef DFA_H
#define DFA_H

#include "boolean.h"
#include <stdio.h>

#define IdxUndef -1
#define MaxNArr 50
#define MaxNStr 10
#define MaxNIn 20

typedef struct{
	char state[MaxNStr];
	boolean finalstate;
} STATUS;

typedef struct{
	STATUS S[MaxNArr];
	int Neff;
} ArrSTATUS;

typedef struct{
	char alpha[MaxNStr];
} ALPHABET;

typedef struct{
	ALPHABET A[MaxNArr];
	int Neff;
} ArrALPHA;

typedef struct{
	int IdxInState[MaxNArr*MaxNArr];
	int IdxAlphabet[MaxNArr*MaxNArr];
	int IdxFState[MaxNArr*MaxNArr];
	int Neff;
} RELASI;

typedef struct{
	int IdxA[2*MaxNArr];
	int Neff;
	boolean ValidIn;
}INPUT;

typedef struct{
	INPUT In[MaxNIn];
	int Neff;
}ArrINPUT;

//Kelompok Konstruktor
void MakeEmptyArrStatus(ArrSTATUS *TabS);
/* I.S. : TabS sembarang
   F.S. : TabS terdefinisi kosong
   deskripsi : membuat Tabel TabS kosong
*/
void MakeEmptyArrALPHA(ArrALPHA *TabA);
/* I.S. : TabA sembarang
   F.S. : TabA terdefinisi kosong
   deskripsi : membuat Tabel TabA kosong
*/
void MakeEmptyArrINPUT(ArrINPUT *TabI);
/* I.S. : TabI sembarang
   F.S. : TabI terdefinisi kosong
   Deskripsi : membuat tabel TabI kosong
*/
void MakeEmptyRELASI(RELASI *R);
/* I.S. : R sembarang
   F.S. : R terdefinisi kosong
   Deskripsi : membuat tabel R kosong
*/

//Kelompok I/O
void BacaFile(ArrSTATUS *TabS, ArrALPHA *TabA, RELASI *R, int *IdxStart);
/* I.S. : TabS, TabA, R, start sembarang
   F.S. : TabS, TabA, R, start terisi / terdefinisi
   Proses : 
   1) Membuka dan membaca file eksternal
   2) Membaca banyak status dan membaca semua status di file eksternal dan menyimpannya ke TabS
   3) Membaca banyak alfabet dan membaca semua alfabet di file eksternal dan menyimpannya ke TabA
   4) Membaca status mulai dari dfa dan menyimpannya ke start
   5) Membaca semua status final dari file eksternal dan mengubah boolean finalstate di TabS menjadi true
   6) Membaca semua fungsi transisi pada file eksternal
*/
void BacaInputDFA(ArrALPHA TabA, RELASI R, ArrINPUT *TabI, int IdxStart);
/* I.S. : TabI sembarang
   F.S. : TabI terdefinisi
   Proses :
   1) Membaca banyak input DFA lalu menyinpannya ke TabI.Neff
   2) Membaca semua input DFA : membaca banyak alfabet input lalu membaca alfabet-alfabet input dan disimpan ke TabI
   3) Untuk setiap input, di cek apakah input tersebut legal apa tidak
      - Input dianggap illegal jika ada input alfabet pada suatu states namun tidak ada fungsi transisinya
*/
void SkipLine(FILE *f);
/* I.S. : f terdefinisi
   F.S. : f terdefinisi
   Proses : membaca file hingga karakter pertama baris berikutnya
*/
void TulisData(ArrSTATUS TabS, ArrALPHA TabA, RELASI R, int IdxStart);
/* I.S. : TabS, TabA, R, start terdefinisi
   Deskripsi : Menulis Alfabet, status, status mulai, status akhir, dan fungsi transisi ke layar
*/
void TulisHasil(ArrSTATUS TabS, ArrALPHA TabA, ArrINPUT TabI, RELASI R, int IdxStart);
/* I.S. : TabI terdefinisi
   Deskripsi : Menulis ke file eksternal "outputdfa.txt" semua proses perpindahan status karena input
   Proses :
   1) Jika input merupakan input illegal, maka akan tertulis "Illegal Input" di file external
   2) Jika input legal, maka akan tertulis setiap status perpindahannya ke file external
      - Jika status terakhir merupakan 'Final State', maka akan ditulis "Input diterima" ke file external
      - Jika sebalikknya, akan ditulis "Input di tolak" ke file external
*/

//Kelompok manipulasi string
void SetStrNull(char *s);
/* I.S. : string S sembarang
   F.S. : string S terdefinisi kosong/Null
   Deskripsi : mengisi string S dengan Null
*/
boolean IsStrEq(char A[], char B[]);
/* Mengembalikan True jika string A dan string B sama, dan false jika tidak sama
   Prekondisi : A dan B terdefinisi
*/

//Kelompok DFA
int CariState(ArrSTATUS TabS, char N[]);
/* Mengembalikan indeks dimana status N berada di tabel TabS, jika tidak ditemukan akan mengembalikan IdxUndef
   Prekondisi : TabS dan N terdefinisi
   Deskripsi : Mencari status N di tabel TabS
*/
int CariAlphabet(ArrALPHA TabA, char N[]);
/* Mengembalikan indeks dimana alfabet N berada di tabel TabA, jika tidak ditemukan akan mengembalikan IdxUndef
   Prekondisi : TabA dan N terdefinisi
   Deskripsi : Mencari status N di tabel TabA
*/
int FungsiTransisi(RELASI R, int IdxState, int IdxAlfa);
/* Mengembalikan indeks status dimana hasil dari input alfabet, jika tidak ditemukan di TabR, mengembalikkan IdxUndef jika tidak ada pasangan status dan alfabet di tabel R
   Prekondisi : R, IdxState, dan IdxAlfa terdefinisi
*/
boolean IsAlphaNStateValid(RELASI R, int IdxState, int IdxAlfa);
/* Mengembalikkan true jika pasangan state dan alfabet ada di tabel R, dan false jika sebalikknya
   Prekondisi : R, IdxState, dan IdxAlfa terdefinisi
*/

#endif
