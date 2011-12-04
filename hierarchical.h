#ifndef _CLUSTERINGBASICS_HIERARCHICAL_
#define _CLUSTERINGBASICS_HIERARCHICAL_

#include "common.h"

#include "cluster.h"
#include "object.h"
#include "similarity.h"

cluster_list_list* hier_clustering(object_space* space, cluster_sim_calc_fun simfun);
#endif
