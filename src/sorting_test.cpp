/*
 * sorting_test.cpp
 *
 *  Created on: Aug 30, 2015
 *      Author: owner
 */

#include <iostream>
#include <iomanip>
#include <cassert>
#include <cstdlib>	// rand
#include <fstream>
#include <cstring>

#include "sorting.h"

using namespace std;

void	print(int *p, int size);
int		compare(const int *pLarger, const int *pSmaller);
bool	isSorted(const int *p, const int num, int (*compare)(const int *, const int *));

#define	NUMBER_OF_ARRAYS			1024
#define	ELEMENTS_IN_LARGEST_ARRAY	65536
#define	NUMBER_OF_TESTS				1

void	getMemory(int ***ppp, int numArrays, int numElements)
{
	cout 	<< "getMemory(" << ppp
			<< ", " 		<< numArrays
			<< ", " 		<< numElements
			<< ")" 			<< endl;

	if (numArrays == 0 || numElements == 0)
		return;

	try
	{
		(*ppp)	= new int *[numArrays];
	}
	catch (std::bad_alloc& ba)
	{
		cout << "Pointer to type pointer, bad_aloc caught: " << ba.what() << endl;
		exit(-1);
	}

	for (int i = 0; i != numArrays; i++)
	{
		try
		{
			(*ppp)[i]	= new int [numElements];
		}
		catch (std::bad_alloc& ba)
		{
			cout << "Pointer to type int #" << i << " bad_alloc caught: " << ba.what() << endl;
			exit(-1);
		}
	}
}


void	releaseMemory(int ***ppp, int numArrays)
{
	if (**ppp)
	{
		for (int i = 0; i != numArrays; i++)
			if ((*ppp)[i])
			{
//				cout << "Deleting (*ppp)[" << i << "] " << (*ppp)[i] << endl;
				delete[]	(*ppp)[i];
				(*ppp)[i]	= nullptr;
			}

		delete[]	(*ppp);
//		cout << "Deleting " << *ppp << endl;
		*ppp	= nullptr;
	}
}


//charBinaryHeap	loadValues[]	= "PABXWPPVPDPCYZ";
//char	loadValues[]	= "RBWWRWBRRWBR";
//const	int	problemValues[]	= {3,    0,    5,    1,    4,    5,    6,    0};

int		main( int argc, char* argv[])
{
	clock_t	t;
	unsigned totalTime	= 0;

	srand (time(NULL));

	int	**arrays;

	try
	{
		arrays	= new int *[NUMBER_OF_ARRAYS];
	}
	catch (std::bad_alloc& ba)
	{
		cout << "Pointer to pointer to int, bad_aloc caught: " << ba.what() << endl;
		exit(-1);
	}


	for (int i = 0; i != NUMBER_OF_ARRAYS; i++)
	{
		try
		{
			arrays[i]	= new int [ELEMENTS_IN_LARGEST_ARRAY];
		}
		catch (std::bad_alloc& ba)
		{
			cout << "Pointer to type int #" << i << ", bad_alloc: " << ba.what() << endl;
			exit(-1);
		}
	}


	t	= clock();
	for (int i = 0; i != NUMBER_OF_ARRAYS; i++)
	{
		for (int j = 0; j != ELEMENTS_IN_LARGEST_ARRAY; j++)
			arrays[i][j]	= rand() % ELEMENTS_IN_LARGEST_ARRAY;
	}
	t	= clock()-t;

	cout	<< "It took " << t << " clicks to load arrays with random numbers" << endl;
	unsigned passTime;

	for (int arraySize = 256; arraySize < ELEMENTS_IN_LARGEST_ARRAY; arraySize <<= 1)
	{
		int	*p = new int [arraySize];

		for (int repeatCounter = 0; repeatCounter != NUMBER_OF_TESTS; repeatCounter++)
		{
			for (int arrayNumber = 0; arrayNumber != NUMBER_OF_ARRAYS; arrayNumber++)
			{
				passTime	= clock();

				memcpy(p, arrays[arrayNumber], arraySize*sizeof(int));

//				cout << "Pass #" << arrayNumber << endl
//					 <<	" before: " << endl;
//				print(p, arraySize);

				t	= clock();

		//		sorting::BinaryHeap::sort(p, arraySize, compare);
		//		sorting::BubbleSort::sortForward(p, arraySize, compare);
		//		sorting::BubbleSort::sortReverse(p, arraySize, compare);
		//		sorting::insertionSort::forwardSort(p, arraySize, compare);
		//		sorting::insertionSort::reverseSort(p, arraySize, compare);
		//		sorting::mergeSort::sort(p, arraySize, compare);
				sorting::quickSort::sort(p, arraySize, compare);
		//		sorting::QuickSortWith3Waypartitioning::sort(p, arraySize, compare);
		//		sorting::selectionSort::sort(p, arraySize, compare);

				unsigned	deltaTime = clock()-t;
				totalTime	+= deltaTime;

//				cout	<< "It took " << deltaTime << " clicks to sort the array" << endl;

//				cout << "After:" << endl;
//				print(p, arraySize);
				t	= clock();

				if (!isSorted(p, arraySize, compare))
				{
					cout << "Array is not sorted." << endl;
					releaseMemory(&arrays, NUMBER_OF_ARRAYS);
					return -1;
				}
				passTime	= clock() - passTime;
//				cout	<< "It took " << passTime << " to go through  sorting & check #" << arrayNumber << endl;
//					print(pArray, j);
			}	//	for every array

		}	// for repeat count
#define	FLOAT_FORMAT	setw(12) << fixed << setprecision(6)

		cout 	<< "Average of " << NUMBER_OF_TESTS << " passes 'quicksort' sorting "
				<< setw(5)
				<< NUMBER_OF_ARRAYS << " arrays of size "
				<< setw(10)
				<< arraySize 		<< " took me "
				<< FLOAT_FORMAT
				<< totalTime/10 	<< " clicks ("
				<< FLOAT_FORMAT
				<< ((double)totalTime)/CLOCKS_PER_SEC/NUMBER_OF_TESTS
				<< " seconds)." << endl;

	}	// for array size

	releaseMemory(&arrays, NUMBER_OF_ARRAYS);

	cout << "Complete" << endl;
	return 0;
}


void	print(int *p, int size)
{
#undef	LINE_SIZE
#define	LINE_SIZE	16
	int	elementCounter	= LINE_SIZE;

	for (int i = 0; i != size; i++)
	{
		cout << setw(8) << *p++ << ' ';
		if(--elementCounter == 0)
		{
			elementCounter	= LINE_SIZE;
			cout << endl;
		}
	}

	if (elementCounter != LINE_SIZE)	cout << endl;
}

int		compare(const int *a, const int *b)
{
	if (*a > *b)
		return	1;
	if (*a < *b)
		return	-1;
	return	0;
}

bool	isSorted(const int *p, const int num, int (*compare)(const int*, const int*))
{
	for (int i = 1; i != num; i++)
		//	Is this one greater than or equal to the previous one?
		if (p[i] < p[i-1])
		{
			cout 	<< "At (i, i-1) " << i << ", " << i-1 << ", a[" << i-1 << "] = " << p[i-1]
			        << " is not less than or equal to a["<< i << "] = " << p[i] << endl;
			return	false;
		}
	return true;
}

