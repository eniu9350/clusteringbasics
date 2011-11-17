#include "cluster.h"

cluster* create_cluster()
{
	cluster* c = (cluster*)malloc(sizeof(cluster));
	c->size = 0;
	c->capacity = NUM_INIT_CLUSTER_SIZE;
	c->objs = (uint*)malloc(c->capacity*sizeof(uint));
	return c;	
}

int expand_cluster(cluster* c)
{
	uint* tmp;
	int newsize = c->capacity+NUM_CLUSTER_SIZE_INCREMENT;
	if(newsize<=NUM_MAX_CLUSTER_SIZE)	{
		tmp = (uint*)realloc(c->objs, newsize);
		if(!tmp)	{
			printf("fail to expand cluster(realloc error)!\n");
			return -1;
		}
		else{
			c->objs = tmp;
			c->capacity = newsize;
		}
	}
	else	{
		printf("fail to expand cluster!(size limit reached)\n");
		return -1;
	}
}
