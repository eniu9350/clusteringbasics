#ifndef _CLUSTERINGBASICS_SIMILARITY_
#define _CLUSTERINGBASICS_SIMILARITY_

#include "common.h"

#include "object.h"
#include "cluster.h"

//typedef void* sim_calc_fun;
typedef double (*object_sim_calc_fun)(object_space* space, object* o1, object* o2);
typedef double (*cluster_sim_calc_fun)(object_space* space, cluster* c1, cluster* c2, double threshold);
/*
typedef struct _obj_sim_matrix	{
	double matrix[NUM_MAX_CLUSTER_SIZE][NUM_MAX_CLUSTER_SIZE];
	int dimension;
	object_sim_calc_fun calc_fun;
}obj_sim_matrix;

typedef struct __sim_matrix	{
	double matrix[NUM_MAX_CLUSTER_SIZE][NUM_MAX_CLUSTER_SIZE];
	int dimension;
	object_sim_calc_fun calc_fun;
}obj_sim_matrix;
*/
typedef struct __sim_matrix	{
	double matrix[NUM_MAX_CLUSTER_SIZE][NUM_MAX_CLUSTER_SIZE];
	int size;
}sim_matrix;
sim_matrix* create_sim_matrix(int size);
int destroy_sim_matrix(sim_matrix* simm);

//---------object sim MATRIX calc-----------------
sim_matrix* calc_obj_sim_matrix(object_space* space, cluster* c, object_sim_calc_fun calc_fun);
//---------cluster sim MATRIX calc-----------------
sim_matrix* calc_cluster_sim_matrix(object_space* space, cluster_list* cl, cluster_sim_calc_fun calc_fun);


//---------object distance metrics---------
double odis_euclidean(object_space* space, object* ol, object* o2);

//---------object sim metrics---------
#define OBJECT_SIMILARITY_MIN -999999
double osim_naive(object_space* space, object* o1, object* o2);

//---------cluster sim metrics---------
double csim_nearest_nb(object_space* space, cluster* c1, cluster* c2, double threshold);

#endif
