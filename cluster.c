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


cluster* create_cluster_by_capacity(object_list* all_objs, int initcapacity)
{
	cluster* c = (cluster*)malloc(sizeof(cluster));
	c->size = 0;
	c->objids = (uint*)malloc(initcapacity*sizeof(uint));
	c->capacity = initcapacity;
	c->all_objs = all_objs;
	return c;
}


void destroy_cluster(cluster* c)
{
	free(c->objids);
	free(c);
}


cluster* clone_cluster(cluster* c)
{
	cluster* cclone = create_cluster_by_capacity(c->all_objs, c->capacity);
	memcpy((void*)cclone->objids, (void*)c->objids, c->size*sizeof(OBJID));
	cclone->size = c->size;
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


int remove_object(cluster* c, int n)
{
	int i;
	if(c->size==0)	{
		printf("remove_object error, size==0!\n");
		return -1;
	}
	else	if(c->size-1<n) {
		printf("remove_object error, c->size-1<n!\n");
		return -1;
	}
	else	{
		for(i=n;i<c->size-1;i++)	{
			c->objids[i] = c->objids[i+1];
		}
		c->size--;
		//mmm: can have capacity changed
	}

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


cluster_list* create_cluster_list_by_capacity(int initcapacity)	
{
	cluster_list* cl;
	cl = (cluster_list*)malloc(sizeof(cluster_list));
	cl->size = 0;
	cl->plist = (cluster**)malloc(initcapacity*sizeof(cluster*));
	cl->capacity = initcapacity;
	return cl;	
}

//destroy_cluster_list


cluster_list* clone_cluster_list(cluster_list* cl)
{
	int i;
	cluster_list* clclone;
	cluster* c;
	clclone = create_cluster_list_by_capacity(cl->capacity);
	for(i=0;i<cl->size;i++)	{
		c = clone_cluster(cl->plist[i]);
		add_cluster(clclone, c);
	}
	return clclone;
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

int remove_cluster(cluster_list* cl, int n)
{
	int i;
	cluster* toremove;
	if(cl->size==0)	{
		printf("remove_cluster error, cl size == 0!\n");
		return -1;
	}
	else if(cl->size-1<n)	{
		printf("remove_cluster error, cl size-1 < n !\n");
		return -1;
	}
	else {
		toremove = cl->plist[n];

		for(i=n;i<cl->size-1;i++)	{
			cl->plist[i] = cl->plist[i+1];
		}
		cl->size--;

		destroy_cluster(toremove);
	}

	return 0;
}

/* ----- struct cluster_list_list ----------------- */
cluster_list_list* create_cluster_list_list()
{
	cluster_list_list* cll = (cluster_list_list*)malloc(sizeof(cluster_list_list));
	cll->plist = (cluster_list**)malloc(NUM_INIT_CLUSTERLISTLIST_SIZE*sizeof(cluster_list*));
	cll->capacity = NUM_INIT_CLUSTERLISTLIST_SIZE;
	cll->size = 0;
	return cll;
}


int add_cluster_list(cluster_list_list* cll, cluster_list* cl)
{
	if(cll->size==cll->capacity)	{
		if(expand_cluster_list_list(cll))	{
			printf("add_cluster_list error, expand_cluster_list_list failed!\n");
			return -1;
			}
			}
	cll->plist[cll->size] = cl;
	cll->size++;

	return 0;
}

int expand_cluster_list_list(cluster_list_list* cll)
{
	int newcapacity = cll->size + NUM_CLUSTERLISTLIST_SIZE_INCREMENT;
	cluster_list** newplist;
	if(newcapacity>NUM_MAX_CLUSTERLISTLIST_SIZE)	{
		printf("expand_cluster_list_list error, size max exceeded!\n");
		return -1;
	}
	else	{
		newplist = (cluster_list**)realloc(cll->plist, newcapacity*(sizeof(cluster_list*)));
		if(!newplist)	{
			printf("expand_cluster_list_list error, realloc failure!\n");
			return -1;
		}
		else	{
			cll->plist = newplist;
			cll->capacity = newcapacity;
		}
	}

	return 0;
}


