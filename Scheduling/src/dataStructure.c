//
//  Algoritm.c
//  Scheduling
//
//  Created by 계용운 on 2021/07/22.
//

#include "dataStructure.h"

// FIFO - Queue //
// ************ //


/* 구현에 필요한 추가적인 함수 필요한 경우 여기에 추가 */
// Struct copy // 일단 임시로 나둠
void deepCopy(Proc *proc, Proc copy){
    proc -> create_time = copy.create_time;
    proc -> pid = copy.pid;
    proc -> priority = copy.priority;
    proc -> process_time = copy.process_time;
    proc -> required_time = copy.required_time;
}

// Queue - init //
void init_queue(queue* que){
    que -> front = NULL;
    que -> rear = NULL;
}
// ************ //

// Queue - check empty //
int check_empty(queue* que){
    if(que -> front == NULL)
        return TRUE;
    else
        return FALSE;
}
// ************ //

// Queue - Enqueue //
void Enqueue(queue* que, Proc process){
    
    Node *node = malloc(sizeof(Node));
    node -> process = malloc(sizeof(Proc));
    node -> next = NULL;

    if(node == NULL){
        PRINT_ERROR("Memory Allocation Failed!\n");
        exit(-1);
    }
    deepCopy(node->process, process);
    
    if(check_empty(que)){
        que -> front = node;
        que -> rear = que -> front;
    }
    else{
        que -> rear -> next = node;
        que -> rear = node;
    }
}
// ************ //

// Queue - Dequeue //
Proc Dequeue(queue *que){
    
    Node *delNode;
    Proc ret;
    delNode = NULL;

    if(check_empty(que)){
        PRINT_ERROR("the queue is empty!\n");
        exit(-1);
    }

    delNode = que -> front;
    deepCopy(&ret, *(delNode -> process));
    que -> front = que -> front -> next;
    free(delNode->process);
    free(delNode);

    return ret;
}


/* ******** Priority Queue *********/
//void Priority_Enqueue(queue *que, Proc process){
//    Node *node = malloc(sizeof(Node));
//    node -> process = malloc(sizeof(Proc));
//    node -> next = NULL;
//
//    if(node == NULL || node -> process == NULL){
//        PRINT_ERROR("Memory Allocation Failed\n");
//        return;
//    }
//
//    deepCopy(node -> process, process);
//
//    if(que -> front == NULL){
//        que -> front = node;
//        que -> rear = node;
//    }
//    else{
//
//        Node *trace = que -> front;
//
//        if(node -> process -> priority < trace -> process -> priority){
//
//        }
//
//
//
//
//
//    }
//
//}



/* ******** Heap *********/

int init_heap(heap *hp, Parser *parser){
    FILE *fp = open_file(parser -> trace_file_path);
    
    // file path check is completed so there is no exception check
    if(fp == NULL){
        PRINT_ERROR("file open failed\n");
        return FALSE;
    }
    unsigned long long size;
    fscanf(fp, "%lld", &size);
    hp -> process = malloc(sizeof(Proc) * size);
    hp -> index = 0;
    
    close_file(fp);
    
    return TRUE;
}

unsigned long long init_heap_for_guaranteed(heap *hp, Parser *parser){
    FILE *fp = open_file(parser -> trace_file_path);
    
    // file path check is completed so there is no exception check
    if(fp == NULL){
        PRINT_ERROR("file open failed\n");
        return FALSE;
    }
    unsigned long long size;
    fscanf(fp, "%lld", &size);
    hp -> process = malloc(sizeof(Proc) * size);
    hp -> index = 0;
    
    close_file(fp);
    
    return size;
}

void push(heap *hp, Proc process){
    
    Index curIndex = hp -> index;
    Index parent = getParent(curIndex);
    
    *((hp->process) + curIndex) = process;
    while(curIndex > 0 && ((hp->process) + curIndex) -> required_time < ((hp -> process) + parent) -> required_time){
        swap(hp, curIndex, parent);
        curIndex = parent;
        parent = getParent(parent);
    }
    hp -> index++;
}

void push_for_guaranteed(heap *hp, Proc process, unsigned long long heap_size){
    Index curIndex = hp -> index;
    Index parent = getParent(curIndex);
    
    heap *new_hp = malloc(sizeof(heap));
    new_hp -> process = malloc(sizeof(heap_size));
    new_hp -> index = 0;
    
    while(hp->index >= 0){
        Proc refresh_node;
        refresh_node = pop(hp);
        double ratio = (double)(refresh_node.process_time) / (get_current_time() - refresh_node.create_time);
    }
    
    
    
    *((hp->process) + curIndex) = process;
    while(curIndex > 0 && ((hp->process) + curIndex) -> required_time < ((hp -> process) + parent) -> required_time){
        swap(hp, curIndex, parent);
        curIndex = parent;
        parent = getParent(parent);
    }
    hp -> index++;
}

Proc pop(heap *hp){
    Proc ret = *(hp -> process);
    
    hp -> index --;
    swap(hp, 0, hp->index);
    Index leftChild = getLeftChild((Index)0);
    Index rightChild = getRightChild((Index)0);
    Index parent = 0;
    while(TRUE){
        
        Index swapIndex = 0;
        if(leftChild >= hp -> index){
            break;
        }
        if(rightChild >= hp -> index){
            swapIndex = leftChild;
        }
        else{
            if(((hp -> process) + leftChild) -> required_time > ((hp -> process) + rightChild) -> required_time)
                swapIndex = rightChild;
            else
                swapIndex= leftChild;
        }
        
        if(((hp -> process) + swapIndex) -> required_time < ((hp -> process) + parent) -> required_time){
            swap(hp, parent, swapIndex);
            parent = swapIndex;
        }
        else
            break;
        
        leftChild = getLeftChild(parent);
        rightChild = getRightChild(parent);
    }
    
    return ret;
}


Index getParent(Index curIndex){
    return (curIndex-1) / 2;
}

Index getLeftChild(Index curIndex){
    return (curIndex * 2) + 1;
}

Index getRightChild(Index curIndex){
    return (curIndex * 2) + 2;
}

void swap(heap *hp, Index index1, Index index2){
    Proc tmp = *((hp -> process) + index1);
    *((hp -> process) + index1)  = *((hp -> process) + index2);
    *((hp -> process) + index2) = tmp;
}

