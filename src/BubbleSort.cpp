/*
 * BubbleSort.cpp
 *
 *  Created on: Feb 22, 2016
 *      Author: owner
 */

#include "BubbleSort.h"
#include <iostream>

using namespace std;

void	BubbleSort::sortForward(int *a, int size, int (*compare)(const int *a, const int *b))
{
	int	tmp;
	if (size <= 0)
		return;

	for (int i = 0; i != size-1 ; i++)
		for (int j = 0; j != size-1; j++)
			if(a[j] > a[j+1]){
				tmp		= a[j+1];
				a[j]	= a[j+1];
				a[j+1]	= tmp;
			}
}


void	BubbleSort::sortReverse(int *a, int size, int (*compare)(const int *a, const int *b))
{
	int tmp;
	if (size <= 0)
		return;

	for (int i = size-1; i != 0; i--)
		for (int j = i ; j != 0; j--)
			if(a[j] < a[j-1]){
				tmp		= a[j];
				a[j]	= a[j+1];
				a[j+1]	= tmp;
			}
}


BubbleSort::BubbleSort() {
	// TODO Auto-generated constructor stub

}

BubbleSort::~BubbleSort() {
	// TODO Auto-generated destructor stub
}
