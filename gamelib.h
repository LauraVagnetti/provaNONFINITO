#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int flagMappaCreata = 0;

typedef enum {morto, ferito, vivo} Stato_Giocatore;
typedef enum {cucina, soggiorno, rimessa, strada, lungo_lago, uscita_campeggio} Tipo_Zona;
typedef enum {cianfrusaglia, bende, coltello, pistola, benzina, adrenalina} Tipo_Oggetto;

const static int probabilita_ogg_zona[6][6] =
{
	{30, 20, 40, 0, 0, 10},
	{20, 10, 10, 30, 0, 30},
	{20, 10, 30, 0, 30, 10},
	{80, 0, 10, 0, 10, 0},
	{70, 0, 10, 0, 20, 0},
	{90, 0, 10, 0, 0, 0}
};

char assoc_nome_oggetti[6][20] =
{
	{"Cianfrusaglia"},
	{"Bende"},
	{"Coltello"},
	{"Pistola"},
	{"Benzina"},
	{"Adrenalina"}
};


char ass_nome_zone[6][20] =
{
	{"Cucina"},
	{"Soggiorno"},
	{"Rimessa"},
	{"Strada"},
	{"Lungo Lago"},
	{"Uscita Campeggio"}
};

typedef struct s_zona
{
	Tipo_Zona nome_zona;
	Tipo_Oggetto oggetto;
	struct s_zona *zona_successiva;
}Zona;

typedef struct
{
	Tipo_Oggetto tipo;
	int quantita;
}Oggetto;

typedef struct
{
	const char nome[30];
	Stato_Giocatore stato;
	Oggetto zaino[6];
}Giocatore;

//dichiarazione delle funzioni
void ins_zona(int);
void gest_mappa();
void crea_mappa();
int gioca();
void elimina_mappa();
int randomOggetti(int);
void inizializzaRand();
void stampaMappa();
void rimuoviElemento();
int controlloInsMappa();
int contaZone();



	

