#ifndef _CLUSTERINGBASICS_CLUSTER_
#define _CLUSTERINGBASICS_CLUSTER_

#include "common.h"

typedef struct cluster	{
	uchar* objs;
	int size;
	int capacity;
}cluster;

typedef struct cluster_list	{
	cluster** plist;
	int size;
	int capcacity;
}
#endif
