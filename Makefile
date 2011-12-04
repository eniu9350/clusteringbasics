main:
	rm -f clustering
	gcc -g -lm cluster.c hierarchical.c similarity.c main.c -o clustering

lib:
	gcc -lm -I../../adt -c -fPIC object.c cluster.c hierarchical.c similarity.c
	gcc -lm -shared -o libclustering.so.1 object.o cluster.o hierarchical.o similarity.o
installlib:
	sudo cp libclustering.so.1 /opt/lib
	sudo ln -sf /opt/lib/libclustering.so.1 /opt/lib/libclustering.so
