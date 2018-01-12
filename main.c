#include <stdio.h>
#include "gamelib.c"

//nel main metto solo la stampa del menu iniziale e i richiami alle tre scelte del giocatore

int main()
{
	char sceltaMenuStart;
	
	do
	{
		printf("\n --! Welcome !--\n");
		printf("\n1) Gestione mappa\n2) Gioca\n3) Termina gioco\n");
		scanf("%s", &sceltaMenuStart);
		
		switch(sceltaMenuStart)
		{
			case '1':
				gest_mappa();
				break;

			case '2':
				break;

			case '3':
				elimina_mappa();
				exit(1);

			default:
				printf("\nScelta non valida!!!\n");
				break;
		}
	}while(sceltaMenuStart != '3');

}	
