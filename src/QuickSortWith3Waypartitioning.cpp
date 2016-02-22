/*
 * QuickSortWith3Waypartitioning.cpp
 *
 *  Created on: Sep 12, 2015
 *      Author: owner
 */

#include <iostream>
#include <iomanip>

#include "QuickSortWith3Waypartitioning.h"
using namespace std;

#define	printQSArray()												\
	cout	<< setw(6) << ' ' << setw(6) << ' ' << setw(6) << ' ';	\
	printArray(pArray, high, i, leftEdge, gt);


void		QuickSortWith3Waypartitioning::sort(int *pArray,
				 int num,
				 int (*compare)(const int *, const int *))
{
	if (num < 2)	return;
	//	both low & high get pre-incr/decr
	sort(pArray, 0,	num-1,	compare);
}


void		QuickSortWith3Waypartitioning::sort(int *pArray,
					 int low,
					 int high,
					 int (*compare)(const int *, const int *))
{
//	cout << "Entering (private) sort(---)'  Low:  " << low << ", High: " << high << endl;

	int	leftEdge, gt;
	int i, cmp, tmp;

	if (high <= low)
		return;

	leftEdge	= low;
	i	= low+1;
	gt	= high;

//	printQSArray();

	while(i<=gt)
	{
		//	compare [i] against left most element that is
		//		equal to the partitioning element

		cmp	= pArray[i] - pArray[leftEdge];//compare(pArray+i, pArray+leftEdge);
//		cout	<< *(pArray+i) << " > " << *(pArray+leftEdge) << " returns " << cmp << endl;

		//	if [i] is less than the partitioning element,
		//	  exchange it with what was the left-most
		//	  ocurrence of the partitioning element:

		//				  le++            i++             gt
		//	|  <,  <,  <, PE, PE, PE, PE, x<,  ?,  ?,  ?,  ?,  >,   >,   >   |
		//  |  <,  <,  <, x<, PE, PE, PE, PE,  ?,  ?,  ?,  ?,  >,   >,   >   |
		//					  le              i           gt

		if 			(cmp < 0)
		{
			tmp					= pArray[i];
			pArray[i++]			= pArray[leftEdge];
			pArray[leftEdge++]	= tmp;
		}

		//	if [i] is greater than the partitioning element,
		//	  exchange it with the left-most
		//	  unknown element
		//	  (a successive pass will compare against [le])

		//				  le              i               gt--
		//	|  <,  <,  <, PE, PE, PE, PE, x>,  ?,  ?,  ?,  q?,  >,   >,   >   |
		//  |  <,  <,  <, PE, PE, PE, PE, q?,  ?,  ?,  ?,  x>,  >,   >,   >   |
		//				  le              i           gt

		else if 	(cmp > 0)
		{
			tmp				= pArray[i];
			pArray[i]		= pArray[gt];
			pArray[gt--]	= tmp;
		}


		//	else [i] is the partitioning element

		//				  le              i               gt
		//	|  <,  <,  <, PE, PE, PE, PE, PE,  ?,  ?,  ?,  ?,   >,   >,   >   |
		//  |  <,  <,  <, PE, PE, PE, PE, PE,  ?,  ?,  ?,  ?,   >,   >,   >   |
		//				  le                  i           gt

		else 					i++;

//		printQSArray();
	}

//	printQSArray();

	sort(pArray, low, leftEdge-1, compare);
	sort(pArray, gt+1, high, compare);
}


#undef	LINE_SIZE
#define	LINE_SIZE	8

//printArray(pArray, 8, low, i, leftEdge, gt);
void	QuickSortWith3Waypartitioning::printArray(
		int *p,
		int high,
		int i,
		int leftEdge,
		int gt)
{
	int	linePos	= LINE_SIZE;

	for(int ct = 0; ct <= high; ct++)
	{
		if		(ct == leftEdge)	cout << "[leftEdge";
		else if (ct == i)	cout << "[i ";
		else if (ct == gt)	cout << "[gt";
		else				cout << "   ";

		cout << setw(4) << (char)*p++;

		if (ct == leftEdge ||
			ct == i  ||
			ct == gt)		cout << "]";
		else				cout << " ";

		if(--linePos == 0)
		{
			cout << endl;
			linePos	= LINE_SIZE;
		}
	}

	if (linePos!=LINE_SIZE)
		cout<<endl;
}


void	QuickSortWith3Waypartitioning::exch(int *pArray, int i, int j)
{
	int		tmp	= pArray[i];
	pArray[i]	= pArray[j];
	pArray[j]	= tmp;
}

QuickSortWith3Waypartitioning::QuickSortWith3Waypartitioning() {
	// TODO Auto-generated constructor stub

}

QuickSortWith3Waypartitioning::~QuickSortWith3Waypartitioning() {
	// TODO Auto-generated destructor stub
}

