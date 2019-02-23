/* The time complexity for task A is O(m^2n^2)*/
/*Explination:- The time complexity for finding the divisors and if the number is present in
divisors is O(mn^2) while the complexity to print the divisors for a elements in set Sp is 
O(nE) where E is number of edges in the graph which is lesser then the complexity of
O(mn^2) hence the complexity of task A is O(mn^2) */

/*The time complexity for task B is O(nE^n) where E is number of edges in graph*/
/*Explination:- The recursive call used to compute the sequence starts with a for loop for 
number of edges E and goes in recursive loop to find the members of monotonic path and the for loop in recursive call runs for n times 
and the recursive call takes place n times in entire for loop and other complexities have complexities O(q) where q is number of monotonic path 
generated and are smaller then O(nE^n) hence the time complexity for task B is O(nE^n).*/

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
#include "queue.h" 

#define MAXVAL 10000
#define LIMIT 2147483647

typedef struct Node { 
  int data1; 
  struct Node *next; 
}Node; 

//This function is used to add a data at end of the linked list.
void add_divisor(Node **head, int new_data){ 
    Node* node = (Node*) malloc(sizeof(Node)); 
    Node *n = *head;
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

//This function remove_Duplicate removes duplicate from a linked list.
void remove_Duplicate(struct Node *n){
  struct Node *p;
  struct Node *q;
  for(p = n; p != NULL; p = p->next){
    for(q = p->next; q!= NULL; q = q->next){
      if(q->data1 == p->data1){
        q->data1 = 0;
      }
    }
  }
}

//This functions is used to find if a number is a part of another number.
int check_number_part(int n1, int n2){
  int temp1 = n1;
  int temp2 = n2;
  int arr1[MAXVAL];
  int arr2[MAXVAL];
  int count1 = 0;
  while(temp1 != 0){ //Loop finds eache digit of number and adds it int array.
    int digit = temp1 % 10;
    temp1 = temp1 / 10;
    arr1[count1] = digit;
    count1 += 1;
  }
  int count2 = 0;
  while(temp2 != 0){ //Loop finds eache digit of number and adds it int array.
    int digit = temp2 % 10;
    temp2 = temp2 / 10;
    arr2[count2] = digit;
    count2 += 1;
  }
  int i,j;
  for (i = 0; i < count2; i++){ //if array 2 is present in array 1 then returns 1 else returns 0.
    for (j = 0; j < count1; j++){
      if(arr2[i] == arr1[j])
        break;
      }         
      if(j == count1)
        return 0;
    }
  return 1;
}

//This function is used to sort all fouund divisors in accending order.
void sort(struct Node *n){
  Node *p;
  Node *q;
  for(p = n; p != NULL; p = p->next){
    for(q = p->next; q!= NULL; q = q->next){
      if(q->data1 < p->data1){
        int temp = p->data1;
        p->data1 = q->data1;
        q->data1 = temp;
      }
    }
  }
}

int main(int argc, char *argv[]){
  if(argc < 2){                     //checks if arguments passed are 2 ie filename and number.
    return 0;
  }
	long long main_number = atoll(argv[1]);
  if (main_number > LIMIT)
    return 0;
  Node* head = NULL;
  Node* node = NULL;
  int inserted_graph = 0;
  int no_divisors = 0;
  int i;
  add_divisor(&head,main_number);
  node = head;
  for(i = 0; i < main_number; i++){       //find the divisors of number passed as argument.
    if(i > 0 && main_number % i == 0){
      add_divisor(&head,i);
    }
  }
  for(node = head; node != NULL; node = node->next)
    no_divisors += 1;
  Graph g = newGraph(no_divisors+1);      //create a graph with vertices equal to divisors of number passed as argument.
  Edge e;
  for(node = head; node != NULL; node = node->next){  
    for(i = 0; i < node->data1; i++){
      if(i > 0 && node->data1 % i == 0 && check_number_part(node->data1,i) == 1){ //find if the divisor contains the number divided.
        inserted_graph = 1;
        e.v = i;
        e.w = node->data1;
        insertEdge(g,e);
      }
    }
  }
  node = head;
  remove_Duplicate(node); //removes duplicate divisors if any.
  sort(node); //sorts divisors in assending order
  printf("Partial order:\n");
  while(node!=NULL){ 
    if(node->data1 != 0){
      printf("%d: ",node->data1);
      display_PO(g, node->data1); //prints the partial order set for specific number in linked list.
      printf("\n");
    }
    node = node->next;
  }
  printf("\nLongest monotonically increasing sequences:\n");
  if(inserted_graph == 1){ //check if there are edges in graph.
    monoIncreasingSequence(g); //passes the graph to find all monotonic increasing sequence and print largest among them.
  }
  else{
    node = head;
    while(node != NULL){ // if no edges just prints the divisors.
      if(node->data1 != 0){
        printf("%d\n",node->data1);
      }
      node = node->next;
    }
  }
  freeGraph(g); //frees the graph.
  Node* curr = head;
  while (curr != NULL) { // frees the linked list.
    struct Node* temp = curr->next;
    free(curr);
    curr = temp;
  }
  free(node);
  return 0;
}
