/*
 * sorting_test.cpp
 *
 *  Created on: Aug 30, 2015
 *      Author: owner
 */

#define	FLOAT_FORMAT	setw(12) << fixed << setprecision(6)

#include <iostream>
#include <iomanip>
#include <cassert>
#include <cstdlib>	// rand
#include <fstream>
#include <cstring>

#include "sorting.h"

using namespace std;

#define	NUMBER_OF_ARRAYS			1024
#define	ELEMENTS_IN_LARGEST_ARRAY	65536
#define	NUMBER_OF_TESTS				16

int		compare(const int *pLarger, const int *pSmaller);
void	getMemory(int ***ppp, int numArrays, int numElements);
bool	isSorted(const int *p, const int num, int (*compare)(const int *, const int *));
void	print(int *p, int size);
void	printTimeReport(int num, int size, int passes, const char *name, unsigned elapsedClicks);
void	releaseMemory(int ***ppp, int numArrays);

int		main( int argc, char* argv[])
{
	const char	*sortName;
	void		(*sort)(int *, int , int (*)(const int *, const int *));

	//sortName	= "binary heap sort"
	//sort 		=		sorting::BinaryHeap::sort(p, arraySize, compare);
	//sort 		=		sorting::BubbleSort::sortForward(p, arraySize, compare);
	//sort 		=		sorting::BubbleSort::sortReverse(p, arraySize, compare);
	//sort 		=		sorting::insertionSort::forwardSort(p, arraySize, compare);
	//sort 		=		sorting::insertionSort::reverseSort(p, arraySize, compare);
	//sortName 	= 	"merge sort";
	//sort 		= 	sorting::mergeSort::sort;
	//sort 		=	sorting::mergeSort::sort(p, arraySize, compare);
	sortName	= 	"quick sort";
	sort 		=	sorting::quickSort::sort;
	//sortName	= 	"shell sort";
	//sort 		=	sorting::ShellSort::sort;

	//sortName	= "selection sort";
	//sort =		sorting::selectionSort::sort;

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


//	t	= clock();
//	for (int i = 0; i != NUMBER_OF_ARRAYS; i++)
//	{
//		for (int j = 0; j != ELEMENTS_IN_LARGEST_ARRAY; j++)
//			arrays[i][j]	= rand() % ELEMENTS_IN_LARGEST_ARRAY;
//	}
//	t	= clock()-t;

//	cout	<< "It took " << t << " clicks to load arrays with random numbers" << endl;

	for (int arraySize = 256; arraySize < ELEMENTS_IN_LARGEST_ARRAY; arraySize <<= 1)
	{
		totalTime	= 0;
		for (int repeatCounter = 0; repeatCounter != NUMBER_OF_TESTS; repeatCounter++)
		{
			for (int i = 0; i != NUMBER_OF_ARRAYS; i++)
				for (int j = 0; j != arraySize; j++)
					arrays[i][j]	= rand() % arraySize;

			for (int arrayNumber = 0; arrayNumber != NUMBER_OF_ARRAYS; arrayNumber++)
			{

				t	= clock();
				sort(arrays[arrayNumber], arraySize, compare);
				totalTime	+= clock()-t;

				if (!isSorted(arrays[arrayNumber], arraySize, compare))
				{
					cout << "Array is not sorted." << endl;
					releaseMemory(&arrays, NUMBER_OF_ARRAYS);
					return -1;
				}
			}	//	for every array
		}	// for repeat count

		printTimeReport(NUMBER_OF_ARRAYS, arraySize, NUMBER_OF_TESTS, sortName, totalTime);

	}	// for array size

	releaseMemory(&arrays, NUMBER_OF_ARRAYS);

	cout << "Complete" << endl;
	return 0;
}


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


void	print(int *p, int size)
{
#undef	_SORTING_TEST_LINE_SIZE
#define	_SORTING_TEST_LINE_SIZE	16
	int	elementCounter	= _SORTING_TEST_LINE_SIZE;

	for (int i = 0; i != size; i++)
	{
		cout << setw(8) << *p++ << ' ';
		if(--elementCounter == 0)
		{
			elementCounter	= _SORTING_TEST_LINE_SIZE;
			cout << endl;
		}
	}

	if (elementCounter != _SORTING_TEST_LINE_SIZE)	cout << endl;
}


void	releaseMemory(int ***ppp, int numArrays)
{
	if (**ppp)
	{
		for (int i = 0; i != numArrays; i++)
			if ((*ppp)[i])
			{
				delete[]	(*ppp)[i];
				(*ppp)[i]	= nullptr;
			}

		delete[]	(*ppp);
		*ppp	= nullptr;
	}
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

void	printTimeReport(int num, int size, int passes, const char *name, unsigned elapsedClicks)
{
	cout 	<< "Total of " << passes << " passes of " << name
			<< setw(5)	<< num 				<< " arrays of size "
			<< setw(10)	<< size 			<< " took me "
//			<< setw(12) << elapsedClicks 	<< " clicks ("
			<< setw(12) << fixed << setprecision(6)
			<< ((double)elapsedClicks)/CLOCKS_PER_SEC
			<< " seconds." << endl;
}
