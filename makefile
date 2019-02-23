poG: poG.o Graph.o queue.o 
	gcc -o poG poG.o Graph.o queue.o
poG.o: poG.c Graph.o queue.o 
	gcc -Wall -Werror -std=c11 -c poG.c
Graph.o: Graph.c Graph.h queue.o 
	gcc -Wall -Werror -std=c11 -c Graph.c
queue.o: queue.c queue.h 
	gcc -Wall -Werror -std=c11 -c queue.c