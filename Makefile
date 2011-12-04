main:
	rm -f clustering
	gcc -g -lm cluster.c hierarchical.c similarity.c main.c -o clustering

lib:
	gcc -I../../adt -c -fPIC cluster.c hierarchical.c similarity.c
	gcc -shared -o libclustering.so.1 cluster.o hierarchical.o similarity.o
installlib:
	sudo cp libclustering.so.1 /opt/lib
	sudo ln -sf /opt/lib/libclustering.so.1 /opt/lib/libclustering.so
