#include "hierarchical.h"

cluster_list_list* hier_clustering(object_space* space, cluster_sim_calc_fun simfun)
{
	int i,j,k;
	//int n;	//current cluster list size
	cluster_list_list* result = create_cluster_list_list(); 
	cluster_list* cl;	//current cluster list
	cluster_list* cltosave;
	cluster* c;	//temp
	int rowmax;
	int colmax;
	double smax;
	sim_matrix* simm;
	//init new !!!
	//	n = nobj;

	cl = create_cluster_list();
	for(i=0;i<space->all->size;i++)	{
		c = create_cluster();
//		add_object(c, objs->list[i].id);
		add_object(c, space->all->list[i]);
		add_cluster(cl, c);
	}

//	for(i=0;i<space->all->size;i++)	{
	while(1)	{
		if(cl->size==1)	{
			break;
		}
		//1. calc similarity
	//	sim_matrix* simm = create_sim_matrix(cl->size, simfun);
	/*
		for(j=1;j<cl->size;j++)	{
			for(k=0;k<j;k++)	{
				simm->matrix[k][j] = (*((cluster_sim_calc_fun)simm->calc_fun))(space, cl->list[k], cl->list[j], 0);
			}
		}
		for(j=1;j<cl->size;j++)	{	//the matrix is symmetric
			for(k=0;k<j;k++)	{
				simm->matrix[j][k] = simm->matrix[k][j];
			}
		}
		*/
		simm = calc_cluster_sim_matrix(space, cl, simfun);

		//2. select and merge
		rowmax = 0;
		colmax = 1;
		smax = simm->matrix[rowmax][colmax];
		for(j=1;j<cl->size;j++)	{
			for(k=0;k<j;k++)	{
				if(simm->matrix[j][k]>smax)	{
					rowmax = j;
					colmax = k;
					smax = simm->matrix[j][k];
				}
			}
		}

		destroy_sim_matrix(simm);

		merge_cluster(cl->list[j], cl->list[k]);

		remove_cluster(cl, k);

		//save current cluster to result
		cltosave = clone_cluster_list(cl);
		add_cluster_list(result, cltosave);
	}

	return result;
}
