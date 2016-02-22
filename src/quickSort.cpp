/*
 * quickSort.cpp
 *
 *  Created on: Sep 5, 2015
 *      Author: owner
 */

#define	debugOut(n)	//debugOut( n
#define	printQSArray()

//	cout	<< setw(4) << low << setw(4) << i << setw(4) << j << "    ");
//	printArray(pArray, 8, low, i, j);

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

	debugOut("Entering first sort()" << endl);
	//
//	int	pposition 	= partition(pArray, 0, num-1, compare);

	debugOut( "First 'partition()' returns " << pposition << endl
		 << " ------- " << endl);

	//	both low & high get pre-incr/decr
	sort(pArray, 0,	num-1,	compare);
}


void	quickSort::sort( int *pArray, int low, int high,
					 	 int (*compare)(const int *, const int *))
{
	if (high <= low)	return;
	debugOut( "Entering recursive sort() with low = " << low
		 << " high = " << high << endl);
	int pposition	= partition(pArray, low, high, compare);
	debugOut( "Recursive 'partition()' returns " << pposition << endl
		 << " ------- " << endl);
	sort(pArray, low, 			pposition-1,	compare);
	sort(pArray, pposition+1,	high,	   		compare);
}


int		quickSort::partition( int *pArray,
					 	 	  int low,
					 	 	  int high,
					 	 	  int (*compare)(const int *, const int *))
{
	debugOut( "Entering 'partition(---)'  Low:  " << low << ", High: " << high << endl);

	if(high == low)	return 0;

	int i, j, tmp;

	//	'i' will pre-increment during the first pass
	//		which will cause the 0th element
	//		to not be swapped, which is necessary
	//		to preserve the 0th element as the partition
	i	= low;

	j	= high+1;


	debugOut( "          low   i   j" << endl);
	while (true)
	{
		debugOut( "Pass   : ");  printQSArray();
		//	find the leftmost item that is larger
		//		than the partitioning element
		//		and thus is not in place

		while (pArray[++i]-pArray[low] < 0)
		{
			debugOut( "While i: ");	printQSArray();
			if (i == high)		break;
		}

		//	move past all the elements at the right
		//		that are greater than the partitioning element
		//		and are thus in place

		while (pArray[--j]-pArray[low]	> 0)
		{
			debugOut( "while j: ");	printQSArray();
			if (j == low)		break;
		}

		if (i >= j)			break;


		//	[i] is first leftward element 		> partitioning element &&
		//	[j] is farthest rightward element 	< partitioning element
		//	exchange them so that
		//	[i] is less than the partitioning element &&
		//	[j] is greater than the partitioning element
		debugOut( "exchange ");
		printQSArray();
		tmp			= pArray[i];
		pArray[i]	= pArray[j];
		pArray[j]	= tmp;
		debugOut( "         ");
		printQSArray();
	}

	debugOut( "FINAL  : ");
	tmp			= pArray[low];
	printQSArray();
	pArray[low]	= pArray[j];
	pArray[j]	= tmp;
	debugOut( "         ");
	printQSArray();

	return	j;
}


void	quickSort::exch(int *pArray, int i, int j)
{
	int		tmp	= pArray[i];
	pArray[i]	= pArray[j];
	pArray[j]	= tmp;
}

#undef	LINE_SIZE
#define	LINE_SIZE	8
void	quickSort::printArray(int *p, int high, int low, int i, int j)
{
	int	linePos	= LINE_SIZE;

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
			linePos	= LINE_SIZE;
		}
	}

	if (linePos != LINE_SIZE)
		debugOut(endl);
}


quickSort::quickSort() {
	// TODO Auto-generated constructor stub

}

quickSort::~quickSort() {
	// TODO Auto-generated destructor stub
}

