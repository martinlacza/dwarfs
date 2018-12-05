/*
						No Country for Old dwarves.
*/
skuska na cviku
#pragma comment(lib, "-lwinmm.lib")		//linker na lwinmm aby isla hudba
#include <stdio.h>
#include <string.h>			//potrebujem na pracu so stringami na intro a outro
#include <stdlib.h>
#include <time.h>		//time potrebujem na random generaciu
#include <windows.h>	//windows potrebujem na konzolu aby som mohol narabat s konzolou
#include "defines.h"

typedef struct _Storage{
	int jedlo;				//struktura storage
	int	pivo;
	int ruda;
	int mince;
} Storage ;

typedef struct{			//struktura dwarf
	char meno[10];
	int jedlo;
	int pivo;
	int unava;
	int nuda;
}Dwarf ;

typedef enum{
	remeselnik=1, oddych, banik,kuchar,pivovarnik,alchimista
}action;												 


void vypisStorage(Storage *s1);
void init_Storage(Storage *s1);
void init_Dwarf( Dwarf d[],int pocet);		//DEKLARACIA KVOLI NIECOMU TO NAJPRV ISLO BEZ NEJ POTOM UZ NIE.... CURIOUS.
void vypisDwarf(Dwarf d[], int pocet);

int a_remeselnik(Dwarf d[],Storage *s1,int pocet,int vyber,int trpaslik);		//pocet je actually maximum trpaslikov, vyber zistuje ci to je hrac alebo NPC,
void a_oddych(Dwarf d[],Storage *s1,int pocet,int vyber,int trpaslik);						//int trpaslik udava ktory trpaslik vykona funkciu
int a_banik(Dwarf d[],Storage *s1,int pocet,int vyber,int trpaslik);
int a_kuchar(Dwarf d[],Storage *s1,int pocet,int vyber,int trpaslik);
int a_pivovarnik(Dwarf d[],Storage *s1,int pocet,int vyber,int trpaslik);			//tieto funkcie platia pre NPC
int a_alchimista(Dwarf d[],Storage *s1,int pocet,int vyber,int trpaslik);

int menu();								//potrebne doplnkove funkcie na vypis intra a outra, na delay
void intro();
void delay(unsigned int mseconds);
void outro();
void outro2();

int main() {
	Storage s1;					
	int action,mince=0,ruda=0,jedlo=0,pivo=0,trpaslik=0,pocet,turns=0,vyber=0;		//deklaracia struktur a premennych

	srand(time(NULL));				//randomize(zamiesam karty)
	//intro();
	
	printf("Kolko Trpaslikov chces?\n");
	scanf("%d", &pocet);
	*Dwarf d= (Dwarf d *) malloc(pocet*sizeof (*Dwarf d));
	
	init_Storage(&s1);
	vypisStorage(&s1);	//Inicializacia (Nacitam zaciatocne hodnoty pre Sklad) Vypis(Vypisem Hodnoty poloziek)
	printf("\n\n");
	init_Dwarf(d, pocet);
	vypisDwarf(d, pocet);
	
	printf("\n\n");				//prazdne riadky
	while(s1.mince<100 && turns<100){					//while s 2 podmienkami alebo sa dosiahne 100 minci na sklade alebo 100 turns
		vyber=0;
		turns++;
		vyber=menu();				//menu vola funkciu ktora vypise ktoru funkciu chce a vrati vybratu pre switch
		action=vyber;
		switch(action){			//tento switch uz ma setovany vyber na danom cisel which means, ze v akcii sa vyhodnoti ze vyber nie je nulovy a preto bude trpaslik numero 0
			case 1:
				mince=a_remeselnik(d,&s1,pocet,vyber,trpaslik);	//AKCIA remeselnik, vyraba mince z rudy, potrebuje nato pivo,jedlo. Doplnit funkcie. 100 krat nahodne vybrana funkcia
				system("pause");
			break;
			case 2:
				a_oddych(d,&s1,pocet,vyber,trpaslik);
				system("pause");
			break;
			case 3:
				ruda=a_banik(d,&s1,pocet,vyber,trpaslik);
				system("pause");
			break;
			case 4:
				jedlo=a_kuchar(d,&s1,pocet,vyber,trpaslik);
				system("pause");
			break;
			case 5:
				pivo=a_pivovarnik(d,&s1,pocet,vyber,trpaslik);
				system("pause");
			break;
			case 6:
				mince=a_alchimista(d,&s1,pocet,vyber,trpaslik);
				system("pause");
			break;
			default:
				printf("Neplatny vstup\n");
				system("pause");
			break;
		}
	}

	if(s1.mince>100)		//outro sa hra podla toho ktora podmienka bola dosiahnuta
		outro();
	else
		outro2();
	return 0;
}

void vypisStorage(Storage *s1){			//vypis
	printf("********Sklad********\n");
	printf("Jedla v sklade je: %d\n", s1->jedlo);
	printf("Piva v sklade je: %d\n", s1->pivo);
	printf("Rudy v sklade je: %d\n", s1->ruda);
	printf("Minci v sklade je: %d\n", s1->mince);
}

void init_Storage(Storage *s1){		//initializacia
 	s1->jedlo=50;
	s1->pivo=50;
	s1->ruda=5;
	s1->mince=70;
	
}

void init_Dwarf( Dwarf d[],int pocet){			
 	int i=0;
 	int j=0;
 	for (i=0;i<MAX_DWARF;i++){	
	d[i].jedlo=3;
	d[i].pivo=3;
	d[i].nuda=2;
	d[i].unava=2;
	}
}
void vypisDwarf(Dwarf d[],int pocet){
	int i=0;
	printf("********Trpaslik********\n");
	for(i=0;i<MAX_DWARF;i++){
	printf("Jedla u Trpaslika %d je: %d\n", i,d[i].jedlo);
	printf("Pivo u trpaslika %d je: %d\n", i,d[i].pivo);
	printf("Nuda trpaslika %d je: %d\n", i,d[i].nuda);
	printf("Unava trpaslika %d je: %d\n", i,d[i].unava);
	printf("\n");
	}
}


int a_remeselnik(Dwarf d[],Storage *s1,int pocet,int vyber,int trpaslik){
	HANDLE  hConsole;									//handle na konzolu aby som mohol menit farbu na error messages
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
	int mince=0;
	int i;
	i=trpaslik;
	if (vyber!=0)				//podmienka ak sa vybrala akcia pre hraca tak sa setne na 0 teda na hracskeho trpaslika
		i=0;
	if(s1->ruda < 1){
		SetConsoleTextAttribute(hConsole, 12);			//premenim na cervenu=errormessage
		printf("Nedostatok rudy na sklade\n");
		SetConsoleTextAttribute(hConsole, 7);			//spat na bielu
		return 0;
	}
	if(d[i].jedlo<1 || d[i].pivo<1){
		SetConsoleTextAttribute(hConsole, 12);
		printf("Nedostatok jedla alebo piva u trpaslika\n");	
		SetConsoleTextAttribute(hConsole, 7);
		return 0;
		}
	if(d[i].unava >=MAX_TIRED){
		SetConsoleTextAttribute(hConsole, 12);
		printf("Trpaslik prilis unaveny.\n");
		SetConsoleTextAttribute(hConsole, 7);
		return 0;
	}					//tieto vsetky nastanu ak je prilis unaveny alebo nema pit,jest
		
	d[i].jedlo--;
	d[i].pivo--;
	d[i].unava++;
	
	if(d[i].unava>MAX_TIRED/2)		//Ak je unaveny, vie spravit 1 mincu, inak vie urobit 2
		mince++;
	else
		mince +=2;
	
	s1->mince+=mince;
	
	if(vyber!=0){
	SetConsoleTextAttribute(hConsole, 2);			//premenim na zelenu,aby sa lahsie hladal vlastny trpaslik
	printf("Tvoj Trpaslik vykonal akciu remeslenik, akcia vratila: %d minci\n",i,mince);
	vypisStorage(s1);
	printf("\n");
	printf("******** Trpaslik %d ********""\n",i);			
	printf("Jedla u Trpaslika %d je: %d\n", i,d[i].jedlo);
	printf("Pivo u trpaslika %d je: %d\n", i,d[i].pivo);
	printf("Nuda trpaslika %d je: %d\n", i,d[i].nuda);
	printf("Unava trpaslika %d je: %d\n", i,d[i].unava);
	printf("\n");
	SetConsoleTextAttribute(hConsole, 7);			//spat na bielu
	}
	else{
	printf("Trpaslik %d Vykonal akciu remeslenik, akcia vratila: %d minci\n",i,mince);
	vypisStorage(s1);
	printf("\n");
	printf("******** Trpaslik %d ********\n",i);
	printf("Jedla u Trpaslika %d je: %d\n", i,d[i].jedlo);
	printf("Pivo u trpaslika %d je: %d\n", i,d[i].pivo);
	printf("Nuda trpaslika %d je: %d\n", i,d[i].nuda);
	printf("Unava trpaslika %d je: %d\n", i,d[i].unava);
	printf("\n");
	}
	return mince;
}

void a_oddych(Dwarf d[],Storage *s1,int pocet,int vyber,int trpaslik){
	HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int dopln_jedlo,dopln_pivo;
	int i;
	i=trpaslik;
	if (vyber!=0)		//ak bol vybraty a nie je to NPC tak si vybral hrac, cize to je nulty dwarf
		i=0;
	if(d[i].jedlo<INV_MAX_FOOD){
		dopln_jedlo=INV_MAX_FOOD-d[i].jedlo;
		d[i].jedlo +=dopln_jedlo ;
		s1->jedlo -=dopln_jedlo;
	}
	if(d[i].pivo<INV_MAX_BEER){
		dopln_pivo=INV_MAX_BEER-d[i].pivo;
		d[i].pivo +=dopln_pivo;
		s1->pivo -=dopln_pivo;
	}
	if(d[i].nuda>0)
		d[i].nuda=0;
	if(d[i].unava>0)
		d[i].unava=0;			//straight forward, oddychne si zo skladu zoberie tolko jedla a piva kolko vladze a pojde pracovat
		
	if(vyber!=0){
	SetConsoleTextAttribute(hConsole, 2);
	printf("Tvoj Trpaslik si oddychol, naplnil si inventar jedlom a hlavne pivom\n");
	vypisStorage(s1);
	printf("\n");
	printf("******** Tvoj Trpaslik ********""\n",i);
	printf("Jedla u Trpaslika %d je: %d\n", i,d[i].jedlo);
	printf("Pivo u trpaslika %d je: %d\n", i,d[i].pivo);
	printf("Nuda trpaslika %d je: %d\n", i,d[i].nuda);
	printf("Unava trpaslika %d je: %d\n", i,d[i].unava);
	printf("\n");
	SetConsoleTextAttribute(hConsole, 7);
	}
	else{
	printf("Trpaslik %d si oddychol, naplnil si inventar jedlom a hlavne pivom\n",i);
	vypisStorage(s1);
	printf("\n");
	printf("******** Trpaslik %d ********\n",i);
	printf("Jedla u Trpaslika %d je: %d\n", i,d[i].jedlo);
	printf("Pivo u trpaslika %d je: %d\n", i,d[i].pivo);
	printf("Nuda trpaslika %d je: %d\n", i,d[i].nuda);
	printf("Unava trpaslika %d je: %d\n", i,d[i].unava);
	printf("\n");
	}
}

int a_banik(Dwarf d[],Storage *s1,int pocet,int vyber,int trpaslik){
	HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int ruda=0;
	int i;
	i=trpaslik;
	if (vyber!=0)
		i=0;
	if(d[i].unava >=MAX_TIRED){
		SetConsoleTextAttribute(hConsole, 12);
		printf("Trpaslik prilis unaveny\n");
		SetConsoleTextAttribute(hConsole, 7);
		return 0;
	}
	if(d[i].jedlo<1 || d[i].pivo<1){
		SetConsoleTextAttribute(hConsole, 12);
		printf("Prilis malo jedla alebo piva u trpaslika\n");
		SetConsoleTextAttribute(hConsole, 7);	
		return 0;
	}
	d[i].jedlo--;
	d[i].pivo--;
	d[i].unava++;
	d[i].nuda++;
	
	if(d[i].unava>MAX_TIRED/2)
		ruda++;
	else
		ruda +=2;
	
	s1->ruda+=ruda;
	
if(vyber!=0){
	SetConsoleTextAttribute(hConsole, 2);
	printf("Tvoj Trpaslik vykonal akciu banik, akcia vratila: %d rudy\n",ruda);
	vypisStorage(s1);
	printf("\n");
	system("Color 02");
	printf("******** Tvoj Trpaslik ********""\n",i);
	printf("Jedla u Trpaslika %d je: %d\n", i,d[i].jedlo);
	printf("Pivo u trpaslika %d je: %d\n", i,d[i].pivo);
	printf("Nuda trpaslika %d je: %d\n", i,d[i].nuda);
	printf("Unava trpaslika %d je: %d\n", i,d[i].unava);
	printf("\n");
	SetConsoleTextAttribute(hConsole, 7);
	}
	else{
	printf("Trpaslik %d Vykonal akciu banik, akcia vratila: %d rudy\n",i,ruda);
	vypisStorage(s1);
	printf("\n");
	printf("******** Trpaslik %d ********\n",i);
	printf("Jedla u Trpaslika %d je: %d\n", i,d[i].jedlo);
	printf("Pivo u trpaslika %d je: %d\n", i,d[i].pivo);
	printf("Nuda trpaslika %d je: %d\n", i,d[i].nuda);
	printf("Unava trpaslika %d je: %d\n", i,d[i].unava);
	printf("\n");
	}
	return ruda;
}

int a_kuchar(Dwarf d[],Storage *s1,int pocet,int vyber,int trpaslik){
	HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int jedlo=0;
	int i;
	i=trpaslik;
	if(vyber!=0)
		i=0;
		
	if(d[i].unava >=MAX_TIRED){
		SetConsoleTextAttribute(hConsole, 12);
		printf("Trpaslik prilis unaveny\n");
		SetConsoleTextAttribute(hConsole, 7);
		return 0;
	}
	if(d[i].nuda >=MAX_NUDA){
		SetConsoleTextAttribute(hConsole, 12);
		printf("Trpaslik prilis unudeny\n");
		SetConsoleTextAttribute(hConsole, 7);
		return 0;
	}
	
	while(d[i].nuda<MAX_NUDA/2){
		if(s1->mince>0){
			jedlo=jedlo+3;	//POZOR 2 premenne menom jedlo, jednu pouzivam ako navrat funkcie, druha meni vlastnosti struktury
			s1->jedlo+=3;
			s1->mince--;	//Zaplati za suroviny, preto znizim mince, ale vyrobi tri * jedlo nie len raz
			d[i].nuda++;
				if(d[i].unava>0)
					d[i].unava--;	
		}
		else{
			jedlo++;
			s1->jedlo++;
			d[i].nuda++;
		}
	}
									//Vypisi
	if(vyber!=0){
	SetConsoleTextAttribute(hConsole, 2);
	printf("Tvoj Trpaslik vykonal akciu kuchar, akcia vratila: %d jedla\n",jedlo);
	vypisStorage(s1);
	printf("\n");
	printf("******** Tvoj Trpaslik ********""\n",i);
	printf("Jedla u Trpaslika %d je: %d\n", i,d[i].jedlo);
	printf("Pivo u trpaslika %d je: %d\n", i,d[i].pivo);
	printf("Nuda trpaslika %d je: %d\n", i,d[i].nuda);
	printf("Unava trpaslika %d je: %d\n", i,d[i].unava);
	printf("\n");
	SetConsoleTextAttribute(hConsole, 7);
	}
	else{
	printf("Trpaslik %d Vykonal akciu kuchar, akcia vratila: %d jedla\n",i,jedlo);
	vypisStorage(s1);
	printf("\n");
	printf("******** Trpaslik %d ********\n",i);
	printf("Jedla u Trpaslika %d je: %d\n", i,d[i].jedlo);
	printf("Pivo u trpaslika %d je: %d\n", i,d[i].pivo);
	printf("Nuda trpaslika %d je: %d\n", i,d[i].nuda);
	printf("Unava trpaslika %d je: %d\n", i,d[i].unava);
	printf("\n");
	}
	
	return jedlo;		
}

int a_pivovarnik(Dwarf d[],Storage *s1,int pocet,int vyber,int trpaslik){
		HANDLE  hConsole;
    	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		int pivo=0;
		int i;
		i=trpaslik;
		if(vyber!=0)
			i=0;
		
		while(d[i].nuda!=0){
			if(s1->mince==0){
			SetConsoleTextAttribute(hConsole, 12);
			printf("Nedostatok minci na sklade na vyrobu piva\n");
			SetConsoleTextAttribute(hConsole, 7);
			break;
			}
			else{
			pivo+=1;
			s1->pivo+=pivo;
			d[i].nuda--;
			s1->mince--;
			}
		}
	
	if(vyber!=0){
	SetConsoleTextAttribute(hConsole, 2);
	printf("Tvoj Trpaslik vykonal akciu pivovarnik, akcia vratila: %d piva\n",pivo);
	vypisStorage(s1);
	printf("\n");
	printf("******** Tvoj Trpaslik ********""\n",i);
	printf("Jedla u Trpaslika %d je: %d\n", i,d[i].jedlo);
	printf("Pivo u trpaslika %d je: %d\n", i,d[i].pivo);
	printf("Nuda trpaslika %d je: %d\n", i,d[i].nuda);
	printf("Unava trpaslika %d je: %d\n", i,d[i].unava);
	printf("\n");
	SetConsoleTextAttribute(hConsole, 7);
	}
	else{
	printf("Trpaslik %d Vykonal akciu pivovarnik, akcia vratila: %d piva\n",i,pivo);
	vypisStorage(s1);
	printf("\n");
	printf("******** Trpaslik %d ********\n",i);
	printf("Jedla u Trpaslika %d je: %d\n", i,d[i].jedlo);
	printf("Pivo u trpaslika %d je: %d\n", i,d[i].pivo);
	printf("Nuda trpaslika %d je: %d\n", i,d[i].nuda);
	printf("Unava trpaslika %d je: %d\n", i,d[i].unava);
	printf("\n");
	}
	
	return pivo;
}

int a_alchimista(Dwarf d[],Storage *s1,int pocet,int vyber,int trpaslik){		//alchimia 50 percent sanca ze sa podari zobere pivo jedlo a rudu, ak sa podari 10 minci
	HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int mince=0;
	int i;
	int nahoda;			//nahoda udava ci sa akcia alchimistu podarila alebo nie
	nahoda=rand() %2;
	i=trpaslik;
	if (vyber!=0)				//podmienka ak sa vybrala akcia pre hraca tak sa setne na 0 teda na hracskeho trpaslika
		i=0;
	if(s1->ruda < 1){
		SetConsoleTextAttribute(hConsole, 12);
		printf("Nedostatok rudy na sklade\n");
		SetConsoleTextAttribute(hConsole, 7);
		return 0;
	}
	if(d[i].jedlo < 1){
		SetConsoleTextAttribute(hConsole, 12);
		printf("Nedostatok jedla u Trpaslika\n");
		SetConsoleTextAttribute(hConsole, 7);
		return 0;
	}
	if(d[i].pivo < 1){
		SetConsoleTextAttribute(hConsole, 12);
		printf("Nedostatok piva u trpaslika\n");
		SetConsoleTextAttribute(hConsole, 7);
		return 0;
		}
	if(d[i].unava>=MAX_TIRED){
		SetConsoleTextAttribute(hConsole, 12);
		printf("Trpaslik prilis unaveny\n");
		SetConsoleTextAttribute(hConsole, 7);
		return 0;
	}
	if(nahoda==0){
		d[i].pivo--;
		d[i].jedlo--;
		d[i].unava++;
		s1->ruda--;
		printf("Alchimia Zlyhala\n");
	}
	if(nahoda==1){
		d[i].pivo--;
		d[i].jedlo--;
		d[i].unava++;
		s1->ruda--;
		mince=mince+ORE_ALCHIM;
		s1->mince+=ORE_ALCHIM;
		printf("Alchimia vydarena\n");
	}
	
	if(vyber!=0){
	SetConsoleTextAttribute(hConsole, 2);
	printf("Tvoj Trpaslik vykonal akciu alchimista, akcia vratila: %d minci\n",mince);
	vypisStorage(s1);
	printf("\n");
	printf("******** Tvoj Trpaslik ********""\n",i);
	printf("Jedla u Trpaslika %d je: %d\n", i,d[i].jedlo);
	printf("Pivo u trpaslika %d je: %d\n", i,d[i].pivo);
	printf("Nuda trpaslika %d je: %d\n", i,d[i].nuda);
	printf("Unava trpaslika %d je: %d\n", i,d[i].unava);
	printf("\n");
	SetConsoleTextAttribute(hConsole, 7);
	}
	else{
	printf("Trpaslik %d Vykonal akciu alchimista, akcia vratila: %d piva\n",i,mince);
	vypisStorage(s1);
	printf("\n");
	printf("******** Trpaslik %d ********\n",i);
	printf("Jedla u Trpaslika %d je: %d\n", i,d[i].jedlo);
	printf("Pivo u trpaslika %d je: %d\n", i,d[i].pivo);
	printf("Nuda trpaslika %d je: %d\n", i,d[i].nuda);
	printf("Unava trpaslika %d je: %d\n", i,d[i].unava);
	printf("\n");
	}
	
	
	return mince;
}


int menu(){				//vypis menu na vyber akcie
	int akcia=0;
	printf("Vyber si akciu pre svojho trpaslika\n");
	printf("[1]Remeselnik     [2]Oddych    [3]Banik     [4]Kuchar     [5]Pivovarnik     [6]Alchimista\n");
	scanf("%d", &akcia);
	return akcia;
}

//int central()

void intro(){
	mciSendString("open hobbit.wav alias hobbit",NULL,0,NULL);
	mciSendString("play hobbit",NULL,0,NULL);
	COORD coord;			//coord su suradnice kde dam kurzor aby to vypisovalo printf z tej pozicie.
	coord.X = 42;
	coord.Y = 15;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	char text[] = "No country for old dwarves.";
  	int i;
													
 	for (i = 0; i < strlen(text); i++) {		//tento for cyklus vypisuje po znaku jeden string
    	printf("%c", text[i]);
    	fflush( stdout );
    	usleep(245000);	
  	}
  	
  	printf("\n");
	delay(10000);
	coord.X = 40;
	coord.Y = 25;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	system("pause");
	system("cls");
	coord.X = 15;
	coord.Y = 15;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	
	char text2[] = "Far, far below the deepest delving of the Dwarves, the world is gnawed by nameless things.";
  	int j;

 	for (j = 0; j < strlen(text2); j++) {
    	printf("%c", text2[j]);
    	fflush( stdout );
    	usleep(122500);	
  	}
	delay(10000);
	coord.X = 40;
	coord.Y = 25;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	system("pause");
	mciSendString("pause hobbit",NULL,0,NULL);
}

void outro(){
	system("cls");
	COORD coord;
	coord.X = 42;
	coord.Y = 15;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	char text[] = "You acquired enough gold to summon Smaug.";
  	int i;

 	for (i = 0; i < strlen(text); i++) {
    	printf("%c", text[i]);
    	fflush( stdout );						//tento for vypisuje posebe string
    	usleep(245000);	
  	}
	mciSendString("open death.wav alias death",NULL,0,NULL);
	mciSendString("play death",NULL,0,NULL);
	delay(5000);
	system("pause");
}

void outro2(){
	system("cls");
	COORD coord;
	coord.X = 42;
	coord.Y = 15;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	char text[] = "You survived for a 100 days Good job.";
  	int i;

 	for (i = 0; i < strlen(text); i++) {
    	printf("%c", text[i]);
    	fflush( stdout );						//tento for vypisuje posebe string
    	usleep(245000);	
  	}
}

void delay(unsigned int mseconds)			//vlastna funckia na delay lebo toto sadly nie je Turbo Pascal :D (sarcasm)?
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}
