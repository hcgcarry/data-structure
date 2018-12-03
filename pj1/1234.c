#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(void){

int count=0;count++; //計算run函式跑幾次 
int tmp_row=0,maze_row,maze_col;
int i,j;
char tmp[250][250],cut[10],a[2];
FILE *file=fopen("fuck.txt","r");
if(!file){
	printf("file no found");
	return 1;
}
while(fscanf(file,"%s",tmp[tmp_row++])!=EOF){ 
           	//擷取資料 
	  
}
tmp_row--;
for(i=0;i<tmp_row;i++){
	
printf("%s\n",tmp[i]);
	
}

return 0;
}
/*
for(j=0;j<maze_row;j++){                    //把擷取到的資料給maze 
	for(k=0;k<maze_col;k++){
		maze[j][k]=(int)(tmp[1+j][1+k]-'0');           
	}
}*/
