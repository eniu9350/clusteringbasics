#include "cluster.h"

#include <stdio.h>

/* ----- struct cluster ----------------- */
cluster* create_cluster(object_list* all_objs)
{
	cluster* c = (cluster*)malloc(sizeof(cluster));
	c->size = 0;
	c->objids = (uint*)malloc(NUM_INIT_CLUSTER_SIZE*sizeof(uint));
	c->capacity = NUM_INIT_CLUSTER_SIZE;
	c->all_objs = all_objs;
	return c;
}

int add_object(cluster* c, int objid)
{
	if(c->size>c->capacity)	{
		printf("add_object error, size>capacity already!\n");
		return -1;
	}
	else if(c->size==c->capacity)	{
		if(expand_cluster(c))	{
			printf("add_object error, expand failed!\n");
			return -1;
		}
	}

	c->objids[c->size]=objid;
	c->size++;
	return 0;
}

int expand_cluster(cluster* c)
{
	int newcapacity = c->capacity+NUM_CLUSTER_SIZE_INCREMENT;
	uint* tmp;
	if(newcapacity>NUM_MAX_CLUSTER_SIZE)	{
		printf("fail to expand cluster!(size limit reached)\n");
		return -1;
	}
	else	{
		tmp = (uint*)realloc(c->objids, newcapacity);
		if(!tmp)	{
			printf("fail to expand cluster(realloc error)!\n");
			return -1;
		}
		c->objids = tmp;
		c->capacity = newcapacity;
	}
	return 0;
}


int merge_cluster(cluster* c, cluster* toadd)
{
	int newsize = c->size + toadd->size;
	int i;
	if(newsize>c->capacity)	{
		if(expand_cluster(c))	{
			printf("merge_cluster error, expand failed!\n");
			return -1;
			}
	}
	for(i=0;i<toadd->size;i++)	{
		add_object(c, toadd->objids[i]);
	}
	return 0;
}
/* ----- struct cluster_list ----------------- */
cluster_list* create_cluster_list()	
{
	cluster_list* cl;
	cl = (cluster_list*)malloc(sizeof(cluster_list));
	cl->size = 0;
	cl->plist = (cluster**)malloc(NUM_INIT_CLUSTERLIST_SIZE*sizeof(cluster*));
	cl->capacity = NUM_INIT_CLUSTERLIST_SIZE;
	return cl;	
}

int expand_cluster_list(cluster_list* cl)
{
	int newcapacity = cl->size+NUM_CLUSTERLIST_SIZE_INCREMENT;
	cluster** newplist;
	if(newcapacity>NUM_MAX_CLUSTERLIST_SIZE)	{
		printf("expand cluster_list error, capacity limit exceeded!\n");
		return -1;
	}
	else	{
		newplist = (cluster**)realloc(cl->plist, newcapacity*sizeof(cluster*));
		if(!newplist)	{
			printf("expand cluster_list error, realloc failed!\n");
			return -1;
		}
		cl->plist = newplist;
		cl->capacity = newcapacity;
	}
	return 0;
}

int add_cluster(cluster_list* cl, cluster* c)
{
	if(c->size>c->capacity)	{
		printf("add_cluster error, size>capacity already!\n");
		return -1;
	}
	else if(c->size==c->capacity)	{
		if(expand_cluster_list(cl))	{
			printf("add_cluster error, expand failed!\n");
			return -1;
		}
	}

	cl->plist[cl->size] = c;
	cl->size++;
	return 0;
}
