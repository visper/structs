#include "right_list_three.h"

struct three_mass3 {
	struct vertex_list3* mass;
};

void three_mass_ini3(struct three_mass3* vmass)
{
	ALLOC_PTR(vmass->mass);
	if (vmass->mass == 0)
		return;

	vertex_list_ini3(vmass->mass);
}

void three_mass_fini3(struct three_mass3* vmass)
{
	vertex_list_fini3(vmass->mass);
}

//invariant check that all lists be equal in lenght
bool three_mass_invariant3(struct three_mass3* vmass)
{
        struct vertex_list_node3* scan = NULL;

	size_t count = 0;
        for (scan = vmass->mass->head; scan != NULL; scan = scan->next)
		count++;

        return 0;
}

//add
int three_mass_add3(struct three_mass3* vmass, struct vertex3* vertex)
{
	int rc = vertex_list_add3(vmass->mass, vertex);
	if (rc == -ENOMEM || rc == ENOMEM)
		return ENOMEM;
	if (rc == -EINVAL || rc == EINVAL)
		return EINVAL;
	assert(rc == 0);

//	printf("invariant in add: %i\n", three_mass_invariant(vmass));
	assert(three_mass_invariant3(vmass) == 0);

	return 0;
}

//ins
int three_mass_ins3(struct three_mass3* vmass, struct vertex3* given,
		   const struct vertex3* after,
		   struct vertex_list_node3* node)
{
	assert(node == NULL || after == NULL);

	int rc = vertex_list_ins3(vmass->mass, given, after, node);
	//printf("first %i\n", rc);
	assert(rc == 0);

	assert(three_mass_invariant3(vmass) == 0);
	return rc;
}

//find

//rm
void three_mass_rm3(struct three_mass3* vmass, struct vertex3* vertex, 
		   struct vertex_list_node3* node)
{
	assert(node == NULL || vertex == NULL);

	vertex_list_rm3(vmass->mass, vertex, node);

	assert(three_mass_invariant3(vmass) == 0);
}

/*
//print
void three_mass_print(struct three_mass* vmass)
{
	printf("row\n");
	vertex_list_print(vmass->row);

	printf("column\n");
	vertex_list_print(vmass->column);

	printf("value\n");
	vertex_list_print(vmass->value);
}
*/
