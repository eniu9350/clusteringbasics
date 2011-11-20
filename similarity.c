#include "similarity.h"

#include <math.h>

sim_matrix* create_sim_matrix(int dimension, sim_calc_fun calc_fun)
{
	sim_matrix* s;
	int i,j;
	if(dimension>NUM_MAX_CLUSTER_SIZE)	{
		printf("dimension exceed dim limit!\n");
		return 0;
	}
	else	{
		s = (sim_matrix*)malloc(sizeof(sim_matrix));
		s->dimension = dimension;
		s->calc_fun = calc_fun;
		for(i=0;i<s->dimension;i++)	{
			for(j=0;j<s->dimension;j++)	{
				s->matrix[i][j] = -1;
			}
		}

		return s;
	}
}

int calc_object_sim_matrix(sim_matrix* s, cluster* c)
{
	int i,j;
	for(i=0;i<c->size;i++)	{
		for(j=0;j<c->size;j++)	{
			if(j==i)	{
				s->matrix[c->objids[i]][c->objids[i]] = 1;
			}
			else	{
				s->matrix[c->objids[i]][c->objids[j]] = (*((object_sim_calc_fun)s->calc_fun))(c->all_objs, c->objids+i, c->all_objs, c->objids+j);
			}
		}
	}
}

//implement in hi.c yet
int calc_cluster_sim_matrix(sim_matrix* s, cluster_list* cl)
{
	int i,j;
	/*
	for(i=0;i<cl->size;i++)	{
		for(j=0;j<cl->size;j++)	{
			if(j==i)	{
				s->matrix[c->objids[i]][c->objids[i]] = 1;
			}
			else	{
				s->matrix[c->objids[i]][c->objids[j]] = (*(()s->calc_fun))(c->objids+i, c->objids+j);
			}
		}
	}
	*/
	return 0;
}


/* ----- similarity calc fun (cluster)----------------- */

//sim = 0 - distance of nearest neighbour
//threshold: 0 for none, other: if sim less than it, return threshold
double csim_nearest_nb(cluster* c1, cluster* c2, double threshold)
{
	int i,j;
	double min;
	double osim;
	if(c1->size==0 || c2->size==0)	{
		printf("csim_nearest_nb: c1 or c2 size == 0\n");
		return 0;
	}

	if(threshold==0)	{
		threshold = OBJECT_SIMILARITY_MIN;
	}

	min = osim_naive(c1->all_objs, 0, c2->all_objs, 0);
	for(i=0;i<c1->size;i++)	{
		for(j=0;j<c2->size;j++)	{
			osim = osim_naive(c1->all_objs, i, c2->all_objs, j);
			if(osim<min)	{
				min = osim;
				if(min<threshold)	{
					return threshold;
				}
			}
		}
	}

	return min;
}

/* ----- similarity calc fun (object) ----------------- */

double osim_naive(object_list* ol1, int objid1, object_list* ol2, int objid2)
{
	return 0 - odis_euclidean(ol1, objid1, ol2, objid2);
}

/* ----- object distance calc fun ----------------- */
double odis_euclidean(object_list* ol1, int objid1, object_list* ol2, int objid2)
{
	if(ol1->dim != ol2->dim)	{
		printf("odis_euclidean error: dim not matched!\n");
		return -1;
	}
	object* o1 = ol1->list+objid1;	
	object* o2 = ol2->list+objid2;	


	double sum = 0.0;
	double result;
	int i;
	for(i=0;i<ol1->dim;i++)	{
		sum += (o1->atts[i]-o2->atts[i])*(o1->atts[i]-o2->atts[i]);
	}

	return sqrt(sum);
}
