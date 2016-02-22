/*
 * selectionSort.cpp
 *
 *  Created on: Aug 30, 2015
 *      Author: owner
 */
#include <iostream>
#include <cstdlib>
#include <cstring>

#include "selectionSort.h"

using namespace std;

/* ************************************************************************************ */
/*                                                                                      */
/* 									Selection Sort										*/
/*																						*/
/*	starting at the first element, 														*/
/*    through and find the smallest element in the array								*/
/*	  exchange the smallest element with the current left-most element					*/
/*	until the left-most element is 'num'th												*/
/*																						*/
/* ************************************************************************************ */

void	selectionSort::exch(unsigned char *a, unsigned char *b, int size)
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


void	selectionSort::sort(int *pBase,
							int num,
							int (*compare)(const int *, const int *))
{
	int	*pLeftMost	= pBase;
	int	*pElement	= pBase;
	int	*pSmallest	= pBase;
	int	tmp;

	for (int i = 0; i < num; i++)
	{
		pElement	= pLeftMost;
		pSmallest	= pLeftMost;

		for (int j = i; j != num; j++)
		{
			if (*pElement < *pSmallest)
				pSmallest	= pElement;

			pElement++;
		}


		tmp			= *pSmallest;
		*pSmallest	= *pLeftMost;
		*pLeftMost	= tmp;

		pLeftMost++;
	}
}

//	default c-tor
selectionSort::selectionSort() {
}

selectionSort::~selectionSort() {
}

