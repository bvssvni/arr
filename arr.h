/*
 Arr - Generic arrays in C with length.
 BSD license.
 by Sven Nilsen, 2012
 http://www.cutoutpro.com
 
 Version: 0.000
 Angular degrees versioning notation
 http://isprogrammingeasy.blogspot.no/2012/08/angular-degrees-versioning-notation.html
 */
/*
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 1. Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.
 2. Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 The views and conclusions contained in the software and documentation are those
 of the authors and should not be interpreted as representing official policies,
 either expressed or implied, of the FreeBSD Project.
 */
/*
 
 C arrays are represented as pointers, but does not allow checking the length.
 This makes translation harder from other languages.
 
 Go             C                                   Arr (this library)
 
 x := [10]int   int x[20] = {};                     arr_init_size(int, x, 10);
 xn := len(x)   int xn = sizeof(x)/sizeof(*x);      long xn = arr_len(x);
 
 void my_function(int n, int *arr);  // C, but not common in most languages.
 void my_function(int *arr);         // With Arr the length can be skipped.
 
 The length of arrays in Arr is long to provide better support on 64 bit CPUs.
 
 We can also see this in data structures, where the number of items in the array
 require an extra variable. 
 
 // Normal C            // With Arr
 typedef struct A       typedef struct A
 {                      {
    int rc;                 double *r;
    double *r;          }
 }
 
 Last is that C does not initialize arrays by standard, which can result in
 crash and damage of data. Using Arr is safer.
 
 // To use it.
 #include "arr.h"
 
 // To initialize an array by detecting size.
 arr_init(double, a, 2.3, 4.5);
 
 // Initialize an array by a fixed size.
 arr_init_size(double, a, 10);
 
 // To get the length of an array.
 long n = arr_len(a);
 
 // To release the memory allocated by array.
 arr_free(a);
 
 IMPORTANT
 
 The memory is dynamically allocated, so you have to use the function 'arr_free'.
 Otherwise it acts just like a normal C array, starting at 0.
 */

#ifndef ARR_MEMGUARD
#define ARR_MEMGUARD

#include <string.h>
#include <stdlib.h>

#define arr_len(a) *((long*)(a)-1)
#define arr_init(type, a, ...) \
type macro_##a##_data[] = {__VA_ARGS__}; \
long *macro_##a##_struct = malloc(sizeof(macro_##a##_data)+sizeof(long)); \
memcpy(macro_##a##_struct+1, macro_##a##_data, sizeof(macro_##a##_data)); \
*macro_##a##_struct = sizeof(macro_##a##_data)/sizeof(type); \
type *a = (type*)(macro_##a##_struct+1);
#define arr_init_size(type, a, n) \
long *macro_##a##_struct = malloc(n*sizeof(type)+sizeof(long)); \
memset(macro_##a##_struct, 0, n*sizeof(type)+sizeof(long)); \
*macro_##a##_struct = n*sizeof(type)/sizeof(type); \
type *a = (type*)(macro_##a##_struct+1);
#define arr_free(a) free((long*)(a)-1)

#endif

