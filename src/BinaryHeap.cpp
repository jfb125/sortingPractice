/*
 * BinaryHeap.cpp
 *
 *  Created on: Sep 27, 2015
 *      Author: owner
 */

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

#include "BinaryHeap.h"

ofstream	logFile;

int		BinaryHeap::delMax()
{
	int	returnValue	= ph[1];

	ph[1]	= ph[N];
	if (N)
		N--;
	sink(1);

	return	returnValue;
}


void	BinaryHeap::insert(int x)
{
	ph[++N]	= x;
	swim(N);
}


bool	BinaryHeap::isEmpty()	{	return	N==0;	}

#if 0
void	BinaryHeap::print(int *p, int numElements)
{
	int	elementsOnThisLine	= 1;
	int	objectCount			= 0;
	int	eachElementsWidth	= WIDTH_OF_OUTPUT_LINE/elementsOnThisLine;

	for (int i = 0; i < numElements; i++)
	{
		cout << setw(eachElementsWidth) << *p++;
		cout << setw(eachElementsWidth) << ' ';

		if (++objectCount == elementsOnThisLine)
		{
			elementsOnThisLine	<<= 1;
			eachElementsWidth	>>= 1;
			if (eachElementsWidth == 0)	eachElementsWidth	= 1;
			objectCount			= 0;
			cout << endl;
		}
	}

	cout << endl;
}
#endif

void	BinaryHeap::print(int *p, int numElements, int parent, int child)
{
	int	elementsOnThisLine	= 1;
	int	objectCount			= 0;
	int	eachElementsWidth	= WIDTH_OF_OUTPUT_LINE/elementsOnThisLine;

	parent--;
	child--;

	for (int i = 0; i < numElements; i++)
	{
		if (i == parent || i == child)
			logFile << setw(eachElementsWidth-2) << "[";
		else
			logFile << setw(eachElementsWidth-2) << " ";

		logFile 	<< setfill('0') << setw(3) << *p++;
		if (i == parent || i == child)
			logFile << "]";
		else
			logFile << " ";

		logFile << setfill(' ') << setw(eachElementsWidth-2) << ' ';

		if (++objectCount == elementsOnThisLine)
		{
			elementsOnThisLine	<<= 1;
			eachElementsWidth	>>= 1;
			if (eachElementsWidth == 0)	eachElementsWidth	= 1;
			objectCount			= 0;
			logFile << endl;
		}
	}

	logFile << endl;
}

#if 0
void	sink(int *p, int k, int length) //, int (*compare)(const int *, const int *))
{
	while (2*k < length)
	{
		//				cout << "Before: " << endl;
		print(p, arraySize);
	point to the left child
		int	j	= 2*k;

		//	if the right child > left child
		if (j < length && p
			[j] < p[j+1])
			j++;		// use the right childproblemValues

		//	if the parent >= largest child
		if (p[k] >= p[j])
			break;			// leave

		//	exchange parent & child
		int tmp	= p[k];
		p[k]	= p[j];
		p[j]	= tmp;

		//	child is the new parent (sink)
		k		= j;
	}
}
#endif

void	BinaryHeap::sink(int k)
{
	while (2*k < N)
	{
		//	point to the left child
		int	j	= 2*k;

		//	if the right child > left child
		if (j < N && ph[j] < ph[j+1])
			j++;		// use the right child

		//	if the parent >= largest child
		if (ph[k] >= ph[j])
			break;			// leave

		//	exchange parent & child
		int tmp	= ph[k];
		ph[k]	= ph[j];
		ph[j]	= tmp;

		//	child is the new parent (sink)
		k		= j;
	}
}


bool	BinaryHeap::isHeapOrdered(int *p, int numElements, int (*compare)(const int *, const int *))
{
	int	parentNumber;
	int	childNumber;

	for (int i = numElements; i != 1; i--)
	{
		childNumber		= i;
		parentNumber	= childNumber>>1;

		if (p[parentNumber-1] < p[childNumber-1])
		{
			logFile	<< "Array is not heap ordered at p["
					<< parentNumber-1 << "] = " << p[parentNumber-1]
					<< " vs. p[" << childNumber-1 << "] = "
					<< p[childNumber-1] << endl;
			print(p, numElements, parentNumber, childNumber);
			return false;
		}
	}

	return	true;
}


//#define	DEBUG_BINARY_HEAP_SORT

void	BinaryHeap::sort(int *p, int numElements, int (*compare)(const int *, const int *))
{
	if (numElements <= 0 || p == nullptr)
		return;

	int	nodeInQuestion, childNumber, parentNumber, childsIndex, parentsIndex, tmp;

#ifdef	DEBUG_BINARY_HEAP_SORT
	logFile.open("thisIsTheLogFile.txt");
#endif

#ifdef	DEBUG_BINARY_HEAP_SORT
	logFile	<< "Before heap ordering array: " << endl;
	print(p, numElements);
#endif

	//	Put the array in a heap order
	//		by 'inserting' each element into the heap-ordered portion of the array

	for (nodeInQuestion = 2; nodeInQuestion <= numElements; nodeInQuestion++)
	{
		childNumber		= nodeInQuestion;
		parentNumber	= nodeInQuestion>>1;
#ifdef	DEBUG_BINARY_HEAP_SORT
		logFile	<< "Inserting at " << nodeInQuestion << endl;
//		print(p, numElements, parentNumber, childNumber);
#endif

		//	Heap order the array by swimming every node from the bottom up

		while (childNumber > 1)
		{
			//	point to the left child
#ifdef	DEBUG_BINARY_HEAP_SORT
			logFile	<< "At the start of this compare, " << childNumber
					<< " is a child of " << parentNumber << endl;
#endif
			if (childNumber < 2*parentNumber)
			{
				cout 	<< "parent / child numbers whacked: ("
						<< parentNumber << " vs "
						<< childNumber << ")" << endl;
				logFile.close();
				return;
			}

			childsIndex		= childNumber-1;
			parentsIndex	= parentNumber-1;

#ifdef	DEBUG_BINARY_HEAP_SORT
			logFile	<< "Examining " << parentNumber << " vs " << childNumber << endl;
			print(p, numElements, parentNumber, childNumber);
#endif

			if (p[parentsIndex] >= p[childsIndex])		// 	if parent is = or greater, done
				break;

			tmp				= p[parentsIndex];
			p[parentsIndex]	= p[childsIndex];
			p[childsIndex]	= tmp;

#ifdef	DEBUG_BINARY_HEAP_SORT
			logFile	<< "After swap" << endl;
			print(p, numElements, parentNumber, childNumber);
#endif

			//	parentsIndex is the next child (up)
			childNumber			= parentNumber;
			parentNumber	 	>>=1;	// divide by 2
		}
	}

#ifdef	DEBUG_BINARY_HEAP_SORT
	logFile	<< endl;
	logFile	<< "After heap ordering array: " << endl;
	print(p, numElements);
#endif

//	if (!isHeapOrdered(p, numElements, compare))
//	{
//		cout	<< "Array is not heap ordered!" << endl;
//		return;
//	}


	int	indexOfLastElement	= numElements-1;

	//	Sort the array by swapping the bottom element with the top
	//		and then sinking the new top element (it will be smaller)

	//	Use the copy of 'numElements' that was passed on the stack
	//		as the counter

	while (numElements > 0)
	{
		tmp						= p[0];
		p[0]					= p[indexOfLastElement];
		p[indexOfLastElement--]	= tmp;

		//	Remove the bottom element of the array
		numElements--;


#ifdef	DEBUG_BINARY_HEAP_SORT
		logFile	<< "Removed element [" << indexOfLastElement << "]" << endl;
		print(p, numElements, 1, indexOfLastElement+1);
#endif

		parentNumber = 1;


		//	sink the new top of the heap

		while (2*parentNumber <= numElements)
		{
			//	point to the left child
			childNumber		= 2*parentNumber;
			childsIndex		= childNumber-1;
			parentsIndex	= parentNumber-1;

//#ifdef	DEBUG_BINARY_HEAP_SORT
//			logFile	<< "parentsIndex = " << parentsIndex
//					<< " childsIndex = " << childsIndex
//					<< " last element = " << indexOfLastElement
//					<< endl;
//#endif
			//	if the left child is not the last element
			//		and if the right child > left child
			//			use the right side child
			if (childsIndex < indexOfLastElement
				&& p[childsIndex] < p[childsIndex+1])
			{
				childNumber++;		// use the right child
				childsIndex++;
			}

#ifdef	DEBUG_BINARY_HEAP_SORT
			logFile	<< " results in childsIndex == " << childsIndex << endl;
			print(p, indexOfLastElement+1, parentNumber, childNumber);
#endif
			//	if the parent >= largest child
			if (p[parentsIndex] >= p[childsIndex])
				break;			// leave

			//	exchange parent & child
			tmp				= p[parentsIndex];
			p[parentsIndex]	= p[childsIndex];
			p[childsIndex]	= tmp;

			//	childsIndex is the new parentsIndex (sink)
			parentNumber	= childNumber;
		}

#ifdef	DEBUG_BINARY_HEAP_SORT
		print(p, numElements);
#endif
	}

#ifdef	DEBUG_BINARY_HEAP_SORT
	print(p, numElements);
	logFile.close();
#endif
}


void	BinaryHeap::swim(int N)
{
	int	child	= N;
	int	parent	= N/2;
	int	tmp;

	while (parent)
	{
		if (ph[child] > ph[parent])
		{
			tmp			= ph[child];
			ph[child]	= ph[parent];
			ph[parent]= tmp;
			child		= parent;
			parent		= child/2;
		}
		else
			break;
	}
}


BinaryHeap::BinaryHeap(int numElements) {
	//	The first element is at [1]
	numberOfElements	= numElements+1;
	ph					= new int[numberOfElements];
	N 					= 0;
}


BinaryHeap::~BinaryHeap() {
	if (ph != NULL){
		delete[] ph;
		ph	= NULL;
	}
}
