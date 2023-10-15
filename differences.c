#include <stdio.h>

#define maxRows    11
#define maxPower    7   /* Includes power of 0 */
#define maxColumns maxPower + 2
/* test1 */
int main() {
 
int printTable               (long long entry[][maxColumns]);
int printDifferenceTable     (long long entry[][maxColumns], int constantColumn);
int printBuildTable          (long long entry[][maxColumns], int constantColumn);
int printParallelEvenTable   (long long entry[][maxColumns], int constantColumn, int row);
int printParallelOddTable    (long long entry[][maxColumns], int constantColumn, int row);
int checkCalculations (long long[maxRows][maxColumns], long long[maxRows]);
int printFx (int x, int constant[]);

/* Reference f(x) array contains calculated f(x) values to check the addition method */
/* of calculating f(x)                                                               */
long long referenceFx[maxRows];

/* Table */
long long cell[maxRows][maxColumns];

/* Equation power constants f(x) = c7x^7 + c6x^6 + c5^5 + c4^4 + c3^3 + c2^2 +c1x c0 */
int constant[maxPower + 1];

int power;          // The power values in f(x)
int row;            // The variable x in f(x)
int column;         // Column 0 is f(x), other columns are differences
int i;              // Tempory variable
long long temp;     // Temporary variable
int nbrDiffColumns; // Number of difference columns

/* temp is a variable that will not need to retain it's value */
int trash;

printf ("This program demonstrats the working of Charles Babbages Difference Engine #2.\n");
printf ("Difference Engine #2 calculates f(x) values of the following polynomial:\n");
printf ("   f(x) = c7x^7 + c6x^6 + c5x^5 + c4x^4 + c3x^3 + c2x^2 +c1x + c0\n");
printf ("   \"^\" means raised to the power of the following number.\n");
printf ("   The coefficients c7 - c0 can be positive or negative integers.\n");
printf ("   If the coeficient is 0, the coresponding term will not be in f(x).\n");
printf ("   For the coefficients of c7=0, c6=0, c5=0, c4=3, c3=0, c2=-5 c1=0, c0=1,\n");
printf ("     the function will be f{x) = 3x^4 -5x^2 +1.  For x=2: f(x) = 3*(2^4} -5*(2^)2 +1 = 3*16 -5*4 +1 = 29.\n");
printf ("\n");
printf (" f(x) can approximate common functions such as sine, cosine, and logarithms.\n");
printf ("  Using these approximations, the Difference Engine can calculate tables to be used");
printf ("  by mathematicians, engineers, scientists, astronomers, etc.\n\n");

trash = getchar ();
/*
printf ("This program demonstrates the use of a table to calculate the value of f(x):\n");
printf ("  The first column of the table is the values of x for which f(x) is calculated.\n");
printf ("  The second column is the calculated value of f(x) for each x.\n");
printf ("  The remaining columns are used to calculate the f(x) values in the second column.\n");

printf ("This program demonstrates the following:\n");
printf ("- First it calculates values of f(x) using traditional methods:\n");
printf ("  It then saves these values in an array to valuate the other methods calculating f(x)\n");
printf ("- Calculation of f(x) using only addition operations\n");
printf ("  Babbages difference engins did not support multiplication or exponiation operations.\n");
printf ("- A modificaation of the previous calculation which does parallel addition operations.\n");
printf ("  This was used on the Babbage Difference 2 and significaltly faster.\n");


printf ("Delete the following comments?????????????\n");
printf ("- Initialization of the table and calculation of f(x) values using only additions\n");
printf ("- An algorithm that can take advantage if parallel additions if a Difference Engine has that capability\n\n");

printf ("Babbage's Differential Engine 2 contained a vertical columns of gears with numbers on them.\n");
printf ("The numbers on the gear represent a decimaal digit.  31 such gears are on a column representing a 31 digit number.\n");
printf ("A column can be added to the next adjacent column or have a constant added to it.\n\n");

printf ("This program can demonstrate the calculation used to create a table of polynomial f(x) for each value of x.\n");
printf ("The user can define the desired constant multiplier for each term.  If the coeficient for a term is 0, the term will\n");
printf ("evaluate to 0 and the term will not be included in the equation.  The terms are input as shown below.\n");
*/
printf ("Get the coefficients that define the function to be calculated.\n");
trash = getchar ();

/* Input the constants for f(x) */
printf("Enter the f(x) constant ");
scanf("%d", &constant[0]);
for (power = 1; power <= maxPower; power++) {
  printf("Enter the f(x) x^%d coefficient ", power);
  scanf("%d", &constant[power]);
}

/* Print f(x) */
printf ("Function entered:     \nf(x) = ");
for (power = maxPower; power > 1; power--) {
  if (constant[power] != 0) {
    printf("%dx^%d + ", constant[power], power);
  }
}
if (constant[1] != 0) {
  printf ("%dx ", constant[1]);
}
if (constant[0] != 0) {
  printf ("+ %d", constant[0]);
}
printf ("\n\n");

trash = getchar ();

printf ("f(x) evaluations:\n");
for (i = 0; i<maxRows; i++) {
  printFx (i, constant);
}
printf ("\n");

trash = getchar ();

/* Calculate the number of Dif columns */
nbrDiffColumns = 0;
for (nbrDiffColumns = maxPower; nbrDiffColumns > 0; nbrDiffColumns--) {
//  printf("In loop nbrDiffColumns = %d\n", nbrDiffColumns);
  if (constant[nbrDiffColumns] != 0) {
    break;
  }
}
if (nbrDiffColumns == 0) {
//  printf ("Error: f(x) has no terms\n");
  return (-1);
}

/* Initialize cells */
for (column = 0; column < maxColumns; column++) {
  for (row = 0; row < maxRows; row++) {
      cell[row][column] = 0;           
  }
}

/* Build table to get the constants */

/* Calculate function column */
printf ("Calculate function f(x) using conventional methods column in the following table.\n");

for (row = 0; row < maxRows; row++) {
  cell[row][0] = constant[0];
  for (power = 1; power <= maxPower; power++) {
    temp = row;  // x is the row number
    i    = power; 
    while (i > 1) {
      temp *= row;
      i--;
    }
    temp *= constant[power];  // temp = constant[power]*x^power
    cell[row][0] += temp;
  }
}

printTable (cell);

trash = getchar ();

printf ("Copy f(x) column to a reference array to be used to verify future f(x) calculations.\n\n");
/* Save f(x) so that we can verify that the addition method calculates it correctly */
for (row = 0; row < maxRows; row++) {
  referenceFx [row] = cell[row][0];
}
// checkCalculations(cell, referenceFx);

trash = getchar ();

/* Calculate difference columns */
printf ("Calculate the difference columns in the table.\n\n");

trash = getchar ();

for (column = 1; column <= nbrDiffColumns; column++) {
  for (row = 0; row < maxRows-1; row++) {
    if ((row == maxRows-1) || (cell[row+1][column-1] == 0)) {
      cell[row][column] = 0;
    } else {
        cell[row][column] = cell[row+1][column-1] - cell[row][column-1];
    }
  }
  if (column ==1) {
    printf("Calculating Dif%d column: Dif%d[row] = f(x)[row+1] - f(x)[row].\n", column, column);
  } else {
    printf("Calculating Dif%d column: Dif%d[row] = Dif%d[row+1] - Dif%d[row].\n", column, column, column-1, column-1);

  }
  printDifferenceTable (cell, nbrDiffColumns);

  trash = getchar ();

}

printf ("Initialize the table so that it can be rebuilt with additions only.  Done by clearing the table except for row[0].\n");
/* Clear the table except for row 0.                                              */
/* Row 0 has the constants that allow us to calsulate the f(x) with only addition */
for (column = 0; column < maxColumns; column++) {
  for (row = 1; row < maxRows; row++) {
    //if (cell[row+1][column-1] == 0) {
      cell[row][column] = 0;
    //}
  }
}
printTable (cell);

trash = getchar ();

printf ("Rebuilding the table with only additions.\n");
/* Build the table with only additions */
for (row = 0; row < maxRows-1; row++) {
  for (column = 0; column < nbrDiffColumns; column++) {
    cell[row+1][column] = cell[row][column] + cell[row][column+1];
  }
 // if (row == 0) {
 //   printf("cell[%d][%d] = %lld", row, column, cell[row][column]);
 // }
  cell[row+1][column] = cell[row][column];
  //if (row == 0) {
  //  printf("   cell[%d][%d] = %lld\n", row+1, column+1, cell[row+1][column+1]);
 // }

  printBuildTable(cell, nbrDiffColumns);

  trash = getchar ();

}
printf("Verify that f(x) column calculated with only additions is the same as the reference calculated by normal means.\n");

trash = getchar ();

checkCalculations(cell, referenceFx);
printf ("Each row except the first (f(x)=0 which was initialized ahead of time) required %d calculations.  %d rows required %d calculations.\n\n", nbrDiffColumns, maxRows-1, nbrDiffColumns*(maxRows-1));

trash = getchar ();

printf("Simulate the parallel calculations of f(x) used by Babbage Difference Engine 2.\n");

trash = getchar ();

/* Algorith used by Babbage Difference Engine 2 */
/* The algorithm can be used on the difference engine to  */
/* update an adjacent pairs of colums simultaneously.     */
/* A columns can be either the source or the destination  */
/* at a given time.  A column can not be a source and a   */
/* destination concurrently.  This algorithm allows 3 or  */
/* 4 of the colums to be updated simultaneously making    */
/* it significantly faster on the Difference Engine 2     */
/* It also could be used to exploit the speed of the      */
/* implementation of ENIAC                                */

/* Clear the table except the portion used to set the    */
/* constants                                             */

cell[0][8] = 0;

cell[1][6] = 0;
cell[1][7] = 0;
cell[1][8] = 0;

cell[2][4] = 0;
cell[2][5] = 0;
cell[2][6] = 0;
cell[2][7] = 0;
cell[2][8] = 0;

cell[3][2] = 0;
cell[3][3] = 0;
cell[3][4] = 0;
cell[3][5] = 0;
cell[3][6] = 0;
cell[3][7] = 0;
cell[3][8] = 0;

printf ("Initialized table to fill with paralled calculations.\n");

trash = getchar ();

for (row = 4; row < maxRows; row++) {
  for(column = 0; column < maxColumns; column++) {
    cell[row][column] = 0;
  }
}
printTable (cell);

trash = getchar ();

printf("Filling table using parallel algorithm\n");
for (row = 3; row < maxRows-1; row++) {
  for (column = 0; column <= 6; column+=2) {
    cell[row+1][column] = cell[row  ][column] + cell[row  ][column+1];
    cell[row  ][column] = cell[row-1][column] + cell[row-1][column+1];
    cell[row-1][column] = cell[row-2][column] + cell[row-2][column+1];
    cell[row-2][column] = cell[row-3][column] + cell[row-3][column+1];
  }
  printf("Update f(x) and even Diff columns\n");

  printParallelEvenTable (cell, nbrDiffColumns, row+1);

  trash = getchar ();

  for (column = 1; column <= 7; column+=2) {
    cell[row+1][column] = cell[row  ][column] + cell[row  ][column+1];
    cell[row  ][column] = cell[row-1][column] + cell[row-1][column+1];
    cell[row-1][column] = cell[row-2][column] + cell[row-2][column+1];
    cell[row-2][column] = cell[row-3][column] + cell[row-3][column+1];
  }
    printf("Update odd Diff columns\n");
  printParallelOddTable (cell, nbrDiffColumns, row+1);
}
trash = getchar ();

printf ("Validate the parallel f(x) calculations.\n");
//  printTable (cell);

trash = getchar ();

printf ("\n");

checkCalculations(cell, referenceFx);

printf ("Each row except the first 3 required 2 parallel calculations.  %d rows required %d parallel calculations.\n", maxRows-3, nbrDiffColumns*(maxRows-1));
printf ("A saving of 2 rows and up to 5 calculations per row.\n\n");

trash = getchar ();

return (0);
}


int printTable (long long entry[][maxColumns]) {
  int column;
  int row;

  printf ("  x            f(x)");
  for (column = 1; column < maxColumns; column++) {
    printf ("          Dif%d ", column);
  }
  printf ("\n");
  for (row = 0; row < maxRows; row++) {
    printf ("%3d", row);
    for (column = 0; column < maxColumns; column++) {
      printf ("%15lld", entry[row][column]);
    }
      printf ("\n");         
  }
  printf ("\n");
}


int printDifferenceTable (long long entry[][maxColumns], int constantColumn) {  
  int column;
  int row;

  printTable (entry);

}

int printBuildTable (long long entry[][maxColumns], int constantColumn) {  
  int column;
  int row;

  printf ("        ");
  printf ("     f(x) = ");
  for (column = 2; column <= constantColumn; column++) {
    printf ("    Dif%d(x) =  ", column-1);
  }
  printf ("         copy\n");
  printf ("           f(x-1) + ");
  for (column = 2; column <= constantColumn; column++) {
    printf ("  Dif%d(x-1) +  ", column-1);
  }
  printf ("  constant to\n");
  printf ("          Dif1(x-1)     ");
  for (column = 2; column <= constantColumn; column++) {
    printf ("Dif%d(x-1)      ", column);
  }
  printf (" next row\n\n");
  printTable (entry);
 // for (column = 1; column < maxColumns; column++) {
 //   printf ("Dif%d(x+1)-Dif%d(x)", column);
 //   printf ("         Dif%d", column);
 // }
}

int printParallelEvenTable (long long entry[][maxColumns], int constantColumn, int row) {  
  int column;
  int tempRow;

//  printf ("Update odd Diff columns:\n");
  printf ("             f(%d) =", row);
  
  tempRow = row;
  for (column = 2; column < constantColumn; column+=2) {
    tempRow -= 1;
    printf ("                    Dif%d(%d) = ", column, tempRow);
  }
  printf("\n");
  printf ("             f(%d) +", row-1);
    tempRow = row;
  for (column = 2; column < constantColumn; column+=2) {
    tempRow -= 1;
    printf ("                    Dif%d(%d) + ", column, tempRow-1);
  }
  printf ("\n");
  printf ("          + Dif1(%d)", row-1);
  tempRow = row;
  for (column = 2; column < constantColumn; column+=2) {
    tempRow -= 1;
    printf ("                      Dif%d(%d) ", column+1, tempRow-1);
  }
  printf ("\n");
  printf ("\n");
  printTable (entry);
}


int printParallelOddTable (long long entry[][maxColumns], int constantColumn, int row) {  
  int column;
  int tempRow;

//  printf ("Update odd Diff columns:\n");
 // printf ("                 f(%d) =", row);
  printf ("    "); 
  tempRow = row;
  for (column = 1; column <= constantColumn; column+=2) {
    tempRow -= 1;
    printf ("                    Dif%d(%d) = ", column, tempRow);
  }
  printf("\n    ");
 // printf ("                 f(%d) +", row-1);
    tempRow = row;
  for (column = 1; column <= constantColumn; column+=2) {
    tempRow -= 1;
    printf ("                    Dif%d(%d) + ", column, tempRow-1);
  }
  printf ("\n    ");
// printf ("              + Dif1(%d)", row-1);
  tempRow = row;
  for (column = 1; column <= constantColumn; column+=2) {
    tempRow -= 1;
    printf ("                      Dif%d(%d) ", column+1, tempRow-1);
  }
  printf ("\n");
  printf ("\n");
  printTable (entry);
}


int checkCalculations (long long fx[maxRows][maxColumns], long long reference[maxRows]) {
  int row;
  int calculationsCompare;   /* Logical compare */


  /* Compare f(x) to reference */
calculationsCompare = 1;

printf ("          f(x)     reference\n");
for (row = 0; row < maxRows; row++) {
  printf("%14lld%14lld\n", fx[row][0], reference[row]);
  if (fx[row][0] != reference[row]) {
    calculationsCompare = 0;
  }
}
if (calculationsCompare) {
  printf ("Calculations Compare \n\n");
} else {
    printf ("Calculations Do Not Compare!! \n\n");
}
return (0);
}


int printFx (int x, int constant[maxPower]) {
  int       power;
  long long sum = 0;;
  long long temp;
  int       firstTerm = 1;

  printf ("f(%d) = ", x);
  for (power = maxPower; power > 1; power--) {
    if (constant[power] != 0) {
      if (!firstTerm) {
        printf (" + ");
      } else {
        firstTerm = 0;
      }
      printf ("%dx^%d", constant[power], power);
    }
  }
  if (constant[1] != 0) {
        if (constant[power] != 0) {
      if (!firstTerm) {
        printf (" + ");
      } else {
        firstTerm = 0;
      }
    printf ("%dx ", constant[1]);
    }
  }
  if (constant[0] != 0) {
    if (!firstTerm) {
      printf (" + ");
    } else {
      firstTerm = 0;
    }
    printf ("%d", constant[0]);
  }
  printf (" = ");
  for (power = maxPower; power > 1; power--) {
    temp = x;
    if (constant[power] != 0) {
      for (int i = 1; i < power; i++) {
        temp *= x;
      }
      printf("%lld + ", temp * constant[power]);
      sum += temp;
    }
  }
  if (constant[1] != 0) {
    printf ("%d + ", constant[1]*x);
    sum += constant[1] * x;
  }
  if (constant[0] != 0) {
    printf ("%d", constant[0]);
    sum += constant[0];
  }
  printf (" = %lld\n", sum);
}