#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define len 100000
int main(void)
{	
	int j=0,k,i,times,cur;
	scanf("%d",&times);
	char **ord=(char**)malloc(sizeof(int*));
	char output[times][len];
	char input[len];
	for(i=0;i<times;i++){
		j=0;
		scanf("%c",input);
		scanf("%[^\n]",input);
	   	char *cut=strtok(input," ");
		while(cut!=NULL){
			ord=(char**)realloc(ord,(j+1)*sizeof(int*));
			
			ord[j]=(char*)malloc(len*sizeof(int));
			memset(ord[j],0,len*sizeof(int));
			ord[j]=cut;
			cut=strtok(NULL," ");
			j++;
			}
		j--;
		strcpy(output[i],ord[j]);
		j--;
		for(j;j>=0;j--){
			strcat(output[i]," ");
			strcat(output[i],ord[j]);
			}
		}
	for(k=0;k<times;k++){
		printf("%s\n",output[k]);
		}
	
return 0;
}

