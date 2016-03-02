/*
 * mergeSort.cpp
 *
 *  Created on: Aug 30, 2015
 *      Author: owner
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>

#include "mergeSort.h"

using namespace std;
#if true
void	mergeSort::sort(int *pArray,
						int num,
						int (*compare)(const int *, const int *))
{
	if (num < 2)
		return;

	int other[num];

	int	gap 	= 1;				//	Start with a half width of side-by-side (1)
	int	leftStart,					//	The leftmost element on this segment
		rightStart,					//  The rightmost element on this segment
		rightStop;					//	The farthest right element on this segment

	int	dst,						//  Destination array's index
		leftSource, rightSource;	//	Source indexes

	int *pDst	= pArray;			//	These will be swapped before 1st pass
	int	*pSrc	= other;
	int	*pSwap;

	while (gap < num)
	{
		//	Swap source & dst pointers
		pSwap		= pSrc;
		pSrc		= pDst;
		pDst		= pSwap;

		//	Start from the left side of the array
		dst			= 0;
		leftStart	= 0;

		while (dst < num)
		{
			rightStart	= leftStart+gap;
			if (rightStart >= num) {
				rightStart 	= num;
				rightStop	= num;
			} else {
				rightStop	= rightStart+gap;
				if (rightStop > num)
					rightStop	= num;
			}

			leftSource	= leftStart;
			rightSource	= rightStart;

			//	While they both have elements to contribute to the dest
			while(leftSource < rightStart && rightSource < rightStop)
			{
				if (pSrc[leftSource] <= pSrc[rightSource])
					pDst[dst++]	= pSrc[leftSource++];
				else
					pDst[dst++]	= pSrc[rightSource++];
			}

			//	Copy whichever elements did not get copied (if any)
			while(leftSource != rightStart)
				pDst[dst++]	= pSrc[leftSource++];
			while(rightSource != rightStop)
				pDst[dst++]	= pSrc[rightSource++];

			//	Move to the next segment of the array
			leftStart	+= 2 * gap;
		}

		gap	*= 2;
	}

	//	If the destination of the previous pass was not
	//		the target, copy the other array into
	//		the target
	if (pDst != pArray)
		memcpy(pArray,other, num*sizeof(int));
}

#else
void	mergeSort::sort( int *pArray,
					 	 int num,
					 	 int (*compare)(const int *, const int *))
{
	int *pTmp = new int[num];

	int *pSrc	= (int*)pArray;
	int *pDst	= (int*)pTmp;

	int	halfwidth;

	int lowest, middle, highest;

	int i, j;

	halfwidth	= 1;

	while (halfwidth < num)
	{
		lowest	= 0;
		middle	= lowest+halfwidth;
		highest	= middle+halfwidth;
		if (highest > num)			highest = num;

		while (lowest < num)
		{
			i	= lowest;
			j	= middle;

			for (int dst = lowest; dst != highest; dst++)
			{
				//	if we do not have any elements in the left half of the array
				//		keep copying the right half;
				if (i >= middle)			pDst[dst]	= pSrc[j++];
				//	if we do not have any elements in the right half of the array,
				//		keep copying the left half
				else if (j >= highest)		pDst[dst] = pSrc[i++];
				//	if j is the smaller of the two, take it
				else if (pSrc[j] < pSrc[i])
					pDst[dst]	= pSrc[j++];
				else
				//	if i is the smaller, or if the two are equal,
				//	always move the left one
					pDst[dst]	= pSrc[i++];
			}	// for dst = lowest to highest

			lowest		+= (halfwidth*2);
			middle		= lowest+halfwidth;
			highest		= middle+halfwidth;
			if (highest > num)			highest = num;
		}	// while(highest <= num)

/*
		cout << "After pass with width: " << 2*halfwidth << endl;
		cout << "pSrc: " << endl;
		printArray(pSrc, num);
		cout << endl;
		cout << "pDst: " << endl;
		printArray(pDst, num);
		cout << endl;
*/

		halfwidth	<<= 1;

		//	Swap the destination and source pointers
		if (pDst == (int*)pArray)
		{
			pDst	= (int*)pTmp;
			pSrc	= (int*)pArray;
		}
		else
		{
			pDst	= (int*)pArray;
			pSrc	= (int*)pTmp;
		}
	}	// while(width <= num/2)

	//	If the given array was not the destination
	//		of the final sort, copy the destination
	//		of the final sort in to the given array
	//	<<< THIS COMPARISON IS AFTER THE POINTERS HAVE BEEN SWAPPED >>>

	if (pDst == (int *)pArray)
	{
		for (int k = 0; k != num; k++)
			*pDst++	= *pSrc++;
	}
}	// sort

#endif


void	mergeSort::printArray(int *p, int num)
{
	int	linePos	= 0;

	while (num != 0)
	{
		cout << setw(5) << *p++;
		if(linePos++  == 15)
		{
			linePos	= 0;
			cout << endl;
		}
		num--;
	}
}

const char * mergeSort::getName(){	return	"merge sort";	}

mergeSort::mergeSort() {
	// TODO Auto-generated constructor stub
}

mergeSort::~mergeSort() {
	// TODO Auto-generated destructor stub
}

