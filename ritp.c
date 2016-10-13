#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define yta_y 110
#define yta_x 45


/*
FIXAT/Uppdaterat 
2016-10-03: 
	- Lagt in break i switch-satserna, för korrekt funktion av penselbyte, markörflyttning
	- Sparfunktion - sparar till txt-fil i samma mapp
	- Fler penslar (+, grader-tecken)
	- Färgbyte av ritytan
	- q: Avsluta

ATT göra
	- Ladda sparade filer - ev svårt om filen inte samma rader/kolumner
	- Penselstorlek
	- Markör för sudded, skitsvårt att veta var man är annars
	- Går det fixa färg per tecken?
	- Bättre meny
	- Mer penslar
	- Borderstopp
	- Styr upp X/Y - oklart vad som är vad i array
*/


//ypos xpos är startposition för markören/penseln
int ypos = yta_y/2;
int xpos = yta_x/2;
//den pensel man börjar med:
int pensel = 'x';

//array som håller ritytan:
int rityta[yta_y][yta_x];

//funktion som matar ut ritytan på skärmen, behöver ej parameter.
void rita_yta(){
	int charcount = 0;
	system("cls");
	for(int x=0;x<yta_x;x++){
		for(int y=0;y<yta_y;y++){
			printf("%c", rityta[y][x]);
			charcount++;
			if (charcount  == yta_y){
				printf("\n");
				charcount = 0;
			}
		}
	} 
}

//funktion som frågar efter filnamn, och sparar den ritade ytan till denna, i textform
_Bool spara_fil(){
	char filnamn[20]/* , s[1] */;
	system("cls");
	printf("Ange filnamn: ");
	scanf("%s", filnamn);
	//strcat lägger till en textsträng i slutet av en annan - här skrivs .txt till det inmatade filnamnet
	strcat(filnamn, ".txt");
	FILE * fil = fopen(filnamn, "w");
	int charcount = 0;
	/* forstatserna fungerar på samma sätt som i funktionen rita_yta, som ritar ut ritytan på skärmen
	dock är printf utbytt till fputc, för skrivning till filen
	*/
	for(int x=0;x<yta_x;x++){
		for(int y=0;y<yta_y;y++){
			//fputc skriver ett enstaka tecken till en fil (jämför putc)
			fputc(rityta[y][x], fil);
			charcount++;
			if (charcount  == yta_y){
				//newline skrivs till filen om bordern på ritytan är nådd
				fputc('\n', fil);
				charcount = 0;
			}
		}
	} 
	//stänger filen när den är färdigskriven
	fclose(fil);
	printf("\nFil Sparad till %s\n",filnamn);
	/*för att ritytan inte ska ritas ut automatiskt efter filsparning så anropas systemkommandot pause 
	"tryck på tangent för att fortsätta..*/
	system("pause");
}

int main(){
	int knapp, int176 = 176;//176 är värdet för grader-tecken
	char border = '*', tom = ' '; //för ritytans border, samt tomma ytor
	//Sätter rätt tecken till arrayen som håller ritytan: om index är på en gräns så ritas border-tecknet
	for(int x=0;x<yta_x;x++){
		for(int y=0;y<yta_y;y++){
			if(x == 0 || x == yta_x-1){
				rityta[y][x] = border;
			}
			else if(y == 0 || y == yta_y-1){
				rityta[y][x] = border;
			}
			else {
				rityta[y][x] = tom;
			}
		}
	}
	//startposition för penseln/markören ritas in i arrayen
	rityta[ypos][xpos] = pensel;
	//Flytta markör med WASD
	printf("Ritprogram!\nTryck på valfri? tangent för att starta!");
	while(1){
		//knapp sätts till den knapp som användaren trycker på, getch väntar ej på returslag, tangentslaget läses direkt
		knapp = getch();
		switch(knapp){ //OBS viktigt med break i case-villkoren
			case 'q':
				return 0;
				break;
			case 'k':
				spara_fil(); //anropar funktion för att spara den ritade ytan
				break;
			case 'b':
				pensel = '.';
				break;
			case 'c':
				pensel = '#';
				break;
			case 'v':
				pensel = 'x';
				break;
			case 'x':
				pensel = ' ';
				break;
			case 'z':
				pensel = int176;
				break;
			case '+':
				pensel = '+';
				break;
			case '1':
				system("color 4");
				break;
			case '2':
				system("color 2");
				break;
			case '3':
				system("color 5");
				break;
			case '4':
				system("color 7"); //vit
				break;
			case '5':
				system("color 9"); //blå
				break;
			case 'a': //vänster
				ypos--;
				break;
			case 'd': //höger
				ypos++;
				break;
				//rita_yta();
			case 's': //ner
				xpos++;
				break;
				//rita_yta();
			case 'w': //upp
				xpos--;
				break;
				//rita_yta();
			default:
				xpos = xpos;
				ypos = ypos;
				break;
		}
		rityta[ypos][xpos] = pensel;
		rita_yta();
		//"meny":
		printf("Y %d  X %d Pensel: %c",xpos, ypos, pensel);
		printf("\nPenslar: [b: .] | [c: #] | [v: x] [z: %c] [+: +] [x: sudd]", int176);
		printf("\nFärg: [1:Röd] [2:Grön] [3:Lila] [4:Vit] [5:Blå]");
		printf("\n[q: Avsluta] [k: Spara fil] [l: Ladda fil (WIP)]");
	}
}