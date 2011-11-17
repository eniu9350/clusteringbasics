main:
	rm -f clustering
	gcc -g cluster.c hierarchical.c similarity.c main.c -o clustering
