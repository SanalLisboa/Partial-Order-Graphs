// Queue ADT header file ... COMP9024 18s2

typedef struct QueueRep *queue;

queue newQueue();               // set up empty queue
void print_queue(queue);
int queue_length(queue Q);
queue sort_queue(queue q);
int compare_queue(queue q, queue r);
queue remove_last(queue q);
queue copy_queue(queue q);
void  dropQueue(queue);         // remove unwanted queue
int   QueueIsEmpty(queue);      // check whether queue is empty
void  QueueEnqueue(queue, int); // insert an int at end of queue
int   QueueDequeue(queue);      // remove int from front of queue