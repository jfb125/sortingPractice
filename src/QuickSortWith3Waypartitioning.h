/*
 * QuickSortWith3Waypartitioning.h
 *
 *  Created on: Sep 12, 2015
 *      Author: owner
 */

#ifndef QUICKSORTWITH3WAYPARTITIONING_H_
#define QUICKSORTWITH3WAYPARTITIONING_H_

class QuickSortWith3Waypartitioning {
public:
	static void		sort(int *pArray,
			 	 	 	 int num,
			 	 	 	 int (*compare)(const int *, const int *));

	QuickSortWith3Waypartitioning();
	virtual ~QuickSortWith3Waypartitioning();

private:
	static	void	exch(int *pArray, int i, int j);
	static	void	printArray(
			int *p,
			int high,
			int i,
			int lt,
			int gt);
	static void		sort(int *pArray,
						 int low,
						 int high,
						 int (*compare)(const int *, const int *));
};

#endif /* QUICKSORTWITH3WAYPARTITIONING_H_ */
