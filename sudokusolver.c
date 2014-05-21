#include <stdio.h> 
#define NUM_RC 9 
#define NUM_B  3 
  
int solve_sdk(   int pzl[][NUM_RC]); 
int legal_move(  int pzl[][NUM_RC], int n, int r, int c); 
int print_puzzle(int pzl[][NUM_RC]); 
int load_puzzle( int pzl[][NUM_RC]); 
  
int main(void) 
{ 
   int pzl[NUM_RC][NUM_RC]; 
   int e; 
  
   /* initialize and display the puzzle */
   if ( (e=load_puzzle(pzl)) != 1){return(e);} 
   printf("This is the original puzzle:\n"); 
   print_puzzle(pzl); 
  
   /* (attempt to) solve the puzzle */
   if (solve_sdk(pzl)) 
   { 
      printf("The puzzle has been solved.\n"); 
      print_puzzle(pzl); 
   } 
   else
   { 
      printf("The puzzle was NOT solved.\n"); 
   } 
return 0; 
} 
  
int solve_sdk(int pzl[][NUM_RC]) 
{ 
#define PUZZLE_COMPLETE 1 
#define NO_LEGAL_MOVE   0 
   int r; 
   int c; 
   int n; 
  
   for (r=0;r<NUM_RC;r++) 
   { 
      for (c=0;c<NUM_RC;c++) 
      { 
         if (pzl[r][c]==0) 
         { 
            for (n=1;n<=NUM_RC;n++) 
            { 
               if (legal_move(pzl,n,r,c)) 
               { 
                  pzl[r][c] = n; 
                  if (solve_sdk(pzl)) 
                  { 
                     return PUZZLE_COMPLETE; 
                  } 
                  else
                  { 
                     pzl[r][c] = 0; 
                  } 
               } 
            } 
            return NO_LEGAL_MOVE; 
         } 
      } 
   } 
   return PUZZLE_COMPLETE; 
} 
  
int legal_move(int pzl[][NUM_RC], int n, int r, int c) 
{ 
#define ILLEGAL_MOVE 0 
#define LEGAL_MOVE   1 
  

    int i; 
    int j; 
    int kr; 
    int kc; 
  
    kr=r/3; 
    kc=c/3; 
  
    for (i=0;i<9;i++) 
    { 
        if (n==pzl[i][c]) 
        { 
            return ILLEGAL_MOVE; 
        } 
    } 
    for (i=0;i<9;i++) 
    { 
        if  (n==pzl[r][i]) 
        { 
            return ILLEGAL_MOVE; 
        } 
    } 
    for (i=0;i<3;i++) 
    { 
        for (j=0;j<3;j++) 
        { 
            if  (n==pzl[3*kr+i][3*kc+j]) 
            { 
                return ILLEGAL_MOVE; 
            } 
        } 
    } 
return LEGAL_MOVE; 
} 
  
int print_puzzle(int pzl[][NUM_RC]) 
{ 
   int  r; 
   int  c; 
   char b; 
   /*char n;*/
  
   for (r=0;r<NUM_RC;r++) 
   { 
      if (r%NUM_B==0){printf("-------------------\n");} 
      for (c=0;c<NUM_RC;c++) 
      { 
         if (c%NUM_B==0){b='|';}else{b=' ';} 
         if (pzl[r][c]==0){printf("%c_",b);}else{printf("%c%d",b,pzl[r][c]);} 
         //printf("%c%c",b,n); 
         //printf("%c%d",b,pzl[r][c]); 
      } 
      printf("|\n"); 
   } 
   printf("-------------------\n"); 
return 0; 
} 

int load_puzzle(int pzl[][NUM_RC]) 
{ 
#define CHAR_LIM 256 
#define NUM_LIM  256 
#define SUCCESSFUL_LOAD    1 
#define UNSUCCESSFUL_LOAD -1 
  
   char filename[] = "sudoku_puzzle.txt"; 
   FILE *fptr; 
   int  pzl_i; 
   int  n; 
   int  i; 
  
   /* open the file containing the list of pzlbers */
   if ((fptr = fopen(filename,"r"))==NULL) 
   { 
      printf("Unable to open file: %s\n",filename); 
      return UNSUCCESSFUL_LOAD; 
   } 
  
   /* load the pzlber array from the file */
   for (i=0;i<NUM_RC;i++) 
   { 
      pzl_i=0; 
      while ( fscanf(fptr,"%d",&n)>0 )//&& pzl_i<NUM_RC ) 
      { 
         pzl[i][pzl_i++] = n; 
      } 
   } 
return SUCCESSFUL_LOAD; 
} 
