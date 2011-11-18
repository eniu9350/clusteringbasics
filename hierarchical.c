#include "hierarchical.h"

int hier_clustering(cluster_list* clist, object_list* objs, cluster_sim_calc_fun simfun)
{
	int i,j,k;
	//int n;	//current cluster list size
	cluster_list_list* result = create_cluster_list_list(); 
	cluster_list* cl;	//current cluster list
	//init new 
	n = nobj;
	for(i=0;i<nobj-1;i++)	{
		//1. calc similarity
		sim_matrix* simm = create_sim_matrix(cl->size, simfun);
		for(j=1;j<cl->size;j++)	{
			for(k=0;k<j;k++)	{
				simm->matrix[k][j] = (*((cluster_sim_calc_fun)simm->calc_fun))(cl->plist[k], cl->plist[j]);
			}
		}
		for(j=1;j<cl->size;j++)	{	//the matrix is symmetric
			for(k=0;k<j;k++)	{
				simm->matrix[j][k] = simm->matrix[k][j];
			}
		}

		//2. choose most similar and merge
		
		

			
			














					//2. select and join
			}
