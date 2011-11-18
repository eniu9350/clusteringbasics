#ifndef _CLUSTERINGBASICS_HIERARCHICAL_
#define _CLUSTERINGBASICS_HIERARCHICAL_

#include "common.h"

#include "cluster.h"
#include "object.h"
#include "similarity.h"

int hier_clustering(cluster_list* clist, object_list* objs, cluster_sim_calc_fun simfun);

#endif
