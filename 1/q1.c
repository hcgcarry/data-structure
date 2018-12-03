#include<stdio.h>
int main(void){
int length;
scanf("%d",&length);
char name[length][100];
for(int i=0;i<length;i++){
scanf(" %[^\n]",name[i]);}
for(int i=0;i<length;i++){
printf("Hello, %s!\n",name[i]);}
return 0; }
