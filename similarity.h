#ifndef _CLUSTERINGBASICS_SIMILARITY_
#define _CLUSTERINGBASICS_SIMILARITY_

#include "common.h"

#include "object.h"
#include "cluster.h"

typedef void* sim_calc_fun;
typedef double (*object_sim_calc_fun)(object_list* ol1, int objid1, object_list* ol2, int objid2);
typedef double (*cluster_sim_calc_fun)(cluster* o1, cluster* o2, double threshold);

typedef struct sim_matrix	{
	double matrix[NUM_MAX_CLUSTER_SIZE][NUM_MAX_CLUSTER_SIZE];
	int dimension;
	sim_calc_fun calc_fun;
}sim_matrix;

sim_matrix* create_cluster_sim_matrix(int dimension, sim_calc_fun calc_fun);


double csim_nearest_nb(cluster* c1, cluster* c2, double threshold);


#define OBJECT_SIMILARITY_MIN -999999
double osim_naive(object_list* ol1, int objid1, object_list* ol2, int objid2);

double odis_euclidean(object_list* ol, int objid1, object_list* ol2, int objid2);
#endif
