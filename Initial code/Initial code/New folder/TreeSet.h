/* Copyright (C) 2018
* Course: CO2003
* Author: Rang Nguyen
* Ho Chi Minh City University of Technology
*/

#pragma once
#include"AVLNode.h"
class TreeSet
{
private:
	AVLNode * root;
	int count;
protected:
	void clearRec(AVLNode*root);
	

public:
	TreeSet();
	~TreeSet();
	void clear();
	// print out the set in ascending order
	friend ostream& operator<<(ostream& os, const TreeSet& t);

	int max(int a, int b);
	int Height(AVLNode *root);
	class AVLNode *SingleRotateLeft(AVLNode *X);
	class AVLNode *SingleRotateRight(AVLNode *W);
	class AVLNode *DoubleRotatewithLeft(AVLNode* Z);
	class AVLNode *DoubleRotatewithRight(AVLNode* X);
	class AVLNode *Insert(AVLNode *root, AVLNode *parent, int data);
	AVLNode *FindMax(AVLNode *root);
	AVLNode *Delete(AVLNode *root, AVLNode *parent, int data);
	void DeleteAVLTree(AVLNode*root);
	AVLNode *GetLeftMostChild(AVLNode *n);
	AVLNode *find_first_bigger(AVLNode *t, int x);
	AVLNode *GetRightMostChild(AVLNode *n);
	AVLNode *find_first_lower(AVLNode *t, int x);
	void subSet_better(AVLNode *root, AVLNode*&temp, int a, int b);
	// YOUR TASKS START HERE	
	bool add(int val);		
	bool contains(int val);
	void copy(const TreeSet& set);
	int first();
	int higher(int val);
	int last();
	int lower(int val);
	bool remove(int val);
	TreeSet* subSet(int fromVal, int toVal);
	int size();
	// END HERE

};

