#pragma warning(disable:4996)
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
#define randCharSize 10 
//#define predictNumSize  78763
#define predictNumSize  10
#define padNumber "0000000000"
int currentPredictSize=0,recordStep = 0;
int durningTreeTravelPreGoodCount,durningTreeTravel=0;
int biasDueToCorrect = 0;
char *predict,*randNum;
int preGoodCount = 0, preBadCount = 0;
int iniPredictTop = 0;
int goodCount = 0, badCount = 0;
int  goodDifferent = 0;
int goodArrayTop = 0, badArrayTop = 0;
int lastTunePredictIndex = 0;
int timeToTuneThree = 1;
int status = 0;
int index = 0;
int sizeOfBadList = 0;

int iniCorrectBias = 0;
//initial predict

typedef struct DifferentStruct *DifferentStructPtr;
typedef struct DifferentStruct{
	int goodDifferent;
	int end,deep, goodElementPositionArray[3];
	DifferentStructPtr  zeroALink;
	DifferentStructPtr  oneALink;
	DifferentStructPtr  twoALink;
	DifferentStructPtr  threeALink;
} goodDif;
typedef struct badList *badListPtr;
typedef struct badList {
	int indexOfPredict;
	badListPtr next;
} badLi;


badListPtr badListRoot,badListTailPtr;


char predictMinusDigit(char digit);
char predictAddDigit(char digit);
badListPtr createBadListElement(int indexOfPredict);
DifferentStructPtr createDifferentStrucuElement(int goodDifferent , int deep);
DifferentStructPtr curTreePtr ,buildTreeTmpPtr,diffTreeInitialPtr;
void tuneThreeDigit(badListPtr root);
void deleteBadListElement(badListPtr root, badListPtr parent, badListPtr deletedElement);

int cutPadNum;
int firstTimeBadListSizeLessthree = 0;
char goodCountTmp[10];
int i;

char *guess(char *clue){
	for (i = 0; clue[i] != 'A'; i=i+1) {
		goodCountTmp[i] = clue[i];
	}
	goodCountTmp[i] = '\0';
	goodCount = strtol(goodCountTmp, NULL, 10);

	if (durningTreeTravel == 1) {
		goodDifferent = goodCount - durningTreeTravelPreGoodCount;
	}
	else {
		goodDifferent = goodCount - preGoodCount;
	}
	if (biasDueToCorrect > 0) {
		goodDifferent = goodDifferent - biasDueToCorrect;
	}
	if (iniCorrectBias == 1) {
		goodDifferent = goodDifferent - 1;
		iniCorrectBias = 0;
	}
	//badlist size 小於三 的第一次還是要扣掉correct predict 所產生的bias
	if (firstTimeBadListSizeLessthree==1) {
		biasDueToCorrect = 0;
		firstTimeBadListSizeLessthree = 0;

	}
	printf("step %d ", recordStep);
	printf("predict:%s ", predict);
	printf("goodcount:%d ,goodDifferent: %d \n ",goodCount, goodDifferent);
	
	//initial predict and tree
	if (recordStep ==0 ) {
		predict = malloc(predictNumSize * sizeof(char));
		predict[0] = '\0';
		//predict
		while (strlen(predict) < predictNumSize) {
			currentPredictSize = strlen(predict);
			if ((currentPredictSize + randCharSize) > predictNumSize) {
				/*
				cutRandom=(int)(pow(10, predictNumSize - currentPredictSize));
				randNum = (char)rand();
				if (strlen(randNum) < randCharSize) {
					strncat(predict, randNum);
				}
				*/
				cutPadNum = predictNumSize - currentPredictSize;
				
				strncat(predict, padNumber,cutPadNum);
			}
			else {
				strcat(predict, padNumber);
			}
		}
		////////////////build the tree
		DifferentStructPtr tmp;
		//zero deep 
		diffTreeInitialPtr = createDifferentStrucuElement(0,0 );
		curTreePtr = diffTreeInitialPtr;

		tmp = createDifferentStrucuElement(0 ,1 );
		tmp->end = 1;
		diffTreeInitialPtr->zeroALink=tmp;

		tmp = createDifferentStrucuElement(1 ,1 );
		diffTreeInitialPtr->oneALink=tmp;

		tmp = createDifferentStrucuElement(2, 1);
		diffTreeInitialPtr->twoALink=tmp;

		tmp = createDifferentStrucuElement(3, 1);
		tmp->end = 1;
		tmp->goodElementPositionArray[0] = 1;
		tmp->goodElementPositionArray[1] = 1;
		tmp->goodElementPositionArray[2] = 1;
		diffTreeInitialPtr->threeALink=tmp;
		// 1 deep 1A
		buildTreeTmpPtr = diffTreeInitialPtr->oneALink;

		tmp = createDifferentStrucuElement(0, 2);
		tmp->end = 1;
		tmp->goodElementPositionArray[0] = -1;
		buildTreeTmpPtr->zeroALink = tmp;

		tmp = createDifferentStrucuElement(1, 2);
		buildTreeTmpPtr->oneALink = tmp;

		tmp = createDifferentStrucuElement(2, 2);
		buildTreeTmpPtr->twoALink= tmp;

		//2 deep 1A left 1
		buildTreeTmpPtr = buildTreeTmpPtr->oneALink;

		tmp = createDifferentStrucuElement(0, 3);
		tmp->end = 1;
		//-1 means old digit is right
		tmp->goodElementPositionArray[1] = -1;
		buildTreeTmpPtr->zeroALink = tmp;

		tmp = createDifferentStrucuElement(1, 3);
		tmp->end = 1;
		tmp->goodElementPositionArray[2] = 1;
		buildTreeTmpPtr->oneALink= tmp;

		tmp = createDifferentStrucuElement(2, 3);
		tmp->end = 1;
		tmp->goodElementPositionArray[1] = 1;
		tmp->goodElementPositionArray[2] = 1;
		buildTreeTmpPtr->twoALink= tmp;

		// 2 deep 2A left 1
		buildTreeTmpPtr = diffTreeInitialPtr->oneALink->twoALink;
		tmp = createDifferentStrucuElement(1, 3);
		tmp->end = 1;
		tmp->goodElementPositionArray[0] = 1;
		tmp->goodElementPositionArray[1] = -1;
		buildTreeTmpPtr->oneALink= tmp;

		tmp = createDifferentStrucuElement(2, 3);
		tmp->end = 1;
		tmp->goodElementPositionArray[0] = 1;
		tmp->goodElementPositionArray[2] = 1;
		buildTreeTmpPtr->twoALink= tmp;

		tmp = createDifferentStrucuElement(3, 3);
		tmp->end = 1;
		tmp->goodElementPositionArray[0] = 1;
		tmp->goodElementPositionArray[1] = 1;
		tmp->goodElementPositionArray[2] = 1;
		buildTreeTmpPtr->threeALink= tmp;
		// 1 deep 2 A
		buildTreeTmpPtr = diffTreeInitialPtr->twoALink;
		tmp = createDifferentStrucuElement(1, 2);
		buildTreeTmpPtr->oneALink= tmp;

		tmp = createDifferentStrucuElement(2, 2);
		tmp->end = 1;
		tmp->goodElementPositionArray[1] = 1;
		tmp->goodElementPositionArray[2] = 1;
		buildTreeTmpPtr->twoALink= tmp;

		tmp = createDifferentStrucuElement(3, 2);
		tmp->end = 1;
		tmp->goodElementPositionArray[0] = 1;
		tmp->goodElementPositionArray[1] = 1;
		tmp->goodElementPositionArray[2] = 1;
		buildTreeTmpPtr->threeALink= tmp;
		//2 deep 1A under 1deep 2A
		buildTreeTmpPtr = diffTreeInitialPtr->twoALink->oneALink;
		tmp = createDifferentStrucuElement(0, 3);
		tmp->end = 1;
		tmp->goodElementPositionArray[0] = -1;
		tmp->goodElementPositionArray[1] = -1;
		buildTreeTmpPtr->zeroALink= tmp;

		tmp = createDifferentStrucuElement(1, 3);
		tmp->end = 1;
		tmp->goodElementPositionArray[0] = -1;
		tmp->goodElementPositionArray[2] = 1;
		buildTreeTmpPtr->oneALink= tmp;

		tmp = createDifferentStrucuElement(2, 3);
		tmp->end = 1;
		tmp->goodElementPositionArray[0] = -1;
		tmp->goodElementPositionArray[1] = 1;
		tmp->goodElementPositionArray[2] = 1;
		buildTreeTmpPtr->twoALink= tmp;

		
	}
	//first return back from pc2
	else if (recordStep == 1) {
		predict[iniPredictTop] = predictAddDigit(predict[iniPredictTop]);
		iniPredictTop++;
	}
	// tune from first to last to check whick digit is good
	else if (iniPredictTop < predictNumSize) {
		if (goodDifferent == 0) {
			badListPtr tmp;
			//initial badlistroot
			if (badListRoot == NULL) {
				tmp = createBadListElement(iniPredictTop - 1);
				badListRoot = tmp;
				badListTailPtr=badListRoot;
			}
			else {
				tmp = createBadListElement(iniPredictTop - 1);
				badListTailPtr->next = tmp;
				badListTailPtr = tmp;
			}
		}
		else if (goodDifferent == -1) {
			predict[iniPredictTop - 1]= predictMinusDigit(predict[iniPredictTop - 1]);
			iniCorrectBias = 1;
		}

		predict[iniPredictTop] = predictAddDigit(predict[iniPredictTop]);
		iniPredictTop++;
	}


	// last check of above action 
	else if (iniPredictTop == predictNumSize) {
		badListPtr tmp;
		if (goodDifferent == 0) {
			tmp = createBadListElement(iniPredictTop - 1);
			badListTailPtr->next = tmp;
			badListTailPtr = tmp;
		}
		if (goodDifferent == -1) {
			predict[iniPredictTop-1]=predictMinusDigit(predict[iniPredictTop - 1]);
		}
		//ini over 
		iniPredictTop++;

	}

		
	//deal with badArray initial
	else if(timeToTuneThree ==1){
		tuneThreeDigit(badListRoot);
	}
	else if (sizeOfBadList < 3) {
		if (goodDifferent == 1) {
			deleteBadListElement(badListRoot,NULL,badListRoot);
		}
		if (sizeOfBadList == 0) {
			printf("finish ");
		}
		//size == 1 or 2
		else{
			predict[badListRoot->indexOfPredict]=predictAddDigit(predict[badListRoot->indexOfPredict]);

		}
	}
	else if (timeToTuneThree == 0) {
		badListPtr badListTmp;

		//check 0A
		if (curTreePtr->zeroALink!=NULL && goodDifferent == curTreePtr->zeroALink->goodDifferent) {
			curTreePtr = curTreePtr->zeroALink;
		}
		//check 1A
		else if (curTreePtr->oneALink!=NULL && goodDifferent == curTreePtr->oneALink->goodDifferent) {
			curTreePtr = curTreePtr->oneALink;
		}
		//check 2A
		else if (curTreePtr->twoALink!=NULL && goodDifferent == curTreePtr->twoALink->goodDifferent) {
			curTreePtr = curTreePtr->twoALink;
		}
		//check 3A
		else if (curTreePtr->threeALink != NULL && goodDifferent == curTreePtr->threeALink->goodDifferent) {
			curTreePtr = curTreePtr->threeALink;
		}

		//check if end
		if (curTreePtr->end == 1) {
			biasDueToCorrect = 0;
			//tune bad sequence according tree result
			int preHasDeleted=0;
			badListPtr tmp;
			tmp = createBadListElement(-1);
			sizeOfBadList--;
			tmp->next = badListRoot;
			badListRoot = tmp;
			for (badListTmp = badListRoot, index = 0; index < 3; index=index+1) {
				if (curTreePtr->goodElementPositionArray[index] == 1) {
					//if pre have deleted root  or first time
						printf("delete no minus ");
						deleteBadListElement(badListRoot, badListTmp, badListTmp->next);
						preHasDeleted = 1;
				}
				else if (curTreePtr->goodElementPositionArray[index] == -1) {
						printf("delete minus ");
						predict[badListTmp->next->indexOfPredict]=predictMinusDigit(predict[badListTmp->next->indexOfPredict]);
						biasDueToCorrect++;
						deleteBadListElement(badListRoot, badListTmp, badListTmp->next);
						preHasDeleted = 1;
					}
				//dosen't delete
				else {
					preHasDeleted = 0;

				}
				if (!preHasDeleted){
					badListTmp = badListTmp->next;

				}

				
			}
			badListPtr tmp2;
			tmp2 = badListRoot;
			badListRoot = badListRoot->next;
			free(tmp2);
			//reposition curtreeptr
			if (sizeOfBadList > 2) {
				tuneThreeDigit(badListRoot);
			}
			else {
				durningTreeTravel = 0;
				firstTimeBadListSizeLessthree = 1;
			}
			curTreePtr = diffTreeInitialPtr;
		}
		//tune digit
		else if (curTreePtr->deep == 1) {
			predict[badListRoot->indexOfPredict]=predictAddDigit(predict[badListRoot->indexOfPredict]);

		}
		else if (curTreePtr->deep == 2) {
			predict[badListRoot->next->indexOfPredict]=predictAddDigit(predict[badListRoot->next->indexOfPredict]);
		}


	}

	badListPtr tmp;
	for (tmp = badListRoot; tmp != NULL; tmp = tmp->next) {
		printf("%d->", tmp->indexOfPredict);
	}
		puts("");
	printf("sizeOfbadlist:%d ", sizeOfBadList);
	preGoodCount = goodCount;
	recordStep++;
	
	return predict;
}



void tuneThreeDigit(badListPtr root) {
	printf("tune three\n");
	//tune three digit in one time
	timeToTuneThree = 0;
	predict[root->indexOfPredict]=predictAddDigit(predict[root->indexOfPredict]);
	predict[root->next->indexOfPredict]=predictAddDigit(predict[root->next->indexOfPredict]);
	predict[root->next->next->indexOfPredict]=predictAddDigit(predict[root->next->next->indexOfPredict]);
	durningTreeTravel = 1;
	durningTreeTravelPreGoodCount= goodCount;
	
	
}

DifferentStructPtr createDifferentStrucuElement(int goodDifferent, int deep ) {
	DifferentStructPtr tmp;
	tmp = malloc(sizeof(struct DifferentStruct));
	tmp->goodDifferent = goodDifferent;
	tmp->deep = deep;
	tmp->goodElementPositionArray[0]=0 ;
	tmp->goodElementPositionArray[1]=0 ;
	tmp->goodElementPositionArray[2]=0 ;
	tmp->zeroALink= NULL;
	tmp->oneALink= NULL;
	tmp->twoALink= NULL;
	tmp->threeALink= NULL;
	tmp->end = 0;
	return tmp;
}


badListPtr createBadListElement(int indexOfPredict) {
	if (indexOfPredict != -1) {
	//	printf("create bad element index :%d\n", indexOfPredict);

	}
	sizeOfBadList++;
	badListPtr tmp;
	tmp= malloc(sizeof(struct badList));
	tmp->indexOfPredict = indexOfPredict;
	tmp->next = NULL;
	return tmp;
}
void deleteBadListElement(badListPtr root, badListPtr parent, badListPtr deletedElement) {
	//if which will be deleted is root
	sizeOfBadList--;
	if (deletedElement ->indexOfPredict != -1) {

		printf("dele index:%d\n", deletedElement->indexOfPredict);
	}
	if (badListRoot== deletedElement){ 
		badListRoot = badListRoot->next;
		free(deletedElement);
	}
	else {
		parent->next = deletedElement -> next;
		free(deletedElement);
	}
	//return 1 if delete root

}
char predictAddDigit(char digit) {
	char result;
	if (digit == '9') {
		result = '0';
	}
	else {
		result = (char)((int)digit +1);
	}
	return result;
}
char predictMinusDigit(char digit) {
	char result;
	if (digit == '0') {
		result = '9';
	}
	else {
		result = (char)((int)digit - 1);
	}
	return result;
}
		
