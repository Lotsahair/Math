#include "matrix.h"
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
int main(int argc, char *argv[]){
  Matrix *a = m_create_matrix(7,9, YES);
  // Matrix *b = m_create_matrix(40000, 3000, YES);
   m_print_matrix(a);
   m_ref(a);
   printf("%s", "\n");
   m_print_matrix(a);
   m_destroy_matrix(a);
  // printf("%s", "matrix a above \n");
  // m_print_matrix(b);
  //  printf("%s", "matrix b above \n");
  //  printf("%s", "matrix c above \n");
     // m_destroy_matrix(c);
  //  printf("%s", "here is the number \n");
  // printf("%d", f);
  return 0;
}
