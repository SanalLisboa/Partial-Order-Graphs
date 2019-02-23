// Queue ADT implementation ... COMP9024 18s2

#include <stdlib.h>
#include <assert.h>
#include "queue.h"
#include<stdio.h>
typedef struct node {
   int data;
   struct node *next;
} NodeT;


typedef struct QueueRep {
   int   length;
   NodeT *head;
   NodeT *tail;
} QueueRep;

// set up empty queue
queue newQueue() {
   queue Q = malloc(sizeof(QueueRep));
   Q->length = 0;
   Q->head = NULL;
   Q->tail = NULL;
   return Q;
}

//sorts queue sorts the queue in accesnding order and also removes duplicate elements from the queue.
queue sort_queue(queue r){
   NodeT *p;
   NodeT *q;
   for (p = r->head; p != NULL; p = p->next){ //This loop sorts queue in accending order.
      for(q = p->next; q != NULL; q = q->next){
         if(p->data > q->data){
            int temp = p->data;
            p->data = q->data;
            q->data = temp;
         }
      }
   }
   NodeT *current = r->head;
   while (current->next != NULL){ //This loop removes duplicate from the queue.
      if (current->data == current->next->data){  
          NodeT *temp;            
          temp = current->next->next; 
          free(current->next); 
          current->next = temp;   
       } 
      else{ 
        current = current->next;  
      } 
    } 
   return r;
}

// remove unwanted queue
void dropQueue(queue Q) {
   NodeT *curr = Q->head;
   while (curr != NULL) {
      NodeT *temp = curr->next;
      free(curr);
      curr = temp;
   }
   free(Q);
}

int queue_length(queue Q){
   return Q->length;
}
// check whether queue is empty
int QueueIsEmpty(queue Q) {
   return (Q->length == 0);
}

// insert an int at end of queue
void QueueEnqueue(queue Q, int v) {
   NodeT *new = malloc(sizeof(NodeT));
   assert(new != NULL);
   new->data = v;
   new->next = NULL;
   if (Q->tail != NULL) {
      Q->tail->next = new;
      Q->tail = new;
   } else {
      Q->head = new;
      Q->tail = new;
   }
   Q->length++;
}

//compare_queue function compares two queues and returns 1 if queue q is greater then r or returns 2.
int compare_queue(queue q, queue r){
  NodeT *m = q->head;
  NodeT *n = r->head;
  while(m != NULL && n != NULL){//This queue compares each element of two queue at same position usefull to compare two queues.
    if (m->data > n->data){
      return 1;
    }
    if (m->data < n->data){
      return 2;
    }
    if (m->data == n->data){
      m = m->next;
      n = n->next;
    }
  }
  return 0;
}

//print_queue is modified to print queue in a way to display monotonic sequence.
void print_queue(queue q){
   NodeT *p;
   p = q->head;
   for(p = q->head; p->next!=NULL; p = p->next){
      printf("%d < ",p->data);
   }
   printf("%d",p->data);
   printf("\n");
}

// remove int from front of queue
int QueueDequeue(queue Q) {
   assert(Q->length > 0);
   NodeT *p = Q->head;
   Q->head = Q->head->next;
   if (Q->head == NULL) {
      Q->tail = NULL;
   }
   Q->length--;
   int d = p->data;
   free(p);
   return d;
}

//copy_queue returns a copy of queue passed as function argument.
queue copy_queue(queue q){
  assert(q->length > 0);
  int n;
  NodeT * temp = q->head;
  queue p = newQueue();
  while(temp != NULL){ //while loop goes through the linkedlist and enqueues linkedlist it into new queue.
    n = temp->data;
    QueueEnqueue(p, n);
    temp = temp->next;
  }
  p = sort_queue(p);
  return p;
}

//remove_last removes last element from the queue and returns the queue.
queue remove_last(queue q){
  assert(q->length > 0);
  int n;
  queue p = newQueue();
  while(!QueueIsEmpty(q)){
    n = QueueDequeue(q);
    if(!QueueIsEmpty(q)){
      QueueEnqueue(p, n);
    }
  }
  while(!QueueIsEmpty(p)){
    n = QueueDequeue(p);
    QueueEnqueue(q, n);
  }
  q = sort_queue(q);
  free(p->head);
  free(p->tail);
  free(p);
  return q;
}