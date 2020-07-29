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
	int height(AVLNode *N);
	AVLNode *rightRotate(AVLNode *y);
	AVLNode* leftRotate(AVLNode *x);
	int getBalance(AVLNode *N);
	AVLNode* insert(AVLNode* node, int key);
	AVLNode * minValueNode(AVLNode* node);
	AVLNode* deleteNode(AVLNode* root, int key);

	AVLNode *GetLeftMostChild(AVLNode *n);
	AVLNode *find_first_bigger(AVLNode *t, int x);
	AVLNode *GetRightMostChild(AVLNode *n);
	AVLNode *find_first_lower(AVLNode *t, int x);
	void subSet_better(AVLNode *root, TreeSet*&temp, int a, int b);

	AVLNode* copy_rer(AVLNode* root);

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

