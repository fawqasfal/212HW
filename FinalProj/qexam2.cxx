// FILE: qexam2.cxx
// Written by: Michael Main (main@colorado.edu), April 17, 1997
//
// This file contains a function to test of the quicksort
// function from quick2.cxx. It should be compiled and then linked with
// quick2.cxx.

#include <iostream>
#include <stdlib.h>
#include "quick2.h"
using namespace std; 

const size_t TEST_SIZE = 3000; // Number of items in a random array
const int MAX = 1000;          // Items in random array range from 0...MAX

// The following is a comparison function that will compare two integers.
// Its two arguments (p1 and p2) are void pointers to the integers.
// The return value of the function is interpreted as follows:
//  negative means *p1 < *p2
//  zero     means *p1 == *p2
//  positive means *p1 > *p2
// In addition, if either of the integers is zero, then the static
// variable saw_zero is set to true.
#define assign(x,y) (memcpy((x), (y), bytes))
#define element(i) (((char*)base) + ((i)*bytes))
#define less_than(x,y) (compar((x),(y)) < 0)

static void insertion_sort(void* base, size_t n, size_t bytes, int compar(const void*, const void*)) {
    void *new_item = malloc(bytes);
    size_t i;
    size_t j;
        
    for (i = 1; i < n; i++) {   // Insert element i into the right place
    assign(new_item, element(i));
    for (j = i; (j > 0) && (less_than(new_item, element(j-1))); j--)
        assign(element(j), element(j-1));
    assign(element(j), new_item);
    }
    free(new_item);
}

int partition(void* pivot, void* base, size_t bytes, size_t low, size_t high, int compar(const void*, const void*)) {
    //everything to the right of *element(pivind) will be larger than it, and everything to left will be smaller
    void* temp = malloc(bytes);
    assign(temp, pivot);
    assign(pivot, element(high));
    assign(element(high), temp);

    void* piv_val = element(high);
    size_t pivind = low;
    for (int i = low; i < high; i++) 
        if (compar(element(i), piv_val) < 0) {
            assign(temp, element(pivind));
            assign(element(pivind), element(i));
            assign(element(i), element(pivind));
            pivind++;
        }
    assign(temp, element(pivind));
    assign(element(pivind), element(high));
    assign(element(high), temp);
    free(temp);
    return pivind;
}


void quicksort(void* base, size_t n, size_t bytes, int compar(const void*, const void*)) {
    if (n  < 2) 
        return;
    srand(time(NULL));
    size_t stack[n + 1];
    int ind = -1; //top of stack
    int l = 0; 
    int h = n - 1;
    stack[++ind] = l;
    stack[++ind] = h;
    while (ind >= 0) { 
        h = stack[ind--];
        l = stack[ind--];
       // if (h - l < 16) 
           // insertion_sort(element(0 + l), h - l, bytes, compar);
       // else {
            int piv = rand() % (h - l) + l; //random pivot point from i and size
            piv = partition(element(piv), base, bytes, l, h, compar);
            cout << "Wow!";
            if (piv > 1) {//we still have to sort the left side
                stack[++ind] = l;
                stack[++ind] = piv - 1;
            }
            if (piv < n - 1) {//we still have to sort the right hand side
                stack[++ind] = piv + 1;
                stack[++ind] = h;
            }
      //  }

    }
}

static bool saw_zero = false;
int compare_ints(const void *p1, const void* p2)
{
    int i1 = *((int *)p1);
    int i2 = *((int *)p2);

    if ((i1 == 0) || (i2 == 0)) saw_zero = true;
    return (i1 - i2);
}

bool access_okay( )
// Postcondition: If the compare_ints function ever saw a zero, then
// a message is printed about an illegal array access  and the function
// returns false (since none of the arrays contain the number zero!).
// Otherwise the function returns true.
{
    if (saw_zero)
	cerr << "Access of array occured outside of data[0]..data[n-1]."
             << endl << endl;
    return !saw_zero;
}

bool correct(int data[ ], int right[ ], size_t n)
// Precondition: data and right are arrays with at least n elements.
// If data[0] ... data[n] is the same as right[0] ... right[n], then
// "Test passed" is printed and the return value is true. Otherwise 
// "Incorrect sort" is printed and the return value is false.
{
    size_t i;
    
    for (i = 0; i < n; i++)
    {
        if (data[i] != right[i])
        {
            cerr << "Incorrect sort." << endl;
            return false;
        }
    }
    cerr << "Test passed." << endl << endl;
    return true;
}

int test1( )
// Postcondition: Tests have been run on the quicksort. If the tests are
// passed, then the function returns 50. Otherwise the function returns zero.
{
    int test[TEST_SIZE+2];      // Has an extra item on either end
    int right[TEST_SIZE];       // Correct data
    size_t occurrences[MAX+1];  // occurrences[i] is the number of times that
                                // i appears in a large random array.
    char test_letter = 'A';
    size_t i;                   // Used as an index of test or right
    int n;                      // A random number put into the test array
    size_t many;                // Number of random items put into the test array

    // Initialize the entire array to zeros. Therefore, if quicksort ever
    // accesses an illegal spot, then access_okay will return false.
    for (i = 0; i <= TEST_SIZE+1; i++) test[i] = 0;

    cerr << test_letter++ << ". ";
    cerr << "Testing quicksort with n=0. There should be no work." << endl;
    quicksort((void *)(test+1), 0, sizeof(int), compare_ints);
    if (!access_okay( )) return 0;
    cerr << "Test passed." << endl << endl;

    cerr << test_letter++ << ". ";
    cerr << "Testing quicksort with n=1. There should be no work." << endl;
    test[1] = 1;
    right[1] = 1;
    quicksort((void *)(test+1), 1, sizeof(int), compare_ints);
    if (!access_okay( )) return 0;
    if (!correct(test+1, right+1, 1)) return 0;

    cerr << test_letter++ << ". ";
    cerr << "Testing quicksort to sort 1 through 20." << endl;
    cerr << "The numbers in the data array start in order." << endl;
    for (i = 2; i <= 20; i++)
    {
        test[i] = i;
        right[i] = i;
    }
    quicksort((void *)(test+1), 20, sizeof(int), compare_ints);
    if (!access_okay( )) return 0;
    if (!correct(test+1, right+1, 20)) return 0;
    
    cerr << test_letter++ << ". ";
    cerr << "Testing quicksort to sort 20 downto 1." << endl;
    cerr << "The numbers in the data array start in backward order." << endl;
    for (i = 1; i <= 20; i++)
        test[i] = 21-i;
    quicksort((void *)(test+1), 20, sizeof(int), compare_ints);
      for (i = 0; i < 20; i++)
        cout << test[i] << " ";
    if (!access_okay( )) return 0;
    if (!correct(test+1, right+1, 20)) return 0;
  
 
    cerr << test_letter++ << ". ";
    cerr << "Testing quicksort to sort two copies of 1 through 10." << endl;
    for (i = 11; i <= 20; i++)
        test[i] = i-10;
    for (i = 1; i <= 20; i++)
        right[i] = (i+1) / 2;
    quicksort((void *)(test+1), 20, sizeof(int), compare_ints);
    if (!access_okay( )) return 0;
    if (!correct(test+1, right+1, 20)) return 0;

    cerr << test_letter++ << ". ";
    cerr << "Testing quicksort to sort " << TEST_SIZE << " random items.";
    cerr << endl;
    for (n = 0; n <= MAX; n++)
        occurrences[n] = 0;
    for (i = 1; i <= TEST_SIZE; i++)
    {
        n = rand( ) % MAX + 1;
        test[i] = n;
        occurrences[n]++;
    }
    many = 0;
    for (n = 0; n <= MAX; n++)
    {   // Put occurrences[n] copies of n into the right array
        for (i = 1; i <= occurrences[n]; i++)
            right[many+i] = n;
        many += occurrences[n];
    }
    quicksort((void *)(test+1), TEST_SIZE, sizeof(int), compare_ints);
    if (!access_okay( )) return 0;
    if (!correct(test+1, right+1, TEST_SIZE)) return 0;

    cerr << "Tests have passed, and I will award 50 points." << endl;
    cerr << "The (human) graders will check later to make sure that" << endl;
    cerr << "you followed directions for removing recursion, etc." << endl;
    
    return 50;
}

int main( )
{
 
    cerr << "Running quicksort test:" << endl;
 
    if (test1( ) > 0) cerr << "Test passed." << endl << endl;
    else cerr << "Test failed." << endl << endl; 

    return 0;

}
