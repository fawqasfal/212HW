// FILE: quick2.h\
//\
// PROVIDES: A better quicksort function:\
//   void quicksort(\
//       void* base,\
//       size_t n,\
//       size_t bytes,\
//       int compar(const void*, const void*)\
//   )\
//   Precondition: data is a pointer to the first component of an array\
//   with at least n elements. The component type of the array may be\
//   any type at all, and the parameter bytes must be the number of bytes\
//   in each component of the array. The fourth parameter, compar, must\
//   be the name of a function that can compare two elements of the data\
//   array. The two arguments of compar are pointers to two elements in\
//   the data array, and the return value of compar indicates which of the\
//   two arguments is largest, as follows:\
//     -- a negative return value means that the 2nd argument is larger\
//     -- a zero return value indicates that the arguments are equal\
//     -- a positive return value means that the 1st argument is larger\
//   Postcondition: The elements of data have been rearranged so\
//   that data[0] <= data[1] <= ... <= data[n-1].\
//\
/* EXAMPLE OF USING quicksort TO SORT AN ARRAY OF 4000 ints:\
     1. The calling program must declare a comparison function, like this:\
     int compare_ints(const void* ptr1, const void* ptr2)\
     \{\
	 // NOTE: *ptr1 is the first integer, but since ptr1 is a void\
	 // pointer, we must use the notation *((int *) ptr1) to refer to\
	 // this first integer. Similarly, *((int *) ptr2) refers to the\
	 // second integer. This comparison function works by subtracting\
	 // the second integer from the first, and returning the result.\
	 // This result meets the requirements listed above (for example,\
	 // it is negative when the second argument is larger than the\
	 // first.\
	 return *((int *) ptr1) - *((int *) ptr2);\
     \}\
  \
     2. In the calling program you can now declare an array of 4000 integers,\
     and use quicksort to sort the array, as shown here:\
\
     int my_numbers[4000];\
     ...code to put 4000 numbers into the array my_numbers...\
\
     // Now use quicksort. Note that the array my_numbers is the first\
     // argument (but we need to cast it to void* to match the quicksort\
     // prototype). The second argument is the number of elements in the\
     // array. The third argument is the number of bytes in each array\
     // component (obtained by using the predefined sizeof operator).\
     // The fourth arguement is the comparison function listed above.\
     quicksort((void *)my_numbers, 4000, sizeof(int), compare_ints);\
*/

#include <stdlib.h>    // Provides size_t\
void quicksort(void* base, size_t n, size_t bytes, int compar(const void*, const void*));
