     
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
#ifndef MATRIX
#define MATRIX
#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define YES 1
#define NO 0
typedef enum{regular, square, identity, identity_square}Matrix_Kind;
typedef struct Matrices{
  unsigned long long rows;
  unsigned long long columns;
  long double **entries;
  Matrix_Kind kind;
}Matrix;

Matrix *m_create_matrix(unsigned long long rows, unsigned long long columns, int initialized);

void m_destroy_matrix(Matrix *m);

void m_print_matrix(Matrix *a);

Matrix *m_add_matrices(Matrix *a, Matrix *b, int destroying);
//does Strassen matrix multiplication on two matrices)
Matrix *m_strassen_multiplication(Matrix *a, Matrix *b, int destroying);
Matrix *m_multiply_matrices(Matrix *a, Matrix *b, int destroying);

Matrix *m_transpose_matrix(Matrix *a, int destroying);

//a helper function used for simple matrix multiplication
void m_ref(Matrix *m);
void m_rref(Matrix *m);
void m_swap_rows(long double *r1, long double *r2);
#endif
