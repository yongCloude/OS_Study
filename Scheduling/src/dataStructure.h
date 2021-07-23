//
//  Algoritm.h
//  Scheduling
//
//  Created by 계용운 on 2021/07/22.
//

#ifndef dataStructure_h
#define dataStructure_h

#include<stdio.h>
#include "process.h"
#include "parser.h"
#include "util.h"

typedef long long Index;
typedef unsigned long long TIME;

typedef struct myQueue{
    struct _node *front;
    struct _node *rear;
}queue;

typedef struct myHeap{
    Proc *process;
    unsigned long long index;
}heap;

typedef struct _node{
    Proc *process;
    struct _node *next;
}Node;




#endif /* Algoritm_h */


void deepCopy(Proc *proc, Proc copy);

// Queue //
void init_queue(queue* que);
int check_empty(queue* que);
void Enqueue(queue* que, Proc process);
Proc Dequeue(queue *que);
// **** //

// Priority Queue //
//void Priority_Enqueue(queue * que, Proc process);
//void swap_node(Node* swap1, Node *swap2);


// Heap //
int init_heap(heap *hp, Parser *parser);
void push(heap *hp, Proc process);
Proc pop(heap *hp);

Index getParent(Index curIndex);
Index getRightChild(Index curIndex);
Index getLeftChild(Index curIndex);
void swap(heap *hp, Index index1, Index index2);
// **** //

