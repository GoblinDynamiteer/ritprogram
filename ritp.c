#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define yta_y 110
#define yta_x 45


/*
FIXAT/Uppdaterat 
2016-10-03: 
	- Lagt in break i switch-satserna, f�r korrekt funktion av penselbyte, mark�rflyttning
	- Sparfunktion - sparar till txt-fil i samma mapp
	- Fler penslar (+, grader-tecken)
	- F�rgbyte av ritytan
	- q: Avsluta

ATT g�ra
	- Ladda sparade filer - ev sv�rt om filen inte samma rader/kolumner
	- Penselstorlek
	- Mark�r f�r sudded, skitsv�rt att veta var man �r annars
	- G�r det fixa f�rg per tecken?
	- B�ttre meny
	- Mer penslar
	- Borderstopp
	- Styr upp X/Y - oklart vad som �r vad i array
*/


//ypos xpos �r startposition f�r mark�ren/penseln
int ypos = yta_y/2;
int xpos = yta_x/2;
//den pensel man b�rjar med:
int pensel = 'x';

//array som h�ller ritytan:
int rityta[yta_y][yta_x];

//funktion som matar ut ritytan p� sk�rmen, beh�ver ej parameter.
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

//funktion som fr�gar efter filnamn, och sparar den ritade ytan till denna, i textform
_Bool spara_fil(){
	char filnamn[20]/* , s[1] */;
	system("cls");
	printf("Ange filnamn: ");
	scanf("%s", filnamn);
	//strcat l�gger till en textstr�ng i slutet av en annan - h�r skrivs .txt till det inmatade filnamnet
	strcat(filnamn, ".txt");
	FILE * fil = fopen(filnamn, "w");
	int charcount = 0;
	/* forstatserna fungerar p� samma s�tt som i funktionen rita_yta, som ritar ut ritytan p� sk�rmen
	dock �r printf utbytt till fputc, f�r skrivning till filen
	*/
	for(int x=0;x<yta_x;x++){
		for(int y=0;y<yta_y;y++){
			//fputc skriver ett enstaka tecken till en fil (j�mf�r putc)
			fputc(rityta[y][x], fil);
			charcount++;
			if (charcount  == yta_y){
				//newline skrivs till filen om bordern p� ritytan �r n�dd
				fputc('\n', fil);
				charcount = 0;
			}
		}
	} 
	//st�nger filen n�r den �r f�rdigskriven
	fclose(fil);
	printf("\nFil Sparad till %s\n",filnamn);
	/*f�r att ritytan inte ska ritas ut automatiskt efter filsparning s� anropas systemkommandot pause 
	"tryck p� tangent f�r att forts�tta..*/
	system("pause");
}

int main(){
	int knapp, int176 = 176;//176 �r v�rdet f�r grader-tecken
	char border = '*', tom = ' '; //f�r ritytans border, samt tomma ytor
	//S�tter r�tt tecken till arrayen som h�ller ritytan: om index �r p� en gr�ns s� ritas border-tecknet
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
	//startposition f�r penseln/mark�ren ritas in i arrayen
	rityta[ypos][xpos] = pensel;
	//Flytta mark�r med WASD
	printf("Ritprogram!\nTryck p� valfri? tangent f�r att starta!");
	while(1){
		//knapp s�tts till den knapp som anv�ndaren trycker p�, getch v�ntar ej p� returslag, tangentslaget l�ses direkt
		knapp = getch();
		switch(knapp){ //OBS viktigt med break i case-villkoren
			case 'q':
				return 0;
				break;
			case 'k':
				spara_fil(); //anropar funktion f�r att spara den ritade ytan
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
				system("color 9"); //bl�
				break;
			case 'a': //v�nster
				ypos--;
				break;
			case 'd': //h�ger
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
		printf("\nF�rg: [1:R�d] [2:Gr�n] [3:Lila] [4:Vit] [5:Bl�]");
		printf("\n[q: Avsluta] [k: Spara fil] [l: Ladda fil (WIP)]");
	}
}