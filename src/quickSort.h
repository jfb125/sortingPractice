/*
 * quickSort.h
 *
 *  Created on: Sep 5, 2015
 *      Author: owner
 */

#ifndef QUICKSORT_H_
#define QUICKSORT_H_

class quickSort {
public:
	static void		sort(int *pArray,
			 	 	 	 int num,
			 	 	 	 int (*compare)(const int *, const int *));

	quickSort();
	virtual ~quickSort();

private:
	static	void	exch(int *pArray, int i, int j);
	static	void	printArray(int *pArray, int num, int low, int i, int j);
	static	void	partitionWithThreeWay(int *a, int low, int high, int (*compare)(const int *, const int *));
	static	int		partitionWithOnePivot(int *a, int low, int high, int (*compare)(const int *, const int *));
	static 	int		partitionLeft(int *pArray,
			 	 	 	 	  int low,
			 	 	 	 	  int high,
			 	 	 	 	  int (*compare)(const int *, const int *));
	static 	int		partitionRight(int *pArray,
			 	 	 	 	  int low,
			 	 	 	 	  int high,
			 	 	 	 	  int (*compare)(const int *, const int *));
	static void		sort(int *pArray,
						 int low,
						 int high,
						 int (*compare)(const int *, const int *));
	static	int		sortSubarray(int *pArray, int low, int high, int (*compare)(const int *, const int *));
	static	void	swap(int *a, int p, int q);
};

#endif /* QUICKSORT_H_ */
