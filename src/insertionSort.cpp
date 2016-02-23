/*
 * insertionSort.cpp
 *
 *  Created on: Aug 30, 2015
 *      Author: owner
 */

#include <iostream>
#include <cstring>
#include <cstdlib>

#include "insertionSort.h"

using namespace std;


/* ************************************************************************ */
/*                                                                          */
/*								insertion sort							    */
/*                                                                          */
/* ************************************************************************ */


void	insertionSort::exch(unsigned char *a, unsigned char *b, int size)
{
	if (size > 0)
	{
		unsigned char *tmp = new unsigned char[size];
		memcpy(tmp, a, size);
		memcpy(a, b, size);
		memcpy(b, tmp, size);
		delete[]	tmp;
	}
}



void	insertionSort::forwardSort( int *pBase,
			 	 	 	 	 int num,
			 	 	 	 	 int (*compare)(const int *, const int *))
{
	int	tmp;

	//	for every element in the array
	//		starting at #2 (which is the
	//		first element to have a predecessor)
	for (int i = 1; i != num; i++)
	{
		//	be prepared to move back to the start
		for (int j = i; j != 0; j--)
		{
			//	If this element is less than the
			//		previous element, sink the previous
			if (pBase[j] < pBase[j-1])
			{
				tmp			= pBase[j];
				pBase[j]	= pBase[j-1];
				pBase[j-1]	= tmp;
			}
			else
				break;
		}
	}
}


void	insertionSort::reverseSort( int *pBase, int num, int (*compare)(const int *, const int *))
{
	int tmp;
	int	last = num-1;

	for (int i = last-1 ; i >= 0; i--)
	{
		for (int j = i; j != last; j++)
		{
			//	If this element is greater than the next
			//		sink this element below the next
			if ( pBase[j] > pBase[j+1]){
				tmp			= pBase[j];
				pBase[j]	= pBase[j+1];
				pBase[j+1]	= tmp;
			}
			else
				break;
		}
	}
}


insertionSort::insertionSort() {
}

insertionSort::~insertionSort() {
}

