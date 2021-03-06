#ifndef _CLUSTERINGBASICS_CLUSTER_
#define _CLUSTERINGBASICS_CLUSTER_

#include "common.h"
#include "object.h"

#define NUM_INIT_CLUSTER_SIZE 50
#define NUM_CLUSTER_SIZE_INCREMENT 50
#define NUM_MAX_CLUSTER_SIZE 200*1000

#define NUM_INIT_CLUSTERLIST_SIZE 50
#define NUM_CLUSTERLIST_SIZE_INCREMENT 50
#define NUM_MAX_CLUSTERLIST_SIZE 200*1000

#define NUM_INIT_CLUSTERLISTLIST_SIZE 50
#define NUM_CLUSTERLISTLIST_SIZE_INCREMENT 50
#define NUM_MAX_CLUSTERLISTLIST_SIZE 200*1000

#include <alisttpl.h>

alisttpl_struct(object);
typedef object_alist cluster;

alisttpl_struct(cluster);
typedef cluster_alist cluster_list;

alisttpl_struct(cluster_list);
typedef cluster_list_alist cluster_list_list;

typedef struct _object_space	{
	int dim;
	cluster* all;
} object_space;
object_space* obj_create_obj_space(int dim);

/*
typedef uint OBJID;

typedef struct cluster	{
	OBJID* objids;
	int size;
	int capacity;

	//env
	object_list* all_objs;
}cluster;

typedef struct cluster_list	{
	cluster** plist;
	int size;
	int capacity;
}cluster_list;

typedef struct cluster_list_list	{
	cluster_list** plist;
	int size;
	int capacity;
}cluster_list_list;

cluster* create_cluster(object_list* all_objs);
cluster* create_cluster_by_capacity(object_list* all_objs, int initcapacity);
void destroy_cluster(cluster* c);
cluster* clone_cluster(cluster* c);
int add_object(cluster* c, int objid);
int remove_object(cluster* c, int n);
int expand_cluster(cluster* c);
int merge_cluster(cluster* c, cluster* toadd);

cluster_list* create_cluster_list();	
cluster_list* clone_cluster_list(cluster_list* cl);
int expand_cluster_list(cluster_list* cl);
int add_cluster(cluster_list* cl, cluster* c);
int remove_cluster(cluster_list* cl, int n);

cluster_list_list* create_cluster_list_list();	
int add_cluster_list(cluster_list_list* cll, cluster_list* cl);
int expand_cluster_list_list(cluster_list_list* cll);
*/

#endif
