/* Copyright (C) 2018
* Course: CO2003
* Author: Rang Nguyen
* Ho Chi Minh City University of Technology
*/

#include "TreeSet.h"
int TreeSet::max(int a, int b) {
	int t = a;
	if (t > b) t = b;
	return t;
}
int TreeSet::Height(AVLNode *root) {
	if (!root)
		return -1;
	else
		return root->balance;
}
class AVLNode *TreeSet::SingleRotateLeft(AVLNode *X) {
	AVLNode *W = X->left;
	X->left = W->right;
	W->right = X;
	X->balance = max(Height(X->left), Height(X->right)) + 1;
	W->balance = max(Height(W->left), X->balance) + 1;
	return W;
}
class AVLNode *TreeSet::SingleRotateRight(AVLNode *W) {
	AVLNode *X = W->right;
	W->right = X->left;
	X->left = W;
	W->balance = max(Height(W->right), Height(W->left)) + 1;
	X->balance = max(Height(X->right), W->balance) + 1;
	return X;
}
class AVLNode *TreeSet::DoubleRotatewithLeft(AVLNode* Z) {
	Z->left = SingleRotateRight(Z->left);
	return SingleRotateLeft(Z);
}
class AVLNode *TreeSet::DoubleRotatewithRight(AVLNode* X) {
	X->right = SingleRotateLeft(X->right);
	return SingleRotateRight(X);
}

class AVLNode *TreeSet::Insert(AVLNode *root, AVLNode *parent, int data)
{
	if (!root) {
		root = new AVLNode(data);
	}
	else if (data < root->key) {
		root->left = Insert(root->left, root, data);
		if ((Height(root->left) - Height(root->right)) == 2) {
			if (data < root->left->key)
				root = SingleRotateLeft(root);
			else root = DoubleRotatewithLeft(root);
		}
	}
	else if (data > root->key) {
		root->right = Insert(root->right, root, data);
		if ((Height(root->right) - Height(root->left)) == 2) {
			if (data > root->right->key)
				root = SingleRotateRight(root);
			else root = DoubleRotatewithRight(root);
		}
	}

	root->balance = max(Height(root->left), Height(root->right)) + 1;
	return root;
};
AVLNode *TreeSet::FindMax(AVLNode *root) {
	if (root == NULL) return NULL;
	else if (root->right == NULL) return root;
	else return FindMax(root->right);
}
AVLNode *TreeSet::Delete(AVLNode *root, AVLNode *parent, int data) {
	AVLNode *temp;
	if (!root) cout << "Element not there in tree " << endl;
	else if (data < root->key) {
		root->left = (Delete(root->left, root, data));
		if ((Height(root->left) - Height(root->right)) == 2) {
			if (data < root->left->key)
				root = SingleRotateLeft(root);
			else root = DoubleRotatewithLeft(root);
		}
	}
	else if (data > root->key) {
		root->right = (Delete(root->right, root, data));
		if ((Height(root->right) - Height(root->left)) == 2) {
			if (data > root->right->key)
				root = SingleRotateRight(root);
			else root = DoubleRotatewithRight(root);
		}
	}
	else {
		if (root->left && root->right) {
			temp = FindMax(root->left);
			root->key = (temp->key);
			root->left = (Delete(root->left, root, root->key));
		}
		else {
			temp = root->left ? root->left : root->right;
			if (!temp) {
				temp = root;
				root = NULL;
			}
			else
				*root = *temp;
			free(temp);
		}
	}
	return root;
}

AVLNode *TreeSet::GetLeftMostChild(AVLNode *n) {
	AVLNode *ptr = n;
	while (ptr->left != NULL) {
		ptr = ptr->left;
	}
	return ptr;
}
AVLNode *TreeSet::find_first_bigger(AVLNode *t, int x) {
	if (t == NULL)
		return NULL;

	if (t->key > x) {
		AVLNode *answer = find_first_bigger(t->left, x);
		if (answer != NULL)
			return answer;
		return t;
	}
	else if (t->key < x) {
		return find_first_bigger(t->right, x);
	}
	else if (t->key == x) {
		if (t->right != NULL)
			return GetLeftMostChild(t->right);
		return NULL;
	}
}
AVLNode *TreeSet::GetRightMostChild(AVLNode *n) {
	AVLNode *ptr = n;
	while (ptr->right != NULL) {
		ptr = ptr->right;
	}
	return ptr;
}
AVLNode *TreeSet::find_first_lower(AVLNode *t, int x) {
	if (t == NULL)
		return NULL;

	if (t->key < x) {
		AVLNode *answer = find_first_lower(t->right, x);
		if (answer != NULL)
			return answer;
		return t;
	}
	else if (t->key > x) {
		return find_first_lower(t->left, x);
	}
	else if (t->key == x) {
		if (t->left != NULL)
			return GetRightMostChild(t->left);
		return NULL;
	}
}
TreeSet::TreeSet()
{
	root = NULL;
	count = 0;
}
TreeSet::~TreeSet()
{
	clear();
}
void TreeSet::clearRec(AVLNode* root) {
	if (root != NULL) {
		clearRec(root->left);
		clearRec(root->right);
		delete root;
	}
}
void TreeSet::clear() {
	clearRec(root);
	root = NULL;
	count = 0;
}
bool TreeSet::add(int val) {
	// TODO
	if (contains(val)) return 0;
	else {
		root = Insert(root, root, val);
		count++;
		return 1;
	}
}

bool TreeSet::contains(int val) {
	// TODO
	AVLNode *temp = root;
	if (!temp)
		return 0;
	while (temp) {
		if (val == temp->key)
			return 1;
		else if (val > temp->key)
			temp = temp->right;
		else temp = temp->left;
	}
	return 0;
}

void TreeSet::copy(const TreeSet& set) {
	// TODO
	clear();
	root = set.root;
}

int TreeSet::first() {	
	if (root == NULL) {
		throw "NoSuchElementException";
	}
	// TODO
	AVLNode*temp = root;
	while (temp->left != NULL) {
		temp = temp->left;
	}
	return temp->key;
}

int TreeSet::last() {
	if (root == NULL) {
		throw "NoSuchElementException";
	}
	// TODO
	AVLNode*temp = root;
	while (temp->right != NULL) {
		temp = temp->right;
	}
	return temp->key;
}

int TreeSet::higher(int val) {
	// TODO
	if (!root) return -1;
	AVLNode* temp = find_first_bigger(root, val);
	if (temp) return temp->key;
	else return -1;
}

int TreeSet::lower(int val) {
	// TODO
	if (!root) return -1;
	AVLNode* temp = find_first_lower(root, val);
	if (temp) return temp->key;
	else return -1;
}

bool TreeSet::remove(int val) {
	// TODO
	if (!contains(val)) return false;
	root = Delete(root, root, val);
	count--;
	return true;
}
void TreeSet::subSet_better(AVLNode *root,AVLNode*&temp, int a, int b) {
	if (!root) return;
	else if (root->key > b)
		 subSet_better(root->left,temp, a, b);
	else if (root->key < a)
		 subSet_better(root->right,temp, a, b);
	else if (root->key >= a && root->key < b) {
		temp = Insert(temp, temp, root->key);
		subSet_better(root->left,temp, a, b);
		subSet_better(root->right, temp, a, b);
	}	 
}

TreeSet* TreeSet::subSet(int fromVal, int toVal) {
	// TODO
	TreeSet* temp = new TreeSet();
	subSet_better(root, temp->root, fromVal, toVal);
	return temp;
}

int TreeSet::size() {
	// TODO
	return count;
}

