/*
 * quickSort.cpp
 *
 *  Created on: Sep 5, 2015
 *      Author: owner
 */

#define	debugOut(n)	//debugOut( n
#define	printQSArray()

#include <iostream>
#include <iomanip>
#include <string>

#include "quickSort.h"

using namespace std;

void	quickSort::sort(int *pArray,
						int num,
						int (*compare)(const int *, const int *))
{
	if (num < 2)	return;

	sort(pArray, 0,	num-1,	compare);
//	partitionWithThreeWay(pArray, 0, num-1, compare);
}


void	quickSort::sort( int *pArray, int low, int high,
					 	 int (*compare)(const int *, const int *))
{
	if (high <= low)	return;
	int pposition	=  partitionWithOnePivot(pArray, low, high, compare);
	sort(pArray, low, 			pposition-1,	compare);
	sort(pArray, pposition+1,	high,	   		compare);
}


/*	The goal here is to organize the array into three parts:
 * 		Less Than partition	:	== Partition	: Greater Than Partition
 * 		lt	is the index of where the next value 'less than' the partition will go
 * 		gt	is the index of where the next value 'greater than' the partition will go
 * 		i is simply the index
 */
void	quickSort::swap(int *a, int p, int q){
	int	tmp	= a[p];
	a[p] = a[q];
	a[q] = tmp;
}

void		quickSort::partitionWithThreeWay(int *a, int low, int high, int (*compare)(const int *, const int *))
{
	if (high <= low)	return;

	int 	dstLT	= low;
	int		dstGT	= high;
	int		i		= low;

	while (i <= dstGT)
	{
		if(a[i] < a[dstLT])			swap(a, i++, dstLT++);
		else if (a[i] > a[dstLT])	swap(a, i, dstGT--);
		else						i++;
	}

	partitionWithThreeWay(a, low, dstLT-1, compare);
	partitionWithThreeWay(a, dstGT+1, high, compare);
}

int		quickSort::partitionWithOnePivot(int *a, int low, int high, int (*compare)(const int *, const int *))
{
	if (high <= low)	return 0;

	int	lessThan	= low;
	int	greaterThan	= high+1;
	int	pivotValue	= a[low];
	int tmp;

	while(true)
	{
		while(a[++lessThan] < pivotValue)
			if (lessThan == high)
				break;
		while(a[--greaterThan] > pivotValue);

		if (lessThan >= greaterThan)
			break;

		tmp				= a[lessThan];
		a[lessThan]		= a[greaterThan];
		a[greaterThan]	= tmp;
	}

	a[low]			= a[greaterThan];
	a[greaterThan]	= pivotValue;

	return	greaterThan;
}


//	Partitioning using the leftmost element as the partitioning value
int		quickSort::partitionLeft( int *pArray,
					 	 	  int low,
					 	 	  int high,
					 	 	  int (*compare)(const int *, const int *))
{
	if(high == low)	return 0;

	int i, j, tmp;

	//	'i' will pre-increment during the first pass
	//		which will cause the 0th element
	//		to not be swapped, which is necessary
	//		to preserve the 0th element as the partition
	i	= low;

	j	= high+1;

	int partitioningValue	= pArray[low];
	int	partitioningIndex 	= low;

	while (true)
	{
		//	find the leftmost item that is larger
		//		or equal to the partitioning element
		//	if the element is larger than the partitioning
		//		element, it needs to be swapped
		//	a pre-increment is necessary b/c we to
		//		not want to advance i once it
		//		is at the element to be swapped
		while (pArray[++i] < partitioningValue)
		{
			if (i == high)		break;
		}

		//	move past all the elements at the right
		//		that are greater than the partitioning element
		//		and are thus in place

		while (pArray[--j] > partitioningValue)
		{
			// 	The partitioning element is at low, so
			//	  while([--j] > [low]) will break out of the loop
			//		without having to do this check:
			//if (j == low)		break;
		}

		if (i >= j)			break;


		//	[i] is first leftward element 		> partitioning element &&
		//	[j] is farthest rightward element 	< partitioning element
		//	exchange them so that
		//	[i] is less than the partitioning element &&
		//	[j] is greater than the partitioning element
		tmp			= pArray[i];
		pArray[i]	= pArray[j];
		pArray[j]	= tmp;
	}

	//	Exchange the partition value with the rightmost value < or = to the partition
	pArray[partitioningIndex]	= pArray[j];
	pArray[j]					= partitioningValue;

	return	j;
}



//	Partition using the right most element as the partitioning value
//	left & right must point to their respective end elements i.e. - right = num-1

int		quickSort::partitionRight(int *pArray,
					 	 	  	  int left,
								  int right,
								  int (*compare)(const int *, const int *))
{
	if (right <= left)	return 0;

	int		lessThan		= left-1;	// Index that starts at left and moves to the right
	int		greaterThan		= right;  	// Index that starts at right-1 and moves to the left
	int		partitionIndex  = right;	// Index &		Value of partitioning element
	int		partitionValue	= pArray[partitionIndex];
	int		tmp;

	while (true)
	{
		//	move to each element rightwards starting at the left & then compare it
		while (pArray[++lessThan] < partitionValue);

		//	One element was found that was > or = to partition value
		//	also, the lessThan index may be at the partitionIndex

		//	move to each element leftwards starting to the left of the partition value
		while (pArray[--greaterThan] > partitionValue){
			if(greaterThan == left) break;
		}
		//	one element was found that was less than (or equal to) the partitioning value

		//	If the pointers cross, then there are no smaller to the right of lt
		//	and no larger to the left of gt
		if (greaterThan <= lessThan)
			break;

		//	lt is at an element that is larger than (or equal to) the partitionValue
		//	gt is at an element that is smaller than (or equal to) to the partitionValue
		//	exchange the two values  If the two values are equal to the partitioning element
		//		this exchange will not disrupt the process although it is arguably unnecessary
		tmp					= pArray[lessThan];
		pArray[lessThan]	= pArray[greaterThan];
		pArray[greaterThan]	= tmp;

	}

	//	exchange the partitioning element with the place that has none larger to the left
	//		and none smaller to the right
	pArray[partitionIndex]	= pArray[lessThan];
	pArray[lessThan]		= partitionValue;

	return	lessThan;
}


void	quickSort::exch(int *pArray, int i, int j)
{
	int		tmp	= pArray[i];
	pArray[i]	= pArray[j];
	pArray[j]	= tmp;
}

#undef	_QS_LINE_SIZE
#define	_QS_LINE_SIZE	8
void	quickSort::printArray(int *p, int high, int low, int i, int j)
{
	int	linePos	= _QS_LINE_SIZE;

	for(int ct = 0; ct < high; ct++)
	{
		if(ct == i)			debugOut( "[i ");
		else if (ct == j)	debugOut( "[j ");
		else if (ct == low)	debugOut( "[p ");
		else				debugOut( "   ");

		debugOut( setw(10) << *p++);

		if(ct == i || ct == j || ct == low)	debugOut( "]");
		else								debugOut( " ");

		if(--linePos == 0)
		{
			debugOut( endl);
			linePos	= _QS_LINE_SIZE;
		}
	}

	if (linePos != _QS_LINE_SIZE)
		debugOut(endl);//partitionRight(pArray, left, lessThan-1, compare);
	//partitionRight(pArray, lessThan+1, right, compare);

}


quickSort::quickSort() {
	// TODO Auto-generated constructor stub

}

quickSort::~quickSort() {
	// TODO Auto-generated destructor stub
}

