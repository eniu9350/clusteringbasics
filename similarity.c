#include "similarity.h"

sim_matrix* create_sim_matrix(int dimension)
{
	sim_matrix* s;
	if(dimension>NUM_MAX_CLUSTER_SIZE)	{
		printf("dimension exceed dim limit!\n");
		return 0;
	}
	else	{
		s = (sim_matrix*)malloc(sizeof(sim_matrix));
		s->dimension = dimension;
		return s;
	}
}

int calc_sim_matrix(sim_matrix* s, cluster* c)
{
}
