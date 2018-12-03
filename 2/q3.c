#include<stdio.h>
#include<string.h>
int main(void){
int times,i,j;
char org[10000],find[1000],repl[1000],result[10000];

scanf("%d",&times);
char final[times][10000];
for(i=0;i<times;i++){
scanf("%s",org);
scanf("%s",find);
scanf("%s",repl);
int findln=strlen(find);
int replln=strlen(repl);
char *cur,*location;
int gap=0;
strcpy(result,org);
cur=org;
location=strstr(cur,find);
while(location!=NULL){
gap+=(location-cur);
result[gap]='\0';
strcat(result,repl);
cur=location+findln;
gap+=replln;
strcat(result,cur);
location=strstr(cur,find);
}
result[strlen(result)]='\0';

strcpy(final[i],result);
}


for(j=0;j<times;j++)
printf("%s\n",final[j]);
return 0;}


