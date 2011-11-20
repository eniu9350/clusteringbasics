#ifndef _CLUSTERINGBASICS_OBJECT_
#define _CLUSTERINGBASICS_OBJECT_

#include "common.h"


#define NUM_OBJECT_ATTRIBUTES_DIMENSION 100

typedef struct object	{
	int id;
	double* atts;
}object;

typedef struct object_list	{
	object* list;
	int size;
	int capacity;
	int dim;
}object_list;



#endif
