/*
 * ShellSort.h
 *
 *  Created on: Feb 28, 2016
 *      Author: owner
 */

#ifndef SHELLSORT_H_
#define SHELLSORT_H_

class ShellSort {
public:
	static	void	sort(int *a, int n, int (*compare)(const int *, const int *));

	ShellSort();
	virtual ~ShellSort();
};

#endif /* SHELLSORT_H_ */
