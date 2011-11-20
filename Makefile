main:
	rm -f clustering
	gcc -g -lm cluster.c hierarchical.c similarity.c main.c -o clustering
