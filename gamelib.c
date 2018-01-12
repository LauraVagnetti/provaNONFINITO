#include "gamelib.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

static Zona *prima_zona = NULL;
static Zona *ultima_zona = NULL;

static Giocatore giacomo;
static Giocatore marzia;

static int flagPrimaZonaIns = 0;
char sceltaMappa;
//inserisci un item(zona) nella lista
void ins_zona(int sceltaMenuZona)
{
	if(prima_zona ==NULL) //creazione prima zona
	{
		prima_zona = (Zona *)malloc(sizeof(Zona));
		prima_zona -> nome_zona = sceltaMenuZona;
		prima_zona -> oggetto = randomOggetti(sceltaMenuZona);
		prima_zona -> zona_successiva = NULL;
		ultima_zona = prima_zona;
	}
	else
	{
		ultima_zona ->zona_successiva = (Zona *)malloc(sizeof(Zona));
		ultima_zona = ultima_zona ->zona_successiva;
		ultima_zona->nome_zona = sceltaMenuZona;
		ultima_zona-> oggetto = randomOggetti(sceltaMenuZona);
		ultima_zona-> zona_successiva = NULL;
	}
}

//stampa la lista(mappa)
void stampaMappa()
{
	Zona *temp = prima_zona;
	int countZone = 1;
	
	while(temp != NULL)
	{
		printf("\n-----------------\n");
		printf("%d, %s\n", countZone, ass_nome_zone[temp->nome_zona]);
		printf("%s\n", assoc_nome_oggetti[temp->oggetto]);
		printf("------------------\n");
		temp = temp->zona_successiva;
		countZone++;
	}
	
	if(prima_zona == NULL)
	{
		printf("\n-------Mappa Vuota-------\a\n");
	}
}

//menù  per la gestione della mappa
void gest_mappa()
{
	int sceltaMenuMappa;
	int sceltaMenuZona;
	char sceltaEliminazioneMappa = ' ';

	do
	{
		printf("\n --Crea Mappa--\n");
		printf("\n1) Inserisci zona\n2) Cancella zona\n3) Stampa mappa\n4) Eliminazione mappa\n5) Chiudi mappa\n");
		scanf("%d", &sceltaMenuMappa);
		switch(sceltaMenuMappa)
		{
			case 1:
				if(flagMappaCreata == 0)
				{
					do
					{
						printf("\nScegli:\n1) Cucina\n2) Soggiorno\n3) Rimessa\n4) Strada\n 5) Lungo lago\n6) Fine inserimento ^-^\n");
						scanf("%d", &sceltaMenuZona);
						sceltaMenuZona--;
						if(sceltaMenuZona >= 0 && sceltaMenuZona <= 4)
						{
							ins_zona(sceltaMenuZona);
							printf("%d", sceltaMenuZona);
						}		
						else if(sceltaMenuZona == 5)
						{
							break;
						}
						else
						{
							printf("\n------ Sbagliato (>-<) ------\a\n");
						}
					}
					
					while(sceltaMenuZona != 5);
				}
				
				else
				{
					printf("\n Mappa già creata, non puoi inserire zone (^-^)''\a\n");
				}
				break;

			case 2:
				if(flagMappaCreata == 0)
				{
					rimuoviElemento();
				}
				else
				{
					printf("\n Mappa già creata, non puoi eliminare zone (°v°)\a\n");
				}
				break;

			case 3:
				stampaMappa();
				break;

			case 4:
				do
				{
					printf("\n Ne sei sicuro?(S/N)\n");
					scanf("%s", &sceltaEliminazioneMappa);
					switch(sceltaEliminazioneMappa)
					{
						case 'S':
						case 's':
							elimina_mappa();
							flagMappaCreata = 0;
							break;
						
						case 'N':
						case 'n':
							break;
		
						default:
							sceltaEliminazioneMappa = 'e';
							break;
					}
				}
				while(sceltaEliminazioneMappa == 'e');
				break;

		      case 5:
				switch(controlloInsMappa())
				{
					case 1:
						flagMappaCreata = 1; //flag responsabile della creazione completa della lista(mappa)
						ins_zona(5); //inserisci il campo UscitaCampeggio alla fine dell'insermento di tutti gli elementi(zone)

						printf("\n PERFECT! Mappa chiusa (*-*)\n");
						break;
				
					case -1:
						printf("\n Devi aggiungere più zone (<_<)\n");
						sceltaMenuMappa = -1;
						break;

					case -2: 
						printf("\n Mappa Vuota (T_T) non hai inserito nulla\a\n");
						break;				
				}
				break;
			
			default:
				printf("\nScelta errata!\n"); 
				break;
			}
		}
		while(sceltaMenuMappa !=5);

}
				

//rimuovere ultimo elemento lista (mappa)
void rimuoviElemento()
{
	if(prima_zona == ultima_zona)
	{
		free(prima_zona);
		prima_zona = NULL;
		ultima_zona = NULL;
		if(prima_zona == NULL)
		{
			printf("La mappa non ha zone da eliminare!\n");
		}
	}
	else
	{
		Zona *temp = prima_zona;
		while(temp != NULL)
		{
			if(temp->zona_successiva == ultima_zona)
			{
				free(ultima_zona);
				temp->zona_successiva = NULL;
				ultima_zona=temp;
				break;
			}
			
			temp= temp-> zona_successiva;
		}
	}
}

//inizializza la funzione di sistema rand()
void inizializzazioneRand()
{
	time_t t;
	srand((unsigned) time(&t));
}

//estrarre casualmente un oggetto attinendosi alle probabilità della matrice probabilita_ogg_zona

int randomOggetti(int indexZona)
{
	int randNum = (rand() % 100);
	int count = 0;
	int i = -1;
	do 
	{
		i++;
		count = count + probabilita_ogg_zona[indexZona][i];
	}
	while(count < randNum);
	return i;
}

//controllo parametri lista(mappa)
int controlloInsMappa()
{
	Zona *temp = prima_zona;
	int countZone = 0;
	if(prima_zona == NULL) //controllo se nella lista ci sta aleno un elemento(zona)
	{
		return -2;
	}
	if(contaZone() < 8) //controllo se il numero di elementi (zone) siano almeno 8
	{
		return -1;
	}
	else if(ultima_zona -> nome_zona == 5)
	{
		return -3;
	}
	else //se tutti i controlli sono andati a buon fine
	{
		return 1;
	}
}

//elimina intera lista (mappa)
void elimina_mappa()
{
	//eliminazione e deallocazione delle liste dati
	while(prima_zona != NULL)
	{
		Zona *temp = prima_zona;
		prima_zona = prima_zona -> zona_successiva;
		free(temp);
	}

	ultima_zona = NULL;
}

//conta elementi (zone) all interno della lista(mappa)
int contaZone()
{
	Zona *temp = prima_zona;
	int countZone = 0;
	while(temp !=NULL)
	{
		countZone++;
		temp = temp-> zona_successiva;
	}
	return countZone;
} 

