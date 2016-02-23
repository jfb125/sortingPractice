/*
 * insertionSort.h
 *
 *  Created on: Aug 30, 2015
 *      Author: owner
 */

#ifndef INSERTIONSORT_H_
#define INSERTIONSORT_H_

class insertionSort {
public:
	static void	forwardSort(int *pBase,
				 	 int num,
				 	 int (*compare)(const int *, const int *));
	static void reverseSort(int *pBase,
							int num,
							int (*compare)(const int *, const int *));
	insertionSort();
	virtual ~insertionSort();

private:
	static void	exch(unsigned char *a, unsigned char *b, int size);
};

#endif /* INSERTIONSORT_H_ */
