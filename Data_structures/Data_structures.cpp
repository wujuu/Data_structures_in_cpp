// Data_structures.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <climits>
using namespace std;
const int N = 50, K = 50;

void Swap(int* A, int i, int j) {
	int tmp = A[i];
	A[i] = A[j];
	A[j] = tmp;
}

//Heaps
struct heap {
	int* A, heapsize, n;
};
heap Init_heap(int n) {
	heap H;
	H.A = new int[n];
	H.n = n;
	H.heapsize = 0;
	return H;
}
int Parent(int i) {
	return (i - 1) / 2;
}
int Left(int i) {
	return 2 * i + 1;
}
int Right(int i) {
	return 2 * i + 2;
}
void Heapify(heap H, int i) {
	int id_max = i;
	if (Left(i) <= H.heapsize && H.A[Left(i)] > H.A[id_max]) id_max = Left(i);
	if (Right(i) <= H.heapsize && H.A[Right(i)] > H.A[id_max]) id_max = Right(i);
	if (id_max != i) {
		Swap(H.A, i, id_max);
		Heapify(H, id_max);
	}
}
void Incr_key(heap H, int i, int key) {
	H.A[i] = key;
	while (i > 0 && H.A[Parent(i)] > H.A[i]) {
		Swap(H.A, Parent(i), i);
		i = Parent(i);
	}
}
bool Push(heap H, int key) {
	if (H.heapsize + 1 < H.n) {
		H.heapsize++;
		H.A[H.heapsize] = INT_MIN;
		Incr_key(H, H.heapsize, key);
		return true;
	}

	return false;
}
int Pop(heap H) {
	if (H.heapsize > 0) {
		int max = H.A[0];
		H.A[0] = H.A[H.heapsize];
		H.heapsize--;
		Heapify(H, 0);
		return max;
	}
}

//Hash tables
struct Hash_field {
	int key;
	int state; // 0 - free, 1 - taken, 2 - complicated
};
int Hash(int i, int key, int n) {
	return (key + i) % n;
}
bool Insert_hash(Hash_field *&H, int key, int n) {
	int i = 0, k = Hash(i, key, n);

	while (i != n && H[k].state == 1) {
		i++;
		k = Hash(i, key, n);
	}
	if (i == n) return false;

	H[k].key = key;
	H[k].state = 1;
	return true;
}
int Search_hash(Hash_field *&H, int key, int n) {
	int i = 0, k = Hash(i, key, n);

	while (i != n && H[k].state != 0) {
		if (H[k].key == key) return k;
		i++;
		k = Hash(i, key, n);
	}
	return -1;
}
bool Delete_hash(Hash_field *&H, int key, int n) {
	int k = Search_hash(H, key, n);
	if (k != -1) {
		H[k].state = 2;
		return true;
	}
	return false;
}
void Print_hash_table(Hash_field *&H, int n) {
	for (int i = 0; i < n; i++) {
		cout << i << ":	";
		if (H[i].state == 1) cout << H[i].key;
		else cout << "NULL";
		cout << endl;
	}
	cout << endl;
}

//Binary Search Trees
struct BST {
	int key;
	BST *right, *left, *parent;
};
BST* Init_BST(int key) {
	BST* x = new BST;
	x->key = key;
	x->parent = x;
	x->right = NULL;
	x->left = NULL;
	return x;
}
void BST_insert(BST* &root, BST* x) {
	if (root == NULL) { root = x; return; }

	else {
		if (x->key < root->key) {
			if (root->left == NULL) { root->left = x; x->parent = root; }
			else BST_insert(root->left, x);
		}

		else {
			if (root->right == NULL) { root->right = x; x->parent = root; }
			else BST_insert(root->right, x);
		}
	}
}
BST* BST_search(BST* root, int key) {
	if (root->key == key) return root;

	else if (root->key < key) {
		if (root->right != NULL)
			return BST_search(root->right, key);
		else return NULL;
	}

	else {
		if (root->left != NULL)
			return BST_search(root->left, key);
		else return NULL;
	}
}
void Print_BST(BST* root) {
	if (root->left != NULL) Print_BST(root->left);
	cout << root->key << " ";
	if (root->right != NULL) Print_BST(root->right);
}
BST* BST_max(BST* root) {

	if (root->right != NULL) return BST_max(root->right);
	else return root;
}
BST* BST_min(BST* root) {
	if (root->left != NULL) return BST_min(root->left);
	else return root;
}
BST* BST_succ(BST* x) {
	if (x->right != NULL) return BST_min(x->right);
	else if (x = x->parent->left) return x->parent;
	else return NULL;
}
BST* BST_pred(BST* x) {
	if (x->left != NULL) return BST_max(x->left);
	else if (x = x->parent->right) return x->parent;
	else return NULL;
}

//to be contiuned...

//Skip List
struct SLNode {
	int key;
	SLNode** next;
	int height;
};
struct SkipList {
	SLNode* head;
	SLNode* tail;
	int max_height;
};
int Get_height(int max_height) {
	int h = 1;

	while (h <= max_height && rand() % 100 < 50) h++;

	return h;
}
SLNode* Init_SLNode(int h, int key) {
	SLNode* x = new SLNode;
	x->key = key;
	x->next = new SLNode*[h];
	x->height = h;

	return x;
}
SkipList* Init_SL(int max_height) {
	SkipList* S=new SkipList;
	
	S->max_height = max_height;

	S->head = Init_SLNode(max_height, INT_MIN);
	S->tail = Init_SLNode(max_height, INT_MAX);
	
	for (int i = 0; i <= max_height; i++) {
		S->head->next[i] = S->tail;
		S->tail->next[i] = NULL;
	}
		

	return S;
}
void Print_SL(SkipList* SL) {
	for (SLNode* x = SL->head->next[0]; x != SL->tail; x = x->next[0]) 
		cout << x->key << " ";
	cout << endl;
}
void Print_detail(SkipList* SL) {
	for (SLNode* x = SL->head->next[0]; x != SL->tail; x = x->next[0]) {
		cout << x->key << ": ";
		for (int i = 0; i < x->height; i++) cout << x->next[i]->key << " ";
		cout << endl;
	}
	cout << endl;
}
void Insert_SL(SkipList* SL, int key) {
	SLNode* x = Init_SLNode(Get_height(SL->max_height), key), *prev = SL->head;
	
	for (int i = SL->max_height - 1; i >= 0; i--) {
		while (prev->next[i]->key < key)
			prev = prev->next[i];

		if (i < x->height) {
			x->next[i] = prev->next[i];
			prev->next[i] = x;
		}

	}

}
SkipList *Make_SL(int maxheight, int n, int k) {
	SkipList *SL = Init_SL(maxheight);
	for (int i = 0; i < n; i++) Insert_SL(SL, rand() % k);
	return SL;
}
SLNode* Search_SL(SkipList* SL, int key) {
	SLNode *prev = SL->head;
	for (int i = SL->max_height - 1; i >= 0; i--)
		while (prev->next[i]->key < key)
			prev = prev->next[i];

	if (prev->next[0]->key == key) return prev->next[0];
	
	return NULL;
}
bool Delete_SL(SkipList* SL, int key) {
	SLNode *prev = SL->head;
	for (int i = SL->max_height - 1; i >= 0; i--) { 
		while (prev->next[i]->key < key)
			prev = prev->next[i];

		if (prev->next[i]->key == key) 
			prev->next[i] = prev->next[i]->next[i];
	}

	if (prev->next[0]->key == key) {
		SLNode* tmp = prev->next[0];
		prev->next[0] = prev->next[0]->next[0];
		delete tmp;
		return true;
	}

	return false;
}

//Lasy zbiorow rozlacznych
struct node {
	int key, rank;
	node *parent;
};
node* Make_set(int key) {
	node *x = new node;
	x->key = key;
	x->parent = x;
	x->rank = 0;
	return x;
}
node* Find_parent(node* x) {
	if (x->parent == x) return x;
	else x->parent = Find_parent(x->parent);
}
void Union(node* x, node* y) {
	x = Find_parent(x);
	y = Find_parent(y);
	if (x->rank < y->rank) y->parent = x;
	else if (x->rank == y->rank) { y->parent = x; x->rank++; }
	else x->parent = y;
}











int main()
{
	srand(time(NULL));
	BST* root = NULL;
	for (int i = 0; i < N; i++) BST_insert(root, Init_BST(rand() % K));
	Print_BST(root);
	cout << endl;
	cout << BST_max(root);
	cout << endl;
	system("pause");
	
	return 0;
}

