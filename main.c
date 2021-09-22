//Sudoko Solver(9*9) in c
/*Basic header flies. Nothinng fancy*/

#include<stdio.h>
#define MAX_LEN 128
#include<string.h>

int sudoku[9][9];
void prnt_img(FILE *fptr);
void sol_sudu(int,int);


void prnt_img(FILE *fptr)
{
    char read_string[MAX_LEN];
 
    while(fgets(read_string,sizeof(read_string),fptr) != NULL)
        printf("%s",read_string);
}

int CHK_row(int row,int num) //Check funtion for row
{
int column;
for(column=0;column<9;column++)
    if(sudoku[row][column]==num)
        return 0 ;//Only 0 if the number is present in one of the cells
return 1; //1 if the number is not found elsewhere in the given cells
}
int CHK_col(int column,int num)//Just like CHK_row funtion but for column
{
int row;
for(row=0;row<9;row++)
    if(sudoku[row][column]==num)
        return 0; //0 for if the number is already preesnt in one of the given cells of given type like column here
return 1;//If the number is not found anywhere we return 1
}
int CHK_cells(int row,int column,int num) //The hardships of backtracking start here. So, an evil plan to break into 3x3 matrix to check grid accuracy
{
row=(row/3)*3 ;
column=(column/3)*3;
int r,c;
for(r=0;r<3;r++)
    for(c=0;c<3;c++)
         if(sudoku[row+r][column+c]==num)
            return 0; //You know the drill, why we return 0, you know like above return statements!!
return 1; //Same thing for return 1 as above.
}
void navigate(int row,int column) //So in backtracking, we also have to move to another cell or navigate tbh!!
{
if(column<8)
        sol_sudu(row,column+1);
    else
       sol_sudu(row+1,0);
}
void display() //The only function in backtracking which makes sense to me haha!! Prince le vaneko ho hai yo!!
{
int row,column;
printf("\n\n\t\t\t\t\t\tHere you go but always try to solve it yourself. \n\t\t\t\t\t\t");
for(row=0;row<9;row++)
{
for(column=0;column<9;column++)
printf(" %d ",sudoku[row][column]);
printf("\n");
}
}
void sol_sudu(int row,int column)
{
    if(row>8)//Greater than 8 implies that we have filled all cells
    display();
    if(sudoku[row][column]!=0)
    navigate(row,column); //This is magic. So if value is non-zero we basically navigate. Like the function says 
    else
    {int ctr;//This is a counter to check numbers from 1 to 9 whether the number can be filled in the cell or not
        for(ctr=1;ctr<=9;ctr++)
        {//We check row,column and the grid
        if((CHK_row(row,ctr)==1)&&(CHK_col(column,ctr)==1)&&(CHK_cells(row,column,ctr)==1))
        {
            sudoku[row][column]=ctr;
             navigate(row,column);
        }
        }
        sudoku[row][column]=0;//No valid number was found so we clean up and return to the caller.
    }
}

int main()
{
int row,column;
	
    char confirm[20];

    char *filename = "image.txt";
    FILE *fptr = NULL;
 do{
    if((fptr = fopen(filename,"r")) == NULL)
    {
        fprintf(stderr,"error opening %s\n",filename);
        return 0;
    }
 
    prnt_img(fptr);
 
    fclose(fptr);
 
printf("Enter the desired sudoku and enter 0 for unknown entries\n");
for(row=0;row<9;row++)
for(column=0;column<9;column++)
scanf("%d",&sudoku[row][column]);
sol_sudu(0,0);//We start solving the sudoku.
printf("\n\n\t\t\tDo you want to go again?");
printf("\n\t\t\t\tPress 'y' for yes and 'n' for no-> ");
scanf("%s",&confirm);
 }
while(strcmp(confirm,"y")==0);
}
/*A sample run of the program was carried out and the results were as follows:-
1 0 3 4 0 0 7 0 9
0 5 6 0 8 9 0 2 3
0 8 9 1 0 3 4 0 6
2 1 4 0 6 5 0 9 7
3 0 0 8 0 7 0 1 4
8 0 7 0 1 4 0 Greater than zero implies that we have filled all cells0 4 2
THE SOLVED SUDOKU
1 2 3 4 5 6 7 8 9
4 5 6 7 8 9 1 2 3
7 8 9 1 2 3 4 5 6
2 1 4 3 6 5 8 9 7
3 6 5 8 9 7 2 1 4
8 9 7 2 1 4 3 6 5
5 3 1 6 4 2 9 7 8
6 4 2 9 7 8 5 3 1
9 7 8 5 3 1 6 4 2
*/
