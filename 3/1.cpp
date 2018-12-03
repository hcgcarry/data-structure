#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define table_size 997
#define max_char 20
#include<stdlib.h> 
typedef struct{
char str[max_char];	
}element;


char *strlwr(char *str)
{
  unsigned char *p = (unsigned char *)str;

  while (*p) {
     *p = tolower((unsigned char)*p);
      p++;
  }

  return str;
}
typedef struct list *list_pointer;

typedef struct list{
element item;
list_pointer link;
}list1;
list_pointer hash_table[table_size];

typedef struct{
char str[max_char];
int count;
}key;



int transform(char *key){
int number=0;
while (*key) number += *key++;
return number;
}
int hash(char *key){
return (transform(key)%table_size);
}

void chain_insert(list_pointer ht[],element item){
int hash_num=hash(item.str);
list_pointer trail=NULL,lead=ht[hash_num],ptr;
for(;lead;trail=lead,lead=lead->link);
ptr=(list_pointer)malloc(sizeof(list1));
ptr->item=item;
ptr->link=NULL;
if(trail)trail->link=ptr;
else ht[hash_num]=ptr;

}

                                            //main
int main(void){
key key_array;

int key_num=0,hash_num=0;
element item;
list_pointer lead;




int status;
char eat[100];
while(1){
	status=scanf("%[a-zA-Z0-9_]",item.str);
	
	 if(status>0){
		strlwr(item.str);
		chain_insert(hash_table,item);
	}
	else if(status==0){	
		scanf("%[^a-zA-Z0-9_]",eat);
		if(strstr(eat,"-----")!=NULL)break;
	}
	puts("1111");

}
int max_count=0;
char max_count_key[30];
scanf("%s",key_array.str);
while(strcmp(key_array.str,"-1")){
puts("2222");
key_array.count=0;
	hash_num=hash(strlwr(key_array.str));
	lead=hash_table[hash_num];
	for(;lead;lead=lead->link){
		
		if(strcmp(lead->item.str,key_array.str)==0){
			key_array.count++;	
		}
	}
if(max_count<key_array.count){
	max_count=key_array.count;
	strcpy(max_count_key,key_array.str);
}
scanf("%s",key_array.str);
}


printf("%s %d",max_count_key,max_count);



return 0;
}





