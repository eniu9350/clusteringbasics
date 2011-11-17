#ifndef _CLUSTERINGBASICS_CLUSTER_
#define _CLUSTERINGBASICS_CLUSTER_

#include "common.h"

#define NUM_INIT_CLUSTER_SIZE 50
#define NUM_CLUSTER_SIZE_INCREMENT 50
#define NUM_MAX_CLUSTER_SIZE 1000

#define NUM_INIT_CLUSTERLIST_SIZE 50
#define NUM_CLUSTERLIST_SIZE_INCREMENT 50
#define NUM_MAX_CLUSTERLIST_SIZE 500

typedef struct cluster	{
	uint* objs;
	int size;
	int capacity;
}cluster;

typedef struct cluster_list	{
	cluster** plist;
	int size;
	int capcacity;
}
#endif
