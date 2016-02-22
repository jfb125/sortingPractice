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

#include "sorting.h"

using namespace std;

void	print(int *p, int size);
int		compare(const int *pLarger, const int *pSmaller);
int		isSorted(const int *p, const int num, int (*compare)(const int *, const int *));

#define	NUMBER_OF_ARRAYS			1024
#define	ELEMENTS_IN_LARGEST_ARRAY	65536

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
	if (*ppp)
	{
		for (int i = 0; i != numArrays; i++)
			if ((*ppp)[i])
			{
				delete[]	(*ppp)[i];
				(*ppp)[i]	= NULL;
			}

		delete[]	*ppp;
		*ppp	= NULL;
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

	int	*p;

//	static	int	pp[NUMBER_OF_ARRAYS][ELEMENTS_IN_LARGEST_ARRAY];
	int **pp	= NULL;
	try
	{
		pp	= new int *[NUMBER_OF_ARRAYS];
	}
	catch (std::bad_alloc& ba)
	{
		cout << "Pointer to type pointer, bad_aloc caught: " << ba.what() << endl;
		exit(-1);
	}

	for (int i = 0; i != NUMBER_OF_ARRAYS; i++)
	{
		try
		{
			pp[i]	= new int [ELEMENTS_IN_LARGEST_ARRAY];
		}
		catch (std::bad_alloc& ba)
		{
			cout << "Pointer to type int #" << i << " bad_alloc caught: " << ba.what() << endl;
			exit(-1);
		}
	}

	for (int arraySize = 256; arraySize < ELEMENTS_IN_LARGEST_ARRAY; arraySize <<= 1)
	{
		for (int repeatCounter = 0; repeatCounter != 10; repeatCounter++)
		{
			for (int i = 0; i != NUMBER_OF_ARRAYS; i++)
			{
				for (int j = 0; j != arraySize; j++)
					pp[i][j]	= rand() % arraySize;
			}

			for (int k = 0; k != NUMBER_OF_ARRAYS; k++)
			{
				p	= pp[k];
//				cout << "Pass #" << k << endl
//					 <<	" before: " << endl;
//				print(p, arraySize);

				t	= clock();

				sorting::BinaryHeap::sort(p, arraySize, compare);
		//		sorting::insertionSort::sort(p, arraySize, compare);
		//		sorting::mergeSort::sort(p, arraySize, compare);
		//		sorting::quickSort::sort(p, arraySize, compare);
		//		sorting::QuickSortWith3Waypartitioning::sort(p, arraySize, compare);
		//		sorting::selectionSort::sort(p, arraySize, compare);

				totalTime	+= clock()-t;

//				cout << "After:" << endl;
//				print(p, arraySize);

				if (isSorted(p, arraySize, compare) != 0)
				{
					releaseMemory(&pp, NUMBER_OF_ARRAYS);
					return -1;
				}
//					print(pArray, j);
			}	//	for k

		}	// for repeat count

		cout 	<< "Average of ten passes sorting "
				<< setw(5)
				<< NUMBER_OF_ARRAYS << " arrays of size "
				<< setw(10)
				<< arraySize 		<< " took me "
				<< setw(10) 		<< setprecision(6)
				<< totalTime/10 	<< " clicks ("
				<< setw(10) 		<< setprecision(6)
				<< ((double)totalTime)/CLOCKS_PER_SEC/10
				<< " seconds)." << endl;

	}	// for array size

	releaseMemory(&pp, NUMBER_OF_ARRAYS);

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
		cout << setw(4) << *p++ << ' ';
		if(--elementCounter == 0)
		{
			elementCounter	= LINE_SIZE;
			cout << endl;
		}
	}

	if (elementCounter != LINE_SIZE)	cout << endl;
}

int		compare(const int *pLarger, const int *pSmaller)
{
	if (*pLarger > *pSmaller)
		return	1;
	if (*pLarger < *pSmaller)
		return	-1;
	return	0;
}

int	isSorted(const int *p, const int num, int (*compare)(const int*, const int*))
{
	for (int i = 1; i != num; i++)
		//	Is the next one greater than or equal to the previous one?
		if (p[i] < p[i-1])
		{
			cout 	<< "At (i, i-1) " << i << ", " << i-1 << ", a[i] = " << p[i]
			        << " is not greater than or equal to a[i-1] = " << p[i-1] << endl;
			return	i;
		}
	return 0;
}

