/*
 * selectionSort_test.cpp
 *
 *  Created on: Aug 30, 2015
 *      Author: owner
 */

#if false
#include <iostream>
#include <iomanip>
#include <cassert>

#define	ARRAY_SIZE	64

#include "selectionSort.h"
#include "insertionSort.h"

using namespace std;

void	print(int *p, int size);
int		compare(const int *pLarger, const int *pSmaller);
bool	isSorted(const int *p, const int num, int (*compare)(const int *, const int *));


int		main( int argc, char* argv[])
{
	int	*pArray	= new int[ARRAY_SIZE];

	std::cout <<  static_cast<void*>(pArray) << std::endl;

	int *p	= pArray;
	for (int i = 0; i != ARRAY_SIZE; i++)
	{
		*p++ = ARRAY_SIZE-i;
	}

	cout << "Before selection sort: " << endl;
	print(pArray, ARRAY_SIZE);

	selectionSort::sort((unsigned char*)pArray, ARRAY_SIZE, sizeof(int), compare);

	assert(isSorted(pArray,ARRAY_SIZE,compare));
	cout << "After selection sort: " << endl;
	print(pArray, ARRAY_SIZE);

	p	= pArray;
	for (int i = 0; i != ARRAY_SIZE; i++)
	{
		*p++ = ARRAY_SIZE-i;
	}

	cout << "Before insertion sort: " << endl;
	print(pArray, ARRAY_SIZE);

	insertionSort::sort((unsigned char*)pArray, ARRAY_SIZE, sizeof(int), compare);

	assert(isSorted(pArray,ARRAY_SIZE,compare));

	cout << "After insertion sort: " << endl;
	print(pArray, ARRAY_SIZE);


	delete[]	pArray;
	pArray	= NULL;
}

void	print(int *p, int size)
{
#undef	LINE_SIZE
#define	LINE_SIZE	16
	int	elementCounter	= LINE_SIZE;

	for (int i = 0; i != size; i++)
	{
		cout << setw(5) << *p++;
		if(--elementCounter == 0)
		{
			elementCounter	= LINE_SIZE;
			cout << endl;
		}
	}
}

int		compare(const int *pLarger, const int *pSmaller)
{
	if (*pLarger > *pSmaller)
		return	1;
	if (*pLarger < *pSmaller)
		return	-1;
	return	0;
}

bool	isSorted(const int *p, const int num, int (*compare)(const int*, const int*))
{
	for (int i = 1; i != num; i++)
		//	Is the next one greater than or equal to the previous one?
		if (compare((p+i), (p+i-1)) < 0)
			return	false;

	return true;
}
#endif
