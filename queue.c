#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>

struct node {
	int weight;
};

struct queue_node {
	struct queue_node* prev;
	struct node* node;
};

struct queue {
	struct queue_node* head;
	struct queue_node* tail;
};

#define ALLOC_ARR(arr, count) ((arr) = malloc((count) * sizeof ((arr)[0])))
#define ALLOC_PTR(ptr) ALLOC_ARR(ptr, 1)

//maybe better write 0,1,2
#define EMPTY 0
#define ONE   1
#define MORE  2
#define ERROR -1

void queue_ini(struct queue* vqueue);
void queue_fini(struct queue* vqueue);
//add to head
int queue_add(struct queue* vqueue, struct node* vnode);

int invariant(struct queue* vqueue);
void queue_print(struct queue* vqueue);
int queue_del(struct queue* vqueue);

//identify state of list
//@0 if empty, @1 if only one element, @2 if more than 1 elem
int invariant(struct queue* vqueue)
{
	if (vqueue->head == vqueue->tail && vqueue->head == 0)
		return EMPTY;
	else if (vqueue->head == vqueue->tail && vqueue->head != 0)
		return ONE;
	else if (vqueue->head != vqueue->tail && vqueue->head != 0
		 && vqueue->tail != 0)
		return MORE;
	else
		return ERROR;
}


void queue_ini(struct queue* vqueue)
{
	struct queue_node* t = 0;
	vqueue->head = t;
	vqueue->tail = vqueue->head;
}

int queue_add(struct queue* vqueue, struct node* vnode)
{
	int rc = invariant(vqueue);
	if (rc == EMPTY) {
		struct queue_node* temp;
		ALLOC_PTR(temp);
		assert(temp > 0);

		temp->prev = 0;
		temp->node = vnode;

		vqueue->head = temp;
		vqueue->tail = vqueue->head;

		assert(vqueue->head != 0
		       && vqueue->tail != 0
		       && vqueue->head == vqueue->tail);
		assert(vqueue->head->prev == 0);

		return 0;
	}
	if (rc == ONE) {
		struct queue_node* temp;
		ALLOC_PTR(temp);
		assert(temp > 0);

		temp->prev = 0;
		temp->node = vnode;

		vqueue->tail->prev = temp;
		vqueue->head = temp;

		//2 elements
		assert(vqueue->head != vqueue->tail);
		assert(vqueue->tail->prev != 0);
 		assert(vqueue->head != 0);
 		assert(vqueue->tail != 0);

		return 0;
	}
	if (rc == MORE) {
		struct queue_node* temp;
		ALLOC_PTR(temp);
		assert(temp > 0);

		temp->prev = 0;
		temp->node = vnode;

		vqueue->head->prev = temp;
		vqueue->head = temp;

		assert(vqueue->head != vqueue->tail);

		return 0;
	}
	if (rc == ERROR) {
		perror("somthing wrong with queue");
		return rc;
	}

	perror("no one case is not apply");
	return ERROR;
}

void queue_print(struct queue* vqueue)
{
	//prev
	struct queue_node* temp;
	temp = vqueue->tail;
	assert(temp != 0);

	printf("print list from tail: \n");

	while(temp) {
		printf("%i ", temp->node->weight);
		temp = temp->prev;
	}
	printf("\n");
}

int queue_del(struct queue* vqueue)
{
	int rc = invariant(vqueue);
	if (rc == EMPTY) {
		//here maybe error
		return ERROR;
	}
	if (rc == ONE) {
		assert(vqueue->tail != 0);
		assert(vqueue->head != 0);
		assert(vqueue->head->node != 0);
//		assert(vqueue->tail->node->weight != 0);

		printf("del if ONE: %i\n", vqueue->tail->node->weight);
		int t = vqueue->tail->node->weight;

		struct queue_node* temp;
		temp = vqueue->tail;

		temp->prev = 0;

		if(temp->node) {
			free(temp->node);
			temp->node = 0;
		}
		if(temp) {
			free(temp);
			temp = 0;
		}

		vqueue->tail = temp;
		vqueue->head = temp;

		return t;
	}
	if (rc == MORE) {
		assert(vqueue->tail->node->weight != 0);
		int t = vqueue->tail->node->weight;

		struct queue_node* temp;
		temp = vqueue->tail;

		vqueue->tail = temp->prev;
		temp->prev = 0;

		if(temp->node) {
			free(temp->node);
			temp->node = 0;
		}
		if(temp) {
			free(temp);
			temp = 0;
		}

		return t;
	}
	if (rc == ERROR) {
		perror("somthing wrong with queue_in_del");
		return rc;
	}

	perror("no one case is not apply_in_del");
	return ERROR;

}

void queue_fini(struct queue* vqueue)
{
/*
	struct queue_node* t;
	t = vqueue->tail;
	if(t == 0)
		return;

	struct queue_node* temp;
	while (t) {
		t = vqueue->tail->prev;

		temp = vqueue->tail;
		if (temp->node != 0) {
			free(temp->node);
			temp->node = 0;
		}

//		vqueue->tail = temp->prev;
		vqueue->tail = t;//if one element, here tail = link
		temp->prev = 0;

		if(temp != 0) {
			free(temp);
			temp = 0;
		}
	}

	vqueue->head == 0; // now link in prev = 0;
	assert(vqueue->tail == 0);
*/
//	assert(vqueue->head != 0);

	while(vqueue->head != 0) {
//		printf("test fini\n");
		printf("tail: %i ", vqueue->tail->node->weight);
		printf("head: %i\n", vqueue->head->node->weight);
		queue_del(vqueue);
	}
}

int main(int argc, char** argv)
{
	struct queue* que;
	ALLOC_PTR(que);
	assert(que > 0);

	queue_ini(que);

	struct node* t1;
	ALLOC_PTR(t1);
	assert(t1 > 0);

	t1->weight = 2;

	int rc = queue_add(que, t1);
	assert(rc == 0);

	queue_print(que);

	rc = queue_del(que);
	printf("returned value: %i \n", rc);
	assert(que->head == 0);

	struct node* t2;
	ALLOC_PTR(t2);
	assert(t2 > 0);
	t2->weight = 3;

	struct node* t3;
	ALLOC_PTR(t3);
	assert(t3 > 0);
	t3->weight = 4;

	struct node* t4;
	ALLOC_PTR(t4);
	assert(t4 > 0);
	t4->weight = 5;

//	queue_print(que); //must be assert

	rc = queue_add(que, t2);
	assert(rc == 0);

	rc = queue_add(que, t3);
	assert(rc == 0);

	rc = queue_add(que, t4);
	assert(rc == 0);

	queue_print(que);

	printf("test\n");
/*
	rc = queue_del(que);
	printf("returned value: %i \n", rc);

	rc = queue_del(que);
	printf("returned value: %i \n", rc);

	rc = queue_del(que);
	printf("returned value: %i \n", rc);
*/
	queue_fini(que);
	assert(que->head == 0);
	assert(que->tail == 0);

	printf("test2\n");

//	if(que->head == que->tail && que->head == 0) {
	if(que->head == 0 && que->tail == 0) {
		free(que);
		que = 0;
	}
	else
		perror("error fini");
	assert(que == 0);
	//end test rm____________

	return 0;
}
