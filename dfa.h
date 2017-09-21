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

typedef struct{
	ALPHABET A[35];
	int Neff;
}INPUT;

typedef struct{
	INPUT I[35];
	int Neff;
}ArrINPUT;

//Kelompok Konstruktor
void MakeEmptyArrStatus(ArrSTATUS *TabS);
/* I.S : TabS sembarang
   F.S : TabS terdefinisi kosong
   deskripsi : membuat Tabel TabS kosong
*/
void MakeEmptyArrALPHA(ArrALPHA *TabA);
/* I.S : TabA sembarang
   F.S : TabA terdefinisi kosong
   deskripsi : membuat Tabel TabA kosong
*/

//Kelompok I/O
void BacaFile(ArrSTATUS *TabS, ArrALPHA *TabA, RELASI *R, STATUS *start);
/* I.S : TabS, TabA, R, start sembarang
   F.S : TabS, TabA, R, start terisi / terdefinisi
   Proses : 
   1) Membuka dan membaca file eksternal
   2) Membaca banyak status dan membaca semua status di file eksternal dan menyimpannya ke TabS
   3) Membaca banyak alfabet dan membaca semua alfabet di file eksternal dan menyimpannya ke TabA
   4) Membaca status mulai dari dfa dan menyimpannya ke start
   5) Membaca semua status final dari file eksternal dan mengubah boolean finalstate di TabS menjadi true
   6) Membaca semua fungsi transisi pada file eksternal
*/
void TulisData(ArrSTATUS TabS, ArrALPHA TabA, RELASI R, STATUS start);
/* I.S : TabS, TabA, R, start terdefinisi
   F.S : TabS, TabA, R, start terdefinisi
   Deskripsi : Menulis Alfabet, status, status mulai, status akhir, dan fungsi transisi ke layar
*/

//Kelompok manipulasi string
void SetStrNull(char *s);
/* I.S. : string S sembarang
   F.S. : string S terdefinisi kosong/Null
   Deskripsi : mengisi string S dengan Null
*/
int CariState(ArrSTATUS TabS, char N[]);
/* Mengembalikan indeks dimana status N berada di tabel TabS, jika tidak ditemukan akan mengembalikan IdxUndef
   Prekondisi : TabS dan N terdefinisi
   Deskripsi : Mencari status N di tabel TabS
*/
boolean CompStatus (char A[], char B[]);
/* Mengembalikan True jika string A dan string B sama, dan false jika tidak sama
   Prekondisi : A dan B terdefinisi
*/
#endif
