00001 /* Copyright (C) 1995, 1997, 2001 Free Software Foundation, Inc.
00002    This file is part of the GNU C Library.
00003    Contributed by Ulrich Drepper <drepper@gnu.ai.mit.edu>, August 1995.
00004 
00005    The GNU C Library is free software; you can redistribute it and/or
00006    modify it under the terms of the GNU Lesser General Public
00007    License as published by the Free Software Foundation; either
00008    version 2.1 of the License, or (at your option) any later version.
00009 
00010    The GNU C Library is distributed in the hope that it will be useful,
00011    but WITHOUT ANY WARRANTY; without even the implied warranty of
00012    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
00013    Lesser General Public License for more details.
00014 
00015    You should have received a copy of the GNU Lesser General Public
00016    License along with the GNU C Library; if not, write to the Free
00017    Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
00018    02111-1307 USA.  */
00019 
 /***************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <ieee754.h>
#include <string.h>
 
//typedef unsigned long long uint64_t
 
typedef signed __int8 sint8;
typedef unsigned __int8 uint8;
typedef signed __int16 sint16;
typedef unsigned __int16 uint16;
typedef signed __int32 sint32;
typedef unsigned __int32 uint32;
typedef signed __int64 sint64;
typedef unsigned __int64 uint64;
 

struct drand48_data
{
 unsigned short int __x[3]; /* Current state. */
 unsigned short int __old_x[3]; /* Old state. */
 unsigned short int __c; /* Additive const. in congruential formula. */
  unsigned short int __init; /* Flag for initializing. */
 uint64 __a; /* Factor in congruential formula. */
};

 
/* Global state for non-reentrant functions. */
struct drand48_data __libc_drand48_data;
int __drand48_iterate (unsigned short int xsubi[3], struct drand48_data *buffer );
int __erand48_r (unsigned short int xsubi[3],struct drand48_data *buffer, double *result);
int drand48_r (struct drand48_data *buffer, double *result);
int seed48_r (unsigned short int seed16v[3],struct drand48_data *buffer);