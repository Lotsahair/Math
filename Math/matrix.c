
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
  m->entries = malloc(rows * sizeof(int*));
  if(m->entries == NULL){
    printf("%s", "Not neough memory available for matrix creation" );
  }
  for(i=0; i<rows; i++){
    m->entries[i] = malloc(columns * sizeof(int));
  }
  if(initialized == 1){
    srand(time(NULL));
    for(i = 0; i < rows; i++){
      for(j = 0 ; j < columns; j++){
	int val = rand() % 100 +1;
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
      printf("%d", *(*(a->entries+i)+j));
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

//Matrix *m_transpose_matrix(Matrix *a){

  //}
