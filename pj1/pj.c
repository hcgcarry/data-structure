#include<stdio.h>
#include<string.h>
#define max_stack_size 1000

typedef struct {
	int row,col,dir;
}element;
typedef struct  {
	int row,col;
}step;

step move[4]={{1,0},{0,1},{-1,0},{0,-1}};
element stack[max_stack_size]; 
element delet(int *top);
void add(int *top,element item);
//執行函式 
int count=0;
int run(char *file_name){     
count++; //計算run函式跑幾次 
int tmp_row=0,maze_row,maze_col;
int i,j,k,l,m,n,o,p,u,q;
char tmp[500][500];
FILE *file=fopen(file_name,"r");
if(!file){
	printf("file no found");
}
while(fscanf(file,"%s",tmp[tmp_row++])!=EOF){ 
           	//擷取資料 
}
tmp_row--;
/*for(i=0;i<tmp_row;i++)
printf("%s\n",tmp[i]);*/

fclose(file);
maze_row=tmp_row-2;maze_col=strlen(tmp[2])-2;  
int maze[maze_row][maze_col];

for(j=0;j<maze_row;j++){                    //把擷取到的資料給maze 
	for(k=0;k<maze_col;k++){
		maze[j][k]=(int)(tmp[1+j][1+k]-'0');           
	}
}

					
   //search path
int start_col=0,start_row=0,end_col=maze_col-1,end_row=maze_row-1; 	//設定起點和終點 
int next_row,next_col,top=0,min_step=0,col,row,dir; 
int mark[maze_row][maze_col];
for(i=0;i<maze_row;i++){
	for(q=0;q<maze_col;q++){
		mark[i][q]=0;
	}
}
mark[0][0]=1; 
int found=0;
stack[0].row=0;stack[0].col=0;stack[0].dir=0; 
element position;
element min_stack[max_stack_size];

while(top>-1){   
                    
	position=delet(&top);
	
	col=position.col;row=position.row;dir=position.dir;
	while(dir<4){
		next_col=col+move[dir].col;
		next_row=row+move[dir].row;
	
		if(end_col==next_col&&end_row==next_row){           	//如果走到終點 
		
			mark[end_row][end_col]=mark[row][col]+1;
			found=1;
			dir++;
			if(mark[end_row][end_col]<min_step||min_step==0){
				position.row=row;position.col=col;position.dir=dir; //將現在的這步方向++加入棧 是為了讓輸出方便 
				add(&top,position);
				min_step=mark[end_row][end_col]-1;
				for(p=0;p<min_step;p++){
				min_stack[p]=stack[p];		
				}
			}
		}
		 //先判斷是否符合基本的道路條件，接下來如果是沒走過的就可以走或是有走過但是路徑較近的路就走 
		else if(maze[next_row][next_col]!=0&&next_row>=0&&next_col>=0&&next_row<maze_row&&next_col<maze_col&&
		(mark[next_row][next_col]==0||mark[row][col]+1<mark[next_row][next_col])){           
			mark[next_row][next_col]=mark[row][col]+1;
			position.row=row;position.col=col;position.dir=++dir;
			add(&top,position);
			row=next_row;col=next_col;dir=0;
		
		}
	    else dir++;
	
	}
}



//如果有找到終點 
if(found){
	//找coin
	int coin=0;
	for(u=0;u<min_step;u++){
		if(maze[min_stack[u].row][min_stack[u].col]==2)
		coin++;	
	}
	if(maze[end_row][end_col]==2)
	coin++;
/*	printf("coin:%d\n",coin);
	for(n=0;n<min_step;n++){
		switch(min_stack[n].dir-1){
			case 0:
				printf("down");
				break;
			case 1:
				printf("right");
				break;
			case 2:
				printf("up");
				break;
			case 3:
				printf("left");	
				break;
		}
	
		
		printf("%3d%5d\n",min_stack[n].row,min_stack[n].col);}
*/	
	FILE *write;
	if(count==1){
	write=fopen("layer1-path.txt","w");
	}
	else{
	write=fopen("layer2-path.txt","w");	
	} 
	
	for(n=0;n<min_step;n++)
		for(n=0;n<min_step;n++){
			switch(min_stack[n].dir-1){
				case 0:
					fprintf(write,"down\n");
					break;
				case 1:
					fprintf(write,"right\n");
					break;
				case 2:
					fprintf(write,"up\n");
					break;
				case 3:
					fprintf(write,"left\n");	
					break;
			}
		}
	fprintf(write,"coin:%d",coin);
	fclose(write);

	}
	int h=0;
	i=0;
	if(count==2){
		while(1){
	
		
				
				for(k=0;k<min_stack[i].row;k++){
					puts("");
				}
				for(j=0;j<min_stack[i].col;j++){
					printf(" ");
				}
				printf("@");
				system("ping 127.0.0.1 -n 1 -w 100 >nul");	
				system("ping 127.0.0.1 -n 1 -w 100 >nul");
				system("ping 127.0.0.1 -n 1 -w 100 >nul");
				system("cls");							
		
		i++;
		if(i==min_step)
		i=0;
		}
	}
	
return found;



}

//呼叫 
int main(void){
	if(run("maze-layer1.txt")){
		run("maze-layer2.txt");
		}
return 0;
}



element delet(int *top){
if(*top==-1){
    fprintf(stderr,"delet error\n");

    }
return stack[(*top)--];
}

void add(int *top,element item){
if(*top>=max_stack_size-1){
	fprintf(stderr,"out of size\n");

	}
stack[++*top]=item;
}
	
	
	
	
	
	


	
	
	
	
	

