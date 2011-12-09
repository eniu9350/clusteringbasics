#include "similarity.h"

#include <math.h>
#include <unistd.h>

sim_matrix* create_sim_matrix(int size)
{
	sim_matrix* s;
	int i,j;
	printf("csm size=%d\n", size);
	if(size>NUM_MAX_CLUSTER_SIZE)	{
		printf("create_sim_matrix error, size exceed limit!\n");
		return 0;
	}
	else	{
		s = (sim_matrix*)malloc(sizeof(sim_matrix));
		printf("csm step 1, sim_matrix size=%d\n", sizeof(sim_matrix));
		s->size = size;
		for(i=0;i<size;i++)	{
			for(j=0;j<size;j++)	{
				s->matrix[i][j] = -1;
			}
		}
		printf("csm step 2\n");

		return s;
	}
}

int destroy_sim_matrix(sim_matrix* simm)
{
	free(simm);
}
//---------object sim MATRIX calc-----------------
sim_matrix* calc_obj_sim_matrix(object_space* space, cluster*c, object_sim_calc_fun calc_fun)
{
	int i,j;
	sim_matrix* simm = create_sim_matrix(c->size);
	for(i=0;i<c->size;i++)	{
		for(j=0;j<c->size;j++)	{
			if(j==i)	{
				simm->matrix[c->list[i]->id][c->list[i]->id] = 1;	//mmm: ok?
			}
			else	{
				simm->matrix[c->list[i]->id][c->list[i]->id] = (*calc_fun)(space, c->list[i], c->list[j]);
			}
		}
	}

	return simm;
}

//---------cluster sim MATRIX calc-----------------
sim_matrix* calc_cluster_sim_matrix(object_space* space, cluster_list* cl, cluster_sim_calc_fun calc_fun)
//int calc_cluster_sim_matrix(sim_matrix* s, cluster_list* cl)
{
	int j,k;
	sim_matrix* simm;
	//printf("ccsm step 0\n");
	simm = create_sim_matrix(cl->size);
	//printf("ccsm step 1\n");
	for(j=1;j<cl->size;j++)	{
		for(k=0;k<j;k++)	{
			simm->matrix[k][j] = (*((cluster_sim_calc_fun)calc_fun))(space, cl->list[k], cl->list[j], 0);
		}
		simm->matrix[j][j] = 1;	//mmm: right?
	}
	//printf("ccsm step 2\n");
	for(j=1;j<cl->size;j++)	{	//the matrix is symmetric
		for(k=0;k<j;k++)	{
			simm->matrix[j][k] = simm->matrix[k][j];
		}
	}
	//printf("ccsm step 3\n");

	return 0;
}

//---------find most similar clusters--------------
int find_most_sim_cluster(object_space* space, cluster_list* cl, cluster_sim_calc_fun calc_fun, int* cid1, int* cid2)
{
	double maxsim;
	double sim;
	int i,j;
	int imax, jmax;

	maxsim = -999999;
	imax = 0;
	jmax = 1;

	for(i=0;i<cl->size;i++)	{
		for(j=0;j<i;j++)	{
			sim =  (*calc_fun)(space, cl->list[i], cl->list[j], 0);
#if 1
		if(i%10==1)	{
			printf("fmsc, %d/%d, sim=%f (dim=%d), maxsim=%f(%d,%d)\n", i, cl->size, sim, space->dim, maxsim, imax, jmax);
		}
#endif
			if(sim>maxsim)	{
				maxsim = sim;
				imax = i;
				jmax = j;
			}
		}
#if 1
		//if(i%1000==1)	{
	//		printf("fmsc, %d/%d, maxsim=%f\n", i, cl->size, maxsim);
		//}
#endif
	}

	*cid1 = imax;
	*cid2 = jmax;

	return 0;
}

//---------cluster sim metrics---------

//sim = 0 - distance of nearest neighbour
//threshold: 0 for none, other: if sim less than it, return threshold
double csim_nearest_nb(object_space* space, cluster* c1, cluster* c2, double threshold)
{
	int i,j;
	double max;
	double osim;
	//printf("cnn, threshold=%f\n", threshold);
	if(c1->size==0 || c2->size==0)	{
		//printf("csim_nearest_nb: c1 or c2 size == 0\n");
		return 0;
	}

	if(threshold==0)	{
		threshold = OBJECT_SIMILARITY_MIN;
	}

	max = osim_naive(space, c1->list[0], c2->list[0]);
	//printf("c1size=%d, c2size=%d\n",c1->size,c2->size);
	for(i=0;i<c1->size;i++)	{
		for(j=0;j<c2->size;j++)	{
			//printf("c1o attn = %d, c2o attn = %d\n", c1->list[i]->atts->size, c2->list[i]->atts->size);
			osim = osim_naive(space, c1->list[i], c2->list[j]);
			//printf("cnn, osim=%f\n", osim);
			if(osim>max)	{
				max = osim;
				/*
				if(min<threshold)	{
					return threshold;
				}
				*/
			}
		}
	}

	return max;
}


//---------object sim metrics---------
double osim_naive(object_space* space, object* o1, object* o2)
{
	return 0 - odis_euclidean(space, o1, o2);
}

//---------object distance metrics---------
double odis_euclidean(object_space* space, object* o1, object* o2)
{
	double sum = 0.0;
	double result;
	int i;
	double v1, v2;
	object_att *att1, *att2;


	for(i=0;i<space->dim;i++)	{
		att1 = obj_get_att(o1, i+1);	//i+1 equals tid
		att2 = obj_get_att(o2, i+1);	//i+1 equals tid

		v1 = att1!=0?att1->v:0.0;
		v2 = att2!=0?att2->v:0.0;
		
		sum += (v1-v2)*(v1-v2);
				
	}

	return sqrt(sum);
}
