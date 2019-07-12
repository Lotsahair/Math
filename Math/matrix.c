
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
  m->kind = regular;
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

void m_ref(Matrix *m){
  int i = 0;
  int j = 0;
  while(i < m->rows && j < m->columns){
    if(*(*(m->entries+i)+j) == 0){
      int k = i+1;
      while(k < m->columns){
	if(*(*(m->entries+k)+j) != 0){
	  m_swap_rows(*(m->entries+i), *(m->entries+k));
	  k= m->rows;
	}
  else{
    k++;
  }
      }
    }
    long double entry = *(*(m->entries+i)+j);
    // printf("%1.Lf%s", entry, "  ");
    for(int c = 0; c < m->columns; c++){
      for(int r = i; r < m->rows; r++){
	long double one = 1.0;
	//maybe using 1 causes error?
	*(*(m->entries+r)+c)= *(*(m->entries+r)+c) * one/entry;
	//	printf("%1.Lf", *(*(m->entries+l)+c));
      }
    }
    int a = i+1;
    //    printf("%s%d%s", "value of a:" , a, "\n");
    while(a < m->rows){
      long double zeroed_entry = *(*(m->entries+a)+j);
      printf("%Lf%s", zeroed_entry, "\n");
      for(int c = j; c < m->columns; c++){
	//	printf("%1.Lf", zeroed_entry);
	//	printf("%d%s%d%s", a, " ", c, "\n");
	*(*(m->entries+a)+c) = *(*(m->entries+a)+c) - *(*(m->entries+i)+j) * zeroed_entry;
      }
      a++;
    }
  i++;
  j++;
  }
}

void m_rref(Matrix *m){
  m_ref(m);
  for(int i = m->rows; i > 0; i--){
    for(int j = m->columns; j > 0; j){
      for(int a = i+1; 
}

void m_swap_rows(long double *r1, long double *r2){
  long double *temp;
  temp = r1;
  r1 = r2;
  r2 = temp;
}
