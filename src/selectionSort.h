/*
 * selectionSort.h
 *
 *  Created on: Aug 30, 2015
 *      Author: owner
 */

#ifndef SELECTIONSORT_H_
#define SELECTIONSORT_H_

class selectionSort {
public:

	static void	sort(int *pBase,
				 	 int 	num,
				 	 int 	(*compare)(const int *, const int *));

	selectionSort();
	virtual ~selectionSort();

private:
	static void	exch(unsigned char *a, unsigned char *b, int size);
};

#endif /* SELECTIONSORT_H_ */
