#include<stdio.h>
#include<string.h>
#define max 1000
int main(void){
char rev[max]={0};
char input[max]={0}; 
char sum[max]={0};
int i,j,u,f,h,times,len;
scanf("%d",&times);
for(i=0;i<times;i++){
for(h=0;h<max;h++){
input[h]=0;}
scanf("%s",input);
len=strlen(input);

for(j=0;j<len;j++){
rev[j]=input[len-j-1]-'0';}

for(u=0;u<len;u++){
sum[u]+=rev[u];
if(sum[u]>10){
sum[u+1]+=sum[u]/10;
sum[u]=sum[u]%10;}
}
}
for(f=max;f>0;f--)
if (sum[f]!=0)break;
for(;f>=0;f--)
{printf("%d",sum[f]);}

return 0;}





