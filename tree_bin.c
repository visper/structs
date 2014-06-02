#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "timer.h"

struct tree {
	struct node* root;
};

struct node {
	int value;
	struct node* left;
	struct node* right;
};

#define ALLOC_ARR(arr, count) ((arr) = malloc((count) * sizeof ((arr)[0])))
#define ALLOC_PTR(ptr) ALLOC_ARR(ptr, 1)

#define EMPTY     0
#define NO_EMPTY  1
#define ERROR     -1

void tree_ini(struct tree* vtree, int ivalue);
void tree_fini();
//struct tree* tree_node_add();
int tree_node_add(struct tree* vtree, int value);
void tree_node_remove();
struct node* inorder_add(struct node* vnode, int value, int* index);
//обход  void tree_
//struct node* inorder_node(struct node* vnode, int dir);
//struct node* inorder(struct tree* vtree, int dir);
//int invariant(struct tree* vtree);

void tree_ini(struct tree* vtree, int ivalue)
{
	struct node* temp;
	ALLOC_PTR(temp);
	assert(temp != 0);

	temp->value = ivalue;
	temp->left = 0;
	temp->right = 0;

	vtree->root = temp;
}

//in tree all values < root places left, all values > root placed right
int tree_node_add(struct tree* vtree, int value)
{
	int index = 0;
	struct node* temp;

	//left
	if (value <= vtree->root->value) {
		if (vtree->root->left != 0) 
			temp = inorder_add(vtree->root->left, value, &index);
		else {
			temp = vtree->root;
			index = 1;
		}
	}
	//right
	if (value > vtree->root->value) {
		if (vtree->root->right != 0)
			temp = inorder_add(vtree->root->right, value, &index);
		else {
			temp = vtree->root;
			index = 2;
		}
	}
	printf("test\n");
	//assert(temp == 0);
//	assert(index != 0);

	struct node* t;
	ALLOC_PTR(t);
	assert(t > 0);
	
	t->left = 0;
	t->right = 0;
	t->value = value;
	
	if (index == 1) 
		temp->left = t;
	else if (index == 2)
		temp->right = t;
	else {
		perror("wrong returned data from inorder");
	}

//	assert(temp->)
	return 0;
}

//index = 1 - left, 2 - right
struct node* inorder_add(struct node* vnode, int value, int* index)
{
	struct node *t = 0;
	//left
	if (value <= vnode->value) {
		if(vnode->left == 0) {
			*index = 1;
			return vnode;
		}
		else {
			t = inorder_add(vnode->left, value, &index);
		}
	}
	//right
	if (value > vnode->value) {
		if(vnode->right == 0) {
			*index = 2;
			return vnode; //here problem
		}
		else {
			t = inorder_add(vnode->right, value, &index);
		}
	}
}
/*
struct node* inorder_node(struct node* vnode, int dir)
{
	static struct node* prev;

	if(vnode == 0)
		return prev;

	struct node* t = 0;
	if(dir == 0) {//left
		prev = vnode;
		t = inorder_node(vnode->left, dir);
	}
	else if(dir == 1) {
		prev = vnode;
		t = inorder_node(vnode->right, dir);
	}
	else {
		t = 0;
		perror("error dir in inorder");
		return (struct node*)-1;
	}
}

struct node* inorder(struct tree* vtree, int dir)
{
	//left or right
	if(dir == 0 || dir == 1) {
		struct node* temp = vtree->root;
//		while(temp != 0) {
			temp = inorder_node(temp, dir);
//		}
		return temp;
	}
	else {
		perror("error dir in inorder");
		return (struct node*)-1;
	}
}
*/
//__________________________________________________________________________
//                               algo from Korman
//__________________________________________________________________________
void inorder_tree_walk(struct node* vroot)
{
	if (vroot != 0) {
		inorder_tree_walk(vroot->left);
		printf("%i ", vroot->value);
		inorder_tree_walk(vroot->right);
	}
}
/*
void inorder_tree_walk(x)
{
	if (x != 0) {
		inorder_tree_walk(left[x]);
		printf(value[x]);
		inorder_tree_walk(right[x]);
	}
}
*/
struct node* tree_search(struct node* vroot, int value_find)
{
	if (vroot == 0 || value_find == vroot->value)
		return vroot;
	if (value_find < vroot->value) 
		tree_search(vroot->left, value_find);
	else
		tree_search(vroot->right, value_find);
}
//x - root, k - element for finding
/*
//return no void
void tree_search(x,k)
{
	if (x == 0 || k == key[x])
		return x;
	if (k < key[x]) 
		tree_search(left[x],k);
	else
		tree_search(right[x],k);
}
*/

struct node* iterative_tree_search(struct node* vroot, int value_find)
{
	while(vroot != 0 && value_find != vroot->value) {
		if (value_find < vroot->value)
			vroot = vroot->left;
		else
			vroot = vroot->right;
	}
	return vroot;
}
/*
void iterative_tree_search(x,k)
{
	while(x != 0 && k != key[x]) {
		if (k < key[x])
			x = left[x];
		else
			x = right[x];
	}
	return x;
}
*/

//не учитывается значение root
struct node* tree_minimum(struct node* vroot)
{
	while(vroot->left != 0) {
		vroot = vroot->left;
	}
	return vroot;
}

/*
void tree_minimum(x)
{
	while(left[x] != 0) {
		x = x->left[x];
	}
	return x;
}
*/

//не учитывается значение root
struct node* tree_maximum(struct node* vroot)
{
	while(vroot->right != 0) {
		vroot = vroot->right;
	}
	return vroot;
}

/*
void tree_maximum(x)
{
	while(right[x] != 0) {
		x = right[x];
	}
	return x;
}
*/
/*
struct node* tree_successor(struct node* vroot)
{
	if (vroot->right != 0) {
		struct node* t;
		t = tree_minimum(vroot->right);
		//тут не понятно как эта функция найдет следующий елемент
		//если minimum найдет замого дальнего потомка
	}
	//не ясно как эта штука работате над левам деревом
	//что за "y" и что за "p"
	y = p[x];
	while (y != 0 && x == right[y]) {
		x = y;
		y = p[y];
	}
	return y;
}
*/
/*
void tree_successor(x)
{
	if (right[x] != 0)
		tree_minimum(right[x]);

	y = p[x];
	while (y != 0 && x == right[y]) {
		x = y;
		y = p[y];
	}
	return y;
}
*/

//T - дерево, z - указатель на вставляемую вершину
void tree_insert(struct tree* vtree, struct node* vnode)
{
//	y = 0;
//	x = root[T];
	struct node* y = 0;
	struct node* root = vtree->root;
	while (root != 0) {
		y = root;
		if (vnode->value < root->value)
			root = root->left;
		else
			root = root->right;
	}
	//что такое p[z]???????????????
//	p[z] = y;
	if (y == 0) 
		vtree->root = vnode;
//		root[T] = z;
	else {
		if (vnode->value < y->value)
			y->left = vnode;
//			left[y] = z;
		else
			y->right = vnode;
//			right[y] = z;
	}
}

/*
//
void tree_insert(T,z)
{
	y = 0;
	x = root[T];
	while (x != 0) {
		y = x;
		if (key[z] < key[x])
			x = left[x];
		else
			x = right[x];
	}
	p[z] = y;
	if (y == 0) 
		root[T] = z;
	else {
		if (key[z] < key[y])
			left[y] = z;
		else
			right[y] = z;
	}
}
*/
/*
void tree_delete(T, struct node* z)
{
	struct node* y = 0;
	if (z->left == 0 || z->right == 0)
		y = z;
	else
		y = tree_successor(z); //not work
	struct node* x = 0;
	if (y->left != 0)
		x = y->left;
	else
		x = y->right;
	if (x != 0)
		p[x] = p[y]; //не понимаю что это такое
	if (p[y] == 0) //опять непонимаю что за p[y]
		T->root = x;
	else {
		if (y == left[p[y]]) //тут дальше ваще лажа с p[y]
			left[p[y]] = x;
		else
			right[p[y]] = x;
	}
	if (y != z) {
		key[z] = key[y];
		//копируем данные связанные с игриком
	}
	return y;
}
*/
/*
void tree_delete(T,z)
{
	if (left[z] == 0 || right[z] == 0)
		y = z;
	else
		y = tree_successor(z);
	if (left[y] != 0)
		x = left[y];
	else
		x = right[y];
	if (x != 0)
		p[x] = p[y];
	if (p[y] == 0)
		root[T] = x;
	else {
		if (y = left[p[y]])
			left[p[y]] = x;
		else
			right[p[y]] = x;
	}
	if (y != z) {
		key[z] = key[y];
		//копируем данные связанные с игриком
	}
	return y;
}
*/


int main(int argc, char** argv)
{
	struct tree* tree;
	ALLOC_PTR(tree);
	assert(tree != 0);

	tree_ini(tree, 50);

//	int tree_node_add(struct tree* vtree, int value)
	int rc = tree_node_add(tree, 10);
	rc = tree_node_add(tree, 20);
	rc = tree_node_add(tree, 1);
	rc = tree_node_add(tree, 4); //fail
	rc = tree_node_add(tree, 120);
	rc = tree_node_add(tree, 110);
	rc = tree_node_add(tree, 130);
	rc = tree_node_add(tree, 100); //fail
	rc = tree_node_add(tree, 3); //fail

	inorder_tree_walk(tree->root);

	size_t start = 0;
	size_t finish = 0;

	struct node* t = 0;
	start = checkpoint();
	t = tree_search(tree->root, 120);
	finish = checkpoint();
	printf("\nrecursuve search %i\n", t->value);
	printf("time recursive: %zu\n", finish - start);

	start = finish = 0;
	start = checkpoint();
	t = iterative_tree_search(tree->root, 120);
	finish = checkpoint();
	printf("\niterative search %i\n", t->value);
	printf("time iterative: %zu\n", finish - start);

	t = tree_minimum(tree->root);
	printf("minimum: %i \n", t->value);

	t = tree_maximum(tree->root);
	printf("maximum: %i \n", t->value);


	struct node* temp;
	ALLOC_PTR(temp);
	assert(temp != 0);
	temp->value = 64;
	temp->right = 0;
	temp->left = 0;
//T - дерево, z - указатель на вставляемую вершину
	tree_insert(tree, temp);

	inorder_tree_walk(tree->root);
/*
	tree = tree_node_add(tree, 1, 1);
	//bad bug
	tree = tree_node_add(tree, 4, 1);
	tree = tree_node_add(tree, 2, 0);
	tree = tree_node_add(tree, 3, 0);
	tree = tree_node_add(tree, 4, 1);
*/
	//tree_print(tree);

/*
	tree_fini(tree);
*/

	return 0;
}
