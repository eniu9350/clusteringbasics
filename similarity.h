#ifndef _CLUSTERINGBASICS_SIMILARITY_
#define _CLUSTERINGBASICS_SIMILARITY_

#include "common.h"

#include "object.h"
#include "cluster.h"

typedef struct sim_matrix	{
	uchar matrix[NUM_MAX_CLUSTER_SIZE][NUM_MAX_CLUSTER_SIZE];
	int dimension;
}sim_matrix;


sim_matrix* create_sim_matrix(int dimension);

#endif
