#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>

#define ALLOC_ARR(arr, count) ((arr) = malloc((count) * sizeof ((arr)[0])))
#define ALLOC_PTR(ptr) ALLOC_ARR(ptr, 1)

struct stack {
	size_t max;	       // maximum elements in this stack
	size_t count;          // number of free elements in stack
	int *stack_store;      // elements
};

int  stack_init(struct stack *s, int count);
void stack_fini(struct stack *s);

int  stack_pop(struct stack *s);
void stack_push(struct stack *s, int elem);

int stack_init(struct stack *s, int count)
{
//	s->count       = count-1;//count - 1 because malloc(100) is from 0 to 99
	s->count       = count;
	s->max         = count; //if max used only with < 
	ALLOC_ARR(s->stack_store, s->count);
	//	s->stack_store = (int*)malloc(s->count * (sizeof(int)));

	return s == NULL ? -ENOMEM : 0;
}

void stack_fini(struct stack *s)
{
	free(s->stack_store);
	s->stack_store = NULL;
}

void stack_push(struct stack *s, int elem)
{
	assert(s->count > 0);
/*
	if(s->count == 0)
//	if(s->count < 0) // size_t
		return;
*/
//	printf("%i ", s->stack_store[s->count]);
	s->stack_store[--s->count] = elem; //here error --s->count
	//printf("s->count value: %zu ", s->count);
}

int  stack_pop(struct stack *s)
{
	assert(s->count < s->max);
/*
	if (s->count < s->max)
		return; // problem with idintification of error
*/
//	printf("%i ", s->stack_store[s->count]);
//______________________del_test
	int temp = s->stack_store[s->count];
	s->stack_store[s->count++] = -1;
	return temp;
//______________________del_test
//	return s->stack_store[s->count++];
}

void stack_print(struct stack *s)
{
	printf("max: %zu\n", s->max);
	printf("count: %zu\n", s->count);

	for(size_t i = 0; i < s->max; ++i) {
		printf("%i ", s->stack_store[i]);
	}
}

int main(int argc, char** argv)
{
	int rc;
	struct stack *s;

	//	s = (struct stack *)malloc(sizeof(struct stack));
	ALLOC_PTR(s);
	assert(s != NULL);
/*
	if (s == 0) {
		perror("error malloc");
		return -ENOMEM;
	}
*/

	rc = stack_init(s, 100);
	assert(rc == 0);
/*
	if (rc != 0) {
		perror("error init");
		return rc; //not (-rc) because init return value with -
	}
*/

//	for (size_t i = 0; i < 100; ++i)
	for (size_t i = 0; i < s->max; ++i)
		stack_push(s, i); // push 2 times 0 in start

	stack_print(s);

	printf("\n");

//	for (size_t i = 99; i > 10; --i) {
	for (size_t i = s->max-1; i > 10; --i) { //maybe (s->max-1)
		rc = stack_pop(s);
		assert(rc == i); // wrong in some cases
/*
		if (rc != i) {
		//hz, problem with return
			printf("%i\n", rc);
			fprintf(stderr ,"problem with return value\n");
			return -1;
		}
*/
	}

	printf("after pop\n");
	stack_print(s);
	printf("\n");

	size_t temp = s->count;

	for (size_t i = 0; i < temp; ++i) 
		stack_push(s, i);
/*
	for (size_t i = s->count; i > 0; --i) 
		stack_push(s, i);
*/
	printf("count after second push: %zu \n", s->count);

	stack_print(s);
	printf("\n");

	stack_fini(s);
	free(s);
	s = 0;

	return 0;
}
