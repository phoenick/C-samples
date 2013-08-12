/*File:squares.c*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



struct substack{
	int position_of_pan;	/*Position of placed number.*/
	int peak;
	int choices[8][2];
};
struct Stack{
	int peak;
	int sqrtsize;
	struct substack *array;
};
struct coord{
	int x;
	int y;
};
/*----------------------*/
int createStack(int, struct Stack *);
void deleteStack(struct Stack *);
int full(struct Stack *curstack);
int append(int, struct Stack *curstack);
/*----------------------*/
void sort(struct Stack *, int );
void sherror(int);
struct coord position_of_lpn(struct Stack *curstack);
struct coord move(int);


int load(int ***p, struct Stack *curstack);
int place(int ***p, struct Stack *curstack);
void backtrace(int steps, int ***p, struct Stack *curstack);
void print_array(int ***p, int sqrtsize);

main(int argc, char *argv[])
{int n, i, j, k, l, chk;
 int nochoices, cannotload;
 int **p;
 char *s;
 struct Stack choicekeeper;
 
 
 s="-check";
 putchar('!');

 if((argc==2)&&(n=atoi(argv[1])>4))
	 n=atoi(argv[1]);
 else if((argc==3)&&(strcmp(s, argv[1])==0)&&(n=atoi(argv[2])>4))
	 n=atoi(argv[2]);
 else{
	printf("Please give a valid set of arguments\n");
	printf("for the program to work!\n");
	return;
 }
 p=malloc(n*sizeof(int *));
 if(p==NULL){
 	printf("Sorry, cannot allocate memory!");
 	return;
 }
 for(i=0;i<n;i++){
 	p[i]=malloc(n*sizeof(int));
 	if(p[i]==NULL){
 		printf("Sorry, cannot allocate memory!");
 		return;
 	}
 }
 putchar('p');
 if(argc==2){
	 chk=createStack(n, &choicekeeper);
	 if(chk==0){
		sherror(1);
	        return;	
	 }
	 for(i=0;i<n;i++)
		 for(j=0;j<n;j++)
			p[i][j]=0;
	 p[0][0]=1;
	 nochoices=0; cannotload=0;
 	 while(!(choicekeeper.peak==(n*n-1))){
		 putchar('l');
		 cannotload=load(&p, &choicekeeper);
		 if(cannotload){
				 do{
				 backtrace(1, &p, &choicekeeper);
				 nochoices=place(&p, &choicekeeper);
				 }while(nochoices);

		 }
		 else{
			place(&p, &choicekeeper);
		 }
	 }
	 print_array(&p, choicekeeper.sqrtsize);
	 /*-----------------------*/
	 deleteStack(&choicekeeper);
 }
 else{  int x, y;

 	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			scanf("%d ", &p[i][j]);
		}
		scanf("\n");
	}
	putchar('\n');
	i=0; j=0;
	for(k=1;k<n*n;k++){
		for(l=1;l<=8;l++){
			x=i+move(l).x;
			y=j+move(l).y;
			if((x>=0)&&(x<n)){
				if((y>=0)&&(y<n))
					if(p[x][y]==k+1){
						i=x;
						j=y;
						break;
					}
			}
			if(l==8){
				printf("Problem in placing %d \n", k+1);
				return;
			}			
		}
	}
	printf("Everything is OK ! ! ! ! !\n");
 }
 for(i=0;i<n;i++)
	 free(p[i]);
 free(p);

}

/*----------------------------------*/
/*----------------------------------*/
int createStack(int sqrtsize, struct Stack *curstack){
 int i;
 curstack->array=malloc(sqrtsize*sqrtsize*sizeof(struct substack));
 if(curstack->array==NULL)	 
	 return 0;
 for(i=0;i<sqrtsize*sqrtsize;i++){
	 curstack->array[i].peak=-1;
 }
 curstack->array[0].position_of_pan=1;
 curstack->sqrtsize=sqrtsize;
 curstack->peak=0;
 return 1;
}

void deleteStack(struct Stack *curstack){
 free(curstack->array);
}

int empty(struct Stack *curstack){
if(curstack->peak==0)	
 	return 1;
else
	return 0;
}

int full(struct Stack *curstack){
 int m=curstack->sqrtsize;
 return (m*m==curstack->peak-1);
}

int append(int element, struct Stack *curstack){
 if(full(curstack))
	 return 0;
 curstack->peak+=1;
 curstack->array[curstack->peak].position_of_pan=element;
 return 1;
}

int poplast(struct Stack *curstack){
 if(empty(curstack))
	 return 0;
 curstack->peak=curstack->peak-1;
 return (curstack->array[curstack->peak+1].position_of_pan);
}
/*-------------------------------*/
struct coord move(int i){
 struct coord mcoord;
 switch(i){
	 case 1:mcoord.x=-3;
		mcoord.y=0;
		break;
	 case 2:mcoord.x=-2;
		mcoord.y=2;
		break;
	 case 3:mcoord.x=0;
		mcoord.y=3;
		break;
	 case 4:mcoord.x=2;
		mcoord.y=2;
		break;
	 case 5:mcoord.x=3;
		mcoord.y=0;
		break;
	 case 6:mcoord.x=2;
		mcoord.y=-2;
		break;
	 case 7:mcoord.x=0;
		mcoord.y=-3;
		break;
	 case 8:mcoord.x=-2;
		mcoord.y=-2;
		break;
 }
 return mcoord;
}
/*-------------------------------*/
struct coord position_of_lpn(struct Stack *curstack){
 int position;		/*Position of the last placed number as it is*/
			/* kept in the "Stack".*/
 struct coord polpn;	/*//Position of last placed number */
 position=curstack->array[curstack->peak].position_of_pan;
 if((position/curstack->sqrtsize)*curstack->sqrtsize!=position){
 polpn.x=position/curstack->sqrtsize;
 }
 else
	polpn.x=position/curstack->sqrtsize - 1;
 polpn.y=position - (curstack->sqrtsize*polpn.x) - 1;/*bug fixed*/
 	
 return polpn;
}
/*-------------------------------*/
int possible_moves(int ***p, struct coord movement, struct Stack *curstack){
 int i, j, x, y, k, l, pm, position;
 pm=0;
 position=curstack->array[curstack->peak].position_of_pan;
 if((position/curstack->sqrtsize)*curstack->sqrtsize!=position)
 	i=position/curstack->sqrtsize;
 else
	i=position/curstack->sqrtsize -1;
 j=position-(curstack->sqrtsize*i)-1;
 x=movement.x;
 y=movement.y;
 i+=x;
 j+=y;
 (*p)[i][j]=-1;
 for(k=1;k<=8;k++){
	 x=i+move(k).x;
	 y=j+move(k).y;
	 if((x>=0)&&(x<curstack->sqrtsize))
		 if((y>=0)&&(y<curstack->sqrtsize))
				 if((*p)[x][y]==0){
					//putchar('m');
				 	pm+=1;
				 }
 }
 (*p)[i][j]=0;
 return pm;
}

/*-------------------------------*/
/*	"substack" functions	 */
int sfull(struct Stack *curstack){
 if(curstack->array[curstack->peak].peak==7) 
	 return 1;
 else
	 return 0;
}
int sempty(struct Stack *curstack){
 if(curstack->array[curstack->peak].peak==-1)
	 return 1;
 else
	 return 0;
}
int sappend(int element, int pm, struct Stack *curstack){
 int subpeak;
 if(sfull(curstack)) return 0;
 curstack->array[curstack->peak].peak++;
 subpeak=curstack->array[curstack->peak].peak; //bug corrected
 curstack->array[curstack->peak].choices[subpeak][0]=element;
 curstack->array[curstack->peak].choices[subpeak][1]=pm;
 return 1;
}
int spoplast(struct Stack *curstack){
 int subpeak, popelement;
 if(sempty(curstack)) return 0;
 subpeak=curstack->array[curstack->peak].peak;
 popelement=curstack->array[curstack->peak].choices[subpeak][0];
 curstack->array[curstack->peak].peak-=1;
 return popelement;
}
/*-------------------------------*/
void sort(struct Stack *curstack ,int lel){
 int i, j, chk, cspos, temp[2]; //cspos : current position on the stack
 cspos=curstack->peak;
 chk=1;
 for(i=0;i<lel;i++){
  if(chk==1) chk=0;
  else break;	
  for(j=0;j<lel-1;j++){
   if(curstack->array[cspos].choices[j+1][1]>curstack->array[cspos].choices[j][1]){
   	temp[0]=curstack->array[cspos].choices[j][0];
	temp[1]=curstack->array[cspos].choices[j][1];
	curstack->array[cspos].choices[j][0]=curstack->array[cspos].choices[j+1][0];
	curstack->array[cspos].choices[j][1]=curstack->array[cspos].choices[j+1][1];
	curstack->array[cspos].choices[j+1][0]=temp[0];
	curstack->array[cspos].choices[j+1][1]=temp[1];
	chk=1;
   }
 			
  }	
 }
}
/*------------------------------*/
int load(int ***p, struct Stack *curstack){
 int i, j, k, x, y, chk;
 chk=0;
 i=position_of_lpn(curstack).x;
 j=position_of_lpn(curstack).y;
 for(k=1;k<=8;k++){
	 x=i+move(k).x;
	 y=j+move(k).y;
	 if((x>=0)&&(x<curstack->sqrtsize)){
		 if((y>=0)&&(y<curstack->sqrtsize)){
		 	if((*p)[x][y]==0){
 		 		chk=sappend(k, possible_moves(p, move(k), curstack), curstack);
		 	}
	 	 }
 }
 if(chk==0)
	 return 1;
 else{	 
 	sort(curstack, 8);
 	return 0;
 }
 }
}
int place(int ***p, struct Stack *curstack){
 int i, j, choice;
 struct coord movement;
 i=position_of_lpn(curstack).x;
 j=position_of_lpn(curstack).y;
 choice=spoplast(curstack);
 if(choice==0){
	 return 1;
 }
 else{	
	 movement=move(choice);
	 append(curstack->sqrtsize*(i+movement.x)+j+movement.y+1, curstack);
	 (*p)[i+movement.x][j+movement.y]=curstack->peak+1;
	 return 0;
 }
}

void backtrace(int steps, int ***p, struct Stack *curstack){
 int i, j, k;
 for(k=1;k<=steps;k++){
 	i=position_of_lpn(curstack).x;
 	j=position_of_lpn(curstack).y;
 	(*p)[i][j]=0;
 	curstack->array[curstack->peak].peak=-1;
 	poplast(curstack); 
 }
}

void print_array(int ***p, int sqrtsize){
 int i, j;
 for(i=0;i<sqrtsize;i++){
	 for(j=0;j<sqrtsize;j++)
		 printf("%3d ", (*p)[i][j]);
	 putchar('\n');
 }
}
/*-------------------------------*/
 void sherror(const int w){
 switch(w){
	 case 1:printf("Attention: Memory allocation process failed!");
	 	break;
 }
}
