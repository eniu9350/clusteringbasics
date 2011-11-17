#ifndef _CLUSTERINGBASICS_OBJECT_
#define _CLUSTERINGBASICS_OBJECT_

#include "common.h"


#define NUM_OBJECT_ATTRIBUTES_DIMENSION 100

typedef struct object	{
	int id;
	int atts[NUM_OBJECT_ATTRIBUTES_DIMENSION];
}object;

typedef struct object_list	{
	object* list;
	int size;
}object_list;



#endif
