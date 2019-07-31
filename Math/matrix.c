
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
  m->column_offset = 1;
  m->has_swapped[0] = 'n';
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
  int a;
    // printf("%s", "does the code reach here? \n");
  /*We will continue looking for pivots untill we have reached min(rows, columns)  */
  while(i <= m->rows && j <= m->columns){
    /* If pivot is zero, look for swapping row */
    if(*(*(m->entries+i)+j) == 0.000000){
    //  printf("%s%d%d%s", " Entry ", i, j, " found to be zero, looking for suitable row to swap with \n " );
      int k = i+1;
      while(k < m->rows){
	if(*(*(m->entries+k)+j) != 0.000000){
	 /* printf("%s%d%s%d%s", " We have found a suitable row to swap with, we swap row "  ,i ," with row ", k, "\n");
	  printf("%s%Lf%s", "value of k,j : ", *(*(m->entries+k)+j), "\n"); */
      	  m_swap_rows(*(m->entries+i), *(m->entries+k), m->columns);
	  k= m->rows;
	  m->has_swapped[0] = 'y';
	}
  else{
    k++;
    m->column_offset++;
  }
	//	j++;
      }
    /*   printf("%s", " We are done looking a rows to swap \n");
       m_print_matrix(m);
       printf("%s", " Here is the matrice after swapping rows \n");*/
    }
    /*pivot we will reduce to 1 */
    long double entry = *(*(m->entries+i)+j);
    /* printf("%s%d%s%d%s%s%d%d%s%Lf%s", " Okay, for row ", i , " of ", m->rows, " rows ", " we will reduce ", i,j, " i.e ", *(*(m->entries+i)+j), " to 1 \n");
          sleep(3); */
    /*Multiply each row in current row of pivot with 1/pivotval to reduce it to 1  */
    for(int c = j; c < m->columns; c++){
	long double one = 1.0;
	/*	printf("%s%d%d%s%Lf%s%Lf", " We will now multiply entry ", i, c, " i.e ", *(*(m->entries+i)+c), " by " , one/entry);
				sleep(3); */
	*(*(m->entries+i)+c)= *(*(m->entries+i)+c) * one/entry;
/*		printf("%s%d%d%s%Lf%s", " and the value of ", i , c, " is now ", *(*(m->entries+i)+c), "\n");
			sleep(3);
		       	printf("%d%d%s", i, c, "\n"); */
   }
  //   m_print_matrix(m);
  /*   printf("%s", "\n");
     printf("%s%d%s", "This is the matrix after reducing the first nonzero entry in ",i, " to a leading one \n ");
          sleep(3);
     printf("%s%d%d%s%lld%d%s", " Okay, now to reduce all values from ", i+1, j, " to ", m->rows, j, " to zero \n ");
             sleep(3); */
    /*For row = i+1 to # rows, we will reduce all entries of r+j to #rows+j to zero */
	if(m->has_swapped[0] == 'y'){
	  a = m->column_offset+1;
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
    //   printf("%s%d%s%d%d%s%Lf%s",  " Now for row ", r, " We will reduce ", a,j, " to zero i.e ", *(*(m->entries+a)+j), "\n");
      long double zeroed_entry = *(*(m->entries+a)+j);
    //  printf("%Lf", *(*(m->entries+i)+j));
            a++;
  /*     sleep(3);
       printf("%Lf%s%s", zeroed_entry," the value of the entry to be zeroed " , "\n");*/
      for(int c = j; c < m->columns; c++){
	//	printf("%1.Lf", zeroed_entry);
		/*	printf("%s%d%s%d%s","value of rows x columns: " , r, " ", c, "\n");
					sleep(3);
			printf("%s%d%d%s%d%d%s", " We multiply-subtract ", r,c, " by ", i,c, "\n" );
			printf("%s%Lf%s%Lf%s", "Now, we multiply-subtract ", *(*(m->entries+r)+c), " by - ", *(*(m->entries+i)+c) * zeroed_entry  , "\n"); */
	*(*(m->entries+r)+c) = *(*(m->entries+r)+c) - *(*(m->entries+i)+c) * zeroed_entry;
	//	sleep(3);
      }
    }
  }
    if(m->has_swapped[0] == 'y' && *(*(m->entries+i+1)+j+1) == 0.000000){
      i++;
      j+= m->column_offset+1;
      m->column_offset = 1;
      //      has_swapped = 'n';
    }
    else{
  i++;
  j++;
    }
  }
}

void m_rref(Matrix *m){
  m_ref(m);
  int i;
  int j;
  m_print_matrix(m);
  printf("%s", "\n");
  if(m->kind == square){
    //we take index-1 as max index == length-1
    i = m->rows-1;
    j = m->columns-1;
  }
  else{
    if(m->rows > m->columns){
      i = m->columns-1;
      j = m->rows-2;
    }
    if(m->columns > m->rows){
      i = m->rows-1;
      j = m->columns-2;
    }
  }
  while(i >= 0 && j >= 0){
    printf("%s%d%s%d%s", "We are at ", i, " ", j, "\n");
    sleep(3);
      long double current_pivot = *(*(m->entries+i)+j);
    for(int r = i-1; r > -1; r--){
        long double row_pivot = *(*(m->entries+r)+j);
        for(int c = j; c < m->columns; c++){
          printf("%Lf%s",row_pivot*current_pivot, "\n" );
            *(*(m->entries+r)+c) = *(*(m->entries+r)+c) - row_pivot*current_pivot;
            printf("%s%d%s", " value of r ", r, "\n");
        }
    }
    if(m->has_swapped[0] == 'y'){
      i--;
      j-= m->column_offset+1;
      m->column_offset = 1;
    }
    else{
      i--;
      j--;
    }
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

void m_upper_tri_form(Matrix *m){
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

void m_lower_tri_form(Matrix *m){
  int i = m->rows-1;
  int j = m->columns-1;
  long double one = 1.000000;
  while(i >= 0 && j >= 0){
  //  printf("%d%s%d%s", i, " ", j, "\n");
//    sleep(3);
     long double current_pivot = *(*(m->entries+i)+j);
  //   printf("%Lf%s", current_pivot, "\n");
  //     sleep(3);
     for(int c = j; c > -1; c--){
         *(*(m->entries+i)+c) = *(*(m->entries+i)+c) * one/current_pivot;
     }
  //   sleep(3);
  //   m_print_matrix(m);
  //   sleep(3);
  //    printf("%s%Lf%s"," Value of the pivot " , current_pivot, "\n");
     for(int r = i-1; r > -1; r--){
      // printf("%s", "does code reach here");
         long double row_pivot = *(*(m->entries+r)+j);
    //     printf("%s%d%s%Lf%s", "Multiply row ", i, " by ", row_pivot, "\n");
       for(int c = j; c > -1; c--){
           *(*(m->entries+i)+c) = *(*(m->entries+i)+c) * row_pivot;
        }
    //    m_print_matrix(m);
    //    printf("%s", "\n");
//        sleep(3);
  //      printf("%s%d%s%d", "subtract row ", i, " from ", r);
        for(int c = j; c > -1; c--){
            *(*(m->entries+r)+c) = *(*(m->entries+r)+c) - *(*(m->entries+i)+c);
         }
    //     m_print_matrix(m);
    //     printf("%s", "\n");
    //     sleep(3);
    //     printf("%Lf%s", row_pivot, "\n");
    //     printf("%s", " and restore it \n" );
         for(int c = j; c > -1; c--){
             *(*(m->entries+i)+c) = *(*(m->entries+i)+c) * one/row_pivot;
          }
      //   m_print_matrix(m);
      //    printf("%s", "\n");
        //  sleep(3);

       }
         for(int c = j; c > -1; c--){
           *(*(m->entries+i)+c) = *(*(m->entries+i)+c) * current_pivot;
         }

      i--;
      j--;
    }
  //    printf("%s", "\n");
  //  m_print_matrix(m);
  m->kind = square_lower_triangular;
  }



void m_scalar_mult(Matrix *m, long double scalar){
  for(int i = 0; i < m->rows; i++){
    for(int j = 0; j < m->columns; j++){
      *(*(m->entries+i)+j) =  *(*(m->entries+i)+j) * scalar;
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

Matrix *m_inverse_matrix(Matrix *m){
  Matrix *copy = m_copy_matrix(m);
  double long determinant = m_determinant(copy);
  m_destroy_matrix(copy);
  Matrix *inverse = m_copy_matrix(m);
  m_scalar_mult(m, 1.000000/determinant);
  return inverse;
}

Matrix *m_copy_matrix(Matrix *m){
  Matrix *copy = m_create_matrix(m->rows, m->columns, NO);
  for(int i = 0; i < m->rows; i++){
    for(int j = 0; j < m->columns; j++){
      *(*(copy->entries+i)+j) =  *(*(m->entries+i)+j);
    }
  }
  return copy;
}
