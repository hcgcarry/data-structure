#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct input{
	char source[10];
	char dest[10];
	int distance;
};

	#define ture 1
	#define false 0
void singlesourcealldest(int *distance,int *table,int max_num,short int found[],int start_num);

int main(void){
	char sort[100][20];
	int i,first,temp_top=0,sort_top=0;
	struct input temp[100];
	
	do{
		scanf("%s %d %s",temp[temp_top].source,&temp[temp_top].distance,temp[temp_top].dest);
		if(temp[temp_top].distance==-1)break;
		for(i=0;i<sort_top;i++){
		if(strcmp(sort[i],temp[temp_top].source)==0)
		first=false;
		}
		if(first==ture){
		strcpy(sort[sort_top],temp[temp_top].source);
		sort_top++;
		}
		first=ture;
		for(i=0;i<sort_top;i++){
		if(strcmp(sort[i],temp[temp_top].dest)==0)
		first=false;
		}	
		if(first==ture){
		strcpy(sort[sort_top],temp[temp_top].dest);
		sort_top++;
		}	
		temp_top++;
	}while(1);
	int table[sort_top][sort_top],j;
	int source_num,dest_num;
	for(i=0;i<sort_top;i++)//initial
		for(j=0;j<sort_top;j++){
			table[i][j]=1000;
		}
	for(i=0;i<sort_top;i++)table[i][i]=0;
	for(i=0;i<temp_top;i++){     
		for(j=0;j<sort_top;j++){
			if(strcmp(sort[j],temp[i].source)==0)
				source_num=j;
			if(strcmp(sort[j],temp[i].dest)==0)
				dest_num=j;
		}
		table[source_num][dest_num]=temp[i].distance;	
		table[dest_num][source_num]=temp[i].distance;	
	}
	int distance[sort_top];
	short int found[sort_top];
	for(i=0;i<sort_top;i++){
	
		singlesourcealldest(distance,&table[0][0],sort_top,found,i);
	for(j=0;j<sort_top;j++){
		printf("%d ",distance[j]);
	}
	puts("");
	}
	return 0;
}



void singlesourcealldest(int *distance,int *table,int max_num,short int found[],int start_num){
	int m,i,j,min,current;

	for(i=0;i<max_num;i++){               //intinal
		found[i]=false;
		distance[i]=*(table+start_num*max_num+i);
	}
	found[start_num]=ture;
	distance[start_num]=0;
	min=1000;
	for(i=0;i<max_num-2;i++){
		for(j=0;j<max_num;j++){
			if(!found[j]&&min>distance[j]){
				min=distance[j];
				current=j;
			}
		}
		found[current]=ture;
		for(m=0;m<max_num;m++){
			if(distance[m]>distance[current]+*(table+current*max_num+m)){
				distance[m]=distance[current]+*(table+current*max_num+m);
			}
		}
	}
}































