#include<stdio.h>
#include<stdlib.h>
int main(void){
int numbers;int numbers2;
int num;int value;int num2;
scanf("%d",&numbers);
int **array=(int**)malloc(numbers*sizeof(int*));

if(NULL==array){exit(1);}
for(int i=0;i<numbers;i++){
array[i]=(int*)malloc(100000*sizeof(int));
if(NULL==array[i]){
exit(1);}
scanf("%d",&num);
for(int j=0;j<num;j++){
scanf("%d",&value);
array[i][j]=value;
array[i][j+1]=0;

}
}


scanf("%d",&numbers2);
int array3[numbers2]; 
for(int i=0;i<numbers2;i++){
scanf("%d",&num2);
array3[i]=num2;}
for(int i=0;i<numbers2;i++){
printf("%d",array[array3[i]-1][0]);
for(int j=1;array[array3[i]-1][j]!=0;j++)
printf("% d",array[array3[i]-1][j]);
puts("");


}

for(int i=0;i<numbers;i++)
free(array[i]);
free(array);
return 0;}





