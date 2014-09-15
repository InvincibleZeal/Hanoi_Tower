/* GeeoksOnBoard
   2013

program is to simulate the solution of Hanoi tower with the simple algorithm:
1) move the smallest block to the next stick ("next" means "next on the right" if the
   amount of blocks is even, or "next on the left" if the amount of blocks is odd.)
2) make the only possible move without touching the smallest block.
3) repeat till finished.

blocks are shown on the screen represented by the numbers with their size

User just need to answer the question of the number of blocks. He can also choose the stick
from which to start, and the one where he eventually wants the blocks to be moved.
Then: press enter and enjoy :)

*/

//libraries
#include <stdio.h>
#include <stdlib.h>

//variables
#define bufor 300 //max amount of blocks
int a[3][bufor];  //array simulating the sticks
int rotator;      //variable telling whether the smallest block is going right or left

//functions declarations
int init(int, int);           //initialization
void move_1(int, int, int*);  //moving the smallest block
void move(int, int*);         //moving other blocks
int write(int);               //printing results to the screen
void clean(void);             //erasing the console screen

//*******************main*******************************************
int main(void) {

  int k, x, y, where_1[2]={0}; //k- amount of blocks, x- stick to start from, y- stick to finish on
                               //where_1- position of the smallest block
  
  //taking the startup parameters
  printf("type the amount of blocks: ");
  scanf(" %d", &k);
  printf("which stick are we starting from? (1,2,3) ");
  scanf(" %d", &x);
  if(x>3 || x<1) return 0; //finishing if user typed anything strange...

  where_1[0]=x; //position of the smallest block
  where_1[1]=1;

  printf("And to which one you want to move the blocks? ");
  scanf(" %d", &y);
  
  //initialization
  init(k, x);

  //checking the rotation direction
  if ((x-y)==1 || (x-y)==-2){ //if there's 2 sticks distance between starting and finishing stick
    rotator = 1;              //on the right (or 1 on the left) -> rotating right
  }
  else //otherwise rotating left
    rotator = -1;

  if(k%2!=0) //checking the parity of blocks. If odd, turning the rotation direction
   rotator *=-1;

  //writting results on the cleaned screen
  clean();
  write(k);
  //getting some unusefull chars from the input (somehow it works better now...)
  getchar();
  getchar();

  //**THE MAIN LOOP**
  while(1){
    clean();
    if(where_1[0]==y && where_1[1]==1) return 0; //finishing when... finished ;)
    
    move_1(k, rotator, where_1); //steps described in the algorithm on the top
    write(k);
    getchar(); //waiting for "enter" to continue
 
    clean();  
    
    move(k, where_1);
    write(k);
    getchar();
  
  } //**while**

  return 0 ;
} //end of main

//**************FUNCTIONS***************************
//
int init(int k, int x){
  int i;

  for(i=0; i<k; i++)
     a[x-1][i]=i+1; //blocks initialization (filling the array with zeros)
  
  return 0;
}// end if init

int write(int j) {
  int i;
  for(i=0; i<j; i++){
    printf("	%d	%d	%d\n", a[0][i], a[1][i], a[2][i]); //printing restults in the form of 3 columns
  }
  return 0;
}//end of write

void move_1(int k, int r, int* w) {
  int i;
  a[w[0]-1][w[1]-1]=0; //deleting the former position of the smallest block
  w[0]+=r;             //moving right or left (depends on rotator, taken in "r")
  
  if(w[0]==0)          //the loop in if ;) - if the smallest is on the marginal stick, it goes to the other marginal one
    w[0]=3;
  else if(w[0]==4)     
    w[0]=1;
  
  for(i=0; i<k ;i++){  //looking for the highest no-zero element in the column
    if(a[w[0]-1][i]!=0) {
      a[w[0]-1][i-1]=1;//settling the smallest block down in the new position, one place higher than the highest block
      w[1]=i;
      return;
    }
  }
  
  a[w[0]-1][k-1]=1;    //settling the smallest block down, if the new column is empty
  w[1]=k;
}//end of move_1

void move(int k, int* w) {
  int i,j, kol_x, kol_y;
  
  if(w[0]==1){         //determining position of the smallest
  kol_x=1;             //determining "free" sticks
  kol_y=2;
  }
  else if(w[0]==2){
  kol_x=2;
  kol_y=0;
  }
  else {
  kol_x=0;
  kol_y=1;
  }

  for(i=0; i<k-1;i++){ //looking for the highest, no-zero element
    if(a[kol_y][i]!=0) break; //searching in the column after the one with the smallest (kol_y)
  }                           //giving "i" the right value
  for(j=0; j<k-1;j++){ //the same..
    if(a[kol_x][j]!=0) break; //searching in the last column (kol_x)
  }

  //settling block down in the new position. 
  //if any column is empty..
  if(a[kol_y][i]==0){  //searching in kol_y
    a[kol_y][i]=a[kol_x][j];  //copying the block to the empty place
    a[kol_x][j]=0;     //removing the copied block
    return;            //function finishes
  }
  if(a[kol_x][j]==0){  //the same for kol_x
    a[kol_x][j]=a[kol_y][i];
    a[kol_y][i]=0;
    return;
  }
  //if no column is empty        
  if(a[kol_y][i]>a[kol_x][j]){  //checking what's to be moved where
    a[kol_y][i-1]=a[kol_x][j];  //copying...
    a[kol_x][j]=0;              //and removing tracks ;)
  }
  else {                        //the same but otherwise
    a[kol_x][j-1]=a[kol_y][i];
    a[kol_y][i]=0;
  }
   
  
return ;
}//end of move

void clean(void){ //I could use system("clear"), but then it works only on my red hat...
  printf("\033[2J");   // cleans the screen
  printf("\033[0;0f"); // sets cursor in the left, top corner
}//end of clean




