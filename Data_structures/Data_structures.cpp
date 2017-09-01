// Data_structures.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <climits>
using namespace std;
const int N = 20, K = 10;

void Swap(int* A, int i, int j) {
	int tmp = A[i];
	A[i] = A[j];
	A[j] = tmp;
}

//Heaps
struct heap {
	int* A, heapsize, lenght;
};
heap Init_heap(int lenght) {
	heap H;
	H.A = new int[lenght];
	H.lenght = lenght;
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
void Push(heap H, int key) {
	H.heapsize++;
	H.A[H.heapsize] = INT_MIN;
	Incr_key(H, H.heapsize, key);
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
struct field {
	int key=-1;
	bool free = true;
	bool deleted=false;
};
struct Hash_table {
	field* H;
	int n;
};
void Init_hash_table(Hash_table &H, int n) {
	H.H = new field[n];
	H.n = n;
}
int Hash(int i, int key, int n) {
	return (key + i) % n;
}
void Insert_hash_table(Hash_table H, int key, int n) {
	int i=0, k = Hash(i, key, n);

	while (i != n && !H.H[k].free) {
		i++;
		k = Hash(i, key, n);
	}
	if (i == n) cout << "ERROR";

	H.H[k].key = key;
	H.H[k].free = false;
}
int Search_hash_table(Hash_table H, int key, int n) {
	int i = 0, k = Hash(i, key, n);
	while (i != n && H.H[k].deleted) {
		if (H.H[k].key == key) return k;
		i++;
		k = Hash(i, key, n);
	}
	if (i == n) cout << "ERROR";
	else cout << "NO GIVEN VALUE";

	return -1;
}
void Delete_hash_table(Hash_table H, int key, int n) {
	int k = Search_hash_table(H, key, n);
	if (k != -1) {
		H.H[k].key = -1;
		H.H[k].free = true;
		H.H[k].deleted = true;
	}
}

//Binary Search Trees
struct BST_node {
	int key;
	BST_node *right, *left, *parent;
};
BST_node* Make_BST_node(int key) {
	BST_node* x = new BST_node;
	x->key = key;
	x->parent = x;
	x->right = NULL;
	x->left = NULL;
	return x;
}
void BST_insert_recurr(BST_node* root, BST_node* x) {
	if (root == NULL) root = x;

	else {
		if (x->key < root->key) {
			if (root->left == NULL) { root->left = x; x->parent = root; }
			else BST_insert_recurr(root->left, x);
		}

		else {
			if (root->right == NULL) { root->right = x; x->parent = root; }
			else BST_insert_recurr(root->right, x);
		}
	}
}
BST_node* BST_search(BST_node* root, int key) {
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
struct Node {
	int key, rank;
	Node *parent;
};
Node* Make_node(int key) {
	Node *x;
	x->key = key;
	x->parent = x;
	x->rank = 0;
	return x;
}
Node* Find_parent(Node* x) {
	if (x->parent == x) return x;
	else x->parent = Find_parent(x->parent);
}
void Union(Node* x, Node* y) {
	x = Find_parent(x);
	y = Find_parent(y);
	if (x->rank <= y->rank) {
		y->parent = x;
		if (x->rank == y->rank) x->parent++;
	}
	else if (x->rank < y->rank) x->parent = y;
}











int main()
{
	srand(time(NULL));
	SkipList *SL = Make_SL(16, N, K);
	Print_detail(SL);
	Delete_SL(SL, 2);
	Delete_SL(SL, 4);
	Delete_SL(SL, 0);
	Print_detail(SL);
    return 0;
}

