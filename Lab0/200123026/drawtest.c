#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
	static char buf[2000];
	printf(1,"Draw sys call returns %d\n",draw((void*) buf,2000));

	printf(1,"%s",buf);
	exit();
}
