
/* Math is a simple program intended as personal training in C
   Copyright (C) 2019-undetermined  Anton Norgaard

   This file is a part of Math, a simple set of additional mathematical and compsci functions and data structures

   Math is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   Math is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.
   I'd prefer not to give any contact information as this is a personal project. I made it free out of principle */
#include "matrix.h"
#include "probability.h"
Matrix *m_create_matrix(unsigned long long rows, unsigned long long columns, int initialized){
  int i;
  int j;
  Matrix *m = malloc(sizeof(Matrix));
  if(m == NULL){
    printf("%s", "not enough memory available for matrix creation");
  }
  m->rows = rows;
  m->columns = columns;
  if( m->rows == m->columns){
    m->kind == square;
  }
  else{
    m->kind = regular;
  }
  m->entries = malloc(rows * sizeof(long double*));
  if(m->entries == NULL){
    printf("%s", "Not neough memory available for matrix creation" );
  }
  for(i=0; i<rows; i++){
    m->entries[i] = malloc(columns * sizeof(long double));
  }
  if(initialized == 1){
    srand(time(NULL));
    for(i = 0; i < rows; i++){
      for(j = 0 ; j < columns; j++){
	long double val;
	int nval = rand() % 100 +1;
	val = (long double) nval;
	*(*(m->entries + i) + j) = val;
      }
    }
  }
  return m;
}

void m_destroy_matrix(Matrix *m){
  int i;
  for(i=0; i < m->rows; i++){
    free(m->entries[i]);
  }
  free(m->entries);
  free(m);
}

void m_print_matrix(Matrix *a){
  int i = 0;
  int j = 0;
  for(i = 0; i < a->rows; i++){
    for(j=0; j < a->columns; j++){
      printf("%Lf", *(*(a->entries+i)+j));
      printf("%s", " ");
    }
    printf("%s", "\n");
  }
}

Matrix *m_add_matrices(Matrix *a, Matrix *b, int destroying){
  if(a->rows != b->rows || a->columns != b->columns){
    printf("%s", "invalid matrx dimensions when adding");
    return NULL;
  }
  else{
    Matrix *m = m_create_matrix( a->rows, a->columns, NO);
    for( int i = 0; i < m->rows; i++){
      for(int j = 0; j < m->columns; j++){
	*(*(m->entries+i)+j) = *(*(a->entries+i)+j) + *(*(b->entries+i)+j);
      }
    }
    if(destroying == 1){
      m_destroy_matrix(a);
      m_destroy_matrix(b);
    }
    return m;
  }
}

//Matrix *m_strassen_multiplication
Matrix *m_multiply_matrices(Matrix *a, Matrix *b, int destroying){
  if(a->columns != b->rows){
    printf("%s", "invalid rows dimensions when multiplying matrices");
    return NULL;
  }
  Matrix *m = m_create_matrix(a->rows, b->columns, NO);
  for(int i = 0; i < m->rows; i ++){
    for(int j = 0; j < m->columns; j++){
      for(int k = 0; k < a->columns; k++){
	  *(*(m->entries+i)+j)+= *(*(a->entries+i)+k) * *(*(b->entries+k)+j);
      }
    }
  }
  if(destroying == 1){
    m_destroy_matrix(a);
    m_destroy_matrix(b);
  }
  return m;
}

double long  m_determinant(Matrix *m){
  m_lower_tri_form(m);
  m_print_matrix(m);
  double long determinant = 1.000000;
  int i = 0;
  int j = 0;
  while(i < m->rows && j < m->columns){
    determinant *= *(*(m->entries+i)+j);
    i++;
    j++;
  }
  return determinant;
}




void m_ref(Matrix *m){
  /*Our initial starting point for pivot element */
  int i = 0;
  int j = 0;
  /*A byte to denote whether we have had to swap rows to ensure nonzero entry in pivot. Used to adjus where to look for next entry */
  char has_swapped;
  int column_offset = 1;
  int a;
    // printf("%s", "does the code reach here? \n");
  /*We will continue looking for pivots untill we have reached min(rows, columns)  */
  while(i <= m->rows && j <= m->columns){
    /* If pivot is zero, look for swapping row */
    if(*(*(m->entries+i)+j) == 0.000000){
      printf("%s%d%d%s", " Entry ", i, j, " found to be zero, looking for suitable row to swap with \n " );
      int k = i+1;
      while(k < m->rows){
	if(*(*(m->entries+k)+j) != 0.000000){
	  printf("%s%d%s%d%s", " We have found a suitable row to swap with, we swap row "  ,i ," with row ", k, "\n");
	  printf("%s%Lf%s", "value of k,j : ", *(*(m->entries+k)+j), "\n");
      	  m_swap_rows(*(m->entries+i), *(m->entries+k), m->columns);
	  k= m->rows;
	  has_swapped = 'y';
	}
  else{
    k++;
    column_offset++;
  }
	//	j++;
      }
       printf("%s", " We are done looking a rows to swap \n");
       m_print_matrix(m);
       printf("%s", " Here is the matrice after swapping rows \n");
    }
    /*pivot we will reduce to 1 */
    long double entry = *(*(m->entries+i)+j);
     printf("%s%d%s%d%s%s%d%d%s%Lf%s", " Okay, for row ", i , " of ", m->rows, " rows ", " we will reduce ", i,j, " i.e ", *(*(m->entries+i)+j), " to 1 \n");
          sleep(3);
    /*Multiply each row in current row of pivot with 1/pivotval to reduce it to 1  */
    for(int c = j; c < m->columns; c++){
	long double one = 1.0;
		printf("%s%d%d%s%Lf%s%Lf", " We will now multiply entry ", i, c, " i.e ", *(*(m->entries+i)+c), " by " , one/entry);
				sleep(3);
	*(*(m->entries+i)+c)= *(*(m->entries+i)+c) * one/entry;
		printf("%s%d%d%s%Lf%s", " and the value of ", i , c, " is now ", *(*(m->entries+i)+c), "\n");
			sleep(3);
		       	printf("%d%d%s", i, c, "\n");
   }
     m_print_matrix(m);
     printf("%s", "\n");
     printf("%s%d%s", "This is the matrix after reducing the first nonzero entry in ",i, " to a leading one \n ");
          sleep(3);
     printf("%s%d%d%s%lld%d%s", " Okay, now to reduce all values from ", i+1, j, " to ", m->rows, j, " to zero \n ");
             sleep(3);
    /*For row = i+1 to # rows, we will reduce all entries of r+j to #rows+j to zero */
	if(has_swapped == 'y'){
	  a = column_offset+1;
	}
	else{
	  a = i+1;
	}
  //an ugly hack to prevent reducing the last entry to zero, needs to be fixed, but for the time being, it works
     if(i+1 == m->rows){
       return;
     }
     else{
    for(int r = a;  r < m->rows; r++){
       printf("%s%d%s%d%d%s%Lf%s",  " Now for row ", r, " We will reduce ", a,j, " to zero i.e ", *(*(m->entries+a)+j), "\n");
      long double zeroed_entry = *(*(m->entries+a)+j);
      printf("%Lf", *(*(m->entries+i)+j));
            a++;
       sleep(3);
       printf("%Lf%s%s", zeroed_entry," the value of the entry to be zeroed " , "\n");
      for(int c = j; c < m->columns; c++){
		printf("%1.Lf", zeroed_entry);
			printf("%s%d%s%d%s","value of rows x columns: " , r, " ", c, "\n");
					sleep(3);
			printf("%s%d%d%s%d%d%s", " We multiply-subtract ", r,c, " by ", i,c, "\n" );
			printf("%s%Lf%s%Lf%s", "Now, we multiply-subtract ", *(*(m->entries+r)+c), " by - ", *(*(m->entries+i)+c) * zeroed_entry  , "\n");
	*(*(m->entries+r)+c) = *(*(m->entries+r)+c) - *(*(m->entries+i)+c) * zeroed_entry;
		sleep(3);
      }
    }
  }
    if(has_swapped == 'y' && *(*(m->entries+i+1)+j+1) == 0.000000){
      i++;
      j+=column_offset+1;
      column_offset = 1;
      //      has_swapped = 'n';
    }
    else{
  i++;
  j++;
    }
  }
}

void m_rref(Matrix *m){
  // printf("%s", "can the code at least beging reducing to rref? \n");
  m_ref(m);
   m_print_matrix(m);

  int i;
  int j;
  if(m->kind == identity || m->kind == identity_square){
    return;
  }
  if(m->kind == square){
    i = m->rows;
    j = m->columns;
  }
  else{
    if(m->rows > m->columns){
      i = m->columns-1;
      j = m->columns-1;
    }
    else{
      i = m->rows-1;
      j = m->rows-1;
    }
  }
  printf("%s%d%d%s", "value of i,j = :", i, j, "\n");
  while(i > 0 && j > 0 ){
    // printf("%s%d%d%s%lld%d%s", " Okay, now to reduce all values from ", i-1, j, " to ", 0, j, " to zero \n ");
    // sleep(3);
    int a = i-1;
    // printf("%s%d%s", "value of a:" , a, "\n");
    for(int r = a; r > -1; r--){
      //  printf("%s%d%s%d%d%s%Lf%s",  " Now for row ", r, " We will reduce ", a,j, " to zero i.e ", *(*(m->entries+a)+j), "\n");
       long double zeroed_entry = *(*(m->entries+a)+j);
      a--;
      // sleep(3);
      // printf("%Lf%s%s", zeroed_entry," the value of the entry to be zeroed " , "\n");
      for(int c = 0; c <  m->columns; c++){
	//	printf("%1.Lf", zeroed_entry);
	//	printf("%s%d%s%d%s","value of rows x columns: " , r, " ", c, "\n");
	//	sleep(3);
	//	printf("%s%d%d%s%d%d%s", " We multiply-subtract ", r,c, " by ", i,c, "\n" );
	//	printf("%s%Lf%s%Lf%s", "Now, we multiply-subtract ", *(*(m->entries+r)+c), " by - ", *(*(m->entries+i)+c) * zeroed_entry  , "\n");
	*(*(m->entries+r)+c) = *(*(m->entries+r)+c) - *(*(m->entries+i)+c) * zeroed_entry;
	//		sleep(3);
      }
    }
  i--;
  j--;
  }
}



void m_swap_rows(long double *r1, long double *r2, int size){
  long double *source_row_end = (r1 + (size-1));
  long double *dest_row_end = (r2 + (size-1));

  while(r1 <= source_row_end && r2 <= dest_row_end){
    long double temp = *r1;
    *r1 = *r2;
    *r2 = temp;
    r1++;
    r2++;
  }
}
//creates a matrix new matrix from two matrices a,b that will be a matrix corresponding to matrix a followed by matrix b rowwise
Matrix *m_rowwise_merge_matrix(Matrix *a, Matrix *b, int destroying){
  if(a->rows != b->rows){
    printf("%s", "Invalid row dimensions when merging matrices rowwise \n");
    return NULL;
  }
  else{
    Matrix *m = m_create_matrix(b->rows, (a->columns+b->columns), NO);
    for(int i = 0; i < a->rows; i++){
      for(int j = 0; j < a->columns; j++){
	*(*(m->entries+i)+j) = *(*(a->entries+i)+j);
      }
    }
    /*declaring values here outside of loop. Apparantly, C dislikes
      making expressions inside of loops or at least hard to get working
     */
    int cstart = a->columns;
     int cend = a->columns+b->columns;
    for(int i = 0; i < b->rows; i++){
      for(int j = 0; j < b->columns; j++){
	*(*(m->entries+i)+(cstart+j)) = *(*(b->entries+i)+j);
	    // printf("%Lf%s",d, " \n");
	/*	     printf("%d%s%d%s", i, " ", c, "\n");
	     printf("%s" ,"i, c above \n");
	     printf("%d%s%d%s", r, " ", j, "\n");
	     printf("%s" ,"r,j  above \n"); */
      }
    }
    if(destroying == 1){
    m_destroy_matrix(a);
    m_destroy_matrix(b);
   }
  return m;
  }
}

Matrix *m_columnwise_merge_matrix(Matrix *a, Matrix *b, int destroying){
  if(a->columns != b->columns){
    printf("%s", "Invalid row dimensions when merging matrices rowwise \n");
    return NULL;
  }
  else{
    Matrix *m = m_create_matrix(a->rows+b->rows, b->columns, NO);
    for(int i = 0; i < a->rows; i++){
      for(int j = 0; j < a->columns; j++){
	*(*(m->entries+i)+j) = *(*(a->entries+i)+j);
      }
    }
    /*declaring values here outside of loop. Apparantly, C dislikes
      making expressions inside of loops
     */
    int rstart = a->rows;
     int cend = a->columns+b->columns;
    for(int i = 0; i < b->rows; i++){
      for(int j = 0; j < b->columns; j++){
	*(*(m->entries+(i+rstart))+j) = *(*(b->entries+i)+j);
	    // printf("%Lf%s",d, " \n");
	/*	     printf("%d%s%d%s", i, " ", c, "\n");
	     printf("%s" ,"i, c above \n");
	     printf("%d%s%d%s", r, " ", j, "\n");
	     printf("%s" ,"r,j  above \n"); */
      }
    }
    if(destroying == 1){
    m_destroy_matrix(a);
    m_destroy_matrix(b);
   }
  return m;
  }
}

void m_lower_tri_form(Matrix *m){
  int i = 0;
  int j = 0;
  long double one = 1.000000;
  //printf("%s", "The matrix in question : \n");
//  m_print_matrix(m);
//  printf("%s", "\n");
//  sleep(3);
  while(i < m-> rows && j < m->columns){
    long double current_pivot = *(*(m->entries+i)+j);
//    printf("%s%d%s%Lf%s", "Diving row ", i, " by ", *(*(m->entries+i)+j), "\n");
    for(int c = j; c < m->columns; c++){
        *(*(m->entries+i)+c) = *(*(m->entries+i)+c) * one/current_pivot;
    }

  //  m_print_matrix(m);
  //  printf("%s", "\n");
  //  sleep(3);
    for(int r = i+1; r < m->rows; r++){
        long double row_pivot = *(*(m->entries+r)+j);
      //  printf("%s%d%s%Lf%s", "Multiply row ", i, " by ", row_pivot, "\n");
      for(int c = j; c < m->columns; c++){
          *(*(m->entries+i)+c) = *(*(m->entries+i)+c) * row_pivot;
       }
      // m_print_matrix(m);
    //   printf("%s", "\n");
    //   sleep(3);
    //   printf("%s%d%s%d", "subtract row ", i, " from ", r);
       for(int c = j; c < m->columns; c++){
           *(*(m->entries+r)+c) = *(*(m->entries+r)+c) - *(*(m->entries+i)+c);
        }
      //  m_print_matrix(m);
      //  printf("%s", "\n");
      //  sleep(3);
        //printf("%Lf%s", row_pivot, "\n");
      //  printf("%s", " and restore it \n" );
        for(int c = j; c < m->columns; c++){
            *(*(m->entries+i)+c) = *(*(m->entries+i)+c) * one/row_pivot;
         }
      //   m_print_matrix(m);
      //   printf("%s", "\n");
      //   sleep(3);

      }
        for(int c = j; c < m->columns; c++){
          *(*(m->entries+i)+c) = *(*(m->entries+i)+c) * current_pivot;
        }
      i++;
      j++;
    }
  //  m_print_matrix(m);
  }


/*void m_lower_tri_form(Matrix *m){
  m_print_matrix(m);
  printf("%s", "\n");
  int i = 0;
  int j = 0;
  long double one = 1.000000;
  this one to restore value
  long double first_pivot = *(*(m->entries+0)+0);

  for (int c = 0; c < m->columns; c++){
      *(*(m->entries+0)+c) *= one/first_pivot;
  }


  for(int r = i+1; r < m->rows; r++){
    long double cur_entry = *(*(m->entries+r)+j);
    for(int c = 0; c < m->columns; c++){
        *(*(m->entries+i)+c) *= cur_entry;
    }
    for(int c = 0; c < m->columns; c++){
        *(*(m->entries+r)+c) = *(*(m->entries+r)+c) - *(*(m->entries+i)+c);
    }
    for(int c = 0; c < m->columns; c++){
        *(*(m->entries+i)+c) *= one/cur_entry;
    }
  }
  //printf("%Lf%s", cur_pivot, "\n");
  for (int c = 0; c < m->columns; c++){
        *(*(m->entries+i)+c) *= first_pivot;
  }

  long double next_pivot = *(*(m->entries+i+1)+j+1);
  for (int c = j+1; c < m->columns; c++){
        *(*(m->entries+i+1)+c) *= 1.000000/next_pivot;
  }
  i++;
  j++;
  m_print_matrix(m);










  while(i < m->rows && j < m->columns){

    sleep(3);
    long double cur_pivot = *(*(m->entries+i)+j);
    for(int r = i+1; r < m->rows; r++){
  //    printf("%Lf%s", cur_pivot, "\n");
      long double cur_entry = *(*(m->entries+r)+j);
      for(int c = 0; c < m->columns; c++){
          *(*(m->entries+i)+c) *= cur_entry;
      }
      sleep(3);
m_print_matrix(m);
      printf("%s", "\n");
      for(int c = 0; c < m->columns; c++){
          *(*(m->entries+r)+c) = *(*(m->entries+r)+c) - *(*(m->entries+i)+c);
      }
      printf("%Lf%s", *(*(m->entries+r)+j), "\n");
      sleep(3);
      m_print_matrix(m);
        sleep(3);
        printf("%s", "\n");
      for(int c = 0; c < m->columns; c++){
          *(*(m->entries+i)+c) *= one/cur_entry;
      }
      m_print_matrix(m);
        sleep(3);
        printf("%s", "\n");
    }
  //  printf("%Lf%s%s", cur_pivot,"the current pivot", "\n");
    for (int c = 0; c < m->columns; c++){
          *(*(m->entries+i)+c) *= cur_pivot;
    }


    i++;
    j++;
  }

}
*/

/*void m_lower_tri_form(Matrix *m){
  int i = 0;
  int j = 0;
  long double one = 1.000000;
  while(i <= m->rows && j <= m->columns){
    long double entry = *(*(m->entries+i)+j);
    for(int r = i+1; r < m->rows; r++){
      long double last_entry = *(*(m->entries+r)+j);
      sleep(3);
     printf("%s%d%s", "value of r: ", r, "\n");
      printf("%s%d%s%d%s%Lf%s", " We are are at row ",r, " column ",j, " i.e ", entry, "\n");
      printf("%s%d%d%s%Lf%s", " Okay, now to reduce ", i, j, " to one i.e ", entry, "\n" );
      for(int c = j; c < m->columns; c++){

    sleep(3);
    printf("%s%d%d%s%Lf%s%Lf%s", " We multiply ", i, c, " i.e ", *(*(m->entries+i)+c), " by ", one/entry, "\n" );
	*(*(m->entries+i)+c) =  *(*(m->entries+i)+c) * one/entry;
  printf("%s%d%d%s%Lf%s", " and the value of ", i,c, " is now ", *(*(m->entries+i)+c), "\n" );
    sleep(3);
	 printf("%s%d%s", "value of c: ", c, "\n");
      }
      sleep(3);
      m_print_matrix(m);
      printf("%s", "\n");
      for(int d = j; d < m->columns; d++){
         multiply row i with current row
        sleep(3);
       printf("%s%d%d%s%d%d%s%Lf%s", " Okay, now to adjust ", i, j, " to be the value of" ,i, d,  " i.e ", *(*(m->entries+r)+j), "\n" );
	*(*(m->entries+i)+d) =  *(*(m->entries+i)+d) *  *(*(m->entries+r)+j);
	 printf("%s%d%s", "value of d: ", d, "\n");
   printf("%s%d%d%s%Lf%s", " And the value of ", i , d, " is now ", *(*(m->entries+i)+d), "\n" );
      }
      sleep(3);
      m_print_matrix(m);
      printf("%s", "\n" );
      sleep(3);
      printf("%s%d%d%s%Lf%s", " Okay, reduce", r, j, " i.e ", *(*(m->entries+r)+j), " to be zero \n" );
      for(int e = j; e < m->columns; e++){
       sleep(3);
	*(*(m->entries+r)+e) =  *(*(m->entries+r)+e) -  *(*(m->entries+i)+e);
  printf("%s%d%d%s%Lf%s", " And the value of ", r , e, " is now ", *(*(m->entries+r)+e), "\n" );
      }
      sleep(3);
      m_print_matrix(m);
      printf("%s", "\n" );
     sleep(3);
      printf("%s%d%d%s%Lf%s%d%s%Lf%s", " Okay, now to reduce ", i, j, " to one i.e ", entry, " again by multiplying row ", i, " by ", one/last_entry ,"\n" );
      for(int f = j; f < m->columns; f++){
     sleep(3);
	*(*(m->entries+i)+f) = *(*(m->entries+i)+f) * one/last_entry;
      }
      sleep(3);
      m_print_matrix(m);
      printf("%s", "\n" );
       sleep(3);
     printf("%s%d%d%s%Lf%s", " and the value of ", i, j, " is now ",*(*(m->entries+i)+j), "\n" );
    sleep(3);
  printf("%s%d%d%s%Lf%s", " Okay, now to restore ", i, j, " its former value i.e ", entry , "\n" );

     m_print_matrix(m);
     printf("%s", "\n" );
    }
    printf("%Lf%s", entry, "\n");
    for(int c = j; c < m->columns; c++){
        sleep(3);
        *(*(m->entries+i)+c)*= *(*(m->entries+i)+c) * entry;
         sleep(3);
        printf("%s%d%d%s%Lf%s", " and the value of ", i,c, " is now ",*(*(m->entries+i)+c), "\n" );
        j++;
        i++;
       }
  }
     printf("%s", "does code reach here? \n");
}
*/


void m_scalar_mult(Matrix *m, int scalar){
  double long scalari = (long double) scalar;
  for(int i = 0; i < m->rows; i++){
    for(int j = 0; j < m->columns; j++){
      *(*(m->entries+i)+j) =  *(*(m->entries+i)+j) * scalari;
    }
  }
}

Matrix *m_create_identity_matrix(unsigned long long rows, unsigned long long columns){
  Matrix *m = m_create_matrix(rows, columns, NO);
  for(int i = 0; i < m->rows; i++){
    for(int j = 0; j < m->columns; j++){
      *(*(m->entries+i)+j) = 0.000000;
    }
  }
  int i = 0;
  int j = 0;
  while(i < m->rows && j < m->columns){
      *(*(m->entries+i)+j) = 1.000000;
      i++;
      j++;
  }
   return m;
}
