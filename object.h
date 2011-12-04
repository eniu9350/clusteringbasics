#ifndef _CLUSTERINGBASICS_OBJECT_
#define _CLUSTERINGBASICS_OBJECT_

#include "common.h"

#include <alisttpl.h>


#define NUM_OBJECT_ATTRIBUTES_DIMENSION 100



typedef struct _object_att	{
	__u32 id;
	double v;
} object_att;
alisttpl_struct(object_att);

typedef struct _object	{
	int id;
	//double* atts;
	object_att_alist* atts;

	//object_space* space;
}object;


object_att* obj_get_att(object* o, __u32 aid);

/*
typedef struct object_list	{
	object* list;
	int size;
	int capacity;
	int dim;
}object_list;
*/



#endif
