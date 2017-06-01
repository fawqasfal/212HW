// FILE: qtest2.cxx
// An interactive test program for the flexible quicksort function.
#include <ctype.h>      // Provides toupper
#include <iomanip.h>    // Provides setw
#include <iostream.h>   // Provides cout and cin
#include <stdlib.h>     // Provides EXIT_SUCCESS and size_t
#include "quick2.h"     // Provides prototype for quicksort( )

int get_number(const char message[ ]);
// Postcondition: The user has been prompted to enter an integer. The
// number has been read and returned by the function.

int compare_ints(const void* ptr1, const void* ptr2);
// Precondition: ptr1 and ptr2 actually point to integers.
// Postcondition: The return value is negative if *ptr1 < *ptr2; it is
// zero if *ptr1 == *ptr2, and it is positive if *ptr1 > *ptr2.

int main( )
{
    int *array;      // An dynamic array entered by the user, which we'll sort
    size_t i;        // An index for the array
    size_t size;     // The size of the dynamic array

    // Get the array size and allocate memory for the dynamic array.
    cout << "This program will sort an array of integers that you provide.n";
    cout << "How big is the array? ";
    cin >> size;
    array = new int[size];

    // Get the entries for the array
    for (i = 0; i < size; i++)
    {
	cout << "[" << i << "]";
	if (i < 10) cout << " ";
	array[i] = get_number(" Please type the next int in the array: ");
    }

    // Print the array, sort it, and print the array again
    cout << endl << "The array before and after sorting: " << endl;
    cout << "Before: ";
    for (i = 0; i < size; i++)
	cout << " " << setw(2) << array[i];
    cout << endl;
    quicksort(array, size, sizeof(int), compare_ints);
    cout << "After:  ";
    for (i = 0; i < size; i++)
	cout << " " << setw(2) << array[i];
    cout << endl;

    cout << endl << "Good-bye" << endl;
    return EXIT_SUCCESS;
}

int get_number(const char message[ ])
// Library facilities used: iostream.h
{
    int result;
    
    cout << message;
    cin  >> result;
    return result;
}

int compare_ints(const void* ptr1, const void* ptr2)
{
    // NOTE: *ptr1 is the first integer, but since ptr1 is a void
    // pointer, we must use the notation *((int *) ptr1) to refer to
    // this first integer. Similarly, *((int *) ptr2) refers to the
    // second integer. This comparison function works by subtracting
    // the second integer from the first, and returning the result.
    // This result meets the requirements listed above (for example,
    // it is negative when the second argument is larger than the
    // first.
    return *((int *) ptr1) - *((int *) ptr2);
}
}