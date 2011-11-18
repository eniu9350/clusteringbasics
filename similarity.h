#ifndef _CLUSTERINGBASICS_SIMILARITY_
#define _CLUSTERINGBASICS_SIMILARITY_

#include "common.h"

#include "object.h"
#include "cluster.h"

typedef void* sim_calc_fun;
typedef double (*object_sim_calc_fun)(object* o1, object* o2);
typedef double (*cluster_sim_calc_fun)(cluster* o1, cluster* o2);

typedef struct sim_matrix	{
	double matrix[NUM_MAX_CLUSTER_SIZE][NUM_MAX_CLUSTER_SIZE];
	int dimension;
	sim_calc_fun calc_fun;
}sim_matrix;

sim_matrix* create_cluster_sim_matrix(int dimension, sim_calc_fun calc_fun);
#endif
