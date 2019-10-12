
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
/* Maybe redundant to call it square upper/lower triangular as only square matrices can be in triangular form, but for readability's sake i call it this */
typedef enum{regular, square, identity, identity_square, square_upper_triangular, square_lower_triangular}Matrix_Kind;
typedef struct Matrices{
  unsigned long long rows;
  unsigned long long columns;
  long double **entries;
  Matrix_Kind kind;
  int current_row; //a helper variable used for the LP/ILP solver to know at which row we add the constraints
  /*A byte to denote whether we have had to swap rows to ensure nonzero entry in pivot. Used to adjus where to look for next entry */
  char has_swapped[1];
  int column_offset;
}Matrix;

Matrix *m_create_matrix(unsigned long long rows, unsigned long long columns, int initialized);

void m_destroy_matrix(Matrix *m);

void m_print_matrix(Matrix *a);

Matrix *m_add_matrices(Matrix *a, Matrix *b, int destroying);
Matrix *m_subtract_matrices(Matrix *a, Matrix *b, int destroying);
//does Strassen matrix multiplication on two matrices)
Matrix *m_strassen_multiplication(Matrix *a, Matrix *b, int destroying);
Matrix *m_multiply_matrices(Matrix *a, Matrix *b, int destroying);

Matrix *m_transpose_matrix(Matrix *a, int destroying);

//a helper function used for simple matrix multiplication
void m_ref(Matrix *m);
void m_rref(Matrix *m);

/* Swaps rows. Assume row one is equal in size to row 2 */
void m_swap_rows(long double *r1, long double *r2, int size);

Matrix *m_rowwise_merge_matrix(Matrix *a, Matrix *b, int destroying);

Matrix *m_columnwise_merge_matrix(Matrix *a, Matrix *b, int destroying);

double long m_determinant(Matrix *m);

void m_scalar_mult(Matrix *m, long double scalar);

void m_lower_tri_form(Matrix *m);

void m_upper_tri_form(Matrix *m);

Matrix *m_create_identity_matrix(unsigned long long rows, unsigned long long columns);

Matrix *m_copy_matrix(Matrix *m);

Matrix *m_inverse_matrix(Matrix *m);
#endif
