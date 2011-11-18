#include "similarity.h"

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
				s->matrix[c->objids[i]][c->objids[j]] = (*((object_sim_calc_fun)s->calc_fun))(c->objids+i, c->objids+j);
			}
		}
	}
}
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
