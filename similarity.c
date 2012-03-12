#include "similarity.h"

#include <math.h>
#include <unistd.h>
int* pint;
sim_matrix* create_sim_matrix(int size)
{
	sim_matrix* s;
	int i,j;
	//printf("csm size=%d\n", size);
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
		//printf("csm step 2\n");

		return s;
	}
}

int destroy_sim_matrix(sim_matrix* simm)
{
	free(simm);
}
//---------object sim MATRIX calc-----------------
/*
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
 */

//---------cluster sim MATRIX calc-----------------
/*
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
 */

//---------find most similar clusters--------------

int find_most_sim_cluster(object_space* space, cluster_list* cl, cluster_sim_calc_fun calc_fun, int* cid1, int* cid2)
{
	double maxsim;
	//double sim;
	int i,j;
	int imax, jmax;
	complex_result sim;

//	printf("imaxaddr=%d\n", &imax);
//	printf("sim=%d\n", &sim);

	maxsim = -999999;
	imax = 0;
	jmax = 1;

//	printf("imaxaddr=%d\n", &imax);
	for(i=1;i<cl->size;i++)	{
		for(j=0;j<i;j++)	{
			//printf("fmsc.1 i/j=%d/%d\n", i, j);
			pint = &i;
			if(i==1&&j==0)	{	//first time
				(*calc_fun)(space, cl->list[i], cl->list[j], 0, &sim);
				//printf("firsttime\n");
			}
			else	{
				(*calc_fun)(space, cl->list[i], cl->list[j], &maxsim, &sim);
			}
#if 1
			//if(i%10==1)	{
				//sleep(10);
			//}
#endif
			//printf("fmsc.2, i=%d,j=%d\n", i, j);
			if(sim.flag)	{	//flag ==1 or 2
				printf("fmsc, %d/%d, sim=%f (dim=%d), maxsim=%f(%d,%d)\n", i, cl->size, sim.value, space->dim, maxsim, imax, jmax);
				//printf("new nearest cluster neighbour\n");
				maxsim = sim.value;
				imax = i;
				jmax = j;
				if(sim.flag == 2)	{
					printf("fmsc, flag22222222222222\n");
					break;
				}
			}
			//printf("fmsc.2 i/j=%d/%d\n\n", i, j);
		}
#if 1
		//if(i%1000==1)	{
		//		printf("fmsc, %d/%d, maxsim=%f\n", i, cl->size, maxsim);
		//}
#endif
		if(sim.flag == 2)	{
			break;
		}
	}

	*cid1 = imax;
	*cid2 = jmax;

	return 0;
}


//---------cluster sim metrics---------

//sim = 0 - distance of nearest neighbour
//threshold: 0 for none, other: if sim less than it, return threshold
void csim_nearest_nb(object_space* space, cluster* c1, cluster* c2, double* threshold, complex_result* sim)
{

	int i,j;
	double max;
	int flag = 0; //1 for threshold broken
	//printf("csim start\n");
	//printf("cnn0, pint=%d\n", *pint);
	//printf("sim addr=%ld\n", sim);
	//sim->value = -0.1;
	//printf("cnna, pint=%d\n", *pint);
	if(c1->size==0 || c2->size==0)	{
		return;
	}

	if(threshold==0 || *threshold==0)	{
		max = OBJECT_SIMILARITY_MIN;
	}
	else	{
		max = *threshold;
	}

	complex_result osim;
	//osim_naive(space, c1->list[0], c2->list[0], &max, &osim);
	//printf("osimflag = %d\n", osim.flag);
	//printf("csim, c1size=%d,c2size=%d\n", c1->size, c2->size);
	for(i=0;i<c1->size;i++)	{
		for(j=0;j<c2->size;j++)	{
			osim_naive(space, c1->list[i], c2->list[j], &max, &osim);
			//printf("csim.osim.flag=%d\n",osim.flag);
			if(osim.flag)	{
				flag = osim.flag;
				max = osim.value;
				if(osim.flag == 2)	{
					break;
				}
				//printf("cnn, maxosim=%d\n", osim.value);
			}
		}
		if(osim.flag==2)	{
			break;
		}
	}
	//printf("csim 1\n");

	//mmm: vip!!!
	if(flag)	{
		sim->flag = osim.flag;
		sim->value = max;
	}
	else	{
		sim->flag = 0;
	}
	//printf("csim,flag=%d\n", sim->flag);
	//printf("csim end\n");

}


//---------object sim metrics---------
//sim flag --- 0. sim<threshold; 1/2: sim>threshold,so sim value is valid
void osim_naive(object_space* space, object* o1, object* o2, double* threshold, complex_result* sim)
{
	complex_result dis;
	double t;
	//printf("osim start\n");
	if(threshold)	{
		//printf("th=%f\n", *threshold);
		t = 0-(*threshold);
		odis_euclidean(space, o1, o2, &t, &dis);
		//printf("osim, flag=%d\n", dis.flag);
		if(!dis.flag)	{	//dis>threshold
			sim->flag = 0;
			//printf("osim end(1)\n");
			return;
		}
		else	{	//dis<threshold (may > or < mindistance
			sim->flag = dis.flag;
			sim->value = 0-dis.value;
			//printf("osim end(2)\n");
			return;
		}
	}
	else	{
		odis_euclidean(space, o1, o2, 0, &dis);
		sim->flag = dis.flag;
		sim->value = 0-dis.value;
		//printf("osim end(3)\n");
		return;
	}
}

//---------object distance metrics---------
//dis flag --- 
//if threshold!=0: 0.dis>threshold; 1.MIN_DISTANCE<dis<threshold; 2.dis<MIN_DISTANCE
//if threshold==0: always 1! right?
void odis_euclidean(object_space* space, object* o1, object* o2, double* threshold, complex_result* dis)
{
	double sum = 0.0;
	double result;
	int i;
	double v1, v2;
	object_att *att1, *att2;
	double tmp;


	//printf("odis, th=%f\n", *threshold);
	if(threshold==0)	{
		for(i=0;i<space->dim;i++)	{
			att1 = obj_get_att(o1, i+1);	//i+1 equals tid
			att2 = obj_get_att(o2, i+1);	//i+1 equals tid

			v1 = att1!=0?att1->v:0.0;
			v2 = att2!=0?att2->v:0.0;

			sum += (v1-v2)*(v1-v2);
		}
		dis->flag = 1;
		dis->value = sqrt(sum);
		return;
	}
	else	{
		for(i=0;i<space->dim;i++)	{
			att1 = obj_get_att(o1, i+1);	//i+1 equals tid
			att2 = obj_get_att(o2, i+1);	//i+1 equals tid

			v1 = att1!=0?att1->v:0.0;
			v2 = att2!=0?att2->v:0.0;

			tmp = (v1-v2)*(v1-v2);
			//printf("tmp=%f, thresh=%f\n", tmp, *threshold);
			if(tmp>(*threshold)*(*threshold))	{
				dis->flag = 0;
				return;
			}
			else	{
				sum += tmp;
				if(sum>(*threshold)*(*threshold))	{
					dis->flag = 0;
					return;
				}
			}
		}
		dis->value = sqrt(sum);
		printf("disvalue=%f\n", dis->value);
		if((dis->value)*(dis->value) < 0-OBJECT_SIMILARITY_MAX)	{
			printf("flag22222222222\n");
			dis->flag = 2;
		}
		else	{
			dis->flag = 1;
		}
	}
}
