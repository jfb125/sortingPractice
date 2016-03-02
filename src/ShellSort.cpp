/*
 * ShellSort.cpp
 *
 *  Created on: Feb 28, 2016
 *      Author: owner
 */

#include "ShellSort.h"

using namespace std;

void	ShellSort::sort(int *a, int n, int (*compare)(const int *, const int *))
{
	int	gapSize	= 1;
	int	tmp;

	while(gapSize < n/3)
		gapSize	= 3*gapSize+1;

	while (gapSize >= 1)
	{
		for(int i = gapSize; i != n; i++)
			for(int j = i; j >= gapSize; j -= gapSize)
				{
					if(a[j] < a[j-gapSize]){
						tmp			= a[j];
						a[j]		= a[j-gapSize];
						a[j-gapSize]= tmp;
					}
					else
						break;
				}

		//	Make the gaps in the fence smaller
		gapSize	/= 3;
	}
}

ShellSort::ShellSort() {
	// TODO Auto-generated constructor stub

}

ShellSort::~ShellSort() {
	// TODO Auto-generated destructor stub
}
