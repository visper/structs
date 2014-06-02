#include <stdio.h>
#include <stdlib.h>
//#include <stdbool.h>
//#include <string.h> /* memset */
#include <assert.h> /* assert */
#include <sys/time.h> /* gettimeofday */
//#include <sys/types.h>
//#include <errno.h>

#include <unistd.h> //sleep

size_t checkpoint(void)
{
	struct timeval  tv;
	int		rc;

	rc = gettimeofday(&tv, NULL);
	assert(rc == 0); /* XXX: provide more correct solution */

	//what the FUCK????
	return 1000000*tv.tv_sec + tv.tv_usec;
}

void report(size_t elapsed)
{
//	printf("time=%5.5f\n", ((float)elapsed)/tm);
//mks
//how from size_t do float
	printf("time=%5.5f\n", ((float)elapsed));
}
/*
int main()
{
	size_t start = checkpoint();

	sleep(2);

	size_t finish = checkpoint();

	report(finish - start);

	return 0;
}
*/
