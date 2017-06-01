#include "quick2.h"
#include <time.h> 
#include <algorithm>
#include <iostream>

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
	return pivind;
}


void quicksort(void* base, size_t n, size_t bytes, int compar(const void*, const void*)) {
	srand(time(NULL));
	size_t stack[n + 1];
	int ind = -1; //top of stack
	int i = 0; 
	size_t size = n;
	stack[++ind] = i;
	stack[++ind] = size;
	while (ind >= 0) { 
		size = stack[ind--];
		i = stack[ind--];
		if (size < 16) 
			insertion_sort(base, size, bytes, compar);
		else {
			int piv = rand() % (size - i) + i; //random pivot point from i and size
			piv = partition(element(piv), base, bytes, i, size, compar);
			if (piv > 1) {//we still have to sort the left side
				stack[++ind] = i;
				stack[++ind] = piv;
			}
			if (piv < n - 1) {//we still have to sort the right hand side
				stack[++ind] = piv + 1;
				stack[++ind] = n;
			}
		}

	}
}
