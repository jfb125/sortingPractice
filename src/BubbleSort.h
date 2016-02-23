/*
 * BubbleSort.h
 *
 *  Created on: Feb 22, 2016
 *      Author: owner
 */

#ifndef BUBBLESORT_H_
#define BUBBLESORT_H_

class BubbleSort {
public:

	static	void	sortForward(int *a, int size, int (*compare)(const int *a, const int *b));
	static	void	sortReverse(int *a, int size, int (*compare)(const int *a, const int *b));
	BubbleSort();
	virtual ~BubbleSort();

};

#endif /* BUBBLESORT_H_ */
