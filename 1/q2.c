#include<stdio.h>
int main(void){
int length;
int numbers;

scanf("%d",&numbers);
int array2[numbers];

for(int k=0;k<numbers;k++)
{
scanf("%d",&length);
int array[length];
for(int i=0;i<length;i++)
{scanf(" %d",&array[i]);}
for(int i=0;i<length;i++){
for(int j=0;j<length;j++){
if(i!=j&array[i]==array[j]){
array[i]=0;array[j]=0;
}}
}
for(int i=0;i<length;i++){   
if(array[i]!=0){
array2[k]=array[i];}}



}


for(int k=0;k<numbers;k++){

printf("%d\n",array2[k]);
 }
 return 0;}
