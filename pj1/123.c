#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(void){

int count=0;count++; //�p��run�禡�]�X�� 
int tmp_row=0,maze_row,maze_col;
int i,j;
char tmp[10][250],cut[10],a[2];
FILE *file=fopen("fuck.txt","r");
if(!file){
	printf("file no found");
	return 1;
}
while(fgets(tmp[tmp_row++],10,file)!=NULL){ 
           	//�^����� 
	  
}
tmp_row--;
for(i=0;i<tmp_row;i++){
	
printf("%s",tmp[i]);
	
}

return 0;
}
/*
for(j=0;j<maze_row;j++){                    //���^���쪺��Ƶ�maze 
	for(k=0;k<maze_col;k++){
		maze[j][k]=(int)(tmp[1+j][1+k]-'0');           
	}
}*/
