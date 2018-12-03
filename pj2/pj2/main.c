#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define table_size 97
#define max_char 30
typedef struct{
char str[max_char];	
}element;

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

int hash(char *key){
return (transform(key)%table_size);
}

int transform(char *key){
int number=0;
while (*key) number += *key++;
return number;
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
int main(int argc,char *argv[]){
key key_array[45000];
char argv1[3][100];
int key_num=0,hash_num=0;
element item;
list_pointer lead;
FILE *file=fopen(argv[1],"r");
if(!file){
	printf("file no found");
	exit(1);
}
while(fscanf(file,"%s",key_array[key_num++].str)!=EOF){
};

key_num--;
fclose(file);
file=fopen(argv[2],"r");
if(!file){
	printf("file no found");
	exit(2);
}
int status;
char eat[100];
while(1){
	status=fscanf(file,"%[a-zA-Z0-9_]",item.str);
	if(status>0){
		strlwr(item.str);
		chain_insert(hash_table,item);
	}
	else if(status==0){	
		fscanf(file,"%[^a-zA-Z0-9_]",eat);
	}
	else{
		break;
	}

};

fclose(file);
int i;

for(i=0;i<key_num;i++){
	key_array[i].count=0;
	hash_num=hash(strlwr(key_array[i].str));
	lead=hash_table[hash_num];
	for(;lead;lead=lead->link){
		
		if(strcmp(lead->item.str,key_array[i].str)==0){
			key_array[i].count++;	
		}
	}
}

file=fopen("output.txt","w");

for(i=0;i<key_num;i++){
	fprintf(file,"%d\n",key_array[i].count);
}
fclose(file);
return 0;
}





