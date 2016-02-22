/*
 * BinaryHeap.h
 *
 *  Created on: Sep 27, 2015
 *      Author: owner
 */

#ifndef BINARYHEAP_H_
#define BINARYHEAP_H_

#define	WIDTH_OF_OUTPUT_LINE	80

class BinaryHeap {
public:
	int		delMax();
	void	insert(int x);
	bool	isEmpty();

	static	void	sort(int *p, int numElements, int (*compare)(const int *, const int *));

	BinaryHeap(int numElements = 1);
	virtual ~BinaryHeap();

private:
//	static	void	print(int *p, int numElements);
	static	void	print(int *p, int numElements, int parent = 0, int child = 0);
	static  bool	isHeapOrdered(int *p, int numElements, int (*compare)(const int *, const int *));

	void	sink(int parentIndex);
	void	swim(int childIndex);

	int	*ph;

	int	numberOfElements;
	int	N;
};

#endif /* BINARYHEAP_H_ */
