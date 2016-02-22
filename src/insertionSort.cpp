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



void	insertionSort::sort( int *pBase,
			 	 	 	 	 int num,
			 	 	 	 	 int (*compare)(const int *, const int *))
{
	int	tmp;

	for (int i = 1; i != num; i++)
	{
		for (int j = i; j != 0; j--)
		{
			if (pBase[j] < pBase[j-1])
			{
				tmp			= pBase[j];
				pBase[j]	= pBase[j-1];
				pBase[j-1]	= tmp;
			}
		}
	}
}


insertionSort::insertionSort() {
}

insertionSort::~insertionSort() {
}

