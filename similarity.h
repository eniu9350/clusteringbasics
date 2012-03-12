#ifndef _CLUSTERINGBASICS_SIMILARITY_
#define _CLUSTERINGBASICS_SIMILARITY_

#include "common.h"

#include "object.h"
#include "cluster.h"

typedef struct _complex_result {
	unsigned char flag;	//true if better sim value obtained,false if no better and the value will not return
	double value;
}complex_result;

//typedef void* sim_calc_fun;
typedef (*object_sim_calc_fun)(object_space* space, object* o1, object* o2, double* threshold, complex_result* sim);
typedef (*cluster_sim_calc_fun)(object_space* space, cluster* c1, cluster* c2, double* threshold, complex_result* sim);
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

//mmm: should not use it as it is too big to hold!
typedef struct __sim_matrix	{
	double matrix[NUM_MAX_CLUSTER_SIZE][NUM_MAX_CLUSTER_SIZE];
	int size;
}sim_matrix;
sim_matrix* create_sim_matrix(int size);
int destroy_sim_matrix(sim_matrix* simm);

//---------object sim MATRIX calc-----------------
//sim_matrix* calc_obj_sim_matrix(object_space* space, cluster* c, object_sim_calc_fun calc_fun);
//---------cluster sim MATRIX calc-----------------
//sim_matrix* calc_cluster_sim_matrix(object_space* space, cluster_list* cl, cluster_sim_calc_fun calc_fun);

//---------find most similar clusters--------------
int find_most_sim_cluster(object_space* space, cluster_list* cl, cluster_sim_calc_fun calc_fun, int* cid1, int* cid2);


//---------object distance metrics---------
void odis_euclidean(object_space* space, object* o1, object* o2, double* threshold, complex_result* dis);

//---------object sim metrics---------
#define OBJECT_SIMILARITY_MIN -999999
#define OBJECT_SIMILARITY_MAX -0.0000001
void osim_naive(object_space* space, object* o1, object* o2, double* threshold, complex_result* sim);

//---------cluster sim metrics---------
void csim_nearest_nb(object_space* space, cluster* c1, cluster* c2, double* threshold, complex_result* sim);

#endif
