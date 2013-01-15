//ETGame.c	
//
// 1. Plays an interval

/*
	1. "Welcome to the ear game"
	2. <randomly choose interval, create .csd, play .csd>
	3. Ask the user if they want the answer or to hear it again or quit
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define ROOT 60
#define LENGTH 2

void make_csd(FILE* csd,  int firstnote, int secondnote, int length, int startime);
void answer(int dice);

void cleanup();

	int main(){
	FILE* csd;
	int dice, offset, startime;
	int lowNote = 0, highNote = 0;
	int ui; 
	char dummy;	
	int firstInterval;

	system("clear");
	cleanup();
	
	restart:
	
	printf("\nWelcome to The Ear Game!\n");
	printf("\nWould you like to hear the interval (1) ascending (2) descending (3) harmonically\n");
	printf("(0) quit\n");
	scanf("%d",&firstInterval);

	srand ( time(NULL) );
	dice   = (rand() % 12) + 1;//Dice is interval size in semitons
	offset = (rand() % 12) + 1;//first note
	
	lowNote  = dice + ROOT;
	highNote = dice + ROOT + offset;

	
	
	csd = fopen("ascending.csd", "w");
	make_csd(csd, lowNote, highNote, LENGTH, LENGTH);
	fclose(csd);

	csd = fopen("descending.csd", "w");
	make_csd(csd, highNote, lowNote, LENGTH, LENGTH);
	fclose(csd);

	csd = fopen("harmonically.csd", "w");
	make_csd(csd, lowNote, highNote, LENGTH, 0);
	fclose(csd);

	switch(firstInterval){

		        case 0: 
				
					printf("Thank you for playing\n");
					cleanup();
					return 0; 
					break;
				case 1: 
					
					system("csound -d -odac  ascending.csd"); 
					goto prompt;
					break;
				case 2:
					
					system("csound -d -odac  descending.csd"); 
					goto prompt;
					break;
				case 3:
				
					system("csound -d -odac  harmonically.csd"); 
					goto prompt;
					break;	
				case 4:
				
					printf("The answer was %d semitones\n", dice);
					cleanup();
					scanf("%c",&dummy);
					goto restart;			
					break;
				default:
					printf("Thank you for playing\n");
					cleanup();
					return 0; 
			}

	prompt:
	system("clear");
	printf("Would you like to hear it again (1) ascending (2) descending (3) harmonically\n");
	printf("(4)TELL ME THE ANSWER (0) quit\n");
	
	scanf("%d", &ui);	

		  switch(ui){

		        case 0: 
				
					printf("Thank you for playing\n");
					cleanup();
					return 0; 
					break;
				case 1: 
					
					system("csound -d -odac  ascending.csd"); 
					goto prompt;
					break;
				case 2:
					
					system("csound -d -odac  descending.csd"); 
					goto prompt;
					break;
				case 3:
				
					system("csound -d -odac  harmonically.csd"); 
					goto prompt;
					break;	
				case 4:
					
					answer(offset);
					cleanup();
					scanf("%c",&dummy);
					goto restart;			
					break;
				default:
					printf("Thank you for playing\n");
					cleanup();
					return 0; 
			}
	}

void make_csd(FILE* csd,  int firstnote, int secondnote, int length, int startime) {
	fprintf(csd, "<CsoundSynthesizer>\n");  
	fprintf(csd, "<CsOptions>\n");
	fprintf(csd, "</CsOptions>\n");
	fprintf(csd, "<CsInstruments>\n");	
	fprintf(csd, "0dbfs = 1\n");		
	fprintf(csd, "instr 1\n");
	fprintf(csd, "kenv expseg .0001, .05, .8, p3 - .070 , .2, .02, .001\n"); 
	fprintf(csd, "a1 oscil3 kenv, cpsmidinn(p5), 1\n");
	fprintf(csd, "outs a1, a1\n");
	fprintf(csd, "endin\n");
	fprintf(csd, "</CsInstruments>\n");
	fprintf(csd, "<CsScore>\n");
	fprintf(csd, "f 1 0 8192 10 1\n");
	fprintf(csd, "i 1 0 %d 1 %d \n" ,  length,  firstnote);
	fprintf(csd, "i 1 %d .  . %d \n",startime, secondnote);	
	fprintf(csd, "f 0 %d\n", length);
	fprintf(csd, "</CsScore>\n");
	fprintf(csd, "</CsoundSynthesizer>\n");
}

void cleanup(){
	system("rm -f ascending.csd");
	system("rm -f descending.csd");
	system("rm -f harmonically.csd");
}

void answer(int offset){

	switch (offset) {

		case 1:
		printf("\nThe answer is a minor second.");
		break;

		case 2:
		printf("\nThe answer is a major second.");
		break;

		case 3:
		printf("\nThe answer is a minor third.");
		break;

		case 4:
		printf("\nThe answer is a major third.");
		break;

		case 5:
		printf("\nThe answer is a perfect fourth.");
		break;

		case 6:
		printf("\nThe answer is a tritone.");
		break;

		case 7:
		printf("\nThe answer is a perfect fifth.");
		break;

		case 8:
		printf("\nThe answer is a minor sixth.");
		break;

		case 9:
		printf("\nThe answer is a major sixth.");
		break;

		case 10:
		printf("\nThe answer is a minor seventh.");
		break;

		case 11:
		printf("\nThe answer is a major seventh.");
		break;

		case 12:
		printf("\nThe answer is an octave.");
		break;


	}




}