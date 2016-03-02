/*
 * mergeSort.h
 *
 *  Created on: Aug 30, 2015
 *      Author: owner
 */

#ifndef MERGESORT_H_
#define MERGESORT_H_

class mergeSort {
public:
	static	void	sort(int *p,
						 int num,
						 int (*compare)(const int *, const int *));

	static	void printArray(int *p, int num);

	static	const char *getName();

	mergeSort();
	virtual ~mergeSort();

private:
};

#endif /* MERGESORT_H_ */
