#include "cluster.h"

#include <stdio.h>

alisttpl_struct_impl(object);
alisttpl_struct_impl(cluster);
alisttpl_struct_impl(cluster_list);

/* ----- struct object_space ----------------- */
object_space* obj_create_obj_space(int dim)
{
	object_space* space;
	space = (object_space*)malloc(sizeof(object_space));
	space->dim = dim;
	space->all = create_object_alist();
	return space;
}

/* ----- struct cluster ----------------- */
cluster* clone_cluster(cluster* c)
{
	int i;
	cluster* cclone = create_object_alist();	//mmm:create by capacity
	for(i=0;i<c->size;i++)	{
		add_object(cclone, c->list[i]);
	}
	
	//memcpy((void*)cclone->objids, (void*)c->objids, c->size*sizeof(OBJID));
	//cclone->size = c->size;
	return cclone;
}


int merge_cluster(cluster* c, cluster* toadd)
{
	int newsize = c->size + toadd->size;
	int i;
	if(newsize>c->capacity)	{
		if(expand_object_alist(c))	{
			printf("merge_cluster error, expand failed!\n");
			return -1;
		}
	}
	for(i=0;i<toadd->size;i++)	{
		add_object(c, toadd->list[i]);
	}
	return 0;
}


/* ----- struct cluster_list ----------------- */
cluster_list* clone_cluster_list(cluster_list* cl)
{
	int i;
	cluster_list* clclone;
	cluster* c;
	clclone = create_cluster_alist();//create by capacity will be more efficient
	for(i=0;i<cl->size;i++)	{
		c = clone_cluster(cl->list[i]);
		add_cluster(clclone, c);
	}
	return clclone;
}
