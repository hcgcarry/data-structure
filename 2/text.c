#include<stdio.h>
#include<string.h>
#define len 1000
int main(void)
{
    int times,i=0,o,j;
    char *cut,*result[len],input[len];
    scanf("%d",& times);
    char final[times][len];
    for(j=0;j<times;j++){
        i=0;
        scanf("%c",input);
        scanf("%[^\n]",input);
        cut=strtok(input," ");
        while(cut!=NULL){
            result[i++]=cut;
            cut=strtok(NULL," ");
        }
        i--;
        strcpy(final[j],result[i]);
        i--;
        for(;i>=0;i--){
            strcat(final[j]," ");
            strcat(final[j],result[i]);
        }
    }
 
    for(o=0;o<times;o++){
        printf("%s\n",final[o]);
    }
    return 0;
}