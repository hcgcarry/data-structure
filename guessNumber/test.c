#include<stdio.h>
#include<string.h>
#include "guess.h"
#include<stdlib.h>
#include <windows.h>

#pragma warning(disable:4996)
//#define sizeOfPredict 10
//#define guessNumSize 10 
#define sizeOfPredict 78763
#define guessNumSize 78763

void createRandomBigNumber(void);
char *readBigNumberFromFile(char *filename);
int main(void) {
	//createRandomBigNumber();
	int i,goodCount=0 ,badCount=0;
	int sizeOfNum = 0;
	int sizeOfGuessNum = 0;
	char *guessNum;
	char clue[10]="0A0B";
	char *num = readBigNumberFromFile("bignumber.txt");
	//sizeOfNum = strlen(num);
	//char testnum[guessNumSize] = "0123456789";
	char testnum[guessNumSize] = "9009835280";
	
	while (goodCount != guessNumSize) {
		goodCount = 0;
		badCount = 0;
		guessNum=guess(clue);
		sizeOfGuessNum = strlen(guessNum);
		for (i=0; i < guessNumSize; i++) {
			if (num[i] == guessNum[i]) {
			//if (testnum[i] == guessNum[i]) {
				goodCount++;
			}
			else {
				badCount++;
			}

		}
		sprintf(clue, "%dA%dB", goodCount, badCount);
		
		
	}
	printf("final predict:%s \n", guessNum);

}

void createRandomBigNumber(void) {
	FILE *file;
	int error = 0;
	char input[sizeOfPredict];
	char *tmp=malloc(1000*sizeof(char));
	int pad = 0;
	int size = 0;
	input[0] = '\0';
	sprintf(tmp, "%d",rand());
	while ((strlen(tmp) + strlen(input)) < sizeOfPredict) {
		sprintf(tmp, "%d",rand());
		strcat(input, tmp);

	}
	pad= sizeOfPredict-strlen(input);
	strncat(input, tmp, pad);
	size = strlen(input);

	file = fopen("bignumber.txt","w");
	error=fprintf(file, "%s", input);

	if (error == EOF) {
		printf("file write error");

	}
	fclose(file);

}

char *readBigNumberFromFile(char *filename) {
	char *readString=malloc(sizeOfPredict*sizeof(char));
	FILE *file;
	file = fopen(filename, "r");
	fscanf(file, "%s", readString);
	return readString;

}
