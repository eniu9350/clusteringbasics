#include "hierarchical.h"

int hier_clustering(cluster_list* clist, object_list* objs, sim_calc_fun simfun)
{
	int i,j,k;
	int n;	//current cluster list size
	cluster_list_list* result = create_cluster_list_list(); 
	cluster_list* c;	//current cluster list
	n = nobj;
	for(i=0;i<nobj-1;i++)	{
	//1. calc similarity
		sim_matrix* simm = create_sim_matrix(n, simfun);
		for(j=0;j<n;j++)	{
			for(k=0;k<j;k++)	{
				simm->matrix
				
		
		
		
		
		
	
	

	
		

	

	//2. select and join
}
