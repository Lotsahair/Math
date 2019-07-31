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
     Matrix *a = m_create_matrix(3,6,YES );
   *(*(a->entries+0)+0)=0.000000;
  *(*(a->entries+0)+1)=0.000000;
  *(*(a->entries+0)+2)=-2.000000;
  *(*(a->entries+0)+3)=0.000000;
  *(*(a->entries+0)+4)=7.000000;
  *(*(a->entries+0)+5)=12.000000;
  *(*(a->entries+1)+0)=2.000000;
  *(*(a->entries+1)+1)=4.000000;
  *(*(a->entries+1)+2)=-10.000000;
  *(*(a->entries+1)+3)=6.000000;
  *(*(a->entries+1)+4)=12.000000;
  *(*(a->entries+1)+5)=28.000000;
  *(*(a->entries+2)+0)=2.000000;
  *(*(a->entries+2)+1)=4.000000;
  *(*(a->entries+2)+2)=-5.000000;
  *(*(a->entries+2)+3)=6.000000;
  *(*(a->entries+2)+4)=-5.000000;
  *(*(a->entries+2)+5)=-1.000000;
    m_print_matrix(a);
  printf("%s", "matrix a above \n");
              m_rref(a);
    printf("%s", "\n");
         m_print_matrix(a);
	 m_destroy_matrix(a);

  return 0;
}
