// Graph ADT
// Adjacency Matrix Representation ... COMP9024 18s2
#include "Graph.h"
#include "queue.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define MAXVAL 10000
#define ENOUGH 1000000  // maximum number of edges

typedef struct GraphRep {
   Edge *edges; // array of edges
   int   nV;    // #vertices (numbered 0..nV-1)
   int   nE;    // #edges
   int   n;     // size of edge array
} GraphRep;

Graph newGraph(int V) {
   assert(V >= 0);

   Graph g = malloc(sizeof(GraphRep));
   assert(g != NULL);

   g->nV = V;
   g->nE = 0;

   // allocate enough memory for edges
   g->n = ENOUGH;
   g->edges = malloc(g->n * sizeof(Edge));
   assert(g->edges != NULL);

   return g;
}

int numOfVertices(Graph g) {
   return g->nV;
}

// check if two edges are equal
bool eq(Edge e1, Edge e2) {
   return ( (e1.v == e2.v && e1.w == e2.w)
      || (e1.v == e2.w && e1.w == e2.v) );
}

void insertEdge(Graph g, Edge e) {
   // ensure that g exists and array of edges isn't full
   assert(g != NULL && g->nE < g->n);

   int i = 0;
   while (i < g->nE && !eq(e, g->edges[i]))
      i++;
   if (i == g->nE)                     // edge e not found
      g->edges[g->nE++] = e;
}

void removeEdge(Graph g, Edge e) {
   assert(g != NULL);                 // ensure that g exists

   int i = 0;
   while (i < g->nE && !eq(e, g->edges[i]))
      i++;
   if (i < g->nE)                      // edge e found
      g->edges[i] = g->edges[--g->nE];
}

bool adjacent(Graph g, Vertex x, Vertex y) {
   assert(g != NULL);

   Edge e;
   e.v = x; e.w = y;

   int i = 0;
   while (i < g->nE) {
      if (eq(e, g->edges[i]))
   return true;
      i++;
   }
   return false;
}

void showGraph(Graph g) {
    assert(g != NULL);

    printf("Number of vertices: %d\n", g->nV);
    printf("Number of edges: %d\n", g->nE);
    int i;
    for (i = 0; i < g->nE; i++)
       printf("Edge %d - %d\n", g->edges[i].v, g->edges[i].w);
}

void freeGraph(Graph g) {
   assert(g != NULL);

   free(g->edges);
   free(g);
}

typedef struct Node1{ 
  queue data1; 
  struct Node1 *next; 
}Node1; 

//This function is used to add a queue at end of the linked list.
void add_queue(Node1 **head, queue new_data){ 
    Node1 *node = (Node1*) malloc(sizeof(Node1)); 
    Node1 *n = *head;
    node->data1  = new_data;
    node->next = NULL; 
    if (*head == NULL) { //if head is not having any data add data into head.
       *head = node; 
       return; 
    }   
    while (n->next != NULL) //find the end of linkedlist and add data there.
        n = n->next; 
    n->next = node; 
    return;     
} 

//This is a recursive sequence that finds all the monotonic sequences recursively.
int find_sequence(Graph g, int n, queue q, Node1** head){
  int o = 0;
  for (int i = 0; i < g->nE; i++){
    if(g->edges[i].v == n){
      if (!QueueIsEmpty(q)){
        QueueEnqueue(q, g->edges[i].w); //The found vertex hving edge from n is found and added in queue.
        queue r = copy_queue(q);
        add_queue(head, r); //the sequence found so far is add in linkedlist which stores queue.
        q = remove_last(q); //the last added elemnt is removed to find other vertex with edges from n.
        o = 1;
        find_sequence(g, g->edges[i].w, r, head); //recursive call to find the next vertex to newly found vertex to add in queue.
      }
    }
  }
  return o;
}

//Computes all the monotonic sequences and displays all the longest monotonic sequences.
void monoIncreasingSequence(Graph g){
  Node1* head = NULL;
  int i,o;
  for (i = 0; i < g->nE; i++){
        queue q = newQueue();
        QueueEnqueue(q, g->edges[i].v);
        QueueEnqueue(q, g->edges[i].w);
        o = find_sequence(g, g->edges[i].w, q, &head); //recursive call to find the sequence and stores it into queue.
        if (o == 0)
          add_queue(&head, q); // in no sequence are found in recursive call just add the queue with two elements.
        else
          dropQueue(q);
  }
  Node1* node;
  node = head;
  queue largest;
  largest = node->data1;
  node = node->next;
  int count = 0;
  while(node != NULL){ //This loop is used to find largest size of queue.
    if(queue_length(node->data1)>queue_length(largest))
      largest = node->data1;
    count += 1;
    node = node->next;
  }
  Node1* head1 = NULL;
  node = head;
  while(node != NULL){//This loop is used to find all queues of largest size.
    if(queue_length(node->data1)==queue_length(largest))
      add_queue(&head1, node->data1);
    node = node->next;
  }
  Node1* m;
  Node1* n;
  for(n = head1; n != NULL; n = n->next){//This function is used to sort the queues of largest size found.
    for(m = n->next; m != NULL; m = m->next){
      if (compare_queue(n->data1,m->data1)==1){
        queue temp = n->data1;
        n->data1 = m->data1;
        m->data1 = temp;
      }
    }
  }
  node = head1;
  while(node != NULL){ //prints sorted queues of largest size.
    print_queue(node->data1);
    node = node->next;
  }
  node = head;
  while(node != NULL){ //This loop drops each queue created.
    dropQueue(node->data1);
    node = node->next;
  }
  Node1* curr = head;
  while (curr != NULL) { //this frees every assigned pointer.
    Node1* temp = curr->next;
    free(curr);
    curr = temp;
  }
  curr = head1;
  while (curr != NULL) { //this frees every assigned pointer.
    struct Node1* temp = curr->next;
    free(curr);
    curr = temp;
  }
  free(node);
}



//This function used to display the POSET for a specific value i and also sorts the fount set of numbers.
int display_PO(Graph g,int i){
  int n, m;
  int a[MAXVAL];
  int count = 0;
  for (n = 0; n < g->nE; n++){ //Loop finds all vertex having edge from i and stores them in array.
    if (g->edges[n].v == i){
     a[count] = g->edges[n].w;
     count += 1;
    }
  }
  for(n = 0; n < count; n++){ //The array is sorted in this two loops.
    for(m = n+1; m < count; m++){
      if(a[n] > a[m]){
        int temp = a[n];
        a[n] = a[m];
        a[m] = temp;
      }
    }
  }
  for (n = 0; n < count; n++){ //The sorted array is printed.
    printf("%d ",a[n]);
  }
  return 0;
}
