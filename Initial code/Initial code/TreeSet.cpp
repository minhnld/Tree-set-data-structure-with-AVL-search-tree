/* Copyright (C) 2018
* Course: CO2003
* Author: Rang Nguyen
* Ho Chi Minh City University of Technology
*/

#include "TreeSet.h"
int TreeSet::max(int a, int b) {
	return (a > b) ? a : b;
}
int TreeSet::height(AVLNode *N)
{
	if (N == NULL)
		return 0;
	return N->balance;
}
AVLNode*TreeSet::rightRotate(AVLNode *y)
{
	AVLNode *x = y->left;
	AVLNode *T2 = x->right;

	// Perform rotation 
	x->right = y;
	y->left = T2;

	// Update heights 
	y->balance = max(height(y->left), height(y->right)) + 1;
	x->balance = max(height(x->left), height(x->right)) + 1;

	// Return new root 
	return x;
}
AVLNode* TreeSet::leftRotate(AVLNode *x)
{
	AVLNode *y = x->right;
	AVLNode *T2 = y->left;

	// Perform rotation 
	y->left = x;
	x->right = T2;

	//  Update heights 
	x->balance = max(height(x->left), height(x->right)) + 1;
	y->balance = max(height(y->left), height(y->right)) + 1;

	// Return new root 
	return y;
}
// Get Balance factor of node N 
int TreeSet::getBalance(AVLNode *N)
{
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}
AVLNode*TreeSet:: insert(AVLNode* node, int key)
{
	/* 1.  Perform the normal BST insertion */
	if (node == NULL)
		return(new AVLNode(key,1));

	if (key < node->key)
		node->left = insert(node->left, key);
	else if (key > node->key)
		node->right = insert(node->right, key);
	else // Equal keys are not allowed in BST 
		return node;

	/* 2. Update height of this ancestor node */
	node->balance = 1 + max(height(node->left),
		height(node->right));

	/* 3. Get the balance factor of this ancestor
		  node to check whether this node became
		  unbalanced */
	int balance = getBalance(node);

	// If this node becomes unbalanced, then 
	// there are 4 cases 

	// Left Left Case 
	if (balance > 1 && key < node->left->key)
		return rightRotate(node);

	// Right Right Case 
	if (balance < -1 && key > node->right->key)
		return leftRotate(node);

	// Left Right Case 
	if (balance > 1 && key > node->left->key)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	// Right Left Case 
	if (balance < -1 && key < node->right->key)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	/* return the (unchanged) node pointer */
	return node;
}
AVLNode * TreeSet:: minValueNode(AVLNode* node)
{
	AVLNode* current = node;

	/* loop down to find the leftmost leaf */
	while (current->left != NULL)
		current = current->left;

	return current;
}
AVLNode*TreeSet:: deleteNode(AVLNode* root, int key)
{
	// STEP 1: PERFORM STANDARD BST DELETE 

	if (root == NULL)
		return root;

	// If the key to be deleted is smaller than the 
	// root's key, then it lies in left subtree 
	if (key < root->key)
		root->left = deleteNode(root->left, key);

	// If the key to be deleted is greater than the 
	// root's key, then it lies in right subtree 
	else if (key > root->key)
		root->right = deleteNode(root->right, key);

	// if key is same as root's key, then This is 
	// the node to be deleted 
	else
	{
		// node with only one child or no child 
		if ((root->left == NULL) || (root->right == NULL))
		{
			AVLNode *temp = root->left ? root->left :
				root->right;

			// No child case 
			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else // One child case 
				*root = *temp; // Copy the contents of 
							   // the non-empty child 
			free(temp);
		}
		else
		{
			// node with two children: Get the inorder 
			// successor (smallest in the right subtree) 
			AVLNode* temp = minValueNode(root->right);

			// Copy the inorder successor's data to this node 
			root->key = temp->key;

			// Delete the inorder successor 
			root->right = deleteNode(root->right, temp->key);
		}
	}

	// If the tree had only one node then return 
	if (root == NULL)
		return root;

	// STEP 2: UPDATE HEIGHT OF THE CURRENT NODE 
	root->balance = 1 + max(height(root->left),
		height(root->right));

	// STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to 
	// check whether this node became unbalanced) 
	int balance = getBalance(root);

	// If this node becomes unbalanced, then there are 4 cases 

	// Left Left Case 
	if (balance > 1 && getBalance(root->left) >= 0)
		return rightRotate(root);

	// Left Right Case 
	if (balance > 1 && getBalance(root->left) < 0)
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	// Right Right Case 
	if (balance < -1 && getBalance(root->right) <= 0)
		return leftRotate(root);

	// Right Left Case 
	if (balance < -1 && getBalance(root->right) > 0)
	{
		root->right = rightRotate(root->right);
		return leftRotate(root);
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
	root = insert(root, val);
	count++;
	return 1;
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

AVLNode* TreeSet::copy_rer(AVLNode* root) {
	if (root == NULL) return NULL;
	AVLNode* temp = new AVLNode(root->key);
	temp->left = copy_rer(root->left);
	temp->right = copy_rer(root->right);
	return temp;
}
void TreeSet::copy(const TreeSet& set) {
	root = copy_rer(set.root);
	count = set.count;
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
	if (!contains(val)) return 0;
	root = deleteNode(root, val);
	count--;
	return 1;
}
void TreeSet::subSet_better(AVLNode *root,TreeSet*&temp, int a, int b) {
	if (!root) return;
	else if (root->key >= b)
		 subSet_better(root->left,temp, a, b);
	else if (root->key < a)
		 subSet_better(root->right,temp, a, b);
	else if (root->key >= a && root->key < b) {
		temp->root = insert(temp->root,root->key);
		temp->count++;
		subSet_better(root->left,temp, a, b);
		subSet_better(root->right, temp, a, b);
	}	 
}

TreeSet* TreeSet::subSet(int fromVal, int toVal) {
	// TODO
	TreeSet* temp = new TreeSet();
	temp->root = NULL;
	temp->count = 0;
	subSet_better(root, temp, fromVal, toVal);
	return temp;
}

int TreeSet::size() {
	// TODO
	return count;
}

